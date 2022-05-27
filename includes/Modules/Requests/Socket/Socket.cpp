//
// Created by Preeti Thorat on 4/3/22.
//

#include "Socket.h"
#include "SocketFunction.h"

template<>
Socket<int>::Socket(Number<double> *port) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    this->port = port;

    map<string, BaseValue *> defaultArgs;

    symbolTable->set("setBufferSize", new SocketFunction<int>(this, "setBufferSize", {"bufferSize"}, defaultArgs, "", ""));
    symbolTable->set("bind", new SocketFunction<int>(this, "bind", {}, defaultArgs, "", ""));
    symbolTable->set("accept", new SocketFunction<int>(this, "accept", {"maxConnections"}, defaultArgs, "", ""));
    symbolTable->set("send", new SocketFunction<int>(this, "send", {"message"}, defaultArgs, "", ""));
    symbolTable->set("receive", new SocketFunction<int>(this, "receive", {}, defaultArgs, "", ""));
    symbolTable->set("close", new SocketFunction<int>(this, "close", {}, defaultArgs, "", ""));
    symbolTable->set("connect", new SocketFunction<int>(this, "connect", {"address"}, defaultArgs, "", ""));
    symbolTable->set("port", port);
}

template<>
BaseValue *Socket<int>::copy() {
    auto *socket = new Socket<int>(this->port);
    return socket;
}

template<>
string Socket<int>::toString() {
    return "<Socket: " + this->port->toString() + ">";
}