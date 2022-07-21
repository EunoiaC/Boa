//
// Created by Preeti Thorat on 6/21/22.
//

#include "WindowObj.h"
#include "WindowFunction.h"

void error_callback(int error, const char* msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

template<>
WindowObj<int>::WindowObj(Number<double> * width, Number<double> * height, String<string> * title) : Widget<int>() {
    map < string, BaseValue * > defaultArgs;
    this->width = width;
    this->height = height;
    this->title = title;

    symbolTable->set("end", new WindowFunction<int>(this, "end", {}, defaultArgs, "", ""));
    symbolTable->set("add", new WindowFunction<int>(this, "add", {"widget"}, defaultArgs, "", ""));

    window = new Fl_Window(width->val, height->val, title->val.c_str());
    // TODO: Make this configurable
    window->resizable(window);
    widget = window;
}

template<>
BaseValue *WindowObj<int>::copy() {
    auto *win = new WindowObj<int>(width->copy(), height->copy(), title->copy());
    return win;
}

template<>
string WindowObj<int>::toString() {
    return "<Window>";
}