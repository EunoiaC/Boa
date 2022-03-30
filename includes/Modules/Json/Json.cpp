//
// Created by Preeti Thorat on 3/21/22.
//

#include "Json.h"

template<>
BaseValue * Json<int>::copy() {
    return new Json<int>(*this);
}

template<>
string Json<int>::toString() {
    return "<Module: random>";
}