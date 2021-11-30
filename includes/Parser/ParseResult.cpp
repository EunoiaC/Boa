//
// Created by Aadi Yadav on 11/17/21.
//

#include "ParseResult.h"

ParseResult::ParseResult(Node *node, Error *error) {
    this->node = node;
    this->error = error;
    advanceCount = 0;
}

void ParseResult::regAdvancement() {
    advanceCount++;
}

Node * ParseResult::reg(ParseResult *result) {
    advanceCount += result->advanceCount;
    if (result->error) {
        error = result->error;
    }
    return result->node;
}

Node * ParseResult::reg(Node *result) {
    return result;
}

ParseResult *ParseResult::success(Node *node) {
    this->node = node;
    return this;
}

ParseResult *ParseResult::failure(Error *error) {
    if(!error || advanceCount == 0) this->error = error;
    return this;
}