//
// Created by Administrator on 10/12/2021.
//

#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>
#include <vector>
#include "../RuntimeResult//RuntimeResult.h"
#include "../Errors/RuntimeError.h"
#include "BaseValue.h"

static const string T_STRING = "STRING";
static const string T_NUM = "NUM";
static const string T_FUNC = "FUNCTION";

template<class valueType>
class Value : public BaseValue {
public:
    /**
     * The value as an instance of the object type
     */
    valueType val;
    Context *ctx;
    Error *rtError;

    Value(valueType v, string t, string f, string txt);

    /**
     * @return The value of the valueType
     */
    valueType getValue();


    virtual BaseValue *setContext(Context *c);
    virtual RuntimeResult *execute(vector<BaseValue *> args);

    void illegalOperation(BaseValue *other);
};


#endif //BOA_VALUE_H
