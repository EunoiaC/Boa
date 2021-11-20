//
// Created by Preeti Thorat on 10/20/21.
//

#include "Number.h"
#include <math.h>

Number::Number(double value) : Value<double>(value, T_NUM){
    numValue = value;
}

bool Number::compare(Number* n) {
    return n->getValue() == numValue;
}

Number* Number::ceiling() {
    return new Number(::ceil(numValue));
}

Number* Number::floor() {
    return new Number(::floor(numValue));
}

double Number::getValue() {
    return numValue;
}

Number *Number::add(Number *s) {
    return new Number(numValue + s->getValue());
}

Number *Number::divide(Number *s) {
    return new Number(numValue / s->getValue());
}

Number *Number::subtract(Number *s) {
    return new Number(numValue - s->getValue());
}

Number *Number::multiply(Number *s) {
    return new Number(numValue * s->getValue());
}

Number *Number::setPos(int start, int end) {
    posEnd = end;
    posStart = start;
    return this;
}