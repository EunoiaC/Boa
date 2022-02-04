//
// Created by Administrator on 10/12/2021.
//

#ifndef BOA_VALUE_H
#define BOA_VALUE_H

#include <string>
#include <vector>
#include "../../RuntimeResult/RuntimeResult.h"
#include "../../Errors/RuntimeError.h"
#include "BaseValue.h"

static const string T_STRING = "STRING";
static const string T_NUM = "NUMBER";
static const string T_FUNC = "FUNCTION";
static const string T_CLASS = "CLASS";
static const string T_LIST = "LIST";
static const string T_MAP = "MAP";

template<class valueType>
class Value : public BaseValue {
public:
    /**
     * The value as an instance of the object type
     */
    valueType val;
    Context *ctx;
    Error *rtError;
    SymbolTable *symbolTable;

    Value(valueType v, string t, string f, string txt);
    ~Value();

    BaseValue * getFromSymbolTable(string name) override;

    virtual /**
     * @return The value of the valueType
     */
    valueType getValue();


    virtual BaseValue *setContext(Context *c);
    virtual RuntimeResult *execute(vector<BaseValue *> args);

    //Overrides methods to give unsupportedOperation RTError
    BaseValue *subtract(BaseValue * other) override;
    BaseValue *set(BaseValue * other) override;
    BaseValue *add(BaseValue * other) override;
    BaseValue *multiply(BaseValue * other) override;
    BaseValue *divide(BaseValue * other) override;
    BaseValue *plusEquals(BaseValue * other) override;
    BaseValue *minusEquals(BaseValue * other) override;
    BaseValue* power(BaseValue* s) override;
    BaseValue* mod(BaseValue* s) override;

    bool isTrue() override;

    BaseValue *compGreaterThan(BaseValue *val) override;
    BaseValue *compLessThan(BaseValue *val) override;
    BaseValue *compGreaterThanEquals(BaseValue *val) override;
    BaseValue *compLessThanEquals(BaseValue *val) override;
    BaseValue *compNotEquals(BaseValue *val) override;
    BaseValue *compEquals(BaseValue *val) override;

    BaseValue* andedBy(BaseValue* s) override;
    BaseValue* oredBy(BaseValue* s) override;
    BaseValue* contains(BaseValue* s) override;
    BaseValue *notted() override;

    void illegalOperation(BaseValue *other);
    void illegalOperation(BaseValue *other, string type);
    void unsupportedOperation(BaseValue *other);
};


#endif //BOA_VALUE_H
