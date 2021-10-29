//
// Created by Preeti Thorat on 10/20/21.
//
#pragma once
#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H


class Number : public Value<double> {
public:
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
};


#endif //BOA_NUMBER_H
