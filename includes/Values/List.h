//
// Created by Preeti Thorat on 12/15/21.
//

#ifndef BOA_LIST_H
#define BOA_LIST_H

#include "Number.h" //Idk why the number class but its some weird compilation shit

template<typename T> class List : public Value<T> {
public:
    vector<BaseValue *> elements;
    List<T>(vector<BaseValue *> elements, string fName, string fTxt);
    BaseValue * add(BaseValue * other) override;
    BaseValue * multiply(BaseValue * other) override;
    List<T> * copy();
    string toString() override;
};


#endif //BOA_LIST_H
