//
// Created by Preeti Thorat on 12/6/21.
//

#include "BaseValue.h"

BaseValue *BaseValue::setPos(int start, int end, int line) {
    this->posStart = start;
    this->posEnd = end;
    this->line = line;
    return this;
}

void BaseValue::setInSymbolTable(string key, BaseValue *value) {
}

BaseValue *BaseValue::getFromSymbolTable(string key) {
    return nullptr;
}

int BaseValue::getLength() {
    return 0;
}

BaseValue *BaseValue::copy() {
    BaseValue *newValue = new BaseValue(type, fName, fTxt);
    newValue->setPos(posStart, posEnd, line);
    return newValue;
}

BaseValue *BaseValue::plusEquals(BaseValue *other) {
    return nullptr;
}

BaseValue *BaseValue::minusEquals(BaseValue *other) {
    return nullptr;
}

BaseValue *BaseValue::get(BaseValue *val) {
    return nullptr;
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

BaseValue *BaseValue::notted() {
    return nullptr;
}

BaseValue *BaseValue::contains(BaseValue *s) {
    return nullptr;
}

bool BaseValue::isTrue() {
    return false;
}

string BaseValue::toString() {
    return type;
}

BaseValue *BaseValue::compSort(BaseValue *val) {
    return nullptr;
}

BaseValue::BaseValue(string t, string f, string txt) {
    type = t;
    fName = f;
    fTxt = txt;
}