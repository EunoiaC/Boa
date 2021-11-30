//
// Created by Aadi Yadav on 11/24/21.
//

#ifndef BOA_RUNTIMERESULT_H
#define BOA_RUNTIMERESULT_H


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
