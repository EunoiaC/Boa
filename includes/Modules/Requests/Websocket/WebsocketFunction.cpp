//
// Created by Aadi Yadav on 5/2/22.
//

#include "WebsocketFunction.h"

#include <utility>

template<>
RuntimeResult *WebsocketFunction<int>::execute_send(Context *execCtx) {
    auto *res = new RuntimeResult();
    BaseValue *temp = execCtx->symbolTable->get("message");
    if (temp->type != TOK_TYPE::T_STRING) {
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
    if (temp->type != TOK_TYPE::T_FUNC) {
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
           RuntimeResult * r = websockObj->msgCallbackFunc->execute({new String<string>(msg->str, "", "")}, {});
           if (r->shouldReturn()) return r;
       } else if (msg->type == ix::WebSocketMessageType::Open) {
       } else if (msg->type == ix::WebSocketMessageType::Error) {
           cout << "Error: " << msg->errorInfo.reason << endl;
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
    type = TOK_TYPE::T_FUNC;
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
RuntimeResult *WebsocketFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    for (auto &it: kwargs) {
        // Check if the keyword argument is a valid argument
        if (find(argNames.begin(), argNames.end(), it.first) == argNames.end()) {
            return res->failure(new RuntimeError(
                    posStart,
                    posEnd,
                    line,
                    fName,
                    fTxt,
                    "Invalid keyword argument " + it.first + " passed into " + name,
                    ctx
            ));
        }
        args.push_back(it.second);
        execCtx->symbolTable->set(it.first, it.second);
    }
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