#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "includes/RunInterface.h"
#include "includes/Values/Constants.h"

using namespace std;

/**
 * Run the program:
 gcc -std=c++11 main.cpp includes/Token/BaseToken.cpp includes/Token/BaseToken.h includes/Values/BaseValue.cpp includes/Values/BaseValue.h includes/Values/String.cpp includes/Values/String.h includes/Values/Function.cpp includes/Values/Function.h includes/Nodes/StringNode.cpp includes/Nodes/StringNode.h includes/Nodes/ListNode.cpp includes/Nodes/ListNode.h includes/Values/List.cpp includes/Values/List.h
**/

SymbolTable * globalSymbolTable = new SymbolTable();

int main(int argc, char** argv) {
    string filePath = "Test.boa";
    string pathRef = "/Users/preetithorat/Documents/GitHub/Boa/Testing/";
    if(argc > 1){
        filePath = argv[1];
        const size_t last_slash_idx = filePath.rfind('/');
        if (std::string::npos != last_slash_idx)
        {
            pathRef = filePath.substr(0, last_slash_idx);
        }
        filePath = filePath.substr(filePath.find_last_of("/\\") + 1);
        pathRef += "/";
    }

    globalSymbolTable->set("null", new Number<double>(0, "", ""));
    globalSymbolTable->set("true", new Number<double>(1, "", ""));
    globalSymbolTable->set("false", new Number<double>(0, "", ""));
    globalSymbolTable->set("print", print);
    globalSymbolTable->set("input", input);
    globalSymbolTable->set("toNum", toNum);
    globalSymbolTable->set("lenOf", lenOf);
    globalSymbolTable->set("toStr", toStr);
    globalSymbolTable->set("typeOf", instanceOf);
    globalSymbolTable->set("eval", eval);
    globalSymbolTable->set("rename", _rename);
    globalSymbolTable->set("getSymbolTable", getSymbolTable);
    globalSymbolTable->set("copy", _copy);
    globalSymbolTable->set("readFile", readFile);

    //Modules
    globalSymbolTable->set("__random__", _random);

    RunInterface * runInterface = new RunInterface(globalSymbolTable, pathRef);
    runInterface->run(filePath);
    return 0;
}

#pragma clang diagnostic pop