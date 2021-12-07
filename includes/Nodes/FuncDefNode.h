//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_FUNCDEFNODE_H
#define BOA_FUNCDEFNODE_H
#include <string>
#include "../Token/Token.h"
#include "Node.h"
#include <vector>

class FuncDefNode : public Node {
public:
    vector<Token<string> *> argNameToks;
    Node *body;
    Token<string> *funcNameTok;
    int posStart, posEnd;

    FuncDefNode(Token<string> *funcNameTok, vector<Token<string> *> argNameToks, Node *body);
};


#endif //BOA_FUNCDEFNODE_H
