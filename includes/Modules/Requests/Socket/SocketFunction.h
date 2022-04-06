//
// Created by Preeti Thorat on 4/3/22.
//

#ifndef BOA_SOCKETFUNCTION_H
#define BOA_SOCKETFUNCTION_H

#include "../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include <sstream>
#include "../../../Values/List/List.h"
#include "Socket.h"

template<typename T> class SocketFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (SocketFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Socket<int> * sockObj;
    SocketFunction<T>(Socket<int> * sockObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    SocketFunction<int> *copy() override;

    RuntimeResult * execute_setBufferSize(Context * execCtx);
    RuntimeResult * execute_bind(Context * execCtx);
    RuntimeResult * execute_send(Context * execCtx);
    RuntimeResult * execute_receive(Context * execCtx);
    RuntimeResult * execute_accept(Context * execCtx);
    RuntimeResult * execute_close(Context * execCtx);
    RuntimeResult * execute_connect(Context * execCtx);

    string toString() override;
};


#endif //BOA_SOCKETFUNCTION_H
