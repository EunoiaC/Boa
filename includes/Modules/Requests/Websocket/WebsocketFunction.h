//
// Created by Aadi Yadav on 5/2/22.
//

#ifndef BOA_WEBSOCKETFUNCTION_H
#define BOA_WEBSOCKETFUNCTION_H


#include "../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../Values/List/List.h"
#include "Websocket.h"

template<typename T> class WebsocketFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (WebsocketFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Websocket<int> * websockObj;
    WebsocketFunction<T>(Websocket<int> * sockObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    WebsocketFunction<int> *copy() override;

    RuntimeResult * execute_send(Context * execCtx);

    string toString() override;
};


#endif //BOA_WEBSOCKETFUNCTION_H
