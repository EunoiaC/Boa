//
// Created by Preeti Thorat on 3/12/22.
//

#include "RequestsFunction.h"
#include <curl/curl.h>
#include <errno.h>

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

    BaseValue * temp2 = execCtx->symbolTable->get("headers");
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

    BaseValue * temp3 = execCtx->symbolTable->get("type");
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

    CURL *curl;
    CURLcode res;
    string responseString;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *chunk = NULL;

        for (auto &header : headers->getValue()) {
            string header_string = header.first->toString() + ": " + header.second->toString();
            chunk = curl_slist_append(chunk, header_string.c_str());
        }

        // Set data
        if(type == "json") {
            if(temp->type != T_STRING) {
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
            chunk = curl_slist_append(chunk, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data->getValue().c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data->getValue().length());
        } else {
            if(temp->type != T_MAP) {
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
            for(auto &data_pair : data->getValue()) {
                string key = data_pair.first->toString();
                string value = data_pair.second->toString();
                string data_string = key + "=" + value;
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_string.c_str());
                curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_string.length());

            }
        }

        /* set our custom set of headers */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_URL, urlStr.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK){
            return (new RuntimeResult())->failure(new RuntimeError(
                    url->posStart,
                    url->posEnd,
                    url->line,
                    url->fName,
                    url->fTxt,
                    "Failed to initialize curl in the requests module",
                    execCtx
            ));
        }

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* free the custom headers */
        curl_slist_free_all(chunk);
    }
    return (new RuntimeResult())->success(new String<string>(responseString, "", ""));
}

template<>
RuntimeResult *RequestsFunction<int>::execute_makeSocket(Context *execCtx) {
    BaseValue * temp = execCtx->symbolTable->get("port");
    if (temp->type != T_NUM){
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
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
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