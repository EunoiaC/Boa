#include <iostream>
#include "includes/Parser/Parser.cpp"
#include "includes/Lexer/Lexer.cpp"
#include <string>
#include <vector>
#include <time.h>
#include "includes/Interpreter/Interpreter.cpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

vector<string> lines;
Lexer *l;
Parser *p;
ParseResult *res;
SymbolTable *globalSymbolTable = new SymbolTable();
string fileName;

int readFile(){
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
    RuntimeResult* result = i->visit(res->node, ctx);
    if(result->error){
        cout << result->error->toString() << endl;
        return 0;
    } else if(result->value){
        cout << result->value->toString() << endl;
    }
    return 0;
}

int shellInput(){
    fileName = "<stdin>";
    while (true){
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
        RuntimeResult* result = i->visit(res->node, ctx);
        clock_t stop = clock();
        if(result->error){
            cout << result->error->toString() << endl;
            continue;
        } else if(result->value){
            cout << result->value->toString() << endl;
        }
        cout << "Execution time: " << (stop - start) / (double) CLOCKS_PER_SEC << " seconds" << endl;
    }
}

int main() {
    globalSymbolTable->set("null", new Number(0, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("PI", new Number(M_PI, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("true", new Number(1, fileName, "Definition in default globalSymbolTable"));
    globalSymbolTable->set("false", new Number(0, fileName, "Definition in default globalSymbolTable"));
    return shellInput();
}

#pragma clang diagnostic pop