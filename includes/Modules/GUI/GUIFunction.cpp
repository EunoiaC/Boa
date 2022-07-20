//
// Created by Preeti Thorat on 6/22/22.
//

#include "GUIFunction.h"

template<>
RuntimeResult *GUIFunction<int>::execute_makeWindow(Context *execCtx) {
    BaseValue * w = execCtx->symbolTable->get("width");
    if (w->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                w->posStart,
                w->posEnd,
                w->line,
                w->fName,
                w->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    BaseValue * h = execCtx->symbolTable->get("height");
    if (h->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                h->posStart,
                h->posEnd,
                h->line,
                h->fName,
                h->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    BaseValue * t = execCtx->symbolTable->get("title");
    if (t->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                t->posStart,
                t->posEnd,
                t->line,
                t->fName,
                t->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    Number<double> * width = (Number<double> *) w;
    Number<double> * height = (Number<double> *) h;
    String<string> * title = (String<string> *) t;

    return (new RuntimeResult())->success(new WindowObj<int>(width, height, title));
}

template<>
RuntimeResult *GUIFunction<int>::execute_makeText(Context *execCtx) {
    // Constructor for Text: X- Double, Y- Double, width- Double, height- Double, text- String
    BaseValue * X = execCtx->symbolTable->get("X");
    if (X->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                X->posStart,
                X->posEnd,
                X->line,
                X->fName,
                X->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * Y = execCtx->symbolTable->get("Y");
    if (Y->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                Y->posStart,
                Y->posEnd,
                Y->line,
                Y->fName,
                Y->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * width = execCtx->symbolTable->get("width");
    if (width->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                width->posStart,
                width->posEnd,
                width->line,
                width->fName,
                width->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * height = execCtx->symbolTable->get("height");
    if (height->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                height->posStart,
                height->posEnd,
                height->line,
                height->fName,
                height->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * text = execCtx->symbolTable->get("text");
    if (text->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                text->posStart,
                text->posEnd,
                text->line,
                text->fName,
                text->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    Number<double> * X_ = (Number<double> *) X;
    Number<double> * Y_ = (Number<double> *) Y;
    Number<double> * width_ = (Number<double> *) width;
    Number<double> * height_ = (Number<double> *) height;
    String<string> * text_ = (String<string> *) text;

    return (new RuntimeResult())->success(new Text<int>(X_, Y_, width_, height_, text_));
}

template<>
RuntimeResult *GUIFunction<int>::execute_makeTextInput(Context *execCtx) {
    // Constructor for Text: X- Double, Y- Double, width- Double, height- Double, text- String
    BaseValue * X = execCtx->symbolTable->get("X");
    if (X->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                X->posStart,
                X->posEnd,
                X->line,
                X->fName,
                X->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * Y = execCtx->symbolTable->get("Y");
    if (Y->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                Y->posStart,
                Y->posEnd,
                Y->line,
                Y->fName,
                Y->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * width = execCtx->symbolTable->get("width");
    if (width->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                width->posStart,
                width->posEnd,
                width->line,
                width->fName,
                width->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * height = execCtx->symbolTable->get("height");
    if (height->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                height->posStart,
                height->posEnd,
                height->line,
                height->fName,
                height->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * text = execCtx->symbolTable->get("text");
    if (text->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                text->posStart,
                text->posEnd,
                text->line,
                text->fName,
                text->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    Number<double> * X_ = (Number<double> *) X;
    Number<double> * Y_ = (Number<double> *) Y;
    Number<double> * width_ = (Number<double> *) width;
    Number<double> * height_ = (Number<double> *) height;
    String<string> * text_ = (String<string> *) text;

    return (new RuntimeResult())->success(new TextInput<int>(X_, Y_, width_, height_, text_));
}

template<>
RuntimeResult *GUIFunction<int>::execute_makeButton(Context *execCtx) {
    // Constructor for Button: X- Double, Y- Double, width- Double, height- Double, text- String
    BaseValue * X = execCtx->symbolTable->get("X");
    if (X->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                X->posStart,
                X->posEnd,
                X->line,
                X->fName,
                X->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * Y = execCtx->symbolTable->get("Y");
    if (Y->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                Y->posStart,
                Y->posEnd,
                Y->line,
                Y->fName,
                Y->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * width = execCtx->symbolTable->get("width");
    if (width->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                width->posStart,
                width->posEnd,
                width->line,
                width->fName,
                width->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * height = execCtx->symbolTable->get("height");
    if (height->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                height->posStart,
                height->posEnd,
                height->line,
                height->fName,
                height->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    BaseValue * text = execCtx->symbolTable->get("text");
    if (text->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                text->posStart,
                text->posEnd,
                text->line,
                text->fName,
                text->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    Number<double> * X_ = (Number<double> *) X;
    Number<double> * Y_ = (Number<double> *) Y;
    Number<double> * width_ = (Number<double> *) width;
    Number<double> * height_ = (Number<double> *) height;
    String<string> * text_ = (String<string> *) text;

    return (new RuntimeResult())->success(new Button<int>(X_, Y_, width_, height_, text_));
}


template<>
GUIFunction<int>::GUIFunction(string name, vector<string> argNames,
                                    map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                   fName,
                                                                                   fTxt, CLASS_FUNC) {
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_makeWindow"] = &GUIFunction<int>::execute_makeWindow;
    funcMap["execute_makeText"] = &GUIFunction<int>::execute_makeText;
    funcMap["execute_makeTextInput"] = &GUIFunction<int>::execute_makeTextInput;
    funcMap["execute_makeButton"] = &GUIFunction<int>::execute_makeButton;
}

template<>
GUIFunction<int> *GUIFunction<int>::copy() {
    auto *func = new GUIFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *GUIFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
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
string GUIFunction<int>::toString() {
    return "<GUIFunction: " + name + ">";
}