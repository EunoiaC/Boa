//
// Created by Administrator on 10/12/2021.
//

#include "Value.h"

BaseValue *BaseValue::setPos(int start, int end, int line) {
    this->posStart = start;
    this->posEnd = end;
    this->line = line;
    return this;
}

BaseValue *BaseValue::compGreaterThan(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::compEquals(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::compLessThan(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::compGreaterThanEquals(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::compLessThanEquals(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::compNotEquals(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::add(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::subtract(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::multiply(BaseValue *s) {
    return nullptr;
}

BaseValue *BaseValue::divide(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::power(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::mod(BaseValue *val) {
    return nullptr;
}

BaseValue *BaseValue::andedBy(BaseValue *s) {
    return nullptr;
}

BaseValue *BaseValue::oredBy(BaseValue *s) {
    return nullptr;
}

BaseValue *BaseValue::notted(BaseValue *s) {
    return nullptr;
}

bool BaseValue::isTrue() {
    return false;
}

string BaseValue::toString() {
    return type;
}

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
valueType Value<valueType>::getValue() {
    return val;
}