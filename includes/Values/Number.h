//
// Created by Preeti Thorat on 10/20/21.
//
#pragma once
#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H
#include "../Errors/RuntimeError.cpp"


class Number : public Value<double> {
public:
    Error *rtError;
    Context *ctx;
    int posStart, posEnd, line;
    double numValue;
    Number(double value, string f, string txt);
    bool compare(Number* s);
    double getValue();
    /**
     * @return The value of this number rounded up
     */
    Number* ceiling();
    /**
     * @return The value of this number rounded down
     */
    Number* floor();
    Number* add(Number* s);
    Number* subtract(Number* s);
    Number* multiply(Number* s);
    Number* divide(Number* s);
    Number* setPos(int start, int end, int line);
    Number * setContext(Context *c);
};


#endif //BOA_NUMBER_H
