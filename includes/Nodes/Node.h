//
// Created by Preeti Thorat on 11/7/21.
//
#pragma once
#ifndef BOA_NODE_H
#define BOA_NODE_H


class Node {
public:
    Node(string type);
    /**
     * Type of the node
     */
     string type;
     virtual string toString();
};


#endif //BOA_NODE_H
