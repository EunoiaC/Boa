//
// Created by Aadi Yadav on 11/24/21.
//

#include "RuntimeResult.h"

RuntimeResult::RuntimeResult() {
    value = nullptr;
    error = nullptr;
}

BaseValue *RuntimeResult::reg(RuntimeResult *result) {
    if (result->error) error = result->error;
    return result->value;
}

RuntimeResult *RuntimeResult::success(BaseValue *value) {
    this->value = value;
    return this;
}

RuntimeResult *RuntimeResult::failure(Error *error) {
    this->error = error;
    return this;
}
