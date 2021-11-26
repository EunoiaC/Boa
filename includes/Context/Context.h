//
// Created by Preeti Thorat on 11/25/21.
//

#ifndef BOA_CONTEXT_H
#define BOA_CONTEXT_H


class Context {
public:
    string displayName, fName, fTxt;
    Context *parentCtx;
    int parentEntry, line;

    Context *setParentCtx(Context *parentCtx), *setParentEntry(int parentEntry, string fName, string fTxt, int line);


    explicit Context(string displayName);
};


#endif //BOA_CONTEXT_H
