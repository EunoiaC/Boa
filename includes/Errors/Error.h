//
// Created by Preeti Thorat on 11/17/21.
//

#ifndef BOA_ERROR_H
#define BOA_ERROR_H


class Error {
public:
    int posStart, posEnd, line;
    string fName, fTxt, msg, errorName;
    Error(int posStart, int posEnd, int line, string fName, string fTxt, string errorName, string msg);
    string toString();
    string getArrows();
};


#endif //BOA_ERROR_H
