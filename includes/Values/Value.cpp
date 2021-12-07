//
// Created by Administrator on 10/12/2021.
//

#include "Value.h"

template<class valueType>
Value<valueType>::Value(valueType v, string t, string f, string txt) : BaseValue(t, f, txt) {
    val = v;
}

template<class valueType>
valueType Value<valueType>::getValue() {
    return val;
}