//
// Created by Preeti Thorat on 12/15/21.
//

#ifndef BOA_LIST_H
#define BOA_LIST_H

#include "../Number/Number.h" //Idk why the number class but its some weird compilation stuff
#include "../String/String.h"

template<typename T> class List : public Value<T> {
public:
    vector<BaseValue *> elements;
    List<T>(vector<BaseValue *> elements, string fName, string fTxt);
    BaseValue * add(BaseValue * other) override;
    BaseValue * multiply(BaseValue * other) override;
    BaseValue * subtract(BaseValue * other) override;
    BaseValue * plusEquals(BaseValue * other) override;
    BaseValue * minusEquals(BaseValue * other) override;
    BaseValue * to(BaseValue * other) override;
    BaseValue * compEquals(BaseValue * other) override;
    BaseValue * compNotEquals(BaseValue * other) override;
    int getLength() override;
    List<T> * copy() override;
    string toString() override;
    BaseValue *get(BaseValue *s) override;
    BaseValue *contains(BaseValue *s) override;

    BaseValue * oredBy(BaseValue * other) override;
    BaseValue * andedBy(BaseValue * other) override;
    BaseValue * notted() override;
    bool isTrue() override;
};


#endif //BOA_LIST_H
