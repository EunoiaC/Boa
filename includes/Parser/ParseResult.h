//
// Created by Aadi Yadav on 11/17/21.
//

#ifndef BOA_PARSERESULT_H
#define BOA_PARSERESULT_H
#include "../Errors/Error.h"
#include "../Nodes/Node.h"

class ParseResult {
public:
    int advanceCount, toReverseCount, lastRegAdvanceCount;
    Node * node;
    Error * error;
    ParseResult(Node * node, Error * error);
    Node * reg(ParseResult * result);
    Node * tryReg(ParseResult * result);
    Node * reg(Node * result);
    ParseResult * success(Node * node);
    ParseResult * failure(Error * error);
    void regAdvancement();
};


#endif //BOA_PARSERESULT_H
