//
// Created by Preeti Thorat on 12/18/21.
//

#include "Map.h"

template<>
Map<map<BaseValue *, BaseValue *>>::Map(map<BaseValue *, BaseValue *> dict, string fName, string fTxt)
        : Value<map<BaseValue *, BaseValue *>>(dict, T_MAP, fName, fTxt) {
    this->dict = dict;
}

template<>
Map<map<BaseValue *, BaseValue *>> *Map<map<BaseValue *, BaseValue *>>::copy() {
    Map<map<BaseValue *, BaseValue *>> *copy = new Map<map<BaseValue *, BaseValue *>>(dict, fName, fTxt);
    copy->setPos(posStart, posEnd, line);
    copy->setContext(ctx);
    return copy;
}

template<>
int Map<map<BaseValue *, BaseValue *>>::getLength() {
    return dict.size();
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::plusEquals(BaseValue *keyAndVal) {
    if (keyAndVal->type == T_LIST) {
        List<vector<BaseValue *>> *list = (List<vector<BaseValue *>> *) keyAndVal;
        if (list->elements.size() != 2) {
            rtError = new RuntimeError(
                    list->posStart,
                    list->posEnd,
                    list->line,
                    list->fName,
                    list->fTxt,
                    "LIST needs 2 elements",
                    ctx
            );
        } else {
            dict[list->elements[0]] = list->elements[1];
            return this;
        }
    } else {
        illegalOperation(keyAndVal, T_LIST);
    }
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::add(BaseValue *keyAndVal) {
    if (keyAndVal->type == T_LIST) {
        List<vector<BaseValue *>> *list = (List<vector<BaseValue *>> *) keyAndVal;
        if (list->elements.size() != 2) {
            rtError = new RuntimeError(
                    list->posStart,
                    list->posEnd,
                    list->line,
                    list->fName,
                    list->fTxt,
                    "LIST needs 2 elements",
                    ctx
            );
        } else {
            Map<map<BaseValue *, BaseValue *>> *m = copy();
            m->dict[list->elements[0]] = list->elements[1];
            return m;
        }
    } else {
        illegalOperation(keyAndVal, T_LIST);
    }
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::minusEquals(BaseValue *key) {
    Map<map<BaseValue *, BaseValue *>> *_copy = this;
    if (key->type == T_LIST) {
        List<vector<BaseValue *>> *list = (List<vector<BaseValue *>> *) key;
        for (auto it: _copy->dict) {
            if (((List<vector<BaseValue *>> *) it.first)->val == list->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == T_NUM) {
        Number<double> *num = (Number<double> *) key;
        for (auto it: _copy->dict) {
            if (((Number<double> *) it.first)->val == num->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == T_STRING) {
        String<string> *val = (String<string> *) key;
        for (auto it: _copy->dict) {
            if (((String<string> *) it.first)->val == val->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == T_MAP) {
        Map<map<BaseValue *, BaseValue *>> *val = (Map<map<BaseValue *, BaseValue *>> *) key;
        for (auto it: _copy->dict) {
            if (((Map<map<BaseValue *, BaseValue *>> *) it.first)->val == val->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    }
    return _copy;
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::subtract(BaseValue *key) {
    Map<map<BaseValue *, BaseValue *>> *_copy = copy();
    for (auto it: _copy->dict) {
        if(((Number<double>*) it.first->compEquals(key))->getValue() == 1) {
            _copy->dict.erase(it.first);
            break;
        }
    }
    return _copy;
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::get(BaseValue *key) {
    //This is the most unoptomized piece of code you will ever see
    for (auto it: dict) {
        if(((Number<double>*) it.first->compEquals(key))->getValue() == 1) {
            return it.second;
        }
    }
    rtError = new RuntimeError(
            key->posStart,
            key->posEnd,
            key->line,
            key->fName,
            key->fTxt,
            "Key not found in map",
            ctx
    );
}

template<typename T>
string Map<T>::toString() {
    string str = "{";
    for (auto it = dict.begin(); it != dict.end(); it++) {
        str += it->first->toString() + ": " + it->second->toString() + ", ";
    }
    str = str.substr(0, str.length() - 2);
    str += "}";
    return str;
}