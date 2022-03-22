//
// Created by Preeti Thorat on 2/3/22.
//

#include "UsableClass.h"
#include <utility>
#include "../../Interpreter/Interpreter.h"

template<>
BaseValue *UsableClass<int>::getFromSymbolTable(string key) {
    BaseValue * val = nullptr;
    if(ctx->symbolTable->symbols.count(key)){
        val = ctx->symbolTable->symbols[key];
    }
    return val;
}

template<>
void UsableClass<int>::setInSymbolTable(string key, BaseValue *newObj) {
    ctx->symbolTable->set(key, newObj);
}

template<>
Context *UsableClass<int>::generateClassContext(string className) {
    Context *classContext = new Context(std::move(className));
    classContext->fName = fName;
    classContext->fTxt = fTxt;

    classContext->symbolTable = new SymbolTable();

    classContext->symbolTable->set("null", new Number<double>(0, "", ""));
    classContext->symbolTable->set("true", new Number<double>(1, "", ""));
    classContext->symbolTable->set("false", new Number<double>(0, "", ""));
    classContext->symbolTable->set("print", print);
    classContext->symbolTable->set("input", input);
    classContext->symbolTable->set("toNum", toNum);
    classContext->symbolTable->set("lenOf", lenOf);
    classContext->symbolTable->set("toStr", toStr);
    classContext->symbolTable->set("typeOf", instanceOf);
    classContext->symbolTable->set("eval", eval);
    classContext->symbolTable->set("rename", _rename);
    classContext->symbolTable->set("getSymbolTable", getSymbolTable);
    //Modules
    classContext->symbolTable->set("__random__", _random);
    classContext->symbolTable->set("this", this);

    return classContext;
}

template<>
UsableClass<int>::UsableClass(string f, string txt, Token<string> * classNameTok, vector<Node *> members, Context *c,
                              Context *parent, Node *super, vector<string> lines) : Value<int>(0, T_CLASS, f,
                                                                                               txt) {
    map<string, BaseValue *> defaultArgs;
    this->lines = lines;
    this->classNameTok = classNameTok;

    print = new BuiltInFunction<int>("print", {"value"}, {}, "fName", "fTxt");
    input = new BuiltInFunction<int>("input", {"value"}, {}, "fName", "fTxt");
    toNum = new BuiltInFunction<int>("toNum", {"value"}, {}, "fName", "fTxt");
    lenOf = new BuiltInFunction<int>("lenOf", {"value"}, {}, "fName", "fTxt");
    toStr = new BuiltInFunction<int>("toStr", {"value"}, {}, "fName", "fTxt");
    instanceOf = new BuiltInFunction<int>("instanceOf", {"value"}, {}, "fName", "fTxt");
    eval = new BuiltInFunction<int>("eval", {"value"}, {}, "fName", "fTxt");
    _rename = new BuiltInFunction<int>("rename", {"oldName", "newName"}, {}, "fName", "fTxt");
    getSymbolTable = new BuiltInFunction<int>("getSymbolTable", {}, {}, "fName", "fTxt");
    _random = new Random<int>("fName", "fTxt");

    this->className = classNameTok->getValueObject()->getValue();
    ctx = generateClassContext(className);
    ctx->symbolTable->parent = parent->symbolTable;

    for (auto &it: c->symbolTable->symbols) {
        ctx->symbolTable->set(it.first, it.second);
    }

    Interpreter *i = new Interpreter(className, lines);
    RuntimeResult *res = new RuntimeResult();
    if (super) {
        BaseValue *superClass = res->reg(i->visit(super, ctx));
        if (res->error) {
            rtError = res->error;
            return;
        }
        if (superClass->type != T_CLASS) {
            rtError = new RuntimeError(
                    superClass->posStart,
                    superClass->posEnd,
                    superClass->line,
                    superClass->fName,
                    superClass->fTxt,
                    "Expected a class, but got " + superClass->type + " instead.",
                    ctx
            );
            return;
        }
        for (auto &it: ((UsableClass<int> *) superClass)->ctx->symbolTable->symbols) {
            if (it.first == "init") continue;
            ctx->symbolTable->set(it.first, it.second);
        }
    }
    for (auto &method: members) {
        if (method->type == N_FUNC_DEF) {
            FuncDefNode *node = (FuncDefNode *) method;
            string funcName = node->funcNameTok->getValueObject()->getValue();
            auto *v = (Function<int> *) res->reg(i->visit(node, ctx));
            if (res->shouldReturn()) {
                rtError = res->error;
                return;
            }
            ClassFunction<int> *val = new ClassFunction<int>(v->fName, v->fTxt, funcName, v->body, v->argNames,
                                                             v->defaultArgs, v->lines, v->autoReturn, ctx,
                                                             className);
            ctx->symbolTable->set(funcName, val);
            this->members[funcName] = val;
        } else {
            BaseValue *val = res->reg(i->visit(method, ctx));
            if (res->shouldReturn()) {
                rtError = res->error;
                return;
            }
            if (method->type == N_VAR_ASSIGN) {
                VarAssignNode *node = (VarAssignNode *) method;
                string varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
                ctx->symbolTable->set(varName, val);
                this->members[varName] = val;
            } else if (method->type == N_CLASS_DEF) {
                ClassDefNode *node = (ClassDefNode *) method;
                string className = node->classNameTok->getValueObject()->getValue();
                ctx->symbolTable->set(className, val);
                this->members[className] = val;
            }
        }

    }

    ClassFunction<int> *init = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("init"));
    // Avoid running init for builtin classes
    if (init) {
        res->reg(init->execute({}));
        if (res->shouldReturn()) {
            rtError = res->error;
        }
    }

    memAddress = (string *) this;
    asString = "<InstantiatedClass: " + this->className + ">";
}

template<>
bool UsableClass<int>::isTrue() {
    return true;
}

template<>
Error * UsableClass<int>::funcNotFound(string funcName) {
    return new RuntimeError(
            classNameTok->posStart,
            classNameTok->posEnd,
            classNameTok->line,
            fName,
            classNameTok->fTxt,
            "Class '" + className + "' doesn't have a method '" + funcName + "'",
            this->ctx
    );
}

template<>
BaseValue *UsableClass<int>::compLessThan(BaseValue *other) {
    ClassFunction<int> *lt = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compLessThan"));
    if (lt) {
        if (lt->argNames.size() != 1){
            rtError = new RuntimeError(
                    classNameTok->posStart,
                    classNameTok->posEnd,
                    classNameTok->line,
                    classNameTok->fName,
                    classNameTok->fTxt,
                    "Class '" + className + "' doesn't have a method 'compLessThan' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = lt->execute({other});
        if (res->error) rtError = res->error;
        return (new Number<double>(res->value->isTrue(), "", ""))->setContext(ctx);
    } else {
        rtError = funcNotFound("compLessThan");
    }
}

template<>
BaseValue *UsableClass<int>::compEquals(BaseValue *other) {
    ClassFunction<int> *gt = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compEquals"));
    if (gt) {
        if (gt->argNames.size() != 1){
            rtError = new RuntimeError(
                    classNameTok->posStart,
                    classNameTok->posEnd,
                    classNameTok->line,
                    classNameTok->fName,
                    classNameTok->fTxt,
                    "Class '" + className + "' doesn't have a method 'compEquals' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = gt->execute({other});
        if (res->error) rtError = res->error;
        return (new Number<double>(res->value->isTrue(), "", ""))->setContext(ctx);
    } else {
        if (other->type == T_CLASS){
            UsableClass<int> *otherClass = (UsableClass<int> *) other;
            if (otherClass->memAddress == memAddress){
                return new Number<double>(1, "", "");
            }
        }
        return new Number<double>(0, "", "");
    }
}

template<>
BaseValue *UsableClass<int>::compGreaterThan(BaseValue *other) {
    ClassFunction<int> *gt = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compGreaterThan"));
    if (gt) {
        if (gt->argNames.size() != 1){
            rtError = new RuntimeError(
                    classNameTok->posStart,
                    classNameTok->posEnd,
                    classNameTok->line,
                    classNameTok->fName,
                    classNameTok->fTxt,
                    "Class '" + className + "' doesn't have a method 'compGreaterThan' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = gt->execute({other});
        if (res->error) rtError = res->error;
        return (new Number<double>(res->value->isTrue(), "", ""))->setContext(ctx);
    } else {
        rtError = funcNotFound("compGreaterThan");
    }
}

template<>
BaseValue *UsableClass<int>::compLessThanEquals(BaseValue *other) {
    ClassFunction<int> *lte = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compLessThanEquals"));
    if (lte) {
        if (lte->argNames.size() != 1){
            rtError = new RuntimeError(
                    classNameTok->posStart,
                    classNameTok->posEnd,
                    classNameTok->line,
                    classNameTok->fName,
                    classNameTok->fTxt,
                    "Class '" + className + "' doesn't have a method 'compLessThanEquals' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = lte->execute({other});
        if (res->error) rtError = res->error;
        return (new Number<double>(res->value->isTrue(), "", ""))->setContext(ctx);
    } else {
        rtError = funcNotFound("compLessThanEquals");
    }
}

template<>
BaseValue *UsableClass<int>::compGreaterThanEquals(BaseValue *other) {
    ClassFunction<int> *gte = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compGreaterThanEquals"));
    if (gte) {
        if (gte->argNames.size() != 1){
            rtError = new RuntimeError(
                    classNameTok->posStart,
                    classNameTok->posEnd,
                    classNameTok->line,
                    classNameTok->fName,
                    classNameTok->fTxt,
                    "Class '" + className + "' doesn't have a method 'compGreaterThanEquals' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = gte->execute({other});
        if (res->error) rtError = res->error;
        return (new Number<double>(res->value->isTrue(), "", ""))->setContext(ctx);
    } else {
        rtError = funcNotFound("compGreaterThanEquals");
    }
}

template<>
BaseValue *UsableClass<int>::compSort(BaseValue *other) {
    ClassFunction<int> *sort = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("compSort"));
    if (sort) {
        if (sort->argNames.size() != 1){
            rtError = new RuntimeError(
                    sort->posStart,
                    sort->posEnd,
                    sort->line,
                    sort->fName,
                    sort->fTxt,
                    "Class '" + className + "' doesn't have a method 'sort' with just one arg",
                    ctx
            );
            return nullptr;
        }
        RuntimeResult * res = sort->execute({other});
        if (res->error) rtError = res->error;
        return res->value;
    } else {
        rtError = funcNotFound("compSort");
    }
}

template<>
BaseValue *UsableClass<int>::copy() {
    auto *c = new UsableClass<int>(*this);
    return c;
}

template<>
string UsableClass<int>::toString() {
    return asString;
}