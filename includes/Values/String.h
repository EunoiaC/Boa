//
// Created by Aadi Yadav on 10/15/21.
//
#pragma once
#ifndef BOA_STRING_H
#define BOA_STRING_H

#include "Value.cpp"


class String : public Value<string> {
public:
    string strValue;
    String(string value);
    bool compare(String* s);
    string getValue();
};


#endif //BOA_STRING_H
