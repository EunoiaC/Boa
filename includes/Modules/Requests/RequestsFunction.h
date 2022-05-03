//
// Created by Preeti Thorat on 3/12/22.
//

#ifndef BOA_REQUESTSFUNCTION_H
#define BOA_REQUESTSFUNCTION_H

#include "../../Values/Functions/BaseFunction.h"
#include "../../Values/String/String.h"
#include "../../Values/Map/Map.h"
#include "curl/curl.h"
#include "Socket/Socket.h"
#include "Websocket/Websocket.h"

template<typename T> class RequestsFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (RequestsFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    RequestsFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    RequestsFunction<int> *copy() override;

    RuntimeResult * execute_get(Context * execCtx);
    RuntimeResult * execute_post(Context * execCtx);
    RuntimeResult * execute_makeSocket(Context * execCtx);
    RuntimeResult * execute_makeWebsocket(Context * execCtx);

    string toString() override;
};


#endif //BOA_REQUESTSFUNCTION_H
