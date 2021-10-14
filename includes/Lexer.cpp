//
// Created by Administrator on 10/13/2021.
//

#include "Lexer.h"

Lexer::Lexer(string txt) {
    text = txt;
    advance();
}

list<Token> Lexer::makeTokens() {
    list<Token*> * toks = new list<Token*>();
    while(currentChar != '\0'){
        advance();
        toks->push_back(new Token("asda", new Value<char>(currentChar, "char")));
    }
}

void Lexer::advance() {
    idx++;
    /* If the index is the length
    of the string, the
    end of the text has been reached.
     */
    if(idx == text.length()){
        currentChar = '\0';
        return;
    }

    currentChar = text.at(idx);
}