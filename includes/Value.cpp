//
// Created by Administrator on 10/12/2021.
//

#include "Value.h"

template<class valueType>
Value<valueType>::Value(valueType v, string t) {
    val = v;
    type = t;
}

template<class valueType>
bool Value<valueType>::compare(Value<valueType>* v) {
    return (val == v->val) && (type == v->type);
}