//
// Created by Preeti Thorat on 4/2/22.
//

#include "Future.h"
#include "FutureFunction.h"
#include <sstream>

template <>
Future<shared_future<RuntimeResult *>>::Future(shared_future<RuntimeResult *> value, string f, string txt) : Value<shared_future<RuntimeResult *>>(value, TOK_TYPE::T_FUTURE, f, txt) {
    promise = value;
    map<string, BaseValue *> defaultArgs;
    symbolTable->set("get", new FutureFunction<int>(this, "get", {},
                                                  defaultArgs, "",
                                                  ""));
    symbolTable->set("isReady", new FutureFunction<int>(this, "isReady", {},
                                                    defaultArgs, "",
                                                    ""));
}

template<>
shared_future<RuntimeResult *> Future<shared_future<RuntimeResult *>>::getValue() {
    return promise;
}

template<>
Future<shared_future<RuntimeResult *>> *Future<shared_future<RuntimeResult *>>::copy() {
    Future<shared_future<RuntimeResult *>> *fut = new Future<shared_future<RuntimeResult *>>(promise, fName, fTxt);
    fut->setPos(posStart, posEnd, line);
    fut->setContext(ctx);
    return fut;
}

template<>
string Future<shared_future<RuntimeResult *>>::toString() {
    stringstream ss;
    ss << "<Future: ";
    ss << &promise << ">";
    return ss.str();
}