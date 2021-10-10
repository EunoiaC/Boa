//
// Created by Preeti Thorat on 10/6/21.
//

#ifndef BOA_TOKEN_H
#define BOA_TOKEN_H

#include "Value.h"
#include <string>

using namespace std;

class Token {
    Value val;
    string type;
public:
    Token(Value value, string valType);
    string toString();
};


#endif //BOA_TOKEN_H
