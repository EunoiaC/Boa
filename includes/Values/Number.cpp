//
// Created by Aadi Yadav on 10/20/21.
//

#include "Number.h"
#include "String.h"
#include "String.h"
#include <math.h>


template<>
Number<double>::Number(double value, string f, string txt) : Value<double>(value, T_NUM, f, txt) {
    numValue = value;
    rtError = nullptr;
}

template<>
double Number<double>::getValue() {
    return numValue;
}

template<>
Number<double> *Number<double>::copy() {
    Number<double> *val = new Number<double>(numValue, fName, fTxt);
    val->setPos(posStart, posEnd, line);
    val->setContext(ctx);
    return val;
}

template<>
Number<double> *Number<double>::divide(BaseValue *s) {
    Number<double> *output;
    if (s->type == T_NUM) {
        auto *num = (Number<double> *) s;
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
        output = dynamic_cast<Number<double> *>((new Number<double>(numValue / num->getValue(), fName,
                                                                    fTxt))->setContext(ctx));
        output->rtError = rtError;
        return output;
    }
    illegalOperation(s);
}

template<>
BaseValue *Number<double>::compGreaterThanEquals(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number<double>(numValue >= ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compLessThanEquals(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number<double>(numValue <= ((Number<double> *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compGreaterThan(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number<double>(numValue > ((Number<double> *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compLessThan(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number(numValue < ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compEquals(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number(numValue == ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compNotEquals(BaseValue *val) {
    if (val->type == T_NUM) {
        return (new Number<double>(numValue != ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(1, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::andedBy(BaseValue *s) {
    return (new Number<double>(numValue or s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::oredBy(BaseValue *s) {
    return (new Number<double>(numValue or s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::notted() {
    return (new Number<double>(numValue == 0 ? 1 : 0, fName, fTxt))->setContext(ctx);
}

template<>
Number<double> *Number<double>::multiply(BaseValue *s) {
    if (s->type == T_NUM) {
        return dynamic_cast<Number<double> *>((new Number<double>(numValue * ((Number *) s)->getValue(), fName,
                                                                  fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
string Number<double>::toString() {
    return to_string(numValue);
}

template<>
bool Number<double>::isTrue() {
    return numValue != 0;
}

template<>
BaseValue *Number<double>::add(BaseValue *s) {
    if (s->type == T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(numValue + ((Number *) s)->getValue(), fName,
                                                          fTxt))->setContext(
                ctx));
    } else if (s->type == T_STRING) {
        return (new String<string>(toString() + ((String<string> *) s)->getValue(), fName, fTxt))->setContext(
                ctx);
    }
    illegalOperation(s);
}

template<>
BaseValue *Number<double>::set(BaseValue *s) {
    numValue = ((Number *) s)->getValue();
    return this;
}

template<>
Number<double> *Number<double>::plusEquals(BaseValue *s) {
    if (s->type == T_NUM) {
        numValue += ((Number *) s)->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::minusEquals(BaseValue *s) {
    if (s->type == T_NUM) {
        numValue -= ((Number *) s)->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::subtract(BaseValue *s) {
    if (s->type == T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(numValue - ((Number *) s)->getValue(), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::power(BaseValue *s) {
    if (s->type == T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(pow(numValue, ((Number *) s)->getValue()), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::mod(BaseValue *s) {
    if (s->type == T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(fmod(numValue, ((Number *) s)->getValue()), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}