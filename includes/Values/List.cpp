//
// Created by Preeti Thorat on 12/15/21.
//

#include "List.h"

template<>
List<vector<BaseValue *>>::List(vector<BaseValue *> elements, string f, string txt) : Value<vector<BaseValue *>>(
        elements, T_LIST, f, txt) {
    this->elements = elements;
}

template<>
List<vector<BaseValue *>> *List<vector<BaseValue *>>::copy() {
    List<vector<BaseValue *>> *copy = new List<vector<BaseValue *>>(elements, fName, fTxt);
    copy->setPos(posStart, posEnd, line);
    copy->setContext(ctx);
    return copy;
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
BaseValue *List<vector<BaseValue *>>::subtract(BaseValue *other) {
    if(other->type == T_NUM) {
        Number<double> *num = (Number<double> *) other;
        if(num->getValue() > elements.size() - 1) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else{
            List<vector<BaseValue *>> *newList = copy();
            newList->elements.erase(newList->elements.begin() + (int) num->numValue);
            return newList;
        }
    } else {
        illegalOperation(other, T_NUM);
    }
}

template<>
BaseValue *List<vector<BaseValue*>>::get(BaseValue *s) {
    if (s->type == T_NUM) {
        Number<double> *num = (Number<double> *) s;
        if(num->numValue > elements.size() - 1){
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
            BaseValue * val = elements[(int) num->numValue];
            return val;
        }
    } else {
        illegalOperation(s);
    }
}

template<>
BaseValue *List<vector<BaseValue *>>::multiply(BaseValue *other) {
    if (other->type == T_LIST) {
        List<vector<BaseValue *>> *otherList = (List<vector<BaseValue *>> *) other;
        List<vector<BaseValue *>> *newList = copy();
        newList->elements = elements;
        newList->elements.insert(newList->elements.end(), otherList->elements.begin(), otherList->elements.end());
        return newList;
    }
    illegalOperation(other);
}

template<>
BaseValue *List<vector<BaseValue *>>::plusEquals(BaseValue *other) {
    elements.push_back(other);
    return this;
}

template<>
BaseValue *List<vector<BaseValue *>>::minusEquals(BaseValue *other) {
    if(other->type == T_NUM) {
        Number<double> *num = (Number<double> *) other;
        if(num->getValue() > elements.size() - 1) {
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    num->fName,
                    num->fTxt,
                    "Index out of range",
                    ctx
            );
        } else{
            elements.erase(elements.begin() + (int) num->numValue);
            return this;
        }
    } else {
        illegalOperation(other, T_NUM);
    }
    return this;
}