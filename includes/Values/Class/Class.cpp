//
// Created by Preeti Thorat on 2/3/22.
//

#include "Class.h"
#include "UsableClass.h"

#include <utility>


template<>
Class<int>::Class(Token<string> * classNameTok, string fName, string fTxt, vector<Token<string> *> constructorArgs,
                  map<string, BaseValue *> defaultArgs,
                  vector<Node *> members, Node * superClass, vector<string> lines) : Value<int>(-1, T_CLASS, fName,
                                                                             fTxt) {
    this->members = members;
    this->classNameTok = classNameTok;
    this->name = classNameTok->getValueObject()->getValue();
    this->constructorArgs = constructorArgs;
    this->defaultArgs = defaultArgs;
    this->lines = lines;
    this->superClass = superClass;
    parent = nullptr;
    this->fName = fName;
    this->fTxt = fTxt;
}

template<>
BaseValue * Class<int>::getFromSymbolTable(string name) {
    return instantiatedVariables->get(name);
}

template<>
void Class<int>::setParentClass(Class<int> *parent) {
    this->parent = parent;
}

template<>
BaseValue *Class<int>::copy() {
    auto *copy = new Class<int>(classNameTok, fName, fTxt, constructorArgs, defaultArgs, members, superClass, lines);
    copy->setPos(posStart, posEnd, line);
    copy->setContext(ctx);
    return copy;
}

template<>
void Class<int>::populateArgs(vector<BaseValue *> args, vector<string> argNames,
                              Context *context) {
    for (auto &it: defaultArgs) {
        string argName = it.first;
        BaseValue *argValue = it.second;
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(context);
        } else if (argValue->type == T_STRING) {
            ((String<string> *) argValue)->setContext(context);
        } else if (argValue->type == T_LIST) {
            ((List<vector<BaseValue *>> *) argValue)->setContext(context);
        }
        if (argValue->type == T_MAP) {
            ((Map<map<BaseValue *, BaseValue *>> *) argValue)->setContext(context);
        }
        context->symbolTable->set(argName, argValue);
    }

    for (int i = 0; i < args.size(); i++) {
        string argName = argNames[i];
        BaseValue *argValue = args[i];
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(context);
        } else if (argValue->type == T_STRING) {
            ((String<string> *) argValue)->setContext(context);
        } else if (argValue->type == T_LIST) {
            ((List<vector<BaseValue *>> *) argValue)->setContext(context);
        }
        if (argValue->type == T_MAP) {
            ((Map<map<BaseValue *, BaseValue *>> *) argValue)->setContext(context);
        }
        context->symbolTable->set(argName, argValue);
    }
}

template<>
RuntimeResult *Class<int>::checkArgs(vector<BaseValue *> args, vector<string> argNames) {
    auto *res = new RuntimeResult();
    if (args.size() > argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                fTxt,
                to_string(args.size() - argNames.size()) + " too many args passed into " + name,
                ctx
        ));
    }

    int normalArgCount = argNames.size() - defaultArgs.size();

    if (args.size() < normalArgCount) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                fTxt,
                to_string(normalArgCount - args.size()) + " too few args passed into " + name,
                ctx
        ));
    }
    return res->success(nullptr);
}

template<>
RuntimeResult *Class<int>::checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames,
                                                Context *context) {
    RuntimeResult *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames));
    if (res->shouldReturn()) return res;
    populateArgs(args, argNames, context);
    return res->success(nullptr);
}

template<>
RuntimeResult *Class<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();

    vector<string> argNames;
    for (auto &it: constructorArgs) {
        argNames.push_back(it->getValueObject()->getValue());
    }
    Context *context = new Context(name);
    context->symbolTable = new SymbolTable();
    res->reg(checkAndPopulateArgs(args, argNames, context));
    if (res->shouldReturn()) return res;

    UsableClass<int> *usableClass = new UsableClass<int>(fName, fTxt, classNameTok, members, context, ctx, superClass, lines);
    if(usableClass->rtError) {
        return res->failure(usableClass->rtError);
    }
    return (new RuntimeResult())->success(usableClass);
}

template<>
string Class<int>::toString() {
    return "<Class: " + name + ">";
}