//
// Created by Preeti Thorat on 11/25/21.
//

#include "Context.h"

Context::Context(string displayName) {
    this->displayName = displayName;
    parentCtx = nullptr;
    parentEntry = -1;
    line = -1;
    symbolTable = nullptr;
}

Context *Context::setParentEntry(int parentEntry, string fName, string fTxt, int line) {
    this->fName = fName;
    this->fTxt = fTxt;
    this->line = line;
    this->parentEntry = parentEntry;
}

Context *Context::setParentCtx(Context *parentCtx) {
    this->parentCtx = parentCtx;
}