//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_CLASS_H
#define BOA_CLASS_H

#include "../Number/Number.h"
#include "../Functions/Function.h"
#include "ClassFunction.h"
#include "../../Token/Token.h"
#include "../Map/Map.h"
#include "../List/List.h"

template<typename T> class Class : public Value<T> {
public:
    string name, fName, fTxt;
    SymbolTable * instantiatedVariables;
    vector<Token<string> *> constructorArgs;
    map<string, BaseValue *> defaultArgs;
    vector<Node *> members;
    Node * superClass;
    RuntimeResult *execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) override;
    vector<string> lines;
    Class<int> *parent;
    BaseValue * getFromSymbolTable(string name) override;

    string toString() override;

    BaseValue * copy() override;
    RuntimeResult * checkArgs(vector<BaseValue *> args, vector<string> argNames, map<string, BaseValue *> kwargs);
    void populateArgs(vector<BaseValue *> args, vector<string> argNames, map<string, BaseValue *> kwargs, Context * context);
    void setParentClass(Class<int> * parent);
    RuntimeResult * checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames, map<string, BaseValue *> kwargs, Context * context);
    Token<string> * classNameTok;
    Class<T>(Token<string> * classNameTok, string fName, string fTxt, vector<Token<string> *> constructorArgs, map<string, BaseValue *> defaultArgs, vector<Node *> members, Node * superClass, vector<string> lines);
};


#endif //BOA_CLASS_H
