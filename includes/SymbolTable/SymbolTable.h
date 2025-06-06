//
// Created by Aadi Yadav on 11/26/21.
//

#ifndef BOA_SYMBOLTABLE_H
#define BOA_SYMBOLTABLE_H
#include <map>
#include "../Values/BaseValues/BaseValue.h"
#include <string>
using namespace std;

class SymbolTable {
public:
    SymbolTable();
    SymbolTable(SymbolTable *parent);
    map<string, BaseValue *> symbols;
    SymbolTable *parent;
    string toString();
    BaseValue *get(string key);
    void set(string key, BaseValue *value);
    void remove(string key);
};


#endif //BOA_SYMBOLTABLE_H
