//
// Created by Preeti Thorat on 12/12/21.
//

#ifndef BOA_LISTNODE_H
#define BOA_LISTNODE_H

#include <vector>
#include "Node.h"

class ListNode : public Node {
public:
    vector<Node*> elements;
    ListNode(vector<Node*> elements, int posStart, int posEnd, int line);

};


#endif //BOA_LISTNODE_H
