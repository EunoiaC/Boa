//
// Created by Preeti Thorat on 10/20/21.
//

#include "Number.h"
#include <math.h>

Number::Number(double value, string f, string txt) : Value<double>(value, T_NUM, f, txt) {
    numValue = value;
    rtError = nullptr;
    setContext(nullptr);
}

bool Number::compare(Number *n) {
    return n->getValue() == numValue;
}

Number *Number::ceiling() {
    return new Number(::ceil(numValue), fName, fTxt);
}

Number *Number::floor() {
    return new Number(::floor(numValue), fName, fTxt);
}

double Number::getValue() {
    return numValue;
}

Number *Number::setContext(Context *c) {
    ctx = c;
    return this;
}

Number *Number::add(Number *s) {
    return (new Number(numValue + s->getValue(), fName, fTxt))->setContext(ctx);
}

Number *Number::divide(Number *s) {
    Number *output;
    if (s->getValue() == 0) {
        //cout << "Error: Division by zero" << endl;
        rtError = new RuntimeError(
                s->posStart,
                s->posEnd,
                s->line,
                fName,
                fTxt,
                "Division by zero",
                ctx
        );
    }
    output = (new Number(numValue / s->getValue(), fName, fTxt))->setContext(ctx);
    output->rtError = rtError;
    return output;
}

Number *Number::subtract(Number *s) {
    return (new Number(numValue - s->getValue(), fName, fTxt))->setContext(ctx);
}

Number *Number::multiply(Number *s) {
    return (new Number(numValue * s->getValue(), fName, fTxt))->setContext(ctx);
}

Number *Number::setPos(int start, int end, int line) {
    posEnd = end;
    posStart = start;
    this->line = line;
    return this;
}