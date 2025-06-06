//
// Created by Preeti Thorat on 12/18/21.
//

#include "Map.h"
#include "MapFunction.h"

template<>
Map<map<BaseValue *, BaseValue *>>::Map(map<BaseValue *, BaseValue *> dict, string fName, string fTxt)
        : Value<map<BaseValue *, BaseValue *>>(dict, TOK_TYPE::T_MAP, fName, fTxt) {
    this->dict = dict;

    map<string, BaseValue *> defaultArgs;
    symbolTable->set("sortByValue", new MapFunction<int>(this, "sortByValue", {},
                                                  defaultArgs, "",
                                                  ""));
    symbolTable->set("getKeys", new MapFunction<int>(this, "getKeys", {},
                                                         defaultArgs, "",
                                                         ""));
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
BaseValue *Map<map<BaseValue *, BaseValue *>>::add(BaseValue *keyAndVal) {
    if (keyAndVal->type == TOK_TYPE::T_LIST) {
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
        illegalOperation(keyAndVal, VAL_TYPES[TOK_TYPE::T_LIST]);
    }
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::minusEquals(BaseValue *key) {
    Map<map<BaseValue *, BaseValue *>> *_copy = this;
    if (key->type == TOK_TYPE::T_LIST) {
        List<vector<BaseValue *>> *list = (List<vector<BaseValue *>> *) key;
        for (auto it: _copy->dict) {
            if (((List<vector<BaseValue *>> *) it.first)->val == list->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == TOK_TYPE::T_NUM) {
        Number<double> *num = (Number<double> *) key;
        for (auto it: _copy->dict) {
            if (((Number<double> *) it.first)->val == num->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == TOK_TYPE::T_STRING) {
        String<string> *val = (String<string> *) key;
        for (auto it: _copy->dict) {
            if (((String<string> *) it.first)->val == val->val) {
                _copy->dict.erase(it.first);
                break;
            }
        }
    } else if (key->type == TOK_TYPE::T_MAP) {
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

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::replace(BaseValue *old, BaseValue *newVal) {
    bool found = false;
    for (auto it: dict) {
        if(((Number<double>*) it.first->compEquals(old))->getValue() == 1) {
            dict[it.first] = newVal;
            found = true;
            break;
        }
    }
    if (!found) {
        dict[old] = newVal;
    }
    return this;
}


template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::plusEquals(BaseValue *keyAndVal) {
    if (keyAndVal->type == TOK_TYPE::T_LIST) {
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
            replace(list->elements[0], list->elements[1]);
            return this;
        }
    } else {
        illegalOperation(keyAndVal, VAL_TYPES[TOK_TYPE::T_LIST]);
    }
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::to(BaseValue *val) {
    if (val->type == TOK_TYPE::T_MAP) {
        this->dict = ((Map<map<BaseValue *, BaseValue *>> *) val)->dict;
        return this;
    } else {
        illegalOperation(val);
    }
}

template<>
Number<double> *Map<map<BaseValue *, BaseValue *>>::keyExists(BaseValue *key) {
    for (auto it: dict) {
        if(((Number<double>*) it.first->compEquals(key))->getValue() == 1) {
            return new Number<double>(1, "", "");
        }
    }
    return new Number<double>(0, "", "");
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::compEquals(BaseValue *other) {
    if(other->type == TOK_TYPE::T_MAP){
        Map<map<BaseValue *, BaseValue *>> *otherMap = (Map<map<BaseValue *, BaseValue *>> *) other;
        if(dict.size() != otherMap->dict.size()) {
            return new Number<double>(0, "", "");
        }
        for(auto it: dict) {
            if(otherMap->keyExists(it.first)->getValue() == 0) {
                return new Number<double>(0, "", "");
            }
            if(((Number<double> *) it.second->compNotEquals(otherMap->get(it.first)))->getValue() == 1) {
                return new Number<double>(0, "", "");
            }
        }
        return new Number<double>(1, "", "");
    }
    return new Number<double>(0, "", "");
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::compNotEquals(BaseValue *other) {
    return new Number<double>(((Number<double> *) compEquals(other))->getValue() != 1, "", "");
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

template<>
bool Map<map<BaseValue *, BaseValue *>>::isTrue() {
    return dict.size() > 0;
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::oredBy(BaseValue *other) {
    return (new Number<double>(!dict.empty() or other->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::andedBy(BaseValue *other) {
    return (new Number<double>(!dict.empty() and other->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Map<map<BaseValue *, BaseValue *>>::notted() {
    return (new Number<double>(dict.empty() ? 1 : 0, fName, fTxt))->setContext(ctx);
}