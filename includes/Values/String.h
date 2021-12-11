//
// Created by Aadi Yadav on 10/15/21.
//
#ifndef BOA_STRING_H
#define BOA_STRING_H

#include "Value.cpp"
#include "Number.h"


class String : public Value<string> {
public:
    string strValue;
    String(string value, string f, string txt);
    string getValue();

    BaseValue * add(BaseValue * s) override;
    BaseValue * multiply(BaseValue * s) override;
    bool isTrue() override;
    string toString() override;

    BaseValue *notted() override;

    BaseValue *compGreaterThan(BaseValue *val) override;

    BaseValue *compLessThan(BaseValue *val) override;

    BaseValue *compGreaterThanEquals(BaseValue *val) override;

    BaseValue *compLessThanEquals(BaseValue *val) override;

    BaseValue *compNotEquals(BaseValue *val) override;

    BaseValue *compEquals(BaseValue *val) override;

    BaseValue *andedBy(BaseValue *s) override;

    BaseValue *oredBy(BaseValue *s) override;
};


#endif //BOA_STRING_H