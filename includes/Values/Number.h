//
// Created by Aadi Yadav on 10/20/21.
//

#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H

#include "../Errors/RuntimeError.h"
#include "Value.h"

class Number : public Value<double> {
public:
    Error *rtError;
    Context *ctx;
    double numValue;

    Number(double value, string f, string txt);

    double getValue();

    Number *add(BaseValue *s);

    Number *subtract(BaseValue *s);

    Number *multiply(BaseValue *s);

    Number *divide(BaseValue *s);

    Number *power(BaseValue *s);

    Number *mod(BaseValue *s);

    BaseValue *notted();

    bool isTrue();

    BaseValue *compGreaterThan(BaseValue *val);

    BaseValue *compLessThan(BaseValue *val);

    BaseValue *compGreaterThanEquals(BaseValue *val);

    BaseValue *compLessThanEquals(BaseValue *val);

    BaseValue *compNotEquals(BaseValue *val);

    BaseValue *compEquals(BaseValue *val);

    BaseValue *andedBy(BaseValue *s);

    BaseValue *oredBy(BaseValue *s);

    string toString() override;

    Number *setContext(Context *c);
};


#endif //BOA_NUMBER_H
