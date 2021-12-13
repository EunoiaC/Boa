//
// Created by Preeti Thorat on 12/12/21.
//

#include "List.h"

List::List(const vector<BaseValue *>& elems, string f, string txt) : Value<vector<BaseValue *>>(elems, T_LIST, f, txt) {
    this->elems = elems;
}

List * List::copy() {
    return new List(this->elems, this->fName, this->fTxt);
}

BaseValue *List::add(BaseValue *other) {
    List *newList = copy();
    newList->elems.push_back(other);
    return newList;
}

BaseValue *List::subtract(BaseValue *other) {
    if(other->type == T_LIST) {
        List * otherList = (List *) other;
        List *newList = copy();
        newList->elems.reserve(newList->elems.size() + distance(otherList->elems.begin(),otherList->elems.end()));
        return newList;
    }
    illegalOperation(other);
}

string List::toString() {
    string str = "[";
    for(BaseValue *elem : elems) {
        str += elem->toString() + ", ";
    }
    return str + "]";
}