//
// Created by Aadi Yadav on 5/2/22.
//

#include "WebsocketFunction.h"

#include <utility>

template<>
RuntimeResult *WebsocketFunction<int>::execute_send(Context *execCtx) {
    auto *res = new RuntimeResult();
    BaseValue *temp = execCtx->symbolTable->get("message");
    if (temp->type != T_STRING) {
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

    auto *msg = (String<string> *) temp;
    websockObj->webSocket.send(msg->getValue());

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_setMessageHandler(Context *execCtx) {
    auto *res = new RuntimeResult();

    BaseValue *temp = execCtx->symbolTable->get("messageHandler");
    if (temp->type != T_FUNC) {
        return res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a FUNCTION",
                execCtx
        ));
    }

    auto *func = (Function<int> *) temp;
    if (func->argNames.size() != 1) {
        return res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a FUNCTION with 1 argument",
                execCtx
        ));
    }

    websockObj->msgCallbackFunc = func;

    websockObj->webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr &msg) {
       if (msg->type == ix::WebSocketMessageType::Message) {
           RuntimeResult * r = websockObj->msgCallbackFunc->execute({new String<string>(msg->str, "", "")});
           if (r->shouldReturn()) return r;
       } else if (msg->type == ix::WebSocketMessageType::Open) {
       } else if (msg->type == ix::WebSocketMessageType::Error) {
           return res->failure(new RuntimeError(
                   temp->posStart,
                   temp->posEnd,
                   temp->line,
                   temp->fName,
                   temp->fTxt,
                   msg->errorInfo.reason,
                   execCtx
           ));
       }
    });

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_close(Context *execCtx) {
    auto *res = new RuntimeResult();

    websockObj->webSocket.close();

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_start(Context *execCtx) {
    auto *res = new RuntimeResult();

    websockObj->webSocket.start();

    return res->success(new Number<double>(0, "", ""));
}

template<>
WebsocketFunction<int>::WebsocketFunction(Websocket<int> *websockObj, string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->websockObj = websockObj;
    this->defaultArgs = defaultArgs;
    type = "FUNCTION";
    funcMap["execute_close"] = &WebsocketFunction<int>::execute_close;
    funcMap["execute_send"] = &WebsocketFunction<int>::execute_send;
    funcMap["execute_start"] = &WebsocketFunction<int>::execute_start;
    funcMap["execute_setMessageHandler"] = &WebsocketFunction<int>::execute_setMessageHandler;
}

template<>
WebsocketFunction<int> *WebsocketFunction<int>::copy() {
    auto *func = new WebsocketFunction<int>(websockObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *WebsocketFunction<int>::execute(vector<BaseValue *> args) {
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
string WebsocketFunction<int>::toString() {
    return "<WebsocketFunction: " + name + ">";
}