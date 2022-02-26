//
// Created by Preeti Thorat on 2/23/22.
//

#include "EitherNode.h"

EitherNode::EitherNode(vector<Node *> nodes) : Node(N_EITHER) {
    this->nodes = nodes;
}