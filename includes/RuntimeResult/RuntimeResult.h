//
// Created by Aadi Yadav on 11/24/21.
//

#ifndef BOA_RUNTIMERESULT_H
#define BOA_RUNTIMERESULT_H
#include "../Values/Value.h"
#include "../Errors/Error.h"

class RuntimeResult {
public:
    BaseValue *value;
    Error *error;
    RuntimeResult();
    BaseValue *reg(RuntimeResult *result);
    RuntimeResult *success(BaseValue *value);
    RuntimeResult *failure(Error *error);
};


#endif //BOA_RUNTIMERESULT_H
