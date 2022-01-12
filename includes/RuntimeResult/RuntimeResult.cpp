//
// Created by Aadi Yadav on 11/24/21.
//

#include "RuntimeResult.h"

RuntimeResult::RuntimeResult() {
    reset();
}

void RuntimeResult::reset() {
    value = nullptr;
    error = nullptr;
    funcReturnValue = nullptr;
    loopBreak = false;
    loopContinue = false;
}

BaseValue *RuntimeResult::reg(RuntimeResult *result) {
    if (result->error) error = result->error;
    funcReturnValue = result->funcReturnValue;
    loopBreak = result->loopBreak;
    loopContinue = result->loopContinue;
    return result->value;
}

RuntimeResult *RuntimeResult::success(BaseValue *value) {
    reset();
    this->value = value;
    return this;
}

RuntimeResult *RuntimeResult::successReturn(BaseValue *value) {
    reset();
    this->value = value;
    return this;
}

RuntimeResult *RuntimeResult::successContinue() {
    reset();
    loopContinue = true;
    return this;
}

RuntimeResult *RuntimeResult::successBreak() {
    reset();
    loopBreak = true;
    return this;
}

bool RuntimeResult::shouldReturn() {
    return (
            error or
            funcReturnValue or
            loopContinue or
            loopBreak
    );
}

RuntimeResult *RuntimeResult::failure(Error *error) {
    reset();
    this->error = error;
    return this;
}
