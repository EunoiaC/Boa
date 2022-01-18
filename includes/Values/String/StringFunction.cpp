//
// Created by Preeti Thorat on 1/17/22.
//

#include "StringFunction.h"

template <>
RuntimeResult *StringFunction<int>::execute_split(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames));
    if (res->error) return res;

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

    if(sep.empty()){
        vector<char> v(value.begin(), value.end());
        for (char &c : v){
            splitString.push_back(new String<string>(string(1, c), "", ""));
        }
        return res->success(new List<vector<BaseValue *>>(splitString, "", ""));
    }

    size_t pos_start = 0, pos_end, delim_len = sep.length();
    string token;;

    while ((pos_end = value.find (sep, pos_start)) != string::npos) {
        token = value.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splitString.push_back (new String<string>(token, "", ""));
    }

    splitString.push_back (new String<string>(value.substr(pos_start), "", ""));
    return res->success(new List<vector<BaseValue*>>(splitString, "", ""));
}

template<>
StringFunction<int>::StringFunction(string value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt) {
    type = "FUNCTION"; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_split"] = &StringFunction<int>::execute_split;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *StringFunction<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    populateArgs(args, argNames, execCtx);
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