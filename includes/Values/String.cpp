//
// Created by Aadi Yadav on 10/15/21.
//

#include "String.h"

String::String(string value, string f, string txt) : Value<string>(value, T_STRING, fName, fTxt){
    strValue = value;
}

bool String::compare(String* s) {
    return s->getValue() == strValue;
}

string String::getValue() {
    return strValue;
}