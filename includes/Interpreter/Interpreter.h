//
// Created by Aadi Yadav on 11/20/21.
//

#ifndef BOA_INTERPRETER_H
#define BOA_INTERPRETER_H
#include <thread>
#include <future>
#include "../Values/Number/Number.h"
#include "../Values/Future/Future.h"
#include "../Values/String/String.h"
#include "../Values/Functions/Function.h"
#include "../Values/List/List.h"
#include "../Values/Map.h"
#include "../Values/Class/Class.h"
#include "../RuntimeResult/RuntimeResult.h"
#include "../Nodes/Control Flow/ForNode.h"
#include "../Nodes/Control Flow/IterateNode.h"
#include "../Nodes/Control Flow/WhileNode.h"
#include "../Nodes/Control Flow/IfNode.h"
#include "../Nodes/Control Flow/EitherNode.h"
#include "../Nodes/Control Flow/FuncDefNode.h"
#include "../Nodes/Control Flow/ClassDefNode.h"
#include "../Nodes/Control Flow/TryCatchNode.h"
#include "../Nodes/Statements/Branching Statements/ReturnNode.h"
#include "../Nodes/Statements/Branching Statements/BreakNode.h"
#include "../Nodes/Statements/Branching Statements/ContinueNode.h"
#include "../Nodes/Statements/ImportNode.h"
#include "../Nodes/Statements/AwaitNode.h"
#include "../Nodes/VarAccessNode.h"
#include "../Nodes/VarAssignNode.h"
#include "../Nodes/BinaryOperationNode.h"
#include "../Nodes/Value Nodes/NumberNode.h"
#include "../Nodes/Value Nodes/StringNode.h"
#include "../Nodes/Value Nodes/ListNode.h"
#include "../Nodes/Value Nodes/MapNode.h"
#include "../Nodes/UnaryOperationNode.h"
#include "../Nodes/CallNode.h"
#include "../Values/Functions/BuiltInFunction.h"
#include "../Values/Class/ClassFunction.h"
#include "../Values/Class/UsableClass.h"
#include "../Modules/Random/Random.h"
#include <string>
#include <vector>
#include "../Modules/Requests/Requests.h"
#include "../Modules/Json/Json.h"

using namespace std;

class Interpreter {
public:
    string fName, pathRef;
    vector<string> lines;
    //Change typedef with return type of function
    typedef RuntimeResult * (Interpreter::*FnPtr)(Node* n, Context* c);
    map<string, FnPtr> funcMap;
    map<string, BaseValue *> stdlib = {
            {"random", new Random<int>("fName", "fTxt")},
            {"requests", new Requests<int>()},
            {"json", new Json<int>()}
    };
    Interpreter(string name, vector<string> l);
    RuntimeResult * visit(Node * n, Context * c);

    RuntimeResult * visitReturnNode(Node * n, Context* c);
    RuntimeResult * visitBreakNode(Node * n, Context* c);
    RuntimeResult * visitContinueNode(Node * n, Context* c);
    RuntimeResult * visitImportNode(Node * n, Context* c);
    RuntimeResult * visitAwaitNode(Node * n, Context* c);

    RuntimeResult * visitNumberNode(Node * n, Context* c);
    RuntimeResult * visitStringNode(Node * n, Context* c);
    RuntimeResult * visitListNode(Node * n, Context* c);
    RuntimeResult * visitMapNode(Node * n, Context* c);

    RuntimeResult * visitBinOpNode(Node * n, Context* c);
    RuntimeResult * visitUnaryOpNode(Node * n, Context* c);
    RuntimeResult * visitIndexNode(Node * n, Context* c);
    RuntimeResult * visitVarAssignNode(Node * n, Context* c);
    RuntimeResult * visitVarAccessNode(Node * n, Context* c);

    RuntimeResult * visitIfNode(Node * n, Context* c);
    RuntimeResult * visitEitherNode(Node * n, Context* c);
    RuntimeResult * visitForNode(Node * n, Context* c);
    RuntimeResult * visitIterateNode(Node * n, Context* c);
    RuntimeResult * visitWhileNode(Node * n, Context* c);
    RuntimeResult * visitTryCatchNode(Node * n, Context* c);

    RuntimeResult * visitFuncDefNode(Node * n, Context* c);
    RuntimeResult * visitClassDefNode(Node * n, Context* c);
    RuntimeResult * visitCallNode(Node * n, Context* c);
};


#endif //BOA_INTERPRETER_H