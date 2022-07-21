//
// Created by Preeti Thorat on 7/18/22.
//

#include "WidgetFunction.h"

template<>
RuntimeResult * WidgetFunction<int>::execute_setCallback(Context *execCtx) {
    BaseValue *cb = execCtx->symbolTable->get("callback");
    if (cb->type != TOK_TYPE::T_FUNC) {
        return (new RuntimeResult())->failure(new RuntimeError(
                cb->posStart,
                cb->posEnd,
                cb->line,
                cb->fName,
                cb->fTxt,
                "Expected a FUNCTION",
                execCtx
        ));
    }

    Function<int> *callback = (Function<int> *) cb;
    if (callback->argNames.size() != 0) {
        return (new RuntimeResult())->failure(new RuntimeError(
                cb->posStart,
                cb->posEnd,
                cb->line,
                cb->fName,
                cb->fTxt,
                "Expected a FUNCTION with 0 arguments",
                execCtx
        ));
    }

    widget->callback = callback;

    widget->widget->callback([](Fl_Widget *sender, void *wi) {
        auto *widget = (Widget<int> *) wi;
        RuntimeResult *res = widget->callback->execute({}, {});
        if (res->error) {
            widget->rtError = res->error;
            widget->parent->widget->hide();
        }
    }, widget);

    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WidgetFunction<int>::execute_color(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * c = execCtx->symbolTable->get("color");
    if (c->type != TOK_TYPE::T_NUM) {
        return res->failure(new RuntimeError(
                c->posStart,
                c->posEnd,
                c->line,
                c->fName,
                c->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }
    int color = dynamic_cast<Number<double> *>(c)->val;
    widget->widget->color(color);
    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *WidgetFunction<int>::execute_box(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * c = execCtx->symbolTable->get("box");
    if (c->type != TOK_TYPE::T_NUM) {
        return res->failure(new RuntimeError(
                c->posStart,
                c->posEnd,
                c->line,
                c->fName,
                c->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }
    int box = dynamic_cast<Number<double> *>(c)->val;
    widget->widget->box(static_cast<Fl_Boxtype>(box));
    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult * WidgetFunction<int>::execute_hide(Context *execCtx) {
    widget->widget->hide();
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult * WidgetFunction<int>::execute_redraw(Context *execCtx) {
    widget->widget->redraw();
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult * WidgetFunction<int>::execute_getValue(Context *execCtx) {
    return (new RuntimeResult())->success(new String<string>(widget->widgetVal(), "", ""));
}

template<>
RuntimeResult * WidgetFunction<int>::execute_labelColor(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * c = execCtx->symbolTable->get("color");
    if (c->type != TOK_TYPE::T_NUM) {
        return res->failure(new RuntimeError(
                c->posStart,
                c->posEnd,
                c->line,
                c->fName,
                c->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }
    int color = dynamic_cast<Number<double> *>(c)->val;
    widget->widget->labelcolor(color);
    return res->success(new Number<double>(0, "", ""));
}

template<>
WidgetFunction<int>::WidgetFunction(Widget<int> *widget, string name, vector<string> argNames,
                                    map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                   fName,
                                                                                   fTxt, CLASS_FUNC) {
    this->widget = widget;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_color"] = &WidgetFunction<int>::execute_color;
    funcMap["execute_box"] = &WidgetFunction<int>::execute_box;
    funcMap["execute_setCallback"] = &WidgetFunction<int>::execute_setCallback;
    funcMap["execute_hide"] = &WidgetFunction<int>::execute_hide;
    funcMap["execute_redraw"] = &WidgetFunction<int>::execute_redraw;
    funcMap["execute_getValue"] = &WidgetFunction<int>::execute_getValue;
    funcMap["execute_labelColor"] = &WidgetFunction<int>::execute_labelColor;
}

template<>
WidgetFunction<int> *WidgetFunction<int>::copy() {
    auto *func = new WidgetFunction<int>(widget, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *WidgetFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
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
string WidgetFunction<int>::toString() {
    return "<WidgetFunction: " + name + ">";
}