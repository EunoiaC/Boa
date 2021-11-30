//
// Created by Aadi Yadav on 11/26/21.
//

#ifndef BOA_SYMBOLTABLE_H
#define BOA_SYMBOLTABLE_H
#include <map>

class SymbolTable {
public:
    SymbolTable();
    map<string, BaseValue *> symbols;
    SymbolTable *parent;
    BaseValue *get(string key);
    void set(string key, BaseValue *value);
    void remove(string key);
};


#endif //BOA_SYMBOLTABLE_H
