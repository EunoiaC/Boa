//
// Created by Preeti Thorat on 6/21/22.
//

#ifndef BOA_WINDOW_H
#define BOA_WINDOW_H

#include "../../../Values/String/String.h"
#include "../../../Values/Number/Number.h"
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

template <typename T> class Window : public Value<T> {
public:
    Number<double> * width, * height;
    String<string> * title;
    GLFWwindow* window;
    Window<int>(Number<double> * width, Number<double> * height, String<string> * title);
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_WINDOW_H
