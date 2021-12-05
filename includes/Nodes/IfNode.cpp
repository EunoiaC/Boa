//
// Created by Preeti Thorat on 12/4/21.
//

#include "IfNode.h"

IfNode::IfNode(vector<tuple<Node *, Node *>> cases, Node *elseCase) : Node(N_IF){
    this->cases = cases;
    this->elseCase = elseCase;

    posStart = get<0>(cases[0])->posStart;
    if(elseCase != nullptr) {
        posEnd = elseCase->posEnd;
    }else{
        posEnd = get<1>(cases[cases.size()-1])->posEnd;
    }
}