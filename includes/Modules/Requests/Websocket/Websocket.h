//
// Created by Aadi Yadav on 5/2/22.
//

#ifndef BOA_WEBSOCKET_H
#define BOA_WEBSOCKET_H
#include "../../../Values/String/String.h"
#include "easywsclient.hpp"

using easywsclient::WebSocket;

template <typename T> class Websocket : public Value<T> {
public:
    WebSocket::pointer ws = NULL;
    String<string> * url;
    Websocket<int>(String<string> * url);
    BaseValue * copy() override;
    string toString() override;
};

#endif //BOA_WEBSOCKET_H
