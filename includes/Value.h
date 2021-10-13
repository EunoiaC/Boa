//
// Created by Administrator on 10/12/2021.
//

#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>

using namespace std;

template <class valueType> class Value {
    string type;
    valueType val;
public:
    Value(valueType v, string t);
    bool compare(Value<valueType>* v);
};


#endif //BOA_VALUE_H
