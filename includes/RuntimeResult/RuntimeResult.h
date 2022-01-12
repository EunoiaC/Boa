//
// Created by Aadi Yadav on 11/24/21.
//

#ifndef BOA_RUNTIMERESULT_H
#define BOA_RUNTIMERESULT_H
#include "../Values/BaseValues/BaseValue.h"
#include "../Errors/Error.h"

class RuntimeResult {
public:
    BaseValue * funcReturnValue;
    bool loopContinue, loopBreak;
    void reset();
    BaseValue *value;
    Error *error;
    RuntimeResult();
    BaseValue *reg(RuntimeResult *result);
    RuntimeResult *success(BaseValue *value);
    RuntimeResult *successReturn(BaseValue *Value);
    RuntimeResult *successContinue();
    RuntimeResult *successBreak();
    bool shouldReturn();
    RuntimeResult *failure(Error *error);
};


#endif //BOA_RUNTIMERESULT_H
