//
// Created by Preeti Thorat on 1/30/22.
//

#include "IndexNode.h"

IndexNode::IndexNode(Node *left, vector<Node*> indices, string type) : Node(N_IDX) {
    this->left = left;
    this->indices = move(indices);
    this->type = type;
}

IndexNode::~IndexNode() {
    delete left;
    for (auto & index : indices) {
        delete index;
    }
}

string IndexNode::toString() {
    string str = "";
    str += left->toString();
    str += "[";
    for (auto & index : indices) {
        str += index->toString();
        str += ",";
    }
    str.pop_back();
    str += "]";
    return str;
}

