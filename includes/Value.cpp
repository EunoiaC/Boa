//
// Created by Preeti Thorat on 10/6/21.
//

#include "Value.h"

Value::Value(int val, string valType) {
    val = value;
    type = valType;
}

bool Value::compare(Value v1, Value v2) {
    return v1.val == v2.val;
}

string Value::toString() {
    return to_string(val);
}