//
// Created by Preeti Thorat on 6/21/22.
//
#ifndef BOA_WINDOWOBJ_H
#define BOA_WINDOWOBJ_H

#include "../Widget.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>

template<typename T>
class WindowObj : public Widget<T> {
public:
    Number<double> *width, *height;
    String<string> *title;
    Fl_Window *window;
    vector<Widget<int> *> widgets;

    WindowObj<int>(Number<double> *width, Number<double> *height, String<string> *title);

    BaseValue *copy() override;

    string toString() override;
};


#endif //BOA_WINDOWOBJ_H
