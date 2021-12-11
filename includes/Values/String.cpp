//
// Created by Aadi Yadav on 10/15/21.
//

#include <iostream>
#include "String.h"

String::String(string value, string f, string txt) : Value<string>(value, T_STRING, f, txt){
    strValue = value;
}

BaseValue * String::add(BaseValue *s) {
    if (s->type == T_STRING) {
        String *str = (String *) s;
        return (new String(strValue + str->getValue(), s->fName, s->fTxt))->setContext(ctx);
    }
    illegalOperation(s);
}

BaseValue * String::multiply(BaseValue *s) {
    if (s->type == T_NUM) {
        Number *num = (Number *) s;
        string res = "";
        for(int i = 0; i < num->getValue(); i++) {
            res += strValue;
        }
        return (new String(res, s->fName, s->fTxt))->setContext(ctx);
    }
    illegalOperation(s, T_NUM);
}

bool String::isTrue() {
    return strValue.length() > 0;
}


string String::getValue() {
    return strValue;
}

string String::toString() {
    return strValue;
}