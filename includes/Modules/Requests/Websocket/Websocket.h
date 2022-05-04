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
    String<string> * url;
    Websocket<int>(String<string> * url);
    BaseValue * copy() override;
    string toString() override;
};

#endif //BOA_WEBSOCKET_H
