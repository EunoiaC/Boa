//
// Created by Preeti Thorat on 1/14/22.
//

#ifndef BOA_IMPORTNODE_H
#define BOA_IMPORTNODE_H


#include "../Node.h"

class ImportNode : public Node {
public:
    Node * toImport;
    int posStart, posEnd, line;
    ImportNode(Node *toImport, int posStart, int posEnd, int line);
};



#endif //BOA_IMPORTNODE_H
