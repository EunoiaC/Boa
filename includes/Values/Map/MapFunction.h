//
// Created by Preeti Thorat on 4/9/22.
//

#ifndef BOA_MAPFUNCTION_H
#define BOA_MAPFUNCTION_H


//
// Created by Preeti Thorat on 1/18/22.
//

#ifndef BOA_LISTFUNCTION_H
#define BOA_LISTFUNCTION_H

#include "../Functions/BaseFunction.h"
#include "../String/String.h"
#include "../List/List.h"
#include "../Map/Map.h"
#include "../Class/UsableClass.h"

template<typename T> class MapFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (MapFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Map<map<BaseValue *, BaseValue *>> * value;
    MapFunction<T>(Map<map<BaseValue*, BaseValue *>>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    MapFunction<int> *copy() override;

    RuntimeResult * execute_sortByValue(Context * execCtx);

    string toString() override;
};


#endif //BOA_LISTFUNCTION_H


#endif //BOA_MAPFUNCTION_H
