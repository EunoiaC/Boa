#include <iostream>
#include "includes/Parser/Parser.cpp"
#include "includes/Lexer/Lexer.cpp"
#include <string>
#include <vector>
#include "includes/Interpreter/Interpreter.cpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    vector<string> lines;
    Lexer *l;
    Parser *p;
    ParseResult *res;

    string filePath = "/Users/preetithorat/Documents/GitHub/Boa/Testing/Test.boa";
    string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);

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
    RuntimeResult* result = i->visit(res->node, ctx);
    if(result->error){
        cout << result->error->toString() << endl;
        return 0;
    } else {
        cout << ((Number *) result->value)->numValue << endl;
    }
    return 0;
}

#pragma clang diagnostic pop