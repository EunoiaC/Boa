//
// Created by Preeti Thorat on 3/12/22.
//

#ifndef BOA_REQUESTS_H
#define BOA_REQUESTS_H

#include "../../Values/BaseValues/Value.h"

template<typename T> class Requests : public Value<T> {
public:
    Requests<int>();
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_REQUESTS_H
