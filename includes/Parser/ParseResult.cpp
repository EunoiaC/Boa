//
// Created by Aadi Yadav on 11/17/21.
//

#include "ParseResult.h"

ParseResult::ParseResult(Node *node, Error *error) {
    this->node = node;
    this->error = error;
    advanceCount = 0;
    lastRegAdvanceCount = 0;
    toReverseCount = 0;
}

void ParseResult::regAdvancement() {
    lastRegAdvanceCount = 1;
    advanceCount++;
}

Node * ParseResult::reg(ParseResult *result) {
    lastRegAdvanceCount = result->advanceCount;
    advanceCount += result->advanceCount;
    if (result->error) {
        error = result->error;
    }
    return result->node;
}

Node * ParseResult::reg(Node *result) {
    return result;
}

Node * ParseResult::tryReg(ParseResult *res) {
    if(res->error){
        toReverseCount = res->advanceCount;
        return nullptr;
    }
    return reg(res);
}


ParseResult *ParseResult::success(Node *node) {
    this->node = node;
    return this;
}

ParseResult *ParseResult::failure(Error *error) {
    if(not this->error || advanceCount == 0) this->error = error;
    return this;
}