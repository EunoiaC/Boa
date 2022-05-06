//
// Created by Aadi Yadav on 5/2/22.
//

#ifndef BOA_WEBSOCKET_H
#define BOA_WEBSOCKET_H
#include "../../../Values/String/String.h"
#include <ixwebsocket/IXWebSocket.h>

template <typename T> class Websocket : public Value<T> {
public:
    ix::WebSocket webSocket;
    String<string> * url;
    Websocket<int>(String<string> * url);
    BaseValue * copy() override;
    string toString() override;
};

#endif //BOA_WEBSOCKET_H
