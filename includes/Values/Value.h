//
// Created by Administrator on 10/12/2021.
//

#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>
#include "BaseValue.h"

using namespace std;

static const string T_STRING = "STRING";
static const string T_NUM = "NUM";

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
};


#endif //BOA_VALUE_H
