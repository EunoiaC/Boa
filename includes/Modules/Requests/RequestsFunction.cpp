//
// Created by Preeti Thorat on 3/12/22.
//

#include "RequestsFunction.h"
#include <curl/curl.h>
#include <cpr/cpr.h>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char *) ptr, size * nmemb);
    return size * nmemb;
}

template<>
RuntimeResult *RequestsFunction<int>::execute_get(Context *execCtx) {
    BaseValue *url = execCtx->symbolTable->get("url");
    if (url->type != TOK_TYPE::T_STRING) {
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

    BaseValue *temp2 = execCtx->symbolTable->get("headers");
    if (temp2->type != TOK_TYPE::T_MAP) {
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

    string urlStr = ((String<string> *) url)->getValue();

    cpr::Header headers;
    for (auto &header : ((Map<map<string, string>> *) temp2)->getValue()) {
        headers[header.first] = header.second;
    }

    cpr::Response response = cpr::Get(cpr::Url{urlStr}, headers);

    return RuntimeResult().success(new String<string>(response.text, "", ""));
}

template<>
RuntimeResult *RequestsFunction<int>::execute_post(Context *execCtx) {
    BaseValue *url = execCtx->symbolTable->get("url");
    if (url->type != TOK_TYPE::T_STRING) {
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
    if (temp2->type != TOK_TYPE::T_MAP) {
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
    if (temp3->type != TOK_TYPE::T_STRING) {
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

    cpr::Header headers2;
    for (auto &header : headers->getValue()) {
        headers2[header.first->toString()] = header.second->toString();
    }

    cpr::Url url2{urlStr};

    cpr::Session s;
    s.SetUrl(url2);
    s.SetHeader(headers2);
    s.SetVerifySsl(false);
    if (type == "json"){
        if (temp->type != TOK_TYPE::T_STRING) {
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
        s.SetBody(cpr::Body{((String<string> *) temp)->getValue()});
    } else {
        if (temp->type != TOK_TYPE::T_MAP){
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
        vector<cpr::Pair> payloadData;
        for (auto &data : ((Map<map<BaseValue *, BaseValue *>> *) temp)->getValue()){
            payloadData.emplace_back(cpr::Pair{data.first->toString(), data.second->toString()});
        }
        cpr::Payload p(payloadData.begin(), payloadData.end());
        s.SetPayload(p);
    }

    cpr::Response response = s.Post();
    cout << response.reason << endl;

    return (new RuntimeResult())->success(new String<string>(response.text, "", ""));
}

template<>
RuntimeResult *RequestsFunction<int>::execute_makeSocket(Context *execCtx) {
    BaseValue *temp = execCtx->symbolTable->get("port");
    if (temp->type != TOK_TYPE::T_NUM) {
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
RuntimeResult *RequestsFunction<int>::execute_makeWebsocket(Context *execCtx) {
    BaseValue *temp = execCtx->symbolTable->get("url");
    if (temp->type != TOK_TYPE::T_STRING) {
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

    Websocket<int> * sock = new Websocket<int>(dynamic_cast<String<string> *>(temp));

    return (new RuntimeResult())->success(sock);
}

template<>
RequestsFunction<int>::RequestsFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                        string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                       fName,
                                                                                       fTxt, CLASS_FUNC) {
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;
    funcMap["execute_get"] = &RequestsFunction<int>::execute_get;
    funcMap["execute_makeSocket"] = &RequestsFunction<int>::execute_makeSocket;
    funcMap["execute_makeWebsocket"] = &RequestsFunction<int>::execute_makeWebsocket;
    funcMap["execute_post"] = &RequestsFunction<int>::execute_post;
}

template<>
RuntimeResult *RequestsFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    for (auto &it: kwargs) {
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