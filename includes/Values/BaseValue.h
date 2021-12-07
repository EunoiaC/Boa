//
// Created by Preeti Thorat on 12/6/21.
//

#ifndef BOA_BASEVALUE_H
#define BOA_BASEVALUE_H
#include <string>
using namespace std;

class BaseValue {
public:
    BaseValue(string t, string f, string txt);
    /**
     * The object type of the value in a string form
     */
    string type;
    string fName, fTxt;
    int posStart, posEnd, line;


    virtual string toString();

    BaseValue *setPos(int start, int end, int line);

    virtual BaseValue *compGreaterThan(BaseValue *val);
    virtual BaseValue *compLessThan(BaseValue *val);
    virtual BaseValue *compGreaterThanEquals(BaseValue *val);
    virtual BaseValue *compLessThanEquals(BaseValue *val);
    virtual BaseValue *compNotEquals(BaseValue *val);
    virtual BaseValue *compEquals(BaseValue *val);

    virtual BaseValue* andedBy(BaseValue* s);
    virtual BaseValue* oredBy(BaseValue* s);
    virtual BaseValue *notted(BaseValue *s);

    virtual bool isTrue();

    virtual BaseValue* add(BaseValue* s);
    virtual BaseValue* subtract(BaseValue* s);
    virtual BaseValue* multiply(BaseValue* s);
    virtual BaseValue* divide(BaseValue* s);
    virtual BaseValue* power(BaseValue* s);
    virtual BaseValue* mod(BaseValue* s);
};


#endif //BOA_BASEVALUE_H
