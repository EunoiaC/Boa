//
// Created by Administrator on 10/12/2021.
//

#include "Value.h"
#include <utility>

static const string T_STRING = "STRING";
static const string T_NUM = "NUM";

BaseValue::BaseValue(string t, string f, string txt) {
    type = std::move(t);
    fName = std::move(f);
    fTxt = std::move(txt);
}

template<class valueType>
Value<valueType>::Value(valueType v, string t, string f, string txt) : BaseValue(t, f, txt) {
    val = v;
}

template<class valueType>
bool Value<valueType>::compare(Value<valueType>* v) {
    return (val == v->val) && (type == v->type);
}

template<class valueType>
valueType Value<valueType>::getValue() {
    return val;
}