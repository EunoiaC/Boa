//
// Created by Preeti Thorat on 12/9/21.
//

#include "Function.h"

#include "../../Interpreter/Interpreter.h"


template<> Function<int>::Function(string fName, string fTxt, string name, Node *body, vector<string> argNames, vector<string> lines)
        : Value<int>(0, T_FUNC, fName, fTxt) {
    this->name = name;
    this->body = body;
    this->argNames = argNames;
    this->lines = lines;
}

template<> RuntimeResult *Function<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
    Interpreter *interpreter = new Interpreter(fName, lines);

    Context *newContext = new Context(name);
    newContext->setParentEntry(posStart, fName, fTxt, line);
    newContext->setParentCtx(ctx);
    newContext->symbolTable = (new SymbolTable())->setParent(newContext->parentCtx->symbolTable);

    if (args.size() > this->argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                callTxt,
                to_string(args.size() - this->argNames.size()) + " too many args passed into " + name,
                ctx
        ));
    }

    if (args.size() < this->argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                callTxt,
                to_string(this->argNames.size() - args.size()) + " too few args passed into " + name,
                ctx
        ));
    }

    for (int i = 0; i < args.size(); i++) {
        string argName = argNames[i];
        BaseValue *argValue = args[i];
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(newContext);
        }
        newContext->symbolTable->set(argName, argValue);
    }

    BaseValue *value = res->reg(interpreter->visit(body, newContext));
    return res->success(value);
}

template<> Function<int> *Function<int>::copy() {
    Function<int> * func = new Function<int>(fName, fTxt, name, body, argNames, lines);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<typename T> string Function<T>::toString() {
    return "{Func: " + name + "}";
}