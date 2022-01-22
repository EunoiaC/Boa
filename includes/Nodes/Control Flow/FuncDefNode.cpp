//
// Created by Preeti Thorat on 12/5/21.
//

#include "FuncDefNode.h"

#include <utility>

FuncDefNode::FuncDefNode(Token<string>* funcNameTok, vector<Token<string>*> argNameToks, map<string, Node*> defaultArgs, Node *body, bool autoReturn) : Node(N_FUNC_DEF) {
    this->funcNameTok = funcNameTok;
    this->argNameToks = std::move(argNameToks);
    this->body = body;
    this->autoReturn = autoReturn;
    this->defaultArgs = std::move(defaultArgs);

    if(funcNameTok){
        posStart = funcNameTok->posStart;
    } else if(argNameToks.size() > 0){
        posStart = argNameToks[0]->posStart;
    } else {
        posStart = body->posStart;
    }

    posEnd = body->posEnd;
}

string FuncDefNode::toString() {
    return "(FuncDefNode: " + funcNameTok->getValueObject()->getValue() + ", " + body->toString() + ")";
}