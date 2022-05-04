//
// Created by Aadi Yadav on 5/2/22.
//

#include "WebsocketFunction.h"

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

    websockObj->client.send(out_msg).wait();

    return res->success(new String<string>("", "", ""));
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
    funcMap["execute_send"] = &WebsocketFunction<int>::execute_send;
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