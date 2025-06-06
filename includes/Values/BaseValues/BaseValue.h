//
// Created by Preeti Thorat on 12/6/21.
//

#ifndef BOA_BASEVALUE_H
#define BOA_BASEVALUE_H
#include <string>
#include <map>
#include "../../Token/BaseToken.h"
using namespace std;
using TOK_TYPE = BaseToken::TOK_TYPE;

class BaseValue {
public:
    map<TOK_TYPE, string> VAL_TYPES = {
            {TOK_TYPE::T_NUM, "T_NUM"},
            {TOK_TYPE::T_FUNC, "T_FUNC"},
            {TOK_TYPE::T_LIST, "T_LIST"},
            {TOK_TYPE::T_MAP, "T_MAP"},
            {TOK_TYPE::T_STRING, "T_STRING"},
            {TOK_TYPE ::T_CLASS, "T_CLASS"},
            {TOK_TYPE ::T_FUTURE, "T_FUTURE"}
    };

    BaseValue(TOK_TYPE t, string f, string txt);

    virtual BaseValue * getFromSymbolTable(string key);
    virtual void setInSymbolTable(string key, BaseValue * value);

    TOK_TYPE type;
    string fName, fTxt;
    int posStart, posEnd, line;

    virtual int getLength();

    virtual string toString();

    BaseValue *setPos(int start, int end, int line);

    virtual BaseValue *copy();

    virtual BaseValue *compGreaterThan(BaseValue *val);
    virtual BaseValue *compLessThan(BaseValue *val);
    virtual BaseValue *compGreaterThanEquals(BaseValue *val);
    virtual BaseValue *compLessThanEquals(BaseValue *val);
    virtual BaseValue *compNotEquals(BaseValue *val);
    virtual BaseValue *compEquals(BaseValue *val);
    virtual BaseValue *compSort(BaseValue *val);

    virtual BaseValue* andedBy(BaseValue* s);
    virtual BaseValue* oredBy(BaseValue* s);
    virtual BaseValue* contains(BaseValue* s);
    virtual BaseValue* notted();

    virtual bool isTrue();

    virtual BaseValue *plusEquals(BaseValue * other);
    virtual BaseValue *minusEquals(BaseValue * other);
    virtual BaseValue *to(BaseValue *val);

    virtual BaseValue* add(BaseValue* s);
    virtual BaseValue* subtract(BaseValue* s);
    virtual BaseValue* multiply(BaseValue* s);
    virtual BaseValue* divide(BaseValue* s);
    virtual BaseValue* power(BaseValue* s);
    virtual BaseValue* mod(BaseValue* s);

    virtual BaseValue* get(BaseValue* s);
};


#endif //BOA_BASEVALUE_H
