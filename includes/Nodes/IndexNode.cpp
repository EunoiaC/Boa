//
// Created by Preeti Thorat on 1/30/22.
//

#include "IndexNode.h"

IndexNode::IndexNode(Node *left, vector<Node*> indices) : Node(N_IDX_NODE) {
    this->left = left;
    this->indices = move(indices);
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

