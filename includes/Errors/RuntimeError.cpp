//
// Created by Aadi Yadav on 11/25/21.
//

#include <iostream>
#include "RuntimeError.h"

RuntimeError::RuntimeError(int posStart, int posEnd, int line, string fName, string fTxt, string msg, Context *ctx) : Error(posStart, posEnd, line, fName, fTxt, "RuntimeError", msg){
    this->ctx = ctx;
}

string RuntimeError::toString() {
    //TODO: Add arrow under string
    string t = generateTraceback();
    t += errorName + ": " + msg + "\n";
    t += fName + " at line " + to_string(line + 1) + "\n";
    t += "\n" + fTxt;
    t += getArrows();
    return t;
}

string RuntimeError::generateTraceback() {
    string res;
    int l = line;
    Context *context = ctx;
    string fileName = fName;
    while(context){
        //cout << "File: " << fileName << " Line: " << l << endl;
        res = "    File " + fileName + ", line " + to_string( l + 1) + ", in " + context->displayName + "\n";
        fileName = context->fName;
        l = context->line;
        context = context->parentCtx;
    }
    return "Traceback (most recent call last):\n" + res;
}