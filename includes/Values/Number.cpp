//
// Created by Preeti Thorat on 10/20/21.
//

#include "Number.h"

Number::Number(double value) : Value<double>(value, T_NUM){
    numValue = value;
}

bool Number::compare(Number* n) {
    return n->getValue() == numValue;
}

double Number::getValue() {
    return numValue;
}