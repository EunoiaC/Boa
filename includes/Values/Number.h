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

    Number *add(BaseValue *s) override;

    Number *subtract(BaseValue *s) override;

    Number *multiply(BaseValue *s) override;

    Number *divide(BaseValue *s) override;

    Number *power(BaseValue *s) override;

    Number *mod(BaseValue *s) override;

    BaseValue *notted();

    bool isTrue() override;

    BaseValue *compGreaterThan(BaseValue *val) override;

    BaseValue *compLessThan(BaseValue *val) override;

    BaseValue *compGreaterThanEquals(BaseValue *val) override;

    BaseValue *compLessThanEquals(BaseValue *val) override;

    BaseValue *compNotEquals(BaseValue *val) override;

    BaseValue *compEquals(BaseValue *val) override;

    BaseValue *andedBy(BaseValue *s) override;

    BaseValue *oredBy(BaseValue *s) override;

    string toString() override;

    Number *setContext(Context *c);
};


#endif //BOA_NUMBER_H
