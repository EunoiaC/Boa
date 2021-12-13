//
// Created by Preeti Thorat on 12/12/21.
//

#ifndef BOA_LIST_H
#define BOA_LIST_H

#include "Value.h"

class List : public Value<vector<BaseValue*>> {
public:
    vector<BaseValue*> elems;
    List(const vector<BaseValue*>& elems, string f, string txt);

    BaseValue * add(BaseValue * other) ;
    BaseValue * subtract(BaseValue * other) ;
    List * copy();

    string toString() ;
};


#endif //BOA_LIST_H
