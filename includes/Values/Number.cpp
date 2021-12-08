//
// Created by Aadi Yadav on 10/20/21.
//

#include "Number.h"
#include "String.h"
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

BaseValue *Number::compGreaterThanEquals(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue >= ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::compLessThanEquals(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue <= ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::compGreaterThan(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue > ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::compLessThan(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue < ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::compEquals(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue == ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::compNotEquals(BaseValue *val) {
    if(val->type == T_NUM) {
        return (new Number(numValue != ((Number*) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::andedBy(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue and ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::oredBy(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue or ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

BaseValue *Number::notted() {
    return (new Number(numValue == 0 ? 1 : 0, fName, fTxt))->setContext(ctx);
}

Number *Number::multiply(BaseValue *s) {
    if(s->type == T_NUM) {
        return (new Number(numValue * ((Number*) s)->getValue(), fName, fTxt))->setContext(ctx);
    }
}

string Number::toString() {
    return to_string(numValue);
}

bool Number::isTrue() {
    return numValue != 0;
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