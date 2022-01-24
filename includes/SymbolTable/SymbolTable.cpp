//
// Created by Aadi Yadav on 11/26/21.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    symbols = {};
    parent = nullptr;
}

SymbolTable::SymbolTable(SymbolTable *parent) {
    symbols = {};
    this->parent = parent;
}

string SymbolTable::toString() {
    string str = "";
    for (auto &symbol : symbols) {
        str += symbol.first + " " + symbol.second->toString() + "\n";
    }
    return str;
}

BaseValue *SymbolTable::get(string key) {
    BaseValue * val = nullptr;
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