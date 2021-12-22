//
// Created by Aadi Yadav on 10/20/21.
//

#ifndef BOA_NUMBER_H
#define BOA_NUMBER_H

#include "../Errors/RuntimeError.h"
#include "BaseValues/Value.cpp"

template<typename T> class Number : public Value<T> {
public:
    Context *ctx;
    double numValue;

    Number<T>(double value, string f, string txt);

    double getValue() override;

    Number *add(BaseValue *s) override;

    Number *plusEquals(BaseValue *s) override;
    Number *minusEquals(BaseValue *s) override;

    Number *subtract(BaseValue *s) override;

    Number *multiply(BaseValue *s) override;

    Number *divide(BaseValue *s) override;

    Number *power(BaseValue *s) override;

    Number *mod(BaseValue *s) override;

    bool isTrue() override;

    BaseValue *notted() override;

    BaseValue *compGreaterThan(BaseValue *val) override;

    BaseValue *compLessThan(BaseValue *val) override;

    BaseValue *compGreaterThanEquals(BaseValue *val) override;

    BaseValue *compLessThanEquals(BaseValue *val) override;

    BaseValue *compNotEquals(BaseValue *val) override;

    BaseValue *compEquals(BaseValue *val) override;

    BaseValue *andedBy(BaseValue *s) override;

    BaseValue *oredBy(BaseValue *s) override;

    string toString() override;
};


#endif //BOA_NUMBER_H
