//
// Created by Preeti Thorat on 4/16/22.
//

#ifndef BOA_TIME_H
#define BOA_TIME_H


#include "../../Values/BaseValues/Value.h"

template<typename T> class Time : public Value<T> {
public:
    Time<int>();
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_TIME_H
