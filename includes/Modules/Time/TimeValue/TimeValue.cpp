//
// Created by Preeti Thorat on 6/13/22.
//

#include "TimeValue.h"

template<>
TimeValue<int>::TimeValue(time_t tVal) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    this->tVal = tVal;
    map<string, BaseValue *> defaultArgs;
    tm *ltm = localtime(&tVal);
    symbolTable->set("year", new Number<double>(ltm->tm_year + 1900, "", ""));
    symbolTable->set("month", new Number<double>(1 + ltm->tm_mon, "", ""));
    symbolTable->set("day", new Number<double>(ltm->tm_mday, "", ""));
    symbolTable->set("hour", new Number<double>(5+ltm->tm_hour, "", ""));
    symbolTable->set("min", new Number<double>(30+ltm->tm_min, "", ""));
    symbolTable->set("sec", new Number<double>(ltm->tm_sec, "", ""));
}

template<>
BaseValue *TimeValue<int>::subtract(BaseValue *other) {
    auto * toSub = dynamic_cast<TimeValue<int> *>(other);
    if (toSub == nullptr) {
        rtError = rtError = new RuntimeError(
                other->posStart,
                other->posEnd,
                other->line,
                fName,
                fTxt,
                "Expected a time object",
                ctx
        );
        return nullptr;
    }
    return new TimeValue<int>(tVal - toSub->tVal);
}

template<>
BaseValue *TimeValue<int>::copy() {
    auto *tv = new TimeValue<int>(tVal);
    return tv;
}

template<>
string TimeValue<int>::toString() {
    string str(ctime(&tVal));
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}