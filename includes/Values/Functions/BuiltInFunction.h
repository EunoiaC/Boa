//
// Created by Preeti Thorat on 12/22/21.
//

#ifndef BOA_BUILTINFUNCTION_H
#define BOA_BUILTINFUNCTION_H

#include "BaseFunction.h"

template<typename T> class BuiltInFunction : public BaseFunction<T> {
public:
    BuiltInFunction<T>(string name, string fName, string fTxt);
};


#endif //BOA_BUILTINFUNCTION_H
