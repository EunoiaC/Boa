//
// Created by Preeti Thorat on 3/21/22.
//

#ifndef BOA_JSON_H
#define BOA_JSON_H

#include "../../Values/BaseValues/Value.h"

template<typename T> class Json : public Value<T> {
    Json<int>();
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_JSON_H
