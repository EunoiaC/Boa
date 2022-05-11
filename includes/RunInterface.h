//
// Created by Preeti Thorat on 1/14/22.
//

#ifndef BOA_RUNINTERFACE_H
#define BOA_RUNINTERFACE_H

#include "Values/BaseValues/BaseValue.h"
#include "Errors/Error.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ParseResult.h"
#include "Interpreter/Interpreter.h"

typedef pair<BaseValue *, Error *> RunResult;

class RunInterface {
public:
    vector<string> lines;
    string pathRef;
    Lexer *l;
    Parser *p;
    ParseResult *res;
    SymbolTable *globalSymbolTable;
    RunInterface(SymbolTable *symbolTable, string pathRef);
    ~RunInterface();
    RunResult readFile(string fileName);
    RunResult readLine(string fileName);
    void run(string fileName);
};


#endif //BOA_RUNINTERFACE_H
