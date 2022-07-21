//
// Created by Preeti Thorat on 5/30/22.
//

#ifndef BOA_GUI_H
#define BOA_GUI_H

#include "../../Values/BaseValues/Value.h"
#include "FLTK wrappers/Widget.h"

template<typename T> class GUI : public Value<T> {
public:
    GUI<int>();
    BaseValue * copy() override;
    string toString() override;
    vector<Widget<int> *> widgets;
};

#endif //BOA_GUI_H
