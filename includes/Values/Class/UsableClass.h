//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_USABLECLASS_H
#define BOA_USABLECLASS_H

#include "../../Values/BaseValues/Value.h"
#include "ClassFunction.h"
#include "../../Values/Functions/BuiltInFunction.h"
#include "../../Modules/Random/Random.h"
#include "../../Token/Token.h"

template<typename T> class UsableClass : public Value<T> {
public:
    BuiltInFunction<int> * print;
    BuiltInFunction<int> * input;
    BuiltInFunction<int> * toNum;
    BuiltInFunction<int> * lenOf;
    BuiltInFunction<int> * toStr;
    BuiltInFunction<int> * instanceOf;
    BuiltInFunction<int> * eval;
    BuiltInFunction<int> * _rename;
    BuiltInFunction<int> * getSymbolTable;
    Random<int> * _random;
    Context * generateClassContext(string name);
    vector<string> lines;
    map<string, BaseValue *> members;
    Token<string> * classNameTok;
    Error * funcNotFound(string funcName);

    string className, asString;
    UsableClass<int>(string f, string txt, Token<string> * classNameTok, vector<Node *> members, Context * c, Context * parent, Node * superClass, vector<string> lines);
    BaseValue * copy() override;
    string toString() override;
    BaseValue * getFromSymbolTable(string key) override;
    void setInSymbolTable(string key, BaseValue * newObj) override;

    bool isTrue() override;

    BaseValue * compLessThan(BaseValue * other) override;
    BaseValue * compGreaterThan(BaseValue * other) override;
    BaseValue * compLessThanEquals(BaseValue * other) override;
    BaseValue * compGreaterThanEquals(BaseValue * other) override;

    BaseValue * compSort(BaseValue * other) override;
};


#endif //BOA_USABLECLASS_H
