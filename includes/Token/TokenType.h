//
// Created by Preeti Thorat on 11/1/21.
//

#pragma once
#ifndef BOA_TOKENTYPE_H
#define BOA_TOKENTYPE_H

#include <string>

using namespace std;

//All token types
static const string IDENTIFIER = "IDENTIFIER";
static const string KEYWORD = "KEYWORD";
static const string PLUS = "PLUS";
static const string MINUS = "MINUS";
static const string MULTIPLY = "MULTIPLY";
static const string DIVIDE = "DIVIDE";
static const string POWER = "POWER";
static const string MOD = "MOD";
static const string EQUAL = "EQUAL";
static const string PLUS_EQUAL = "PLUS_EQUAL";
static const string LESS_THAN = "LESS_THAN";
static const string GREATER_THAN = "GREATER_THAN";
static const string L_PAREN = "L_PAREN";
static const string R_PAREN = "R_PAREN";
static const string L_BRACKET = "L_BRACKET";
static const string R_BRACKET = "R_BRACKET";
static const string END_OF_FILE = "END_OF_FILE";
static const string STOP_EXPR = "STOP_EXPR";
static const string NUMBERS = "1234567890";
static const string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

#endif //BOA_TOKENTYPE_H
