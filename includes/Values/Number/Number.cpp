//
// Created by Aadi Yadav on 10/20/21.
//

#include "Number.h"
#include "../String/String.h"
#include <math.h>
#include "NumberFunction.h"


template<>
Number<double>::Number(double value, string f, string txt) : Value<double>(value, TOK_TYPE::T_NUM, f, txt) {
    this->val = value;

    map<string, BaseValue *> defaultArgs;

    symbolTable->set("floor", new NumberFunction<int>(this, "floor", {},
                                                      defaultArgs, "",
                                                      ""));
    symbolTable->set("ceil", new NumberFunction<int>(this, "ceil", {},
                                                      defaultArgs, "",
                                                      ""));
}

template<>
double Number<double>::getValue() {
    return this->val;
}

template<>
Number<double> *Number<double>::copy() {
    Number<double> *val = new Number<double>(this->val, fName, fTxt);
    val->setPos(posStart, posEnd, line);
    val->setContext(ctx);
    return val;
}

template<>
Number<double> *Number<double>::divide(BaseValue *s) {
    Number<double> *output;
    if (s->type == TOK_TYPE::T_NUM) {
        auto *num = (Number<double> *) s;
        if (num->getValue() == 0) {
            //cout << "Error: Division by zero" << endl;
            rtError = new RuntimeError(
                    num->posStart,
                    num->posEnd,
                    num->line,
                    fName,
                    fTxt,
                    "Division by zero",
                    ctx
            );
        }
        output = dynamic_cast<Number<double> *>((new Number<double>(this->val / num->getValue(), fName,
                                                                    fTxt))->setContext(ctx));
        output->rtError = rtError;
        return output;
    }
    illegalOperation(s);
}

template<>
BaseValue *Number<double>::compGreaterThanEquals(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number<double>(this->val >= ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compLessThanEquals(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number<double>(this->val <= ((Number<double> *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compGreaterThan(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number<double>(this->val > ((Number<double> *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compLessThan(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number(this->val < ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compSort(BaseValue *val) {
    return compLessThan(val);
}


template<>
BaseValue *Number<double>::compEquals(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number(this->val == ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(0, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::compNotEquals(BaseValue *val) {
    if (val->type == TOK_TYPE::T_NUM) {
        return (new Number<double>(this->val != ((Number *) val)->getValue(), fName, fTxt))->setContext(ctx);
    }
    return (new Number<double>(1, fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::andedBy(BaseValue *s) {
    return (new Number<double>(this->val and s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::oredBy(BaseValue *s) {
    return (new Number<double>(this->val or s->isTrue(), fName, fTxt))->setContext(ctx);
}

template<>
BaseValue *Number<double>::notted() {
    return (new Number<double>(this->val == 0 ? 1 : 0, fName, fTxt))->setContext(ctx);
}

template<>
Number<double> *Number<double>::multiply(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        return dynamic_cast<Number<double> *>((new Number<double>(this->val * ((Number *) s)->getValue(), fName,
                                                                  fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
string Number<double>::toString() {
    string s = to_string(this->val);
    int dotpos = s.find_first_of('.');
    int zeroCount = 0;
    if (dotpos != string::npos) {
        int ipos = s.size() - 1;
        while (s[ipos] == '0' && ipos > dotpos) {
            --ipos;
            zeroCount++;
        }
        s.erase(ipos + 1, string::npos);
    }
    if (zeroCount == 6) {
        s.erase(dotpos, string::npos);
    }
    return s;
}

template<>
bool Number<double>::isTrue() {
    return this->val != 0;
}

template<>
BaseValue *Number<double>::add(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(this->val + ((Number *) s)->getValue(), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::plusEquals(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        this->val += ((Number *) s)->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::to(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        this->val = ((Number *) s)->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::minusEquals(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        this->val -= ((Number *) s)->getValue();
        return this;
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::subtract(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(this->val - ((Number *) s)->getValue(), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::power(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(pow(this->val, ((Number *) s)->getValue()), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}

template<>
Number<double> *Number<double>::mod(BaseValue *s) {
    if (s->type == TOK_TYPE::T_NUM) {
        return dynamic_cast<Number *>((new Number<double>(fmod(this->val, ((Number *) s)->getValue()), fName,
                                                          fTxt))->setContext(
                ctx));
    }
    illegalOperation(s);
}