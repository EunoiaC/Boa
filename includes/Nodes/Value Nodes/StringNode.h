//
// Created by Preeti Thorat on 12/10/21.
//

#ifndef BOA_STRINGNODE_H
#define BOA_STRINGNODE_H


#include "../Node.h"
#include "../../Token/Token.h"

class StringNode : public Node {
public:
    StringNode(Token<string> *value);
    /**
     * Value of the node
     */
    Token<string> *token;
    string toString() override;
};


#endif //BOA_STRINGNODE_H
