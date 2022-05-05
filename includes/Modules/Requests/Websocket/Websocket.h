//
// Created by Aadi Yadav on 5/2/22.
//

#ifndef BOA_WEBSOCKET_H
#define BOA_WEBSOCKET_H
#include "../../../Values/String/String.h"

#include <cpprest/ws_client.h>

using namespace web;
using namespace web::websockets::client;
template <typename T> class Websocket : public Value<T> {
public:
    websocket_client client;
    websocket_callback_client callbackClient;
    enum type {
            CALLBACK,
            NORMAL
    };
    type sockType;
    String<string> * url;
    Websocket<int>(String<string> * url, type t);
    BaseValue * copy() override;
    string toString() override;
};

#endif //BOA_WEBSOCKET_H
