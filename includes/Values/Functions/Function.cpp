//
// Created by Preeti Thorat on 12/9/21.
//

#include "Function.h"

#include "../../Interpreter/Interpreter.h"


template<> Function<int>::Function(string fName, string fTxt, string name, Node *body, vector<string> argNames, vector<string> lines, bool shouldReturnNull) : BaseFunction<int>(name, argNames, fName, fTxt){
    this->shouldReturnNull = shouldReturnNull;
    this->lines = lines;
    this->body = body;
}

template<> RuntimeResult *Function<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
    Interpreter *interpreter = new Interpreter(fName, lines);

    Context *newContext = generateNewContext();

    res->reg(checkAndPopulateArgs(args, argNames, newContext));
    if(res->error) return res;

    BaseValue *value = res->reg(interpreter->visit(body, newContext));
    if(shouldReturnNull){
        value = new Number<double>(0, fName, "");
    }
    return res->success(value);
}

template<> Function<int> *Function<int>::copy() {
    Function<int> * func = new Function<int>(fName, fTxt, name, body, argNames, lines, shouldReturnNull);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<> string Function<int>::toString() {
    return "{Func: " + name + "}";
}