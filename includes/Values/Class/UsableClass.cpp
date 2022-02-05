//
// Created by Preeti Thorat on 2/3/22.
//

#include "UsableClass.h"
#include <utility>
#include "../../Interpreter/Interpreter.h"

template<>
BaseValue *UsableClass<int>::getFromSymbolTable(string key) {
    BaseValue * v = ctx->symbolTable->get(key);
    return v;
}

template<>
Context *UsableClass<int>::generateClassContext(string className) {
    Context *classContext = new Context(std::move(className));
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

    return classContext;
}

template<>
UsableClass<int>::UsableClass(string f, string txt, string className, vector<Node *> methods, Context * c, vector<string> lines) : Value<int>(0, T_CLASS, std::move(f), std::move(txt)) {
    map<string, BaseValue *> defaultArgs;
    this->lines = lines;

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

    this->className = std::move(className);
    ctx = generateClassContext(className);

    for (auto &it : c->symbolTable->symbols) {
        ctx->symbolTable->set(it.first, it.second);
    }

    for (auto &method : methods) {
        FuncDefNode * node = (FuncDefNode *) method;
        Interpreter * i = new Interpreter(className, lines);
        RuntimeResult * res = new RuntimeResult();
        string funcName = node->funcNameTok->getValueObject()->getValue();
        Function<int> * v = (Function<int> *) res->reg(i->visit(node, ctx));
        if(res->shouldReturn()) {
            rtError = res->error;
            return;
        }
        ctx->symbolTable->set(funcName, new ClassFunction<int>(v->fName, v->fTxt, funcName, v->body, v->argNames, v->defaultArgs, v->lines, v->autoReturn, ctx, className));
    }

    ClassFunction<int> * init = dynamic_cast<ClassFunction<int> *>(getFromSymbolTable("init"));
    init->execute({});
}

template<>
BaseValue * UsableClass<int>::copy() {
    auto * c = new UsableClass<int>(*this);
    return c;
}

template<>
string UsableClass<int>::toString() {
    return "<InstantiatedClass: " + className + ">";
}