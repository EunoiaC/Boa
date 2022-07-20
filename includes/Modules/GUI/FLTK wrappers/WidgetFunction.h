//
// Created by Preeti Thorat on 7/18/22.
//

#ifndef BOA_WIDGETFUNCTION_H
#define BOA_WIDGETFUNCTION_H

#include "../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../Values/List/List.h"
#include "../../../Values/Functions/Function.h"
#include "Widget.h"

template<typename T> class WidgetFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (WidgetFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Widget<int> * widget;
    WidgetFunction<T>(Widget<int> * widget, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    WidgetFunction<int> *copy() override;

    RuntimeResult * execute_color(Context * execCtx);
    RuntimeResult * execute_box(Context * execCtx);
    RuntimeResult * execute_setCallback(Context * execCtx);
    RuntimeResult * execute_hide(Context * execCtx);
    RuntimeResult * execute_redraw(Context * execCtx);
    RuntimeResult * execute_getValue(Context * execCtx);

    string toString() override;
};


#endif //BOA_WIDGETFUNCTION_H
