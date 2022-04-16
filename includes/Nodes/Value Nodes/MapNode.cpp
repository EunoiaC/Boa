//
// Created by Preeti Thorat on 12/18/21.
//

#include "MapNode.h"

MapNode::MapNode(map<Node *, Node *> dict, int posStart, int posEnd, int line) : Node(N_MAP) {
    this->dict = dict;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}

MapNode::~MapNode() {
    for (auto & it : dict) {
        delete it.first;
        delete it.second;
    }
}

string MapNode::toString() {
    string str;
    str += "MapNode: ";
    str += "{";
    for (auto it = dict.begin(); it != dict.end(); it++) {
        str += it->first->toString();
        str += ":";
        str += it->second->toString();
        str += ",";
    }
    str += "}";
    return str;
}