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
RuntimeResult *SocketFunction<int>::execute_init(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    int client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    if (client < 0) {
        return res->failure(new RuntimeError(
                0,
                0,
                0,
                "",
                "",
                "Socket creation failed",
                execCtx
        ));
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(sockObj->port->getValue());

    sockObj->server_addr = server_addr;
    sockObj->client = client;

    return res->success(new Number<double>(client, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_bind(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    if ((::bind(sockObj->client, (struct sockaddr*) &sockObj->server_addr, sizeof(sockObj->server_addr))) < 0)  {
        return res->failure(new RuntimeError(
                0,
                0,
                0,
                "",
                "",
                "Bind failed",
                execCtx
        ));
    }

    socklen_t size = sizeof(sockObj->server_addr);
    sockObj->addr_size = size;

    return res->success(new Number<double>(size, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_listen(Context *execCtx) {
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

    int maxConnections = dynamic_cast<Number<double> *>(temp)->getValue();
    listen(sockObj->client, maxConnections);

    return res->success(new Number<double>(1, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_accept(Context *execCtx) {
    auto *res = new RuntimeResult();
    int server = ::accept(sockObj->client, (struct sockaddr *) &sockObj->server_addr, &sockObj->addr_size);
    sockObj->server = server;

    if (server < 0) {
        return res->failure(new RuntimeError(
                0,
                0,
                0,
                "",
                "",
                "Accept failed",
                execCtx
        ));
    }

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *SocketFunction<int>::execute_send(Context *execCtx) {
    auto *res = new RuntimeResult();
    BaseValue * temp = execCtx->symbolTable->get("message");
    if (temp->type != T_STRING){
        return res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    char buffer[(int) sockObj->bufferSize->getValue()];
    strcpy(buffer, dynamic_cast<String<string> *>(temp)->getValue().c_str());

    int bytes = send(sockObj->server, buffer, sockObj->bufferSize->getValue(), 0);

    return res->success(new Number<double>(bytes, "", ""));
}

template<>
SocketFunction<int>::SocketFunction(Socket<int> *sockObj, string name, vector<string> argNames,
                                map<string, BaseValue *> defaultArgs,
                                string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                               fTxt, CLASS_FUNC) {
    this->sockObj = sockObj;
    type = "FUNCTION";
    funcMap["execute_setBufferSize"] = &SocketFunction<int>::execute_setBufferSize;
    funcMap["execute_init"] = &SocketFunction<int>::execute_init;
    funcMap["execute_bind"] = &SocketFunction<int>::execute_bind;
    funcMap["execute_listen"] = &SocketFunction<int>::execute_listen;
    funcMap["execute_accept"] = &SocketFunction<int>::execute_accept;
    funcMap["execute_send"] = &SocketFunction<int>::execute_send;
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