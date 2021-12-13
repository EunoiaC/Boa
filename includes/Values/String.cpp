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

BaseValue *String::compGreaterThanEquals(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue >= ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::compLessThanEquals(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue <= ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::compGreaterThan(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue > ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::compLessThan(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue < ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::compEquals(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue == ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::compNotEquals(BaseValue *val) {
    if(val->type == T_STRING) {
        return (new Number(strValue != ((String*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    illegalOperation(val);
}

BaseValue *String::andedBy(BaseValue *s) {
    return (new Number(!strValue.empty() and s->isTrue(), fName, fTxt))->setContext(ctx);
}

BaseValue *String::oredBy(BaseValue *s) {
    return (new Number(!strValue.empty() or s->isTrue(), fName, fTxt))->setContext(ctx);
}

BaseValue *String::notted() {
    return (new Number(strValue.empty() ? 1 : 0, fName, fTxt))->setContext(ctx);
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