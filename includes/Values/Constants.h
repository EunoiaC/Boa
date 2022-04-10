//
// Created by Preeti Thorat on 12/21/21.
//

#ifndef BOA_CONSTANTS_H
#define BOA_CONSTANTS_H

#include "Functions/BuiltInFunction.h"
#include <string>
#include <cmath>
#include "../../includes/Modules/Random/Random.h"

string fName = "<standard inclusion>";
string fTxt = "Defined in " + fName;

BuiltInFunction<int> * print = new BuiltInFunction<int>("print", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * input = new BuiltInFunction<int>("input", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * toNum = new BuiltInFunction<int>("toNum", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * lenOf = new BuiltInFunction<int>("lenOf", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * toStr = new BuiltInFunction<int>("toStr", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * instanceOf = new BuiltInFunction<int>("instanceOf", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * eval = new BuiltInFunction<int>("eval", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * _rename = new BuiltInFunction<int>("rename", {"oldName", "newName"}, {}, fName, fTxt);
BuiltInFunction<int> * getSymbolTable = new BuiltInFunction<int>("getSymbolTable", {}, {}, fName, fTxt);
BuiltInFunction<int> * _copy = new BuiltInFunction<int>("copy", {"value"}, {}, fName, fTxt);
BuiltInFunction<int> * readFile = new BuiltInFunction<int>("getFile", {"fName"}, {}, fName, fTxt);
BuiltInFunction<int> * clear = new BuiltInFunction<int>("clear", {}, {}, fName, fTxt);


#endif //BOA_CONSTANTS_H
