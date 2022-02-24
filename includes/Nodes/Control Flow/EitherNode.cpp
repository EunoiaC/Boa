//
// Created by Preeti Thorat on 2/23/22.
//

#include "EitherNode.h"

EitherNode::EitherNode(Node *first, Node *second) : Node(N_EITHER) {
    this->first = first;
    this->second = second;
}