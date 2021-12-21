#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include <iostream>
#include "includes/Parser/Parser.h"
#include "includes/Lexer/Lexer.h"
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "includes/Interpreter/Interpreter.h"

using namespace std;

/**
 * Run the program:
 gcc -std=c++11 main.cpp includes/Token/BaseToken.cpp includes/Token/BaseToken.h includes/Values/BaseValue.cpp includes/Values/BaseValue.h includes/Values/String.cpp includes/Values/String.h includes/Values/Function.cpp includes/Values/Function.h includes/Nodes/StringNode.cpp includes/Nodes/StringNode.h includes/Nodes/ListNode.cpp includes/Nodes/ListNode.h includes/Values/List.cpp includes/Values/List.h
**/


vector<string> lines;
Lexer *l;
Parser *p;
ParseResult *res;
SymbolTable *globalSymbolTable = new SymbolTable();
string fileName;

int readFile() {
    string filePath = "/Users/preetithorat/Documents/GitHub/Boa/Testing/Test.boa";
    fileName = filePath.substr(filePath.find_last_of("/\\") + 1);


    //File
    ifstream file(filePath);

    //Reading file
    string fileText;
    string line;

    while (getline(file, line)) {
        line += "\n";
        lines.push_back(line);
        fileText += line;
    }

    file.close();

    l = new Lexer(fileText, fileName);
    vector<BaseToken *> v = l->makeTokens();
    if(v.empty()){
        cout << l->error->toString() << endl;
        return 0;
    }
    p = new Parser(v, fileName, lines);
    res = p->parse();
    if (res->error) {
        cout << res->error->toString() << endl;
        return 0;
    } else {
        //cout << "AST: " + res->node->toString() << endl;
    }
    Interpreter *i = new Interpreter(fileName, lines);
    Context *ctx = new Context("<program>");
    ctx->symbolTable = globalSymbolTable;
    RuntimeResult *result = i->visit(res->node, ctx);
    if (result->error) {
        cout << result->error->toString() << endl;
        return 0;
    } else if (result->value) {
        cout << result->value->toString() << endl;
    }
    return 0;
}

int shellInput() {
    fileName = "<stdin>";
    while (true) {
        lines = vector<string>();
        string input;
        cout << "Boa % ";
        getline(cin, input);

        input += "\n";

        lines.push_back(input);

        clock_t start = clock();
        l = new Lexer(input, fileName);
        vector<BaseToken *> v = l->makeTokens();
        if(v.empty()){
            cout << l->error->toString() << endl;
            continue;
        }
//        for(BaseToken *t : v){
//            cout << t->toString() << endl;
//        }
        p = new Parser(v, fileName, lines);
        res = p->parse();
        if (res->error) {
            cout << res->error->toString() << endl;
            continue;
        } else {
            //cout << "AST: " + res->node->toString() << endl;
        }
        Interpreter *i = new Interpreter(fileName, lines);
        Context *ctx = new Context("<program>");
        ctx->symbolTable = globalSymbolTable;
        try{
            RuntimeResult *result = i->visit(res->node, ctx);
            clock_t stop = clock();
            if (result->error) {
                cout << result->error->toString() << endl;
                continue;
            } else if (result->value) {
                cout << result->value->toString() << endl;
            }
            cout << "Execution time: " << (stop - start) / (double) CLOCKS_PER_SEC << " seconds" << endl;
        } catch (const std::bad_alloc &e) {
            cout << "MemoryError: Can't allocate region" << endl;
        }
    }
}

int main() {
    globalSymbolTable->set("null", new Number<double>(0, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("PI", new Number<double>(M_PI, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("true", new Number<double>(1, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("false", new Number<double>(0, fileName, "Definition in default globalSymbolTable"));
    return shellInput();
}

#pragma clang diagnostic pop