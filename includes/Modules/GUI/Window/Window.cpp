//
// Created by Preeti Thorat on 6/21/22.
//

#include "Window.h"
#include "WindowFunction.h"

template<>
Window<int>::Window(Number<double> * width, Number<double> * height, String<string> * title) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;
    this->width = width;
    this->height = height;
    this->title = title;

    symbolTable->set("start", new WindowFunction<int>(this, "start", {}, defaultArgs, "", ""));

    if (!glfwInit()) {
        //error
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width->getValue(), height->getValue(), title->getValue().c_str(), nullptr, nullptr);
    if (!window){
        glfwTerminate();
        //rtError = new RuntimeError(): failed to init window
    }
    glfwMakeContextCurrent(window);
}

template<>
BaseValue *Window<int>::copy() {
    auto *win = new Window<int>(width->copy(), height->copy(), title->copy());
    return win;
}

template<>
string Window<int>::toString() {
    return "<Window>";
}