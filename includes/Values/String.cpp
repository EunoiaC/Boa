//
// Created by Preeti Thorat on 10/15/21.
//

#include "String.h"

String::String(string value) : Value<string>(value, T_STRING){
    strValue = value;
}

bool String::compare(String* s) {
    return s->getValue() == strValue;
}

string String::getValue() {
    return strValue;
}