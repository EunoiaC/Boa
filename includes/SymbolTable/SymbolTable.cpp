//
// Created by Aadi Yadav on 11/26/21.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    parent = nullptr;
}

BaseValue *SymbolTable::get(string key) {
    BaseValue * val;
    if(symbols.count(key)){
        val = symbols[key];
    }
    if (val == nullptr && parent) {
        return parent->get(key);
    }
    return val;
}

void SymbolTable::set(string key, BaseValue *value) {
    symbols[key] = value;
}

void SymbolTable::remove(string key) {
    delete symbols[key];
}