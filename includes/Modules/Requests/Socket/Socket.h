//
// Created by Preeti Thorat on 4/3/22.
//

#ifndef BOA_SOCKET_H
#define BOA_SOCKET_H
#include "../../../Values/BaseValues/Value.h"
#include "../../../Values/String/String.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

template <typename T> class Socket : public Value<T> {
public:
    Number<double> * port, * bufferSize;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    int client, server;
    Socket<int>(Number<double> * port);
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_SOCKET_H
