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

template<>
Window<int>::Window(Number<double> * width, Number<double> * height, String<string> * title) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map < string, BaseValue * > defaultArgs;
    this->width = width;
    this->height = height;
    this->title = title;

    symbolTable->set("start", new WindowFunction<int>(this, "start", {}, defaultArgs, "", ""));
    symbolTable->set("fontPath", nullptr);
    symbolTable->set("fontSize", nullptr);

    // Setup window
    if (!glfwInit())
        cout << "Failed to initialize GLFW" << endl;

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    window = glfwCreateWindow(width->getValue(), height->getValue(), title->getValue().c_str(), NULL, NULL);
    if (window == NULL)
        cout << "Failed to create GLFW window" << endl;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
        cout << "Failed to initialize GLAD" << endl;
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