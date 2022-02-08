//
// Created by Preeti Thorat on 2/2/22.
//

#ifndef BOA_CLASSDEFNODE_H
#define BOA_CLASSDEFNODE_H

#include "../Node.h"
#include "../../Token/Token.h"

class ClassDefNode : public Node {
public:
    vector<Token<string> *> argNameToks;
    vector<Node *> members;
    Node *superClass;
    map<string, Node*> defaultArgs;
    Node *body;
    Token<string> *classNameTok;
    int posStart, posEnd;
    ClassDefNode(Token<string> *classNameTok, vector<Token<string> *> argNameToks, map<string, Node*> defaultArgs, vector<Node *> members, Node * superClass);
};


#endif //BOA_CLASSDEFNODE_H
