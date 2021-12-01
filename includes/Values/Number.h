//
// Created by Aadi Yadav on 10/20/21.
//
#pragma once
#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H
#include "../Errors/RuntimeError.cpp"


class Number : public Value<double> {
public:
    Error *rtError;
    Context *ctx;
    double numValue;
    Number(double value, string f, string txt);
    double getValue();
    Number* add(BaseValue* s);
    Number* subtract(BaseValue* s);
    Number* multiply(BaseValue* s);
    Number* divide(BaseValue* s);
    Number* power(BaseValue* s);
    Number* mod(BaseValue* s);
    Number * setContext(Context *c);
};


#endif //BOA_NUMBER_H
