//
// Created by Aadi Yadav on 10/15/21.
//

#include <iostream>
#include "String.h"
#include "StringFunction.h"

template<>
String<string>::String(string value, string f, string txt) : Value<string>(value, T_STRING, f, txt) {
    strValue = value;
    map<string, BaseValue *> defaultArgs;

    defaultArgs["separator"] = new Value<string>("", T_STRING, fName, fTxt);
    symbolTable->set("split", new StringFunction<int>(this, "split", {"separator"},
                                                      defaultArgs, "",
                                                      ""));
    defaultArgs.clear();

    defaultArgs["endIdx"] = new Value<double>(-1, T_NUM, fName, fTxt);
    symbolTable->set("slice", new StringFunction<int>(this, "slice", {"startIdx", "endIdx"},
                                                      defaultArgs, "",
                                                      ""));
    defaultArgs.clear();

    symbolTable->set("join", new StringFunction<int>(this, "join", {"toJoin"},
                                                      defaultArgs, "",
                                                      ""));

    symbolTable->set("indexOf", new StringFunction<int>(this, "indexOf", {"toFind"},
                                                     defaultArgs, "",
                                                     ""));
}

template<>
BaseValue *String<string>::get(BaseValue *s) {
    if (s->type == T_NUM) {
        auto *num = (Number<double> *) s;
        if (num->numValue >= strValue.length()) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else {
            return (new String<string>(strValue.substr(num->numValue, 1), s->fName, s->fTxt))->setContext(ctx);
        }
    } else {
        illegalOperation(s);
    }
}

template<>
BaseValue *String<string>::contains(BaseValue *val) {
    if (val->type == T_STRING) {
        if (strValue.find(((String<string> *) val)->strValue) != string::npos) {
            return new Number<double>(1, fName, fTxt);
        } else {
            return new Number<double>(0, fName, fTxt);
        }
    } else {
        illegalOperation(val);
    }
}

template<>
BaseValue *String<string>::add(BaseValue *s) {
    return (new String<string>(strValue + s->toString(), s->fName, s->fTxt))->setContext(ctx);
}

template<>
String<string> *String<string>::copy() {
    String<string> *str = new String<string>(val, fName, fTxt);
    str->setPos(posStart, posEnd, line);
    str->setContext(ctx);
    return str;
}

template<>
int String<string>::getLength() {
    return val.length();
}

template<>
BaseValue *String<string>::plusEquals(BaseValue *s) {
    if (s->type == T_STRING) {
        String *str = (String *) s;
        fName = s->fName;
        fTxt = s->fTxt;
        strValue += str->getValue();
        val += str->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
BaseValue *String<string>::compGreaterThanEquals(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue >= ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::compLessThanEquals(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue <= ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::compGreaterThan(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue > ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::compLessThan(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue < ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}


template<>
BaseValue *String<string>::compSort(BaseValue *val) {
    return compLessThan(val);
}

template<>
BaseValue *String<string>::compEquals(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue == ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::compNotEquals(BaseValue *val) {
    if (val->type == T_STRING) {
        return (new Number<double>(strValue != ((String *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(1, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::andedBy(BaseValue *s) {
    return (new Number<double>(!strValue.empty() and s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::oredBy(BaseValue *s) {
    return (new Number<double>(!strValue.empty() or s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::notted() {
    return (new Number<double>(strValue.empty() ? 1 : 0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *String<string>::multiply(BaseValue *s) {
    if (s->type == T_NUM) {
        Number<double> *num = (Number<double> *) s;
        string res = "";
        for (int i = 0; i < num->getValue(); i++) {
            res += strValue;
        }
        return (new String<string>(res, s->fName, s->fTxt))->setContext(ctx);
    }
    illegalOperation(s, T_NUM);
}

template<>
bool String<string>::isTrue() {
    return strValue.length() > 0;
}


template<typename T>
string String<T>::getValue() {
    return strValue;
}

template<>
string String<string>::toString() {
    return strValue;
}