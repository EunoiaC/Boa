//
// Created by Preeti Thorat on 6/21/22.
//

#include "WindowFunction.h"

class CustomImGui : public UseImGui {
public:
    virtual void Update() override {
        ImGui::Begin("Window");
//        ImGui::BeginTabBar("Settings");
//        if (ImGui::BeginTabItem("GUI")){
//            char *buf;
//            ImGui::InputText("Tab 2", buf, 1000);
//            ImGui::EndTabItem();
//        }
//        if (ImGui::BeginTabItem("Settings")){
//            ImGui::Text("Settings");
//            ImGui::EndTabItem();
//        }
//
//        ImGui::EndTabBar();
        ImGui::End();
    }
};


template<>
RuntimeResult *WindowFunction<int>::execute_start(Context *execCtx) {
    const char *glsl_version = "#version 150";

    int screen_width, screen_height;
    glfwGetFramebufferSize(winObj->window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    CustomImGui myimgui;
    myimgui.Init(winObj->window, glsl_version);
    ImGuiIO& io = ImGui::GetIO();

    BaseValue * fontPath = winObj->symbolTable->get("fontPath");
    if (fontPath != nullptr && fontPath->type == TOK_TYPE::T_STRING) {
        BaseValue *fontSize = winObj->symbolTable->get("fontSize");
        if (fontSize != nullptr && fontSize->type == TOK_TYPE::T_NUM) {
            io.Fonts->AddFontFromFileTTF(((String<string> *) fontPath)->getValue().c_str(), ((Number<double> *) fontSize)->getValue());
        } else {
            io.Fonts->AddFontFromFileTTF(((String<string> *) fontPath)->getValue().c_str(), 12);
        }
    }
    while (!glfwWindowShouldClose(winObj->window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        myimgui.NewFrame();
        myimgui.Update();
        myimgui.Render();
        glfwSwapBuffers(winObj->window);

    }
    myimgui.Shutdown();
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
WindowFunction<int>::WindowFunction(Window<int> *winObj, string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->winObj = winObj;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_start"] = &WindowFunction<int>::execute_start;
}

template<>
WindowFunction<int> *WindowFunction<int>::copy() {
    auto *func = new WindowFunction<int>(winObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *WindowFunction<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
string WindowFunction<int>::toString() {
    return "<WindowFunction: " + name + ">";
}