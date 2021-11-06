#include <iostream>
#include "includes/values/String.cpp"
#include "includes/values/Number.cpp"
#include "includes/Lexer.cpp"
#include "includes/Token.cpp"
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
    Lexer *l = new Lexer(fileText);
    vector<BaseToken *> v = l->makeTokens();
    for (int i = 0; i < v.size(); i++) {
        BaseToken *t = v[i];
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
    return 0;
}
