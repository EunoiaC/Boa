//
// Created by Aadi Yadav on 11/17/21.
//

#include "Error.h"
Error::Error(int posStart, int posEnd, int line, string fName, string fTxt, string errorName, string msg) {
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
    this->fName = fName;
    this->fTxt = fTxt;
    this->msg = msg;
    this->errorName = errorName;
}

string Error::toString() {
    //TODO: Add arrow under string
    string t = errorName + ": " + msg + "\n";
    t += fName + " at line " + to_string(line + 1) + "\n"; //Line incremented by 1 as line starts from 0
    t += "\n" + fTxt;
    t += getArrows();
    return t;
}

string Error::getArrows() {
    //TODO: detect \n
    string arrows;
    for (int i = 0; i < posStart; i++) {
        arrows += " ";
    }
    for (int i = posStart; i <= posEnd; i++) {
        arrows += "^";
    }
    return arrows;
}