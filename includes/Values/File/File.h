//
// Created by Preeti Thorat on 2/27/22.
//

#ifndef BOA_FILE_H
#define BOA_FILE_H

#include "../BaseValues/Value.h"
#include "../String/String.h"
#include <fstream>

template<typename T> class File : public Value<T> {
public:
    fstream file;
    String<string> * fileName, * parentPath;
    File<int>(String<string> * fileName, String<string> * parentPath);
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_FILE_H
