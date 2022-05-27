//
// Created by Preeti Thorat on 3/12/22.
//

#include "Requests.h"
#include "RequestsFunction.h"

template<>
Requests<int>::Requests() : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;

    defaultArgs["headers"] = new Map<map<BaseValue *, BaseValue *>>({}, "", "");
    symbolTable->set("get", new RequestsFunction<int>("get", {"url", "headers"}, defaultArgs, "", ""));
    defaultArgs.clear();

    defaultArgs["type"] = new Value<string>("", TOK_TYPE::T_STRING, "", "");
    symbolTable->set("post", new RequestsFunction<int>("post", {"url", "data", "headers", "type"}, defaultArgs, "", ""));
    defaultArgs.clear();

    symbolTable->set("makeSocket", new RequestsFunction<int>("makeSocket", {"port"}, defaultArgs, "", ""));
    symbolTable->set("makeWebsocket", new RequestsFunction<int>("makeWebsocket", {"url"}, defaultArgs, "", ""));
}

template<>
BaseValue *Requests<int>::copy() {
    return new Requests<int>();
}

template<>
string Requests<int>::toString() {
    return "<Module: requests>";
}