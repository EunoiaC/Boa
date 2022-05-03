//
// Created by Aadi Yadav on 5/2/22.
//

#ifndef BOA_WEBSOCKET_H
#define BOA_WEBSOCKET_H
#include "../../../Values/String/String.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

template <typename T> class Websocket : public Value<T> {
public:
    String<string> * url;
    Websocket<int>(String<string> * url);
    BaseValue * copy() override;
    string toString() override;
};

#endif //BOA_WEBSOCKET_H
