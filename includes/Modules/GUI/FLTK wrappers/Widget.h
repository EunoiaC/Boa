//
// Created by Preeti Thorat on 7/18/22.
//

#ifndef BOA_WIDGET_H
#define BOA_WIDGET_H

#include "../../../Values/String/String.h"
#include "../../../Values/Functions/Function.h"
#include "../../../Values/Number/Number.h"
#include <FL/Fl_Widget.H>

template<typename T>
class Widget : public Value<T> {
public:
    Number<double> *width, *height, *X, *Y;
    String<string> *text;
    Fl_Widget *widget;
    Function<int> *callback;
    Widget<int> * parent;

    Widget<int>();

    BaseValue *copy() override;

    string toString() override;
    virtual string widgetVal();
};

#endif //BOA_WIDGET_H
