//
// Created by Preeti Thorat on 7/2/22.
//

#ifndef BOA_SQLITE3_H
#define BOA_SQLITE3_H

#include "../../Values/BaseValues/Value.h"

template<typename T> class SQLite3 : public Value<T> {
public:
    SQLite3<int>();
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_SQLITE3_H
