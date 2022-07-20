//
// Created by Preeti Thorat on 7/10/22.
//

#ifndef BOA_TEXTINPUT_H
#define BOA_TEXTINPUT_H


#include "../Widget.h"
#include "../../../../Values/Functions/Function.h"
#include <FL/Fl_Input.H>

template<typename T>
class TextInput : public Widget<T> {
public:
    Number<double> *width, *height, *X, *Y;
    String<string> *text;
    Fl_Input *input;

    TextInput<int>(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height, String<string> *text);

    BaseValue *copy() override;

    string toString() override;
    string widgetVal() override;
};


#endif //BOA_TEXTINPUT_H
