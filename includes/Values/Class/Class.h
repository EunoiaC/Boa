//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_CLASS_H
#define BOA_CLASS_H

#include "../Number/Number.h"
#include "../Functions/Function.h"
#include "ClassFunction.h"
#include "../../Token/Token.h"
#include "../Map.h"
#include "../List/List.h"

template<typename T> class Class : public Value<T> {
public:
    string name, fName, fTxt;
    SymbolTable * instantiatedVariables;
    vector<Token<string> *> constructorArgs;
    map<string, BaseValue *> defaultArgs;
    vector<Node *> members;
    Node * superClass;
    RuntimeResult *execute(vector<BaseValue *> args) override;
    vector<string> lines;
    Class<int> *parent;
    BaseValue * getFromSymbolTable(string name) override;

    string toString() override;

    BaseValue * copy() override;
    RuntimeResult * checkArgs(vector<BaseValue *> args, vector<string> argNames);
    void populateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);
    void setParentClass(Class<int> * parent);
    RuntimeResult * checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);

    Class<T>(string name, string fName, string fTxt, vector<Token<string> *> constructorArgs, map<string, BaseValue *> defaultArgs, vector<Node *> members, Node * superClass, vector<string> lines);
};


#endif //BOA_CLASS_H
