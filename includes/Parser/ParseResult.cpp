//
// Created by Preeti Thorat on 11/17/21.
//

#include "ParseResult.h"

ParseResult::ParseResult(Node *node, Error *error) {
    this->node = node;
    this->error = error;
}

Node * ParseResult::reg(ParseResult *result) {
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
    this->error = error;
    return this;
}