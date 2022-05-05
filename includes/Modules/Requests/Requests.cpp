//
// Created by Preeti Thorat on 3/12/22.
//

#include "Requests.h"
#include "RequestsFunction.h"

template<>
Requests<int>::Requests() : Value<int>(0, "REQUESTS", "", "") {
    map<string, BaseValue *> defaultArgs;

    defaultArgs["headers"] = new Map<map<BaseValue *, BaseValue *>>({}, "", "");
    symbolTable->set("get", new RequestsFunction<int>("get", {"url", "headers"}, defaultArgs, "", ""));
    defaultArgs.clear();

    defaultArgs["type"] = new Value<string>("", T_STRING, "", "");
    symbolTable->set("post", new RequestsFunction<int>("post", {"url", "data", "headers", "type"}, defaultArgs, "", ""));
    defaultArgs.clear();

    symbolTable->set("makeSocket", new RequestsFunction<int>("makeSocket", {"port"}, defaultArgs, "", ""));

    defaultArgs["type"] = new String<string>("", "", "");
    symbolTable->set("makeWebsocket", new RequestsFunction<int>("makeWebsocket", {"url", "type"}, defaultArgs, "", ""));
    defaultArgs.clear();
}

template<>
BaseValue *Requests<int>::copy() {
    return new Requests<int>(*this);
}

template<>
string Requests<int>::toString() {
    return "<Module: requests>";
}