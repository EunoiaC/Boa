//
// Created by Administrator on 10/12/2021.
//

#include "Value.h"
#include <utility>

static const string T_STRING = "STRING";
static const string T_NUM = "NUM";

BaseValue::BaseValue(string t) {
    type = t;
}

template<class valueType>
Value<valueType>::Value(valueType v, string t) : BaseValue(t) {
    val = v;
    type = std::move(t);
}

template<class valueType>
bool Value<valueType>::compare(Value<valueType>* v) {
    return (val == v->val) && (type == v->type);
}

template<class valueType>
valueType Value<valueType>::getValue() {
    return val;
}