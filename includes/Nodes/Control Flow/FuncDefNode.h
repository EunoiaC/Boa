//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_FUNCDEFNODE_H
#define BOA_FUNCDEFNODE_H
#include <string>
#include "../../Token/Token.h"
#include "../Node.h"
#include <vector>

class FuncDefNode : public Node {
public:
    vector<Token<string> *> argNameToks;
    map<string, Node*> defaultArgs;
    vector<string> uses;
    Node *body;
    Token<string> *funcNameTok;
    int posStart, posEnd;
    bool autoReturn;

    string toString() override;

    FuncDefNode(Token<string> *funcNameTok, vector<Token<string> *> argNameToks, map<string, Node*> defaultArgs, vector<string> uses, Node *body, bool autoReturn);
};


#endif //BOA_FUNCDEFNODE_H
