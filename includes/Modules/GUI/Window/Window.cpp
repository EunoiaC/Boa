//
// Created by Preeti Thorat on 6/21/22.
//

#include "Window.h"
#include "WindowFunction.h"

void error_callback(int error, const char* msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

void sayHello() {
    std::cout << "Hello World!" << std::endl;
}

template<>
Window<int>::Window(Number<double> * width, Number<double> * height, String<string> * title) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map < string, BaseValue * > defaultArgs;
    this->width = width;
    this->height = height;
    this->title = title;

    symbolTable->set("start", new WindowFunction<int>(this, "start", {}, defaultArgs, "", ""));
    symbolTable->set("fontPath", nullptr);
    symbolTable->set("fontSize", nullptr);

    init((char *) title->getValue().c_str());
    button(".b") -text("Say Hello") -command(sayHello);
    pack(".b") -padx(20) -pady(6);

    runEventLoop();
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