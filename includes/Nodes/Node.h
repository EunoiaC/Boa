//
// Created by Aadi Yadav on 11/7/21.
//
#pragma once
#ifndef BOA_NODE_H
#define BOA_NODE_H

using namespace std;

class Node {
public:
    Node(string type);

    /**
     * Type of the node
     */
    int posStart, posEnd, line;
    string type;

    virtual string toString();
};


#endif //BOA_NODE_H
