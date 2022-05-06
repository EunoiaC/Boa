//
// Created by Aadi Yadav on 5/2/22.
//

#include "Websocket.h"
#include "WebsocketFunction.h"

template<>
Websocket<int>::Websocket(String<string> *url) : Value<int>(0, "WEBSOCKET", "", "") {
    map<string, BaseValue *> defaultArgs;
    this->url = url;

    webSocket.setUrl(url->getValue());
    webSocket.start();

    symbolTable->set("send", new WebsocketFunction<int>(this, "send", {"message"}, defaultArgs, "", ""));
    symbolTable->set("close", new WebsocketFunction<int>(this, "close", {}, defaultArgs, "", ""));
    symbolTable->set("setMessageHandler", new WebsocketFunction<int>(this, "setMessageHandler", {"messageHandler"}, defaultArgs, "", ""));
}

template<>
BaseValue *Websocket<int>::copy() {
    auto *socket = new Websocket<int>(url);
    return socket;
}

template<>
string Websocket<int>::toString() {
    return "<Websocket: " + this->url->getValue() + ">";
}