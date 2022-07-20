//
// Created by Preeti Thorat on 7/19/22.
//

#ifndef BOA_BUTTON_H
#define BOA_BUTTON_H


#include "../Widget.h"
#include <FL/Fl_Button.H>

template<typename T>
class Button : public Widget<T> {
public:
    Number<double> *width, *height, *X, *Y;
    String<string> *text;
    Fl_Button *btn;

    Button<int>(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height, String<string> *text);

    BaseValue *copy() override;

    string toString() override;
};


#endif //BOA_BUTTON_H
