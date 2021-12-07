//
// Created by Aadi Yadav on 11/17/21.
//

#ifndef BOA_ERROR_H
#define BOA_ERROR_H


#include "../Context/Context.h"

#include <string>
using namespace std;

class Error {
public:
    int posStart, posEnd, line;
    string fName, fTxt, msg, errorName;
    Error(int posStart, int posEnd, int line, string fName, string fTxt, string errorName, string msg);
    virtual string toString();
    string getArrows();
};


#endif //BOA_ERROR_H
