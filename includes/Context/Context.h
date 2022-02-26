//
// Created by Aadi Yadav on 11/25/21.
//

#ifndef BOA_CONTEXT_H
#define BOA_CONTEXT_H
#include "../SymbolTable/SymbolTable.h"
#include <string>

using namespace std;

class Context {
public:
    string displayName, fName, fTxt, parentFilePath;
    Context *parentCtx;
    int parentEntry, line;
    SymbolTable *symbolTable;

    Context *setParentCtx(Context *parentCtx), *setParentEntry(int parentEntry, string fName, string fTxt, int line);


    Context(string displayName);
};


#endif //BOA_CONTEXT_H
