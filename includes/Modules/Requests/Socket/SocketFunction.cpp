//
// Created by Preeti Thorat on 4/3/22.
//

#include "SocketFunction.h"

template<>
RuntimeResult *SocketFunction<int>::execute_setBufferSize(Context *execCtx) {
    BaseValue * temp = execCtx->symbolTable->get("bufferSize");
    RuntimeResult * res = new RuntimeResult();

    if (temp->type != T_NUM){
        return res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    sockObj->bufferSize = dynamic_cast<Number<double> *>(temp);
    return res->success(temp);
}

template<>
RuntimeResult *SocketFunction<int>::execute_bind(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    int server_fd;

    sockObj->t = Socket<int>::SERVER;

    if ((server_fd = ::socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        return res->failure(new RuntimeError(
                sockObj->posStart,
                sockObj->posEnd,
                sockObj->line,
                sockObj->fName,
                sockObj->fTxt,
                "socket failed",
                execCtx
        ));
    }

    if (::setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                     (char *) &sockObj->opt, sizeof(int)))
    {
        return res->failure(new RuntimeError(
                sockObj->posStart,
                sockObj->posEnd,
                sockObj->line,
                sockObj->fName,
                sockObj->fTxt,
                "Setsockopt failed",
                execCtx
        ));
    }

    sockObj->address.sin_family = AF_INET;
    sockObj->address.sin_addr.s_addr = INADDR_ANY;
    sockObj->address.sin_port = htons( sockObj->port->getValue() );

    // Forcefully attaching socket to the port 8080
    if (::bind(server_fd, (struct sockaddr *)&sockObj->address,
             sizeof(sockObj->address))<0)
    {
        return res->failure(new RuntimeError(
                sockObj->posStart,
                sockObj->posEnd,
                sockObj->line,
                sockObj->fName,
                sockObj->fTxt,
                "Bind failed",
                execCtx
        ));
    }

    sockObj->server_fd = server_fd;

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_accept(Context *execCtx) {
    auto *res = new RuntimeResult();
    BaseValue * temp = execCtx->symbolTable->get("maxConnections");
    if (temp->type != T_NUM){
        return res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    if (::listen(sockObj->server_fd, ((Number<double> *) temp)->getValue()) < 0)
    {
        return res->failure(new RuntimeError(
                sockObj->posStart,
                sockObj->posEnd,
                sockObj->line,
                sockObj->fName,
                sockObj->fTxt,
                "Listen failed",
                execCtx
        ));
    }

    if ((sockObj->new_socket = ::accept(sockObj->server_fd, (struct sockaddr *)&sockObj->address,
                             (socklen_t*)&sockObj->address))<0)
    {
        return res->failure(new RuntimeError(
                sockObj->posStart,
                sockObj->posEnd,
                sockObj->line,
                sockObj->fName,
                sockObj->fTxt,
                "Accept failed",
                execCtx
        ));
    }

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_send(Context *execCtx) {
    auto *res = new RuntimeResult();


    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_receive(Context *execCtx) {
    auto *res = new RuntimeResult();
    char buffer[(unsigned long) sockObj->bufferSize->getValue()];

    if (sockObj->t == Socket<int>::SERVER) {
        ::read(sockObj->new_socket, buffer, sockObj->bufferSize->getValue());
    }

    return res->success(new String<string>(buffer, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_close(Context *execCtx) {
    auto *res = new RuntimeResult();

    if (sockObj->t == Socket<int>::SERVER) {
        ::close(sockObj->server_fd);
        if (sockObj->new_socket != 0) {
            ::close(sockObj->new_socket);
        }
    }

    return res->success(new Number<double>(0, "", ""));
}


template<>
SocketFunction<int>::SocketFunction(Socket<int> *sockObj, string name, vector<string> argNames,
                                map<string, BaseValue *> defaultArgs,
                                string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                               fTxt, CLASS_FUNC) {
    this->sockObj = sockObj;
    type = "FUNCTION";
    funcMap["execute_setBufferSize"] = &SocketFunction<int>::execute_setBufferSize;
    funcMap["execute_bind"] = &SocketFunction<int>::execute_bind;
    funcMap["execute_accept"] = &SocketFunction<int>::execute_accept;
    funcMap["execute_send"] = &SocketFunction<int>::execute_send;
    funcMap["execute_receive"] = &SocketFunction<int>::execute_receive;
    funcMap["execute_close"] = &SocketFunction<int>::execute_close;
}

template<>
SocketFunction<int> *SocketFunction<int>::copy() {
    auto *func = new SocketFunction<int>(sockObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *SocketFunction<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
string SocketFunction<int>::toString() {
    return "<SocketFunction: " + name + ">";
}