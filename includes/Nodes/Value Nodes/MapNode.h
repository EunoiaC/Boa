//
// Created by Preeti Thorat on 12/18/21.
//

#ifndef BOA_MAPNODE_H
#define BOA_MAPNODE_H

#include "../Node.h"
#include <map>

using namespace std;

class MapNode : public Node {
public:
    int posStart, posEnd, line;
    map<Node*, Node*> dict;
    MapNode(map<Node*, Node*> dict, int posStart, int posEnd, int line);
    string toString() override;
};


#endif //BOA_MAPNODE_H
