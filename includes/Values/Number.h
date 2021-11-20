//
// Created by Preeti Thorat on 10/20/21.
//
#pragma once
#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H


class Number : public Value<double> {
public:
    int posStart, posEnd;
    double numValue;
    Number(double value);
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
    Number* setPos(int start, int end);
};


#endif //BOA_NUMBER_H
