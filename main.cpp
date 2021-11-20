#include <iostream>
#include "includes/Parser/Parser.cpp"
#include "includes/Lexer.cpp"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<string> lines;
    string fileName = "/Users/preetithorat/Documents/GitHub/Boa/Testing/Test.boa";

    //File
    ifstream file(fileName);

    //Reading file
    string fileText;
    string line;

    while (getline(file, line)){
        line += "\n";
        lines.push_back(line);
        fileText += line;
    }


//    if (file.is_open()) {
//        char mychar;
//        while (file) {
//            mychar = file.get();
//            fileText += mychar;
//        }
//    }
    Lexer *l = new Lexer(fileText, fileName);
    vector<BaseToken *> v = l->makeTokens();
    for (auto t : v) {
        if (t->type == T_IDENTIFIER) {
            cout << ((Token<string> *) t)->toString() << endl;
        } else if (t->type == T_NUM) {
            cout << ((Token<double> *) t)->toStringNumber() << endl;
        } else if (t->type == T_STRING) {
            cout << ((Token<string> *) t)->toString() << endl;
        }else {
            cout << t->toString() << endl;
        }
    }
    Parser *p = new Parser(v, fileName, lines);
    ParseResult * res = p->parse();
    if(res->error) {
        cout << res->error->toString() << endl;
    } else{
        cout << "AST: " + res->node->toString() << endl;
    }
    return 0;
}
