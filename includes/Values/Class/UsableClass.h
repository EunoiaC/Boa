//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_USABLECLASS_H
#define BOA_USABLECLASS_H

#include "../../Values/BaseValues/Value.h"
#include "ClassFunction.h"

template<typename T> class UsableClass : public Value<T> {
public:
    string className;
    UsableClass<int>(string f, string txt, string className, vector<ClassFunction<int> *> methods, Context * context);
    BaseValue * copy() override;
    string toString() override;
    BaseValue * getFromSymbolTable(string key) override;
};


#endif //BOA_USABLECLASS_H
