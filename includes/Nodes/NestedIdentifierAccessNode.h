//
// Created by Preeti Thorat on 1/18/22.
//

#ifndef BOA_NESTEDIDENTIFIERACCESSNODE_H
#define BOA_NESTEDIDENTIFIERACCESSNODE_H

#include "../Token/Token.h"
#include "Node.h"

using namespace std;

class NestedIdentifierAccessNode : public Node {
public:
    int posStart, posEnd, line;
    string toString() override;
    string fName, fTxt;
    Node * mainVal;
    vector<BaseToken*> identifiers;
    NestedIdentifierAccessNode(Node * mainVal, vector<BaseToken*> identifiers);
};


#endif //BOA_NESTEDIDENTIFIERACCESSNODE_H
