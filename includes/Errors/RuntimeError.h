//
// Created by Aadi Yadav on 11/25/21.
//

#ifndef BOA_RUNTIMEERROR_H
#define BOA_RUNTIMEERROR_H

#include "Error.h"

class RuntimeError : public Error {
public:
    Context * ctx;
    RuntimeError(int posStart, int posEnd, int line, string fName, string fTxt, string msg, Context * ctx);
    string toString(), generateTraceback();
};


#endif //BOA_RUNTIMEERROR_H
