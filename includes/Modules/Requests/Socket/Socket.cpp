//
// Created by Preeti Thorat on 4/3/22.
//

#include "Socket.h"
#include "SocketFunction.h"

template<>
Socket<int>::Socket(Number<double> *port) : Value<int>(0, "SOCKET", "", "") {
    this->port = port;

    map<string, BaseValue *> defaultArgs;

    symbolTable->set("setBufferSize", new SocketFunction<int>(this, "setBufferSize", {"bufferSize"}, defaultArgs, "", ""));
    symbolTable->set("init", new SocketFunction<int>(this, "init", {}, defaultArgs, "", ""));
    symbolTable->set("bind", new SocketFunction<int>(this, "bind", {}, defaultArgs, "", ""));
    symbolTable->set("listen", new SocketFunction<int>(this, "listen", {"maxConnections"}, defaultArgs, "", ""));
    symbolTable->set("accept", new SocketFunction<int>(this, "accept", {}, defaultArgs, "", ""));
    symbolTable->set("send", new SocketFunction<int>(this, "send", {"message"}, defaultArgs, "", ""));
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