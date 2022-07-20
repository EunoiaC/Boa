//
// Created by Preeti Thorat on 12/15/21.
//

#include "List.h"
#include "ListFunction.h"

template<>
List<vector<BaseValue *>>::List(vector<BaseValue *> elements, string f, string txt) : Value<vector<BaseValue *>>(
        elements, TOK_TYPE::T_LIST, f, txt) {
    this->elements = elements;
    map<string, BaseValue *> defaultArgs;
    rtError = nullptr;

    symbolTable->set("pop", new ListFunction<int>(this, "pop", {"index"},
                                                      defaultArgs, "",
                                                      ""));

    defaultArgs["pos"] = new Number<double>(-1, "", "");
    symbolTable->set("append", new ListFunction<int>(this, "append", {"value", "pos"},
                                                      defaultArgs, "",
                                                      ""));
    defaultArgs.clear();

    defaultArgs["endIdx"] = new Number<double>(-1, fName, fTxt);
    symbolTable->set("slice", new ListFunction<int>(this, "slice", {"startIdx", "endIdx"},
                                                      defaultArgs, "",
                                                      ""));
    defaultArgs.clear();

    symbolTable->set("indexOf", new ListFunction<int>(this, "indexOf", {"key"},
                                                    defaultArgs, "",
                                                    ""));

    symbolTable->set("set", new ListFunction<int>(this, "set", {"idx", "val"},
                                                      defaultArgs, "",
                                                      ""));
    defaultArgs["func"] = new Value<int>(-10, TOK_TYPE::T_FUNC, fName, fTxt);
    symbolTable->set("sort", new ListFunction<int>(this, "sort", {"func"},
                                                  defaultArgs, "",
                                                  ""));
    defaultArgs.clear();
}

template<>
BaseValue *List<vector<BaseValue *>>::oredBy(BaseValue *other) {
    return (new Number<double>(!elements.empty() or other->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *List<vector<BaseValue *>>::andedBy(BaseValue *other) {
    return (new Number<double>(!elements.empty() and other->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *List<vector<BaseValue *>>::notted() {
    return (new Number<double>(elements.empty() ? 1 : 0, fName, fTxt))->setContext(ctx);
}

template<>
List<vector<BaseValue *>> *List<vector<BaseValue *>>::copy() {
    List<vector<BaseValue *>> *copy = new List<vector<BaseValue *>>(elements, fName, fTxt);
    copy->setPos(posStart, posEnd, line);
    copy->setContext(ctx);
    return copy;
}

template<>
bool List<vector<BaseValue *>>::isTrue() {
    return elements.size() > 0;
}

template<typename T>
string List<T>::toString() {
    string str = "[";
    for (int i = 0; i < elements.size(); i++) {
        str += elements[i]->toString();
        if (i != elements.size() - 1) {
            str += ", ";
        }
    }
    str += "]";
    return str;
}

template<>
BaseValue *List<vector<BaseValue *>>::add(BaseValue *other) {
    List<vector<BaseValue *>> *newList = copy();
    newList->elements.push_back(other);
    return newList;
}

template<>
BaseValue *List<vector<BaseValue *>>::contains(BaseValue *other) {
    for (auto it: elements) {
        if (((Number<double> *) it->compEquals(other))->getValue() == 1) {
            return new Number<double>(1, fName, fTxt);
        }
    }
    return new Number<double>(0, fName, fTxt);
}

template<>
BaseValue *List<vector<BaseValue *>>::subtract(BaseValue *other) {
    if (other->type == TOK_TYPE::T_NUM) {
        Number<double> *num = (Number<double> *) other;
        if (num->getValue() > elements.size() - 1) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else {
            List<vector<BaseValue *>> *newList = copy();
            newList->elements.erase(newList->elements.begin() + (int) num->getValue());
            return newList;
        }
    } else {
        illegalOperation(other, VAL_TYPES[TOK_TYPE::T_NUM]);
    }
}

template<>
BaseValue *List<vector<BaseValue *>>::get(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        Number<double> *num = (Number<double> *) s;
        if (num->getValue() >= elements.size() || num->getValue() < 0) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else {
            BaseValue *val = elements[(int) num->getValue()];
            if (val->type == TOK_TYPE::T_STRING) {
                auto *str = (String<string> *) val;
                return str;
            }
            return val;
        }
    } else {
        illegalOperation(s);
    }
}

template<>
BaseValue *List<vector<BaseValue *>>::multiply(BaseValue *other) {
    if (other->type == TOK_TYPE::T_NUM) {
        vector<BaseValue *> copyElems;
        for (int i = 0; i < ((Number<double> *) other)->getValue(); i++) {
            copyElems.insert(copyElems.end(), elements.begin(), elements.end());
        }
        return new List<vector<BaseValue *>>(copyElems, fName, fTxt);
    }
    illegalOperation(other);
}

template<>
int List<vector<BaseValue *>>::getLength() {
    return elements.size();
}

template<>
BaseValue *List<vector<BaseValue *>>::plusEquals(BaseValue *other) {
    elements.push_back(other);
    return this;
}

template<>
BaseValue *List<vector<BaseValue *>>::to(BaseValue *other) {
    if (other->type == TOK_TYPE::T_LIST) {
        elements = ((List<vector<BaseValue *>> *) other)->elements;
        return this;
    } else {
        illegalOperation(other);
    }
}

template<>
BaseValue *List<vector<BaseValue *>>::compEquals(BaseValue *other) {
    if (other->type == TOK_TYPE::T_LIST) {
        auto *otherList = (List<vector<BaseValue *>> *) other;
        if (elements.size() == otherList->elements.size()) {
            for (int i = 0; i < elements.size(); i++) {
                if (((Number<double> *) elements[i]->compEquals(otherList->elements[i]))->getValue() == 0) {
                    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
                }
            }
            return (new Number<double>(1, fName, fTxt))->setContext(ctx);
        }
        return (new Number<double>(0, fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *List<vector<BaseValue *>>::compNotEquals(BaseValue *other) {
    return new Number<double>(((Number<double> *) compEquals(other))->getValue() != 1, "", "");
}

template<>
BaseValue *List<vector<BaseValue *>>::minusEquals(BaseValue *other) {
    if (other->type == TOK_TYPE::T_NUM) {
        Number<double> *num = (Number<double> *) other;
        if (num->getValue() > elements.size() - 1) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else {
            elements.erase(elements.begin() + (int) num->getValue());
            return this;
        }
    } else {
        illegalOperation(other, VAL_TYPES[TOK_TYPE::T_NUM]);
    }
    return this;
}