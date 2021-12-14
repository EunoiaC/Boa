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
    g++ main.cpp includes/Token/Token.cpp includes/Token/Token.h includes/Values/Value.cpp includes/Values/Value.h includes/Nodes/Node.cpp includes/Nodes/Node.h includes/Context/Context.cpp includes/Context/Context.h includes/Errors/Error.cpp includes/Errors/Error.h includes/Errors/RuntimeError.cpp includes/Errors/RuntimeError.h includes/Values/Number.cpp includes/Values/Number.h includes/Nodes/CallNode.cpp includes/Nodes/CallNode.h includes/Nodes/ForNode.cpp includes/Nodes/ForNode.h includes/Nodes/FuncDefNode.cpp includes/Nodes/FuncDefNode.h includes/Nodes/IfNode.cpp includes/Nodes/IfNode.h includes/Nodes/NumberNode.cpp includes/Nodes/NumberNode.h includes/Nodes/UnaryOperationNode.cpp includes/Nodes/UnaryOperationNode.h includes/Nodes/VarAccessNode.cpp includes/Nodes/VarAccessNode.h includes/Nodes/VarAssignNode.cpp includes/Nodes/VarAssignNode.h includes/Nodes/VarOperationNode.cpp includes/Nodes/VarOperationNode.h includes/Nodes/WhileNode.cpp includes/Nodes/WhileNode.h includes/Nodes/BinaryOperationNode.cpp includes/Nodes/BinaryOperationNode.h includes/Parser/ParseResult.cpp includes/Parser/ParseResult.h includes/RuntimeResult/RuntimeResult.cpp includes/RuntimeResult/RuntimeResult.h includes/SymbolTable/SymbolTable.cpp includes/SymbolTable/SymbolTable.h includes/Parser/Parser.cpp includes/Parser/Parser.h includes/Lexer/Lexer.cpp includes/Lexer/Lexer.h includes/Interpreter/Interpreter.cpp includes/Interpreter/Interpreter.h includes/Token/BaseToken.cpp includes/Token/BaseToken.h includes/Values/BaseValue.cpp includes/Values/BaseValue.h
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
        RuntimeResult *result = i->visit(res->node, ctx);
        clock_t stop = clock();
        if (result->error) {
            cout << result->error->toString() << endl;
            continue;
        } else if (result->value) {
            cout << result->value->toString() << endl;
        }
        cout << "Execution time: " << (stop - start) / (double) CLOCKS_PER_SEC << " seconds" << endl;
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