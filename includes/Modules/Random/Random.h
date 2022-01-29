//
// Created by Preeti Thorat on 1/28/22.
//

#ifndef BOA_RANDOM_H
#define BOA_RANDOM_H

#include "../../Values/BaseValues/Value.h"

template<typename T> class Random : public Value<T> {
public:
    Random<int>(string f, string txt);
    string toString() override;
};


#endif //BOA_RANDOM_H
