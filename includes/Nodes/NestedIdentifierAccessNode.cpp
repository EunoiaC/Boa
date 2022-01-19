//
// Created by Preeti Thorat on 1/18/22.
//

#include "NestedIdentifierAccessNode.h"

NestedIdentifierAccessNode::NestedIdentifierAccessNode(Node *mainVal, vector<BaseToken *> identifiers): Node(N_NEST_ID_ACC) {
    this->mainVal = mainVal;
    this->identifiers = identifiers;
    posStart = mainVal->posStart;
    posEnd = identifiers.back()->posEnd;
}

string NestedIdentifierAccessNode::toString() {
    string str = "";
    str += mainVal->toString();
    for (int i = 0; i < identifiers.size(); i++) {
        str += "." + identifiers[i]->toString();
    }
    return str;
}