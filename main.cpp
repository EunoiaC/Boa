#include <iostream>
#include "includes/Parser.cpp"
#include "includes/Lexer.cpp"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    //File
    ifstream file("/Users/preetithorat/Documents/GitHub/Boa/Testing/Test.boa");
    //Reading file
    string fileText;
    if (file.is_open()) {
        char mychar;
        while (file) {
            mychar = file.get();
            fileText += mychar;
        }
    }
    file.close();
    Lexer *l = new Lexer(fileText);
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
    Parser *p = new Parser(v);
    Node * n = p->parse();
    cout << n->toString() << endl;
    return 0;
}
