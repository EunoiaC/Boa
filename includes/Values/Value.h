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
    BaseValue * setPos(int start, int end, int line);
};

template <class valueType> class Value : public BaseValue{
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
    bool compare(Value<valueType>* v);
};


#endif //BOA_VALUE_H
