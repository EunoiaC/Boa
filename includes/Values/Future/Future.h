//
// Created by Preeti Thorat on 4/2/22.
//

#ifndef BOA_FUTURE_H
#define BOA_FUTURE_H

#include "../../Errors/RuntimeError.h"
#include "../BaseValues/Value.h"
#include <future>

template<typename T> class Future : public Value<T> {
public:
    Context *ctx;
    shared_future<RuntimeResult *> promise;

    Future<T>(shared_future<RuntimeResult *> value, string f, string txt);

    shared_future<RuntimeResult *> getValue() override;

    string toString() override;

    Future<shared_future<RuntimeResult *>> * copy() override;
};


#endif //BOA_FUTURE_H
