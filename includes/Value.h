//
// Created by Preeti Thorat on 10/6/21.
//

#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>

using namespace std;

union Any{
    string;
    vector<Any>;
    list<Any>;
    int;
};

class Value {
    Any val;
    string type;
public:
    Value(Any value, string valType);
    bool compare(Value v1, Value v2);
    string toString();
};


#endif //BOA_VALUE_H
