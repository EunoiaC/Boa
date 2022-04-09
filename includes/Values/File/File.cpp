//
// Created by Preeti Thorat on 2/27/22.
//

#include "File.h"
#include "FileFunction.h"

template<>
File<int>::File(String<string> * fileName, String<string> * parentPath) : Value<int>(0, "FILE", "", "") {
    this->fileName = fileName;
    this->parentPath = parentPath;
    symbolTable->set("fileName", fileName);
    symbolTable->set("parentPath", parentPath);
    symbolTable->set("read", new FileFunction<int>(this, "read", {},
                                                             {}, "", ""));
    symbolTable->set("readLines", new FileFunction<int>(this, "readLines", {},
                                                             {}, "", ""));
}

template<>
BaseValue *File<int>::copy() {
    return new File<int>(this->fileName, this->parentPath);
}

template<>
string File<int>::toString() {
    return "<File: " + this->fileName->getValue() + ">";
}