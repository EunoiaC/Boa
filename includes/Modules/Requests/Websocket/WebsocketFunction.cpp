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

    auto * msg = (String<string> *) temp;
    websocket_outgoing_message out_msg;
    out_msg.set_utf8_message(msg->getValue().c_str());

    if (websockObj->sockType == Websocket<int>::type::NORMAL) {
        websockObj->client.send(out_msg).wait();
    } else {
        websockObj->callbackClient.send(out_msg).wait();
    }

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_receive(Context *execCtx) {
    auto *res = new RuntimeResult();

    if (websockObj->sockType != Websocket<int>::type::NORMAL){
        return res->failure(new RuntimeError(
                0,
                0,
                0,
                "",
                "",
                "Websocket type cannot receive",
                execCtx
        ));
    }

    string bod;
    websockObj->client.receive().then([](websocket_incoming_message in_msg) {
        return in_msg.extract_string();
    }).then([&](string body) {
        bod = std::move(body);
    }).wait();

    return res->success(new String<string>(bod, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_setMessageHandler(Context *execCtx) {
    auto *res = new RuntimeResult();

    if (websockObj->sockType != Websocket<int>::type::CALLBACK){
        return res->failure(new RuntimeError(
                0,
                0,
                0,
                "",
                "",
                "Expected a CALLBACK websocket",
                execCtx
        ));
    }

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
    if (func->argNames.size() != 1){
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

    websockObj->callbackClient.set_message_handler([&](websocket_incoming_message in_msg) {
        res->reg(func->execute({new String<string>(in_msg.extract_string().get(), "", "")}));
        if (res->shouldReturn()) return res;
    });

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WebsocketFunction<int>::execute_close(Context *execCtx) {
    auto *res = new RuntimeResult();

    if (websockObj->sockType == Websocket<int>::type::NORMAL){
        websockObj->client.close();
    } else {
        websockObj->callbackClient.close();
    }

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
    funcMap["execute_receive"] = &WebsocketFunction<int>::execute_receive;
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