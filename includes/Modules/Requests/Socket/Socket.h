//
// Created by Preeti Thorat on 4/3/22.
//

#ifndef BOA_SOCKET_H
#define BOA_SOCKET_H
#include "../../../Values/BaseValues/Value.h"
#include "../../../Values/String/String.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

template <typename T> class Socket : public Value<T> {
public:
    int server_fd, new_socket, valread;
    enum type {
        SERVER,
        CLIENT
    };

    type t;

    struct sockaddr_in address;
    int opt = 1;
    Number<double> * port, * bufferSize;
    Socket<int>(Number<double> * port);
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_SOCKET_H
