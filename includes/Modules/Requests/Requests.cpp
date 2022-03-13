//
// Created by Preeti Thorat on 3/12/22.
//

#include "Requests.h"

template<>
Requests<int>::Requests() : Value<int>(0, "REQUESTS", "", "") {
    //symbolTable->set()
}

template<>
BaseValue *Requests<int>::copy() {
    return new Requests<int>(*this);
}

template<>
string Requests<int>::toString() {
    return "<Module: random>";
}