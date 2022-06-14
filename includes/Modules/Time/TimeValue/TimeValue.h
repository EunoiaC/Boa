//
// Created by Preeti Thorat on 6/13/22.
//

#ifndef BOA_TIMEVALUE_H
#define BOA_TIMEVALUE_H


#include "../../../Values/BaseValues/Value.h"
#include "../../../Values/String/String.h"
#include <ctime>

template <typename T> class TimeValue : public Value<T> {
public:
    time_t tVal;
    TimeValue<int>(time_t tVal);
    BaseValue * copy() override;
    string toString() override;
    BaseValue * subtract(BaseValue * other);
};

#endif //BOA_TIMEVALUE_H
