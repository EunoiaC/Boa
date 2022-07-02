//
// Created by Preeti Thorat on 7/2/22.
//

#include "SQLiteDB.h"
#include "SQLiteDBFunction.h"

template<>
SQLiteDB<int>::SQLiteDB(sqlite3 * db) : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;
    this->db = db;

    symbolTable->set("exec", new SQLiteDBFunction<int>(this, "exec", {"stmt"}, defaultArgs, "", ""));
    symbolTable->set("setCallback", new SQLiteDBFunction<int>(this, "setCallback", {"callback"}, defaultArgs, "", ""));
}

template<>
BaseValue *SQLiteDB<int>::copy() {
    auto *socket = new SQLiteDB<int>(db);
    return socket;
}

template<>
string SQLiteDB<int>::toString() {
    return "<SQLiteDB>";
}