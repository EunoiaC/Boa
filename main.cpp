#include <iostream>
#include "includes/Parser/Parser.cpp"
#include "includes/Lexer.cpp"
#include <string>
#include <fstream>
#include <vector>
#include "includes/Interpreter.cpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    vector<string> lines;
    Lexer *l;
    Parser *p;
    ParseResult *res;

    string fileName = "/Users/preetithorat/Documents/GitHub/Boa/Testing/Test.boa";

    //File
    ifstream file(fileName);

    //Reading file
    string fileText;
    string line;

    while (getline(file, line)) {
        line += "\n";
        lines.push_back(line);
        fileText += line;
    }

    l = new Lexer(fileText, fileName);
    vector<BaseToken *> v = l->makeTokens();
    p = new Parser(v, fileName, lines);
    res = p->parse();
    if (res->error) {
        cout << res->error->toString() << endl;
    } else {
        //cout << "AST: " + res->node->toString() << endl;
    }
    Interpreter *i = new Interpreter();
    auto result = i->visit(res->node);
    cout << ((Number*) result)->numValue << endl;
    return 0;
}

#pragma clang diagnostic pop