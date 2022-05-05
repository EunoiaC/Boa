//
// Created by Aadi Yadav on 5/2/22.
//

#include "Websocket.h"
#include "WebsocketFunction.h"

template<>
Websocket<int>::Websocket(String<string> *url, type t) : Value<int>(0, "WEBSOCKET", "", "") {
    map<string, BaseValue *> defaultArgs;
    this->url = url;

    this->sockType = t;

    if (t == type::CALLBACK){
        callbackClient.connect(U(url->getValue())).wait();
    } else {
        client.connect(U(url->getValue())).wait();
    }

    symbolTable->set("send", new WebsocketFunction<int>(this, "send", {"message"}, defaultArgs, "", ""));
    symbolTable->set("receive", new WebsocketFunction<int>(this, "receive", {}, defaultArgs, "", ""));
    symbolTable->set("close", new WebsocketFunction<int>(this, "close", {}, defaultArgs, "", ""));
    symbolTable->set("setMessageHandler", new WebsocketFunction<int>(this, "setMessageHandler", {"messageHandler"}, defaultArgs, "", ""));
}

template<>
BaseValue *Websocket<int>::copy() {
    auto *socket = new Websocket<int>(url, sockType);
    return socket;
}

template<>
string Websocket<int>::toString() {
    return "<Websocket: " + this->url->getValue() + ">";
}