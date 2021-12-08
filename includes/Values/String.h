//
// Created by Aadi Yadav on 10/15/21.
//
#ifndef BOA_STRING_H
#define BOA_STRING_H

#include "Value.cpp"


class String : public Value<string> {
public:
    string strValue;
    String(string value, string f, string txt);
    bool compare(String* s);
    string getValue();
};


#endif //BOA_STRING_H