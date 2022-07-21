//
// Created by Preeti Thorat on 6/21/22.
//

#include "WindowFunction.h"

template<>
RuntimeResult *WindowFunction<int>::execute_add(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * widget = execCtx->symbolTable->get("widget");
    auto * widg = dynamic_cast<Widget<int> *>(widget);
    if (!widg) {
        return res->failure(new RuntimeError(
                widget->posStart,
                widget->posEnd,
                widget->line,
                widget->fName,
                widget->fTxt,
                "Expected a WIDGET",
                execCtx
        ));
    }
    // Add widget to vector for error checking
    winObj->widgets.push_back(widg);
    // Set the parent so we know what to terminate in case of an error
    widg->parent = winObj;
    // Add widget to the window
    winObj->window->add(widg->widget);
    return res->success(new Number<double>(0, "", ""));
}

template<>
void WindowFunction<int>::fltk_callback(void * win) {
    WindowObj<int> * windowObj = (WindowObj<int> *) win;
}

template<>
RuntimeResult *WindowFunction<int>::execute_start(Context *execCtx) {
    winObj->window->end();
    winObj->window->show();
    // For future
    //Fl::add_idle(fltk_callback, winObj);
    Fl::run();
    // After run loop through all widgets and check for errors
    for (auto *widg : winObj->widgets) {
        if (widg->rtError) {
            winObj->window->hide();
            return (new RuntimeResult())->failure(widg->rtError);
        }
    }
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
WindowFunction<int>::WindowFunction(WindowObj<int> *winObj, string name, vector<string> argNames,
                                    map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->winObj = winObj;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_start"] = &WindowFunction<int>::execute_start;
    funcMap["execute_add"] = &WindowFunction<int>::execute_add;
}

template<>
WindowFunction<int> *WindowFunction<int>::copy() {
    auto *func = new WindowFunction<int>(winObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *WindowFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    for (auto &it: kwargs) {
        // Check if the keyword argument is a valid argument
        if (find(argNames.begin(), argNames.end(), it.first) == argNames.end()) {
            return res->failure(new RuntimeError(
                    posStart,
                    posEnd,
                    line,
                    fName,
                    fTxt,
                    "Invalid keyword argument " + it.first + " passed into " + name,
                    ctx
            ));
        }
        args.push_back(it.second);
        execCtx->symbolTable->set(it.first, it.second);
    }
    res->reg(checkAndPopulateArgs(args, kwargs, argNames, execCtx));
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