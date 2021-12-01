//
// Created by Aadi Yadav on 10/20/21.
//

#include "Number.h"
#include <math.h>

Number::Number(double value, string f, string txt) : Value<double>(value, T_NUM, f, txt) {
    numValue = value;
    rtError = nullptr;
    setContext(nullptr);
}

double Number::getValue() {
    return numValue;
}

Number *Number::setContext(Context *c) {
    ctx = c;
    return this;
}

Number *Number::divide(BaseValue *s) {
    Number *output;
    if(s->type == T_NUM){
        auto *num = (Number *) s;
        if (num->getValue() == 0) {
            //cout << "Error: Division by zero" << endl;
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    fName,
                    fTxt,
                    "Division by zero",
                    ctx
            );
        }
        output = (new Number(numValue / num->getValue(), fName, fTxt))->setContext(ctx);
        output->rtError = rtError;
        return output;
    }
}

Number *Number::multiply(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue * ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

Number *Number::add(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue + ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

Number *Number::subtract(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue - ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

Number *Number::power(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(pow(numValue, ((Number*) s)->getValue()), fName, fTxt))->setContext(ctx);
    }
}

Number *Number::mod(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(fmod(numValue, ((Number*) s)->getValue()), fName, fTxt))->setContext(ctx);
    }
}