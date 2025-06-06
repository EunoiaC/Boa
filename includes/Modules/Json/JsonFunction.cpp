//
// Created by Preeti Thorat on 3/21/22.
//

#include "JsonFunction.h"
#include "nlohmann/json.hpp"

template<> RuntimeResult *JsonFunction<int>::execute_loads(Context *execCtx) {
    auto * res = new RuntimeResult();

    BaseValue * temp = execCtx->symbolTable->get("string");
    if (temp->type != TOK_TYPE::T_STRING){
        res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    auto * jsonStr = (String<string> *) temp;
    nlohmann::json parsedObj;
    try{
        parsedObj = nlohmann::json::parse(jsonStr->getValue());
    } catch (nlohmann::detail::parse_error &e) {
        return (new RuntimeResult())->failure(new RuntimeError(
                jsonStr->posStart,
                jsonStr->posEnd,
                jsonStr->line,
                jsonStr->fName,
                jsonStr->fTxt,
                e.what(),
                execCtx
        ));
    }

    String<string> * key;
    vector<BaseValue *> arr;
    map<BaseValue *, BaseValue *> m;
    if (parsedObj.is_object()){
        for(nlohmann::json::iterator it = parsedObj.begin(); it != parsedObj.end(); ++it) {
            string typeName = it.value().type_name();
            key = new String<string>(it.key(), "", "");

            if(typeName == "boolean") {
                m[key] = new Number<double>(it.value() == true ? 1 : 0, "", "");
            } else if(typeName == "number"){
                m[key] = new Number<double>(it.value(), "", "");
            } else if(typeName == "string") {
                m[key] = new String<string>(it.value(), "", "");
            } else if (typeName == "null") {
                m[key] = new Number<double>(0, "", "");
            } else if (typeName == "object"){
                nlohmann::json temp = it.value();
                auto * c = new Context("temp");
                c->symbolTable = new SymbolTable();
                c->symbolTable->set("string", new String<string>(temp.dump(), "", ""));

                BaseValue * b = res->reg(execute_loads(c));
                if (res->shouldReturn()) return res;

                m[key] = b;
            }
        }
    } else {
        for (auto &object : parsedObj){
            nlohmann::json obj = object;
            auto * c = new Context("temp");
            c->symbolTable = new SymbolTable();
            c->symbolTable->set("string", new String<string>(obj.dump(), "", ""));

            BaseValue * b = res->reg(execute_loads(c));
            if (res->shouldReturn()) return res;

            arr.push_back(b);
        }
    }

    if(!arr.empty()) {
        return res->success(new List<vector<BaseValue *>>(arr, "", ""));
    }
    return res->success(new Map<map<BaseValue *, BaseValue *>>(m, "", ""));
}

template<> RuntimeResult *JsonFunction<int>::execute_dumps(Context *execCtx) {
    auto * res = new RuntimeResult();

    BaseValue * temp = execCtx->symbolTable->get("value");
    if (temp->type != TOK_TYPE::T_MAP && temp->type != TOK_TYPE::T_LIST){
        res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a MAP or LIST",
                execCtx
        ));
    }

    nlohmann::json jsonObj;
    if (temp->type == TOK_TYPE::T_MAP){
        auto * m = (Map<map<BaseValue *, BaseValue *>> *) temp;
        for (auto &kv : m->val) {
            if (kv.second->type == TOK_TYPE::T_MAP || kv.second->type == TOK_TYPE::T_LIST){
                auto * c = new Context("temp");
                c->symbolTable = new SymbolTable();
                c->symbolTable->set("value", kv.second);

                BaseValue * b = res->reg(execute_dumps(c));
                if (res->shouldReturn()) return res;

                jsonObj[kv.first->toString()] = nlohmann::json::parse(b->toString());
            } else {
                if (kv.second->type == TOK_TYPE::T_STRING){
                    if (kv.second->toString() == jsonNull) {
                        jsonObj[kv.first->toString()] = nullptr;
                    } else jsonObj[kv.first->toString()] = kv.second->toString();
                } else if (kv.second->type == TOK_TYPE::T_NUM){
                    double num = ((Number<double> *) kv.second)->getValue();
                    if (num == (int) num) {
                        jsonObj[kv.first->toString()] = (int) num;
                    } else {
                        jsonObj[kv.first->toString()] = num;
                    }
                } else jsonObj[kv.first->toString()] = kv.second->toString();
            }
        }
    } else if (temp->type == TOK_TYPE::T_LIST){
        auto * l = (List<vector<BaseValue *>> *) temp;
        for (auto &v : l->val) {
            if (v->type == TOK_TYPE::T_MAP || v->type == TOK_TYPE::T_LIST){
                auto * c = new Context("temp");
                c->symbolTable = new SymbolTable();
                c->symbolTable->set("value", v);

                BaseValue * b = res->reg(execute_dumps(c));
                if (res->shouldReturn()) return res;

                jsonObj.push_back(nlohmann::json::parse(b->toString()));
            } else {
                if (v->type == TOK_TYPE::T_STRING){
                    if (v->toString() == jsonNull) {
                        jsonObj.push_back(nullptr);
                    } else jsonObj.push_back(v->toString());
                } else if (v->type == TOK_TYPE::T_NUM){
                    double num = ((Number<double> *) v)->getValue();
                    if (num == (int) num) {
                        jsonObj.push_back((int) num);
                    } else {
                        jsonObj.push_back(num);
                    }
                } else jsonObj.push_back(v->toString());
            }
        }
    }

    return res->success(new String<string>(jsonObj.dump(), "", ""));
}

template<>
JsonFunction<int>::JsonFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = TOK_TYPE::T_FUNC;
    funcMap["execute_loads"] = &JsonFunction<int>::execute_loads;
    funcMap["execute_dumps"] = &JsonFunction<int>::execute_dumps;
}

template<>
RuntimeResult *JsonFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
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
    res->reg(checkAndPopulateArgs(args, kwargs, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
JsonFunction<int> *JsonFunction<int>::copy() {
    auto *func = new JsonFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string JsonFunction<int>::toString() {
    return "<JsonFunction: " + name + ">";
}