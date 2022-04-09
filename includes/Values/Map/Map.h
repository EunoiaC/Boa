//
// Created by Preeti Thorat on 12/18/21.
//

#ifndef BOA_MAP_H
#define BOA_MAP_H

#include "../Number/Number.h"
#include "../List/List.h"
#include "../String/String.h"
#include "../Functions/Function.h"

template<typename T> class Map : public Value<T> {
public:
    map<BaseValue*, BaseValue*> dict;
    Map<T>(map<BaseValue*, BaseValue*> dict, string fName, string fTxt);
    BaseValue* replace(BaseValue* old, BaseValue* newVal);
    BaseValue* get(BaseValue* key) override;
    BaseValue* add(BaseValue* keyAndVal) override;
    BaseValue* subtract(BaseValue* key) override;
    BaseValue* plusEquals(BaseValue* key) override;
    BaseValue* minusEquals(BaseValue* key) override;
    BaseValue* compEquals(BaseValue* other) override;
    BaseValue* compNotEquals(BaseValue* other) override;
    Number<double>* keyExists(BaseValue* key);
    int getLength() override;
    string toString() override;
    Map<T> * copy() override;

    BaseValue * oredBy(BaseValue * other) override;
    BaseValue * andedBy(BaseValue * other) override;
    BaseValue * notted() override;
    bool isTrue() override;
};


#endif //BOA_MAP_H
