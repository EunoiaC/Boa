//
// Created by Preeti Thorat on 7/2/22.
//

#ifndef BOA_SQLITEDB_H
#define BOA_SQLITEDB_H

#include "../../../Values/String/String.h"
#include "../../../Values/Functions/Function.h"
#include <sqlite3.h>

template <typename T> class SQLiteDB : public Value<T> {
public:
    sqlite3 *db;
    Function<int> * callBack;
    SQLiteDB<int>(sqlite3 *db);
    BaseValue * copy() override;
    string toString() override;
};


#endif //BOA_SQLITEDB_H
