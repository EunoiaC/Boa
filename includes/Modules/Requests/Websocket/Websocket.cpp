//
// Created by Aadi Yadav on 5/2/22.
//

#include "Websocket.h"
#include "WebsocketFunction.h"

template<>
Websocket<int>::Websocket(String<string> *url) : Value<int>(0, "WEBSOCKET", "", "") {
    map<string, BaseValue *> defaultArgs;
    this->url = url;

    ws = WebSocket::from_url(url->getValue());

    symbolTable->set("send", new WebsocketFunction<int>(this, "send", {"message"}, defaultArgs, "", ""));
    symbolTable->set("isClosed", new WebsocketFunction<int>(this, "isClosed", {}, defaultArgs, "", ""));
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