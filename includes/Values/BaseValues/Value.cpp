//
// Created by Administrator on 10/12/2021.
//
#include <iostream>
#include "Value.h"

template<class valueType>
Value<valueType>::Value(valueType v, TOK_TYPE t, string f, string txt) : BaseValue(t, f, txt) {
    val = v;
    setContext(nullptr);
    symbolTable = new SymbolTable();
    rtError = nullptr;
}

template<class valueType>
BaseValue *Value<valueType>::compSort(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
Value<valueType>::~Value<valueType>() {
    delete symbolTable;
    delete rtError;
    delete ctx;
}

template<class valueType>
void Value<valueType>::setInSymbolTable(string name, BaseValue *newObj) {
    symbolTable->set(name, newObj);
}

template<class valueType>
BaseValue *Value<valueType>::getFromSymbolTable(string name) {
    return symbolTable->get(name);
}

template<class valueType>
BaseValue *Value<valueType>::setContext(Context *c) {
    ctx = c;
    return this;
}

template<class valueType>
BaseValue *Value<valueType>::plusEquals(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::minusEquals(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::to(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue * Value<valueType>::contains(BaseValue *s) {
    unsupportedOperation(s);
}

template<class valueType>
valueType Value<valueType>::getValue() {
    return val;
}

template<class valueType>
RuntimeResult *Value<valueType>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    rtError = new RuntimeError(posStart, args.size() > 0 ? args[args.size() - 1]->posEnd : posEnd, line, fName, fTxt, "Cannot call this identifier", ctx);
}

template<class valueType>
RuntimeResult *Value<valueType>::execute(vector<BaseValue *> args) {
    rtError = new RuntimeError(posStart, args.size() > 0 ? args[args.size() - 1]->posEnd : posEnd, line, fName, fTxt, "Cannot call this identifier", ctx);
}

template<class valueType>
void Value<valueType>::illegalOperation(BaseValue *other) {
    if (!other) other = this;
    rtError = new RuntimeError(other->posStart, other->posEnd, other->line, other->fName, other->fTxt, "Illegal operation, expected type " + type, ctx);
}

template<class valueType>
void Value<valueType>::illegalOperation(BaseValue *other, string type) {
    if (!other) other = this;
    rtError = new RuntimeError(other->posStart, other->posEnd, other->line, other->fName, other->fTxt, "Illegal operation, expected type " + type, ctx);
}

template<class valueType>
void Value<valueType>::unsupportedOperation(BaseValue *other) {
    if (!other) other = this;
    rtError = new RuntimeError(posStart, other->posEnd, line, other->fName, other->fTxt, "Type " + to_string(type) + " does not allow this operation.", ctx);
}

template<class valueType>
BaseValue *Value<valueType>::add(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::subtract(BaseValue * other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::multiply(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::divide(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::power(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
BaseValue *Value<valueType>::mod(BaseValue *other) {
    unsupportedOperation(other);
}

template<class valueType>
bool Value<valueType>::isTrue() {
    unsupportedOperation(this);
}

template<class valueType>
BaseValue *Value<valueType>::andedBy(BaseValue *s) {
    unsupportedOperation(s);
}

template<class valueType>
BaseValue *Value<valueType>::oredBy(BaseValue *s) {
    unsupportedOperation(s);
}

template<class valueType>
BaseValue *Value<valueType>::notted() {
    unsupportedOperation(this);
}

template<class valueType>
BaseValue *Value<valueType>::compEquals(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
BaseValue *Value<valueType>::compNotEquals(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
BaseValue *Value<valueType>::compGreaterThan(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
BaseValue *Value<valueType>::compGreaterThanEquals(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
BaseValue *Value<valueType>::compLessThan(BaseValue *val) {
    unsupportedOperation(val);
}

template<class valueType>
BaseValue *Value<valueType>::compLessThanEquals(BaseValue *val) {
    unsupportedOperation(val);
}