//
// Created by Aadi Yadav on 10/15/21.
//

#include <iostream>
#include "String.h"

String::String(string value, string f, string txt) : Value<string>(value, T_STRING, fName, fTxt){
    strValue = value;
}

BaseValue * String::add(BaseValue *s) {
    if (s->type == T_STRING) {
        String *str = (String *) s;
        return (new String(strValue + str->getValue(), fName, fTxt))->setContext(ctx);
    }
    rtError = new RuntimeError(
            s->posStart,
            s->posEnd,
            s->line,
            fName,
            fTxt,
            "Type must be string to do operation",
            ctx
    );
}

BaseValue * String::subtract(BaseValue *s) {
    illegalOperation(s);
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