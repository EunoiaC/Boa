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
    symbolTable->set("readLines", new FileFunction<int>(this, "readLines", {},
                                                        {}, "", ""));
    symbolTable->set("write", new FileFunction<int>(this, "write", {"toAdd"},
                                                        {}, "", ""));
    symbolTable->set("writeLines", new FileFunction<int>(this, "writeLines", {"list"},
                                                    {}, "", ""));
    symbolTable->set("close", new FileFunction<int>(this, "close", {},
                                                        {}, "", ""));

    file = fstream(fileName->getValue());
    if (file.fail()) {
        file = fstream(parentPath->getValue() + fileName->getValue());
    }
    if (file.fail()) {
        rtError = new RuntimeError(
                        fileName->posStart,
                        fileName->posEnd,
                        fileName->line,
                        fileName->fName,
                        fileName->fTxt,
                        "File doesn't exist",
                        ctx
               );
    }
}

template<>
BaseValue *File<int>::copy() {
    return new File<int>(this->fileName, this->parentPath);
}

template<>
string File<int>::toString() {
    return "<File: " + this->fileName->getValue() + ">";
}