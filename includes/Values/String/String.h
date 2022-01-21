//
// Created by Aadi Yadav on 10/15/21.
//
#ifndef BOA_STRING_H
#define BOA_STRING_H

#include "../Number/Number.h"

template<typename T> class String : public Value<T> {
public:
    T strValue;
    String<T>(string value, string f, string txt);
    string getValue() override;

    BaseValue * set(BaseValue * s) override;

    BaseValue * add(BaseValue * s) override;
    BaseValue * plusEquals(BaseValue * s) override;
    BaseValue * multiply(BaseValue * s) override;
    String<string> * copy() override;
    bool isTrue() override;
    int getLength() override;
    string toString() override;

    BaseValue *notted() override;
    BaseValue *contains(BaseValue *val) override;

    BaseValue *compGreaterThan(BaseValue *val) override;

    BaseValue *compLessThan(BaseValue *val) override;

    BaseValue *compGreaterThanEquals(BaseValue *val) override;

    BaseValue *compLessThanEquals(BaseValue *val) override;

    BaseValue *compNotEquals(BaseValue *val) override;

    BaseValue *compEquals(BaseValue *val) override;

    BaseValue *andedBy(BaseValue *s) override;

    BaseValue *oredBy(BaseValue *s) override;

    BaseValue *get(BaseValue *s) override;
};


#endif //BOA_STRIN