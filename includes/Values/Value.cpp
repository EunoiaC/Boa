//
// Created by Administrator on 10/12/2021.
//
#include "Value.h"

template<class valueType>
Value<valueType>::Value(valueType v, string t, string f, string txt) : BaseValue(t, f, txt) {
    val = v;
    setContext(nullptr);
}

template<class valueType>
BaseValue *Value<valueType>::setContext(Context *c) {
    ctx = c;
    return this;
}

template<class valueType>
valueType Value<valueType>::getValue() {
    return val;
}

template<class valueType>
RuntimeResult *Value<valueType>::execute(vector<BaseValue *> args) {
    rtError = new RuntimeError(posStart, args.size() > 0 ? args[args.size() - 1]->posEnd : posEnd, line, fName, fTxt, "Cannot call this identifier", ctx);
}

template<class valueType>
void Value<valueType>::illegalOperation(BaseValue *other) {
    if (!other) other = this;
    rtError = new RuntimeError(posStart, other->posEnd, line, fName, fTxt, "Illegal operation", ctx);
}