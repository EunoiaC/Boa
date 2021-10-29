#include <iostream>
#include "includes/values/String.cpp"
#include "includes/values/Number.cpp"
#include "includes/Token.cpp"
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<BaseToken*> t;
    t.push_back(new Token<string>(T_STRING, "ss"));
    t.push_back(new Token<double>(T_NUM, 12));

    for(auto & i : t){
        if(i->type == T_STRING){
            cout << "string" << endl;
        }
        if(i->type == T_NUM){
            cout << "num" << endl;
        }
    }
    return 0;
}
