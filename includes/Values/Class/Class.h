//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_CLASS_H
#define BOA_CLASS_H

#include "../Number/Number.h"
#include "../Functions/Function.h"

template<typename T> class Class : public Value<T> {
public:
    Context * classContext;
    string name, fName, fTxt;
    vector<string> constructorArgs;
    vector<Function<int> *> methods;

    Class<T>(Context * context, string name, string fName, string fTxt, vector<string> constructorArgs, vector<Function<int> *> methods);
};


#endif //BOA_CLASS_H
