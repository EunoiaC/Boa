//
// Created by Administrator on 10/12/2021.
//
#pragma once
#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>

using namespace std;

class BaseValue {
public:
    BaseValue(string t, string f, string txt);
    /**
     * The object type of the value in a string form
     */
    string type;
    string fName, fTxt;
    int posStart, posEnd, line;


    virtual string toString();

    BaseValue *setPos(int start, int end, int line);

    virtual BaseValue *compGreaterThan(BaseValue *val);
    virtual BaseValue *compLessThan(BaseValue *val);
    virtual BaseValue *compGreaterThanEquals(BaseValue *val);
    virtual BaseValue *compLessThanEquals(BaseValue *val);
    virtual BaseValue *compNotEquals(BaseValue *val);
    virtual BaseValue *compEquals(BaseValue *val);

    virtual BaseValue* andedBy(BaseValue* s);
    virtual BaseValue* oredBy(BaseValue* s);
    virtual BaseValue *notted(BaseValue *s);

    virtual bool isTrue();

    virtual BaseValue* add(BaseValue* s);
    virtual BaseValue* subtract(BaseValue* s);
    virtual BaseValue* multiply(BaseValue* s);
    virtual BaseValue* divide(BaseValue* s);
    virtual BaseValue* power(BaseValue* s);
    virtual BaseValue* mod(BaseValue* s);
};

template<class valueType>
class Value : public BaseValue {
private:
    /**
     * The value as an instance of the object type
     */
    valueType val;
public:
    Value(valueType v, string t, string f, string txt);

    /**
     * @return The value of the valueType
     */
    valueType getValue();

    /**
     * @param v - A value object to compare to the value of this object
     * @return Returns a boolean dependant on if both values match each other
     */
    bool compare(Value<valueType> *v);
};


#endif //BOA_VALUE_H
