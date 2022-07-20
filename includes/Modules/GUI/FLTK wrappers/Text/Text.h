//
// Created by Preeti Thorat on 7/9/22.
//

#ifndef BOA_TEXT_H
#define BOA_TEXT_H


#include "../Widget.h"
#include <FL/Fl_Text_Display.H>

template<typename T>
class Text : public Widget<T> {
public:
    Number<double> *width, *height, *X, *Y;
    String<string> *text;
    Fl_Text_Display *display;
    Fl_Text_Buffer buffer = Fl_Text_Buffer();

    Text<int>(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height, String<string> *text);

    BaseValue *copy() override;

    string toString() override;
};


#endif //BOA_TEXT_H
