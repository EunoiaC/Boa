//
// Created by Aadi Yadav on 11/20/21.
//

#ifndef BOA_INTERPRETER_H
#define BOA_INTERPRETER_H
#include "../Values/Number.h"
#include "../Values/String.h"
#include "../Values/Functions/Function.h"
#include "../Values/List.h"
#include "../Values/Map.h"
#include "../RuntimeResult/RuntimeResult.h"
#include "../Nodes/ForNode.h"
#include "../Nodes/WhileNode.h"
#include "../Nodes/IfNode.h"
#include "../Nodes/FuncDefNode.h"
#include "../Nodes/VarAccessNode.h"
#include "../Nodes/VarAssignNode.h"
#include "../Nodes/BinaryOperationNode.h"
#include "../Nodes/NumberNode.h"
#include "../Nodes/StringNode.h"
#include "../Nodes/ListNode.h"
#include "../Nodes/MapNode.h"
#include "../Nodes/UnaryOperationNode.h"
#include "../Nodes/CallNode.h"
#include <string>
#include <vector>

using namespace std;

class Interpreter {
public:
    string fName;
    vector<string> lines;
    //Change typedef with return type of function
    typedef RuntimeResult * (Interpreter::*FnPtr)(Node* n, Context* c);
    map<string, FnPtr> funcMap;
    Interpreter(string name, vector<string> l);
    RuntimeResult * visit(Node * n, Context * c);

    RuntimeResult * visitNumberNode(Node * n, Context* c);
    RuntimeResult * visitStringNode(Node * n, Context* c);
    RuntimeResult * visitListNode(Node * n, Context* c);
    RuntimeResult * visitMapNode(Node * n, Context* c);

    RuntimeResult * visitBinOpNode(Node * n, Context* c);
    RuntimeResult * visitUnaryOpNode(Node * n, Context* c);
    RuntimeResult * visitVarAssignNode(Node * n, Context* c);
    RuntimeResult * visitVarAccessNode(Node * n, Context* c);

    RuntimeResult * visitIfNode(Node * n, Context* c);
    RuntimeResult * visitForNode(Node * n, Context* c);
    RuntimeResult * visitWhileNode(Node * n, Context* c);

    RuntimeResult * visitFuncDefNode(Node * n, Context* c);
    RuntimeResult * visitCallNode(Node * n, Context* c);
};


#endif //BOA_INTERPRETER_H
