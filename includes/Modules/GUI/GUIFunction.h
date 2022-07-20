//
// Created by Preeti Thorat on 6/22/22.
//

#ifndef BOA_GUIFUNCTION_H
#define BOA_GUIFUNCTION_H

#include "../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../Values/List/List.h"
#include "../../Values/Functions/Function.h"
#include "FLTK wrappers/Window/WindowObj.h"
#include "FLTK wrappers/Text/Text.h"
#include "FLTK wrappers/TextInput/TextInput.h"
#include "FLTK wrappers/Button/Button.h"

template<typename T> class GUIFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (GUIFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    GUIFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    GUIFunction<int> *copy() override;

    RuntimeResult * execute_makeWindow(Context * execCtx);
    RuntimeResult * execute_makeText(Context * execCtx);
    RuntimeResult * execute_makeTextInput(Context * execCtx);
    RuntimeResult * execute_makeButton(Context * execCtx);

    string toString() override;
};

#endif //BOA_GUIFUNCTION_H
