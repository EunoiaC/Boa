//
// Created by Preeti Thorat on 3/12/22.
//

#include "RequestsFunction.h"
#include <curl/curl.h>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

template<>
RuntimeResult *RequestsFunction<int>::execute_get(Context *execCtx) {
    BaseValue * url = execCtx->symbolTable->get("url");
    if (url->type != T_STRING){
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

    auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, urlStr.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        char* _url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &_url);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
        if (response_string.empty()) {
            return (new RuntimeResult())->failure(new RuntimeError(
                    url->posStart,
                    url->posEnd,
                    url->line,
                    url->fName,
                    url->fTxt,
                    "Error fetching data from given url",
                    execCtx
            ));
        }

        return (new RuntimeResult())->success(new String<string>(response_string, "", ""));
    }

    return RuntimeResult().failure(
            new RuntimeError(
                    url->posStart,
                    url->posEnd,
                    url->line,
                    url->fName,
                    url->fTxt,
                    "Failed to initialize curl in the requests module",
                    execCtx
            )
            );
}

template<>
RequestsFunction<int>::RequestsFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = "FUNCTION";
    funcMap["execute_get"] = &RequestsFunction<int>::execute_get;
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