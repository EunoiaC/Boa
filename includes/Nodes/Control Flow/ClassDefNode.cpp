//
// Created by Preeti Thorat on 2/2/22.
//

#include "ClassDefNode.h"

ClassDefNode::ClassDefNode(Token<string> *classNameTok, vector<Token<string> *> argNameToks,
                           map<string, Node *> defaultArgs, vector<Node *> members) : Node(N_CLASS_DEF) {
    this->classNameTok = classNameTok;
    this->argNameToks = argNameToks;
    this->defaultArgs = defaultArgs;
    this->members = members;

    posStart = classNameTok->posStart;
    posEnd = members.back()->posEnd;
}