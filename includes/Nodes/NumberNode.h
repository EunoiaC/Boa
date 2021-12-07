//
// Created by Aadi Yadav on 11/7/21.
//

#ifndef BOA_NUMBERNODE_H
#define BOA_NUMBERNODE_H

#include "Node.h"
#include "../Token/Token.h"

class NumberNode : public Node {
public:
    NumberNode(Token<double> *value);
    /**
     * Value of the node
     */
    Token<double> *token;
    string toString();
};


#endif //BOA_NUMBERNODE_H
