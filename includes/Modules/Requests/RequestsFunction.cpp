//
// Created by Preeti Thorat on 3/12/22.
//

#include "RequestsFunction.h"
#include <cpr/cpr.h>

template<>
RuntimeResult *RequestsFunction<int>::execute_get(Context *execCtx) {
    BaseValue *url = execCtx->symbolTable->get("url");
    if (url->type != T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                url->posStart,
                url->posEnd,
                url->line,
                url->fName,
                url->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    string urlStr = ((String<string> *) url)->getValue();

    cpr::Response r = cpr::Get(cpr::Url{urlStr});
    return (new RuntimeResult())->success(new String<string>(r.text, "", ""));
}

template<>
RuntimeResult *RequestsFunction<int>::execute_post(Context *execCtx) {
    BaseValue *url = execCtx->symbolTable->get("url");
    if (url->type != T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                url->posStart,
                url->posEnd,
                url->line,
                url->fName,
                url->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }
    BaseValue *temp = execCtx->symbolTable->get("data");

    BaseValue *temp2 = execCtx->symbolTable->get("headers");
    if (temp2->type != T_MAP) {
        return (new RuntimeResult())->failure(new RuntimeError(
                temp2->posStart,
                temp2->posEnd,
                temp2->line,
                temp2->fName,
                temp2->fTxt,
                "Expected a MAP",
                execCtx
        ));
    }

    BaseValue *temp3 = execCtx->symbolTable->get("type");
    if (temp3->type != T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                temp3->posStart,
                temp3->posEnd,
                temp3->line,
                temp3->fName,
                temp3->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    string urlStr = ((String<string> *) url)->getValue();
    auto *headers = (Map<map<BaseValue *, BaseValue *>> *) temp2;
    string type = ((String<string> *) temp3)->getValue();

    string responseString;

    cpr::Header header{};

    for (auto &h: headers->getValue()) {
        header.insert(pair<string, string>(h.first->toString(), h.second->toString()));
    }

    // Set data
    if (type == "json") {
        if (temp->type != T_STRING) {
            return (new RuntimeResult())->failure(new RuntimeError(
                    temp->posStart,
                    temp->posEnd,
                    temp->line,
                    temp->fName,
                    temp->fTxt,
                    "Expected a STRING",
                    execCtx
            ));
        }
        auto *data = (String<string> *) temp;
        // Add content type
        header.insert(pair<string, string>("Content-Type", "application/json"));

        cpr::Response r = cpr::Post(cpr::Url{urlStr}, cpr::Body{data->getValue()}, header);
        responseString = r.text;
    } else {
        if (temp->type != T_MAP) {
            return (new RuntimeResult())->failure(new RuntimeError(
                    temp->posStart,
                    temp->posEnd,
                    temp->line,
                    temp->fName,
                    temp->fTxt,
                    "Expected a MAP",
                    execCtx
            ));
        }
        auto *data = (Map<map<BaseValue *, BaseValue *>> *) temp;
        // Create a Payload
        cpr::Payload payload{};
        for (auto &d: data->getValue()) {
            payload.Add(cpr::Pair(d.first->toString(), d.second->toString()));
        }
        cpr::Response r = cpr::Post(cpr::Url{urlStr}, cpr::Payload{payload}, cpr::Header{header});
        responseString = r.text;
    }
    return (new RuntimeResult())->success(new String<string>(responseString, "", ""));
}

template<>
RuntimeResult *RequestsFunction<int>::execute_makeSocket(Context *execCtx) {
    BaseValue *temp = execCtx->symbolTable->get("port");
    if (temp->type != T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    return (new RuntimeResult())->success(new Socket<int>(dynamic_cast<Number<double> *>(temp)));
}

template<>
RequestsFunction<int>::RequestsFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                        string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                       fName,
                                                                                       fTxt, CLASS_FUNC) {
    this->defaultArgs = defaultArgs;
    type = "FUNCTION";
    funcMap["execute_get"] = &RequestsFunction<int>::execute_get;
    funcMap["execute_makeSocket"] = &RequestsFunction<int>::execute_makeSocket;
    funcMap["execute_post"] = &RequestsFunction<int>::execute_post;
}

template<>
RuntimeResult *RequestsFunction<int>::execute(vector<BaseValue *> args) {
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
RequestsFunction<int> *RequestsFunction<int>::copy() {
    auto *func = new RequestsFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string RequestsFunction<int>::toString() {
    return "<RequestsFunction: " + name + ">";
}