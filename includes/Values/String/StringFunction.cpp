//
// Created by Preeti Thorat on 1/17/22.
//

#include "StringFunction.h"

template <>
RuntimeResult *StringFunction<int>::execute_split(Context *execCtx) {
    auto *res = new RuntimeResult();

    BaseValue * separator = execCtx->symbolTable->get("separator");
    if(separator->type != T_STRING){
        return res->failure(new RuntimeError(
                separator->posStart,
                separator->posEnd,
                separator->line,
                separator->fName,
                separator->fTxt,
                "Expected string as separator",
                execCtx
        ));
    }

    vector<BaseValue *> splitString;
    string sep = ((String<string>*)separator)->getValue();
    string strValue = value->copy()->getValue();

    if(sep.empty()){
        vector<char> v(strValue.begin(), strValue.end());
        for (char &c : v){
            splitString.push_back(new String<string>(string(1, c), "", ""));
        }
        return res->success(new List<vector<BaseValue *>>(splitString, "", ""));
    }

    size_t pos_start = 0, pos_end, delim_len = sep.length();
    string token;;

    while ((pos_end = strValue.find (sep, pos_start)) != string::npos) {
        token = strValue.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splitString.push_back (new String<string>(token, "", ""));
    }

    splitString.push_back (new String<string>(strValue.substr(pos_start), "", ""));
    return res->success(new List<vector<BaseValue*>>(splitString, "", ""));
}

template <>
RuntimeResult *StringFunction<int>::execute_slice(Context *execCtx) {
    auto *res = new RuntimeResult();

    BaseValue * start = execCtx->symbolTable->get("startIdx");
    BaseValue * end = execCtx->symbolTable->get("endIdx");

    string toSlice = value->copy()->getValue();

    if(start->type != T_NUM){
        return res->failure(new RuntimeError(
                start->posStart,
                start->posEnd,
                start->line,
                start->fName,
                start->fTxt,
                "Expected a number",
                execCtx
        ));
    }

    if(end->type != T_NUM) {
        return res->failure(new RuntimeError(
                end->posStart,
                end->posEnd,
                end->line,
                start->fName,
                start->fTxt,
                "Expected a number",
                execCtx
        ));
    }

    int startIndex = ((Number<double>*)start)->getValue();
    int endIndex = ((Number<double>*)end)->getValue();

    if(startIndex < 0 || startIndex >= toSlice.length()){
        return res->failure(new RuntimeError(
                start->posStart,
                start->posEnd,
                start->line,
                start->fName,
                start->fTxt,
                "Start index out of range",
                execCtx
        ));
    }

    if((endIndex < 0 || endIndex >= toSlice.length()) && endIndex != -1){
        return res->failure(new RuntimeError(
                end->posStart,
                end->posEnd,
                end->line,
                end->fName,
                end->fTxt,
                "End index out of range",
                execCtx
        ));
    }

    if(endIndex == -1) {
        endIndex = toSlice.length();
    }

    return res->success((new String<string>(toSlice.substr(startIndex, endIndex-startIndex), start->fName, start->fTxt))->setPos(start->posStart, end->posEnd, start->line));
}

template<>
StringFunction<int>::StringFunction(String<string>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt) {
    type = "FUNCTION"; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_split"] = &StringFunction<int>::execute_split;
    funcMap["execute_slice"] = &StringFunction<int>::execute_slice;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *StringFunction<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
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
StringFunction<int> *StringFunction<int>::copy() {
    auto *func = new StringFunction<int>(value, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string StringFunction<int>::toString() {
    return "<StringFunction: " + name + ">";
}