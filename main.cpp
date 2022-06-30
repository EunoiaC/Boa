#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include <string>
#include <vector>
#include "includes/RunInterface.h"
#include "includes/Values/Constants.h"

using namespace std;

/**
 * Build the program:
 * /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/preetithorat/Documents/GitHub/Boa/cmake-build-debug --target Boa -- -j -v  6
**/

// TODO: Fix errors that do to_string(enum)
/* TODO: Populate args in func using varname: value
 * add(num1: 12, num2: 13)
*/

SymbolTable *globalSymbolTable = new SymbolTable();

int main(int argc, char **argv) {
    string filePath, pathRef;
    if (argc > 1) {
        filePath = argv[1];
        const size_t last_slash_idx = filePath.rfind('/');
        if (std::string::npos != last_slash_idx) {
            pathRef = filePath.substr(0, last_slash_idx);
        }
        filePath = filePath.substr(filePath.find_last_of("/\\") + 1);
        pathRef += "/";
    }

    vector<BaseValue *> elem;
    for (int i = 2; i < argc; i++) {
        elem.push_back(new String<string>(argv[i], "", ""));
    }

    globalSymbolTable->set("args", new List<vector<BaseValue *>>(elem, "", ""));
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
    globalSymbolTable->set("getFile", readFile);
    globalSymbolTable->set("clear", clear);

    RunInterface *runInterface = new RunInterface(globalSymbolTable, pathRef);
    if (argc == 1) {
        cout << ">>> ";
        string line;
        while (getline(cin, line)) {
            if (line == "exit") {
                return 15;
            }
            auto result = runInterface->readLine(line);
            if (result.second != nullptr) {
                cout << result.second->toString() << endl;
            } else {
                cout << result.first->toString() << endl;
            }
            cout << ">>> ";
        }
    }
    runInterface->run(filePath);
    delete runInterface;
    return 0;
}

#pragma clang diagnostic pop