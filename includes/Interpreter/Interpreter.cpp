//
// Created by Aadi Yadav on 11/20/21.
//

#include <iostream>
#include "Interpreter.h"
#include "../RunInterface.h"
#include <filesystem>
#include <functional>
namespace fs = std::__fs::filesystem;


Interpreter::Interpreter(string name, vector<string> l) {
    fName = name;
    lines = l;
    funcMap[N_UNOP] = &Interpreter::visitUnaryOpNode;
    funcMap[N_BINOP] = &Interpreter::visitBinOpNode;
    funcMap[N_NUMBER] = &Interpreter::visitNumberNode;
    funcMap[N_STRING] = &Interpreter::visitStringNode;
    funcMap[N_LIST] = &Interpreter::visitListNode;
    funcMap[N_MAP] = &Interpreter::visitMapNode;
    funcMap[N_VAR_ACCESS] = &Interpreter::visitVarAccessNode;
    funcMap[N_VAR_ASSIGN] = &Interpreter::visitVarAssignNode;
    funcMap[N_IF] = &Interpreter::visitIfNode;
    funcMap[N_FOR] = &Interpreter::visitForNode;
    funcMap[N_ITER] = &Interpreter::visitIterateNode;
    funcMap[N_WHILE] = &Interpreter::visitWhileNode;
    funcMap[N_CALL] = &Interpreter::visitCallNode;
    funcMap[N_FUNC_DEF] = &Interpreter::visitFuncDefNode;
    funcMap[N_CLASS_DEF] = &Interpreter::visitClassDefNode;
    funcMap[N_RETURN] = &Interpreter::visitReturnNode;
    funcMap[N_CONTINUE] = &Interpreter::visitContinueNode;
    funcMap[N_BREAK] = &Interpreter::visitBreakNode;
    funcMap[N_IMPORT] = &Interpreter::visitImportNode;
    funcMap[N_IDX] = &Interpreter::visitIndexNode;
    funcMap[N_TRY_CATCH] = &Interpreter::visitTryCatchNode;
    funcMap[N_EITHER] = &Interpreter::visitEitherNode;
    funcMap[N_AWAIT] = &Interpreter::visitAwaitNode;
}

RuntimeResult *Interpreter::visit(Node *n, Context *c) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n, c);
}

RuntimeResult *Interpreter::visitIterateNode(Node *n, Context *c) {
    auto *node = (IterateNode *) n;
    auto *res = new RuntimeResult();
    vector<BaseValue *> elements;

    BaseValue *toIterateThrough = res->reg(visit(node->toIterateThrough, c));
    if (res->shouldReturn()) return res;
    BaseValue *value;

    if (toIterateThrough->type == TOK_TYPE::T_LIST) {
        for (auto *val: ((List<vector<BaseValue *>> *) toIterateThrough)->elements) {
            c->symbolTable->set(node->iterNameTok->getValueObject()->getValue(),
                                val);
            value = res->reg(visit(node->body, c));
            if (res->shouldReturn() && !res->loopContinue && !res->loopBreak) return res;

            if (res->loopContinue) {
                continue;
            }
            if (res->loopBreak) {
                break;
            }

            elements.push_back(value);
        }
    } else if (toIterateThrough->type == TOK_TYPE::T_STRING) {
        for (char ch: ((String<string> *) toIterateThrough)->getValue()) {
            c->symbolTable->set(node->iterNameTok->getValueObject()->getValue(),
                                new String<string>(string(1, ch), "", ""));
            value = res->reg(visit(node->body, c));
            if (res->shouldReturn() && !res->loopContinue && !res->loopBreak) return res;

            if (res->loopContinue) {
                continue;
            }
            if (res->loopBreak) {
                break;
            }
            elements.push_back(value);
        }
    } else if (toIterateThrough->type == TOK_TYPE::T_MAP) {
        auto *dict = (Map<map<BaseValue *, BaseValue *>> *) toIterateThrough;
        for (auto it: dict->dict) {
            auto *kv = new List<vector<BaseValue *>>({it.first, it.second}, "", "");
            c->symbolTable->set(node->iterNameTok->getValueObject()->getValue(),
                                kv);
            value = res->reg(visit(node->body, c));
            if (res->shouldReturn() && !res->loopContinue && !res->loopBreak) return res;

            if (res->loopContinue) {
                continue;
            }
            if (res->loopBreak) {
                break;
            }
            elements.push_back(value);
        }
    } else {
        return res->failure(new RuntimeError(
                toIterateThrough->posStart,
                toIterateThrough->posEnd,
                toIterateThrough->line,
                fName,
                lines[node->line],
                "Can't iterate type " + toIterateThrough->type,
                c
        ));
    }

    BaseValue *val = (new List<vector<BaseValue *>>(elements, fName, lines[node->iterNameTok->line]))->setContext(c)->setPos(
            node->posStart, node->posEnd, node->line);
    if (node->shouldReturnNull) {
        val = new Number<double>(0, fName, lines[node->line]);
    }

    return res->success(val);
}

RuntimeResult *Interpreter::visitForNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    ForNode *forNode = (ForNode *) n;
    vector<BaseValue *> elements;

    Number<double> *startVal = (Number<double> *) res->reg(visit(forNode->startVal, c));
    if (res->shouldReturn()) return res;

    Number<double> *endVal = (Number<double> *) res->reg(visit(forNode->endVal, c));
    if (res->shouldReturn()) return res;

    Number<double> *stepVal = new Number<double>(1, fName, "");

    if (forNode->stepVal) {
        stepVal = (Number<double> *) res->reg(visit(forNode->stepVal, c));
        if (res->shouldReturn()) return res;
    }

    double i = startVal->getValue();

    function<bool()> condition;

    if (stepVal->getValue() >= 0) {
        condition = [&] {
            return i <= endVal->getValue();
        };
    } else {
        condition = [&]() {
            return i >= endVal->getValue();
        };
    }

    BaseValue *val;

    while (condition()) {
        c->symbolTable->set(forNode->varNameTok->getValueObject()->getValue(),
                            new Number<double>(i, fName, lines[n->line]));
        i += stepVal->getValue();

        val = res->reg(visit(forNode->body, c));
        if (res->shouldReturn() && !res->loopContinue && !res->loopBreak) return res;

        if (res->loopContinue) {
            continue;
        }
        if (res->loopBreak) {
            break;
        }

        elements.push_back(val);
    }
    val = (new List<vector<BaseValue *>>(elements, fName, lines[n->line]))->setContext(c)->setPos(
            n->posStart, n->posEnd, n->line);
    if (forNode->shouldReturnNull) {
        val = new Number<double>(0, fName, lines[n->line]);
    }

    return res->success(val);
}

RuntimeResult *Interpreter::visitTryCatchNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *tryCatchNode = (TryCatchNode *) n;

    BaseValue * val = res->reg(visit(tryCatchNode->tryBlock, c));
    if (res->error){
        Context *ctx = new Context(tryCatchNode->catchName->getValueObject()->getValue());
        ctx->symbolTable = new SymbolTable();
        ctx->symbolTable->set("name", new String<string>(res->error->errorName, "", ""));
        ctx->symbolTable->set("message", new String<string>(res->error->msg, "", ""));
        ctx->symbolTable->set("line", new Number<double>(res->error->line + 1, "", ""));

        auto *err = new UsableClass<int>(fName, "", new Token<string>(TOK_TYPE::T_STRING, res->error->errorName, res->error->posStart, res->error->posEnd, res->error->line), {}, ctx, c, nullptr, lines);
        err->asString = res->error->toString();

        c->symbolTable->set(tryCatchNode->catchName->getValueObject()->getValue(), err);
        res->reset();

        BaseValue * v = res->reg(visit(tryCatchNode->catchBlock, c));
        if (res->shouldReturn()) return res;
        return res->success(v);
    }
    if (res->shouldReturn()) return res;
    return res->success(val);
}

RuntimeResult *Interpreter::visitWhileNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *whileNode = (WhileNode *) n;
    vector<BaseValue *> elements;

    BaseValue *val;

    while (true) {
        BaseValue *condition = res->reg(visit(whileNode->condition, c));
        if (res->shouldReturn()) return res;

        if (not condition->isTrue()) break;

        val = res->reg(visit(whileNode->body, c));
        if (res->shouldReturn() && !res->loopContinue && !res->loopBreak) return res;

        if (res->loopContinue) {
            continue;
        }
        if (res->loopBreak) {
            break;
        }
        elements.push_back(val);
    }
    val = (new List<vector<BaseValue *>>(elements, fName, ""))->setContext(c)->setPos(
            n->posStart, n->posEnd, n->line);
    if (whileNode->shouldReturnNull) {
        val = new Number<double>(0, fName, "");
    }
    //delete whileNode;
    return res->success(val);
}

RuntimeResult *Interpreter::visitEitherNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *eitherNode = (EitherNode *) n;

    for (auto &node : eitherNode->nodes) {
        BaseValue *val = res->reg(visit(node, c));
        if (res->shouldReturn()) return res;
        if (val->isTrue()) {
            return res->success(val);
        }
    }
    //delete eitherNode;
    return res->success((new Number<double>(0, fName, ""))->setContext(c));
}

RuntimeResult *Interpreter::visitIfNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *node = (IfNode *) n;
    for (auto &ifCase: node->cases) {
        BaseValue *condValue = res->reg(visit(get<0>(ifCase), c));
        Node *expr = get<1>(ifCase);
        if (res->shouldReturn()) return res;

        if (condValue->isTrue()) {
            BaseValue *exprValue = res->reg(visit(expr, c));
            if (res->shouldReturn()) return res;
            return res->success(exprValue);
        }
    }
    if (node->elseCase) {
        BaseValue *elseValue = res->reg(visit(node->elseCase, c));
        if (res->shouldReturn()) return res;
        return res->success(elseValue);
    }
    return res->success(new Number<double>(0, fName, ""));
}

RuntimeResult *Interpreter::visitListNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    vector<BaseValue *> elements;
    auto *listNode = (ListNode *) n;

    for (auto element: listNode->elements) {
        elements.push_back(res->reg(visit(element, c)));
        if (res->shouldReturn()) return res;
    }

    string fTxt;

    if (n->line >= lines.size()) {
        fTxt = lines[lines.size() - 1];

    } else {
        fTxt = lines.size() == 1 ? lines[0] : lines[n->line];
    }

    return res->success(
            (new List<vector<BaseValue *>>(elements, fName, fTxt))->setContext(c)->setPos(n->posStart,
                                                                                          n->posEnd,
                                                                                          n->line));
}

RuntimeResult *Interpreter::visitMapNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    map<BaseValue *, BaseValue *> dict;
    MapNode *mapNode = (MapNode *) n;

    for (auto element: mapNode->dict) {
        BaseValue *key = res->reg(visit(element.first, c));
        if (res->shouldReturn()) return res;
        BaseValue *value = res->reg(visit(element.second, c));
        if (res->shouldReturn()) return res;
        dict[key] = value;
    }

    auto * m = new Map<map<BaseValue *, BaseValue *>>(dict, fName, lines[mapNode->line]);
    m->setContext(c)->setPos(
            n->posStart, n->posEnd, n->line);
    //delete mapNode;

    return res->success(m);
}

RuntimeResult *Interpreter::visitVarAccessNode(Node *n, Context *c) {
    auto *result = new RuntimeResult();
    auto *node = (VarAccessNode *) n;
    BaseValue *value;
    string varName;

    if (node->toGetIdentifierFrom) {
        value = result->reg(visit(node->toGetIdentifierFrom, c));
    } else {
        varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
        value = c->symbolTable->get(varName);
    }

    if (!value) {
        return result->failure(new RuntimeError(
                node->posStart,
                node->posEnd,
                node->line,
                fName,
                lines[node->line],
                varName + " is not defined",
                c
        ));
    }

    if (node->toGetIdentifierFrom && node->varNameTok) {
        value = value->getFromSymbolTable(((Token<string> *) node->varNameTok)->getValueObject()->getValue());
    }

    string prevType;
    if (value->type == TOK_TYPE::T_CLASS){
        // Check if it's instantiated class or a structure
        auto * temp = dynamic_cast<UsableClass<int> *>(value);
        if (temp){
            prevType = temp->className;
        } else {
            prevType = ((Class<int> *) value)->name;
        }
    } else {
        prevType = value->VAL_TYPES[value->type];
    }
    for (auto &id: node->identifiers) {
        string idName = ((Token<string> *) id)->getValueObject()->getValue();
        value = value->getFromSymbolTable(idName);
        if (!value) {
            return result->failure(new RuntimeError(
                    id->posStart,
                    id->posEnd,
                    id->line,
                    fName,
                    lines[id->line],
                    idName + " is not a member of class " + prevType,
                    c
            ));
        }
        if (value->type == TOK_TYPE::T_CLASS){
            prevType = ((UsableClass<int> *) value)->className;
        } else {
            prevType = value->type;
        }
    }

    value = value->setPos(node->posStart, node->posEnd, node->line);
    if (value->type == TOK_TYPE::T_NUM) {
        ((Number<double> *) value)->setContext(c);
    } else if (value->type == TOK_TYPE::T_STRING) {
        ((String<string> *) value)->setContext(c);
    } else if (value->type == TOK_TYPE::T_FUNC) {
        auto *func = (BaseFunction<int> *) value;
        func->setContext(c);
    } else if (value->type == TOK_TYPE::T_LIST) {
        ((List<vector<BaseValue *>> *) value)->setContext(c);
    } else if (value->type == TOK_TYPE::T_MAP) {
        ((Map<map<BaseValue *, BaseValue *>> *) value)->setContext(c);
    } else if (value->type == TOK_TYPE::T_FUTURE) {
        ((Future<shared_future<RuntimeResult *>> *) value)->setContext(c);
    }

    //delete node->toGetIdentifierFrom;

    return result->success(value);
}

RuntimeResult *Interpreter::visitCallNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    CallNode *callNode = (CallNode *) n;
    vector<BaseValue *> args;

    Value<int> *valToCall;
    BaseValue *b = res->reg(visit(callNode->nodeToCall, c));
    if (res->shouldReturn()) return res;
    if (b->type != TOK_TYPE::T_FUNC && b->type != TOK_TYPE::T_CLASS) {
        return res->failure(new RuntimeError(
                callNode->posStart,
                callNode->posEnd,
                callNode->line,
                fName,
                lines[callNode->line],
                "Can't call non-function",
                c
        ));
    }

    valToCall = dynamic_cast<Value<int> *>(b);

    valToCall = dynamic_cast<Value<int> *>(valToCall->copy()->setPos(callNode->posStart, callNode->posEnd,
                                                                     callNode->nodeToCall->line));
    valToCall->fName = fName;

    for (auto argNode: callNode->args) {
        args.push_back(res->reg(visit(argNode, c)));
        if (res->shouldReturn()) return res;
    }

    map<string, BaseValue *> kwargs;
    for (auto kwarg: callNode->kwargs) {
        string key = kwarg.first->varNameTok->getValueObject()->getValue();
        BaseValue *value = res->reg(visit(kwarg.second, c));
        if (res->shouldReturn()) return res;
        kwargs[key] = value;
    }

    BaseValue *returnVal = res->reg(valToCall->execute(args, kwargs));
    if (res->error) {
        Error * e = res->error;
        e->fTxt = callNode->fTxt;
        return res->failure(e);
    }
    if (res->shouldReturn()) return res;
    if (returnVal->type == TOK_TYPE::T_CLASS) {
        returnVal = returnVal->setPos(callNode->posStart, callNode->posEnd, callNode->line);
    } else {
        returnVal = returnVal->copy()->setPos(callNode->posStart, callNode->posEnd, callNode->line);
    }
    if (returnVal->type == TOK_TYPE::T_NUM) {
        ((Number<double> *) returnVal)->setContext(c);
    } else if (returnVal->type == TOK_TYPE::T_STRING) {
        ((String<string> *) returnVal)->setContext(c);
    } else if (returnVal->type == TOK_TYPE::T_FUNC) {
        auto *func = (BaseFunction<int> *) returnVal;
        func->setContext(c);
    } else if (returnVal->type == TOK_TYPE::T_LIST) {
        ((List<vector<BaseValue *>> *) returnVal)->setContext(c);
    } else if (returnVal->type == TOK_TYPE::T_MAP) {
        ((Map<map<BaseValue *, BaseValue *>> *) returnVal)->setContext(c);
    } else if (returnVal->type == TOK_TYPE::T_FUTURE) {
        ((Future<shared_future<RuntimeResult *>> *) returnVal)->setContext(c);
    }
    return res->success(returnVal);
}


RuntimeResult *Interpreter::visitClassDefNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    ClassDefNode *classDefNode = (ClassDefNode *) n;

    bool foundConstructor = false;

    string className = classDefNode->classNameTok->getValueObject()->getValue();
    vector<Node *> members;
    SymbolTable * instantiatedVars = new SymbolTable();

    for (auto &member: classDefNode->members) {
        if (member->type == N_FUNC_DEF) {
            FuncDefNode * funcDefNode = (FuncDefNode *) member;
            if (funcDefNode->funcNameTok->getValueObject()->getValue() == "init") {
                if(funcDefNode->argNameToks.size() > 0){
                    return res->failure(new RuntimeError(
                            funcDefNode->funcNameTok->posStart,
                            funcDefNode->funcNameTok->posEnd,
                            funcDefNode->funcNameTok->line,
                            fName,
                            lines[funcDefNode->funcNameTok->line],
                            "init method must not have arguments",
                            c
                    ));
                }
                foundConstructor = true;
            }
        }
        if (member->type == N_VAR_ASSIGN){
            VarAssignNode * varAccessNode = (VarAssignNode *) member;
            instantiatedVars->set(((Token<string> *) varAccessNode->varNameTok)->getValueObject()->getValue(),
                                  res->reg(visit(varAccessNode, c)));
            if (res->shouldReturn()) return res;
        }
        members.push_back(member);
    }

    if (!foundConstructor) {
        return res->failure(new RuntimeError(
                classDefNode->classNameTok->posStart,
                classDefNode->classNameTok->posEnd,
                classDefNode->classNameTok->line,
                fName,
                lines[classDefNode->classNameTok->line],
                "Class does not have a constructor defined as 'init', which is required",
                c
        ));
    }

    map<string, BaseValue *> defaultArgs;
    for (auto &arg: classDefNode->defaultArgs) {
        BaseValue *val = res->reg(visit(arg.second, c));
        if (res->shouldReturn()) return res;
        defaultArgs[arg.first] = val;
    }

    auto classObj = new Class<int>(classDefNode->classNameTok, fName, lines[classDefNode->classNameTok->line], classDefNode->argNameToks,
                                   defaultArgs, members, classDefNode->superClass, lines);
    classObj->setContext(c);
    classObj->instantiatedVariables = instantiatedVars;
    c->symbolTable->set(className, classObj);

    return res->success(classObj);
}

RuntimeResult *Interpreter::visitFuncDefNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *node = (FuncDefNode *) n;

    string funcName = node->funcNameTok ? node->funcNameTok->getValueObject()->getValue() : "anonymous";
    Node *bodyNode = node->body;

    vector<string> argNames;
    for (auto &argName: node->argNameToks) {
        argNames.push_back(((Token<string> *) argName)->getValueObject()->getValue());
    }

    map<string, BaseValue *> defaultArgs;
    for (auto &arg: node->defaultArgs) {
        BaseValue *val = res->reg(visit(arg.second, c));
        if (res->shouldReturn()) return res;
        defaultArgs[arg.first] = val;
    }

    BaseValue *funcValue = (new Function<int>(fName, lines[node->funcNameTok->line], funcName, bodyNode, argNames,
                                              defaultArgs,
                                              node->uses,
                                              lines,
                                              node->autoReturn))
            ->setContext(c)
            ->setPos(node->posStart, node->posEnd, node->line);

    if (node->funcNameTok) {
        c->symbolTable->set(funcName, funcValue);
    }

    return res->success(funcValue);
}

RuntimeResult *Interpreter::visitVarAssignNode(Node *n, Context *c) {
    auto *result = new RuntimeResult();
    auto *node = (VarAssignNode *) n;
    string varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
    BaseValue *value = result->reg(visit(node->valueNode, c));
    if (result->shouldReturn()) return result;
    if (!node->parents.empty()){
        BaseValue * toSet = c->symbolTable->get(varName);
        if (toSet == nullptr){
            return result->failure(new RuntimeError(
                    node->posStart,
                    node->posEnd,
                    node->line,
                    fName,
                    lines[node->line],
                    "Variable '" + varName + "' is not defined",
                    c
            ));
        }
        for (int i = 0; i < node->parents.size() - 1; i++){
            auto * parentName = (Token<string> *) node->parents[i];
            toSet = toSet->getFromSymbolTable(parentName->getValueObject()->getValue());
            if (toSet == nullptr){
                return result->failure(new RuntimeError(
                        node->posStart,
                        node->posEnd,
                        node->line,
                        fName,
                        lines[node->line],
                        "Parent " + parentName->getValueObject()->getValue() + " does not exist",
                        c
                ));
            }
        }
        auto * lastParentName = (Token<string> *) node->parents.back();
        toSet->setInSymbolTable(lastParentName->getValueObject()->getValue(), value);
        return result->success(value);
    }
    if (node->assType == REASSIGN_VAR){
        c->symbolTable->set(varName, value);
    } else {
        BaseValue * t = c->symbolTable->get(varName);
        t->to(value);
        if (t->type == TOK_TYPE::T_NUM) {
            if (((Number<double> *) t)->rtError) {
                return result->failure(((Number<double> *) t)->rtError);
            }
        } else if (t->type == TOK_TYPE::T_STRING) {
            if (((String<string> *) t)->rtError) {
                return result->failure(((String<string> *) t)->rtError);
            }
        } else if (t->type == TOK_TYPE::T_FUNC) {
            if (((BaseFunction<int> *) t)->rtError) {
                return result->failure(((BaseFunction<int> *) t)->rtError);
            }
        } else if (t->type == TOK_TYPE::T_LIST) {
            if (((List<vector<BaseValue *>> *) t)->rtError) {
                return result->failure(((List<vector<BaseValue *>> *) t)->rtError);
            }
        } else if (t->type == TOK_TYPE::T_MAP) {
            if (((Map<map<BaseValue *, BaseValue *>> *) t)->rtError) {
                return result->failure(((Map<map<BaseValue *, BaseValue *>> *) t)->rtError);
            }
        } else if (t->type == TOK_TYPE::T_CLASS) {
            if (((UsableClass<int> *) t)->rtError) {
                return result->failure(((UsableClass<int> *) t)->rtError);
            }
        }
    }
    return result->success(value);
}


RuntimeResult *Interpreter::visitNumberNode(Node *n, Context *c) {
    NumberNode *node = (NumberNode *) n;
    Number<double> *num = (Number<double> *) (new Number<double>(node->token->getValueObject()->getValue(), fName,
                                                                 lines[node->token->line]))->setContext(c)->setPos(
            node->token->posStart,
            node->token->posEnd,
            node->token->line
    );
    num->ctx = c;
    return (new RuntimeResult())->success(num);
}

RuntimeResult *Interpreter::visitStringNode(Node *n, Context *c) {
    StringNode *node = (StringNode *) n;
    String<string> *str = (String<string> *) (new String<string>(node->token->getValueObject()->getValue(), fName,
                                                                 lines[node->token->line]))->setContext(c)->setPos(
            node->token->posStart,
            node->token->posEnd,
            node->token->line
    );
    str->ctx = c;
    return (new RuntimeResult())->success(str);
}

RuntimeResult *Interpreter::visitBinOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    BinaryOperationNode *node = (BinaryOperationNode *) n;
    BaseValue *left = rtRes->reg(visit(node->getLeft(), c));
    if (rtRes->shouldReturn()) return rtRes;
    BaseValue *right = rtRes->reg(visit(node->getRight(), c));
    if (rtRes->shouldReturn()) return rtRes;
    BaseValue *result = new BaseValue(left->type, fName, lines[node->opTok->line]);

    if (node->opTok->type == TOK_TYPE::PLUS) {
        result = left->add(right);
    } else if (node->opTok->type == TOK_TYPE::MINUS) {
        result = left->subtract(right);
    } else if (node->opTok->type == TOK_TYPE::MULTIPLY) {
        result = left->multiply(right);
    } else if (node->opTok->type == TOK_TYPE::DIVIDE) {
        result = left->divide(right);
    } else if (node->opTok->type == TOK_TYPE::POWER) {
        result = left->power(right);
    } else if (node->opTok->type == TOK_TYPE::MOD) {
        result = left->mod(right);
    } else if (node->opTok->getType() == TOK_TYPE::GREATER_THAN) {
        result = left->compGreaterThan(right);
    } else if (node->opTok->getType() == TOK_TYPE::GREATER_THAN_EQUAL) {
        result = left->compGreaterThanEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::LESS_THAN) {
        result = left->compLessThan(right);
    } else if (node->opTok->getType() == TOK_TYPE::LESS_THAN_EQUAL) {
        result = left->compLessThanEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::NOT_EQUAL) {
        result = left->compNotEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::EQUAL_EQUAL) {
        result = left->compEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::PLUS_EQUAL) {
        result = left->plusEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::MINUS_EQUAL) {
        result = left->minusEquals(right);
    } else if (node->opTok->getType() == TOK_TYPE::AND) {
        result = left->andedBy(right);
    } else if (node->opTok->getType() == TOK_TYPE::OR) {
        result = left->oredBy(right);
    } else if (node->opTok->getType() == TOK_TYPE::GET) {
        result = left->get(right);
    } else if (node->opTok->getType() == TOK_TYPE::CONTAINS) {
        result = left->contains(right);
    }
    //TODO: Update this area for any errors
    if (left->type == TOK_TYPE::T_NUM) {
        if (((Number<double> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((Number<double> *) left)->rtError);
            ((Number<double> *) left)->rtError = nullptr;
            return r;
        }
    } else if (left->type == TOK_TYPE::T_STRING) {
        if (((String<string> *) left)->rtError) {
            return rtRes->failure(((String<string> *) left)->rtError);
        }
    } else if (left->type == TOK_TYPE::T_FUNC) {
        if (((BaseFunction<int> *) left)->rtError) {
            return rtRes->failure(((BaseFunction<int> *) left)->rtError);
        }
    } else if (left->type == TOK_TYPE::T_LIST) {
        if (((List<vector<BaseValue *>> *) left)->rtError) {
            return rtRes->failure(((List<vector<BaseValue *>> *) left)->rtError);
        }
    } else if (left->type == TOK_TYPE::T_MAP) {
        if (((Map<map<BaseValue *, BaseValue *>> *) left)->rtError) {
            return rtRes->failure(((Map<map<BaseValue *, BaseValue *>> *) left)->rtError);
        }
    } else if (left->type == TOK_TYPE::T_CLASS) {
        if (((UsableClass<int> *) left)->rtError) {
            return rtRes->failure(((UsableClass<int> *) left)->rtError);
        }
    }

    return rtRes->success(result->setPos(n->posStart, n->posEnd, n->line));
}

RuntimeResult *Interpreter::visitIndexNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *node = (IndexNode *) n;

    BaseValue *left = res->reg(visit(node->left, c));
    if (res->shouldReturn()) return res;

    BaseValue *result = left;

    for (int i = 0; i < node->indices.size(); i++) {
        BaseValue *idx = res->reg(visit(node->indices[i], c));
        if (res->shouldReturn()) return res;

        if(i + 1 == node->indices.size()){
            if (node->type == SET_VALUE){
                if (result->type == TOK_TYPE::T_LIST){
                    if (idx->type != TOK_TYPE::T_NUM){
                        return res->failure(new RuntimeError(
                                idx->posStart,
                                idx->posEnd,
                                idx->line,
                                idx->fName,
                                idx->fTxt,
                                "Expected a number",
                                c
                        ));
                    }
                    ((List<vector<BaseValue *>> *) result)->elements[((Number<double> *) idx)->getValue()] = res->reg(visit(node->newVal, c));
                    if (res->shouldReturn()) return res;
                } else if(result->type == TOK_TYPE::T_MAP){
                    auto *m = ((Map<map<BaseValue *, BaseValue *>> *) result);
                    m->replace(idx, res->reg(visit(node->newVal, c)));
                    if (res->shouldReturn()) return res;
                } else {
                    return res->failure(new RuntimeError(
                            idx->posStart,
                            idx->posEnd,
                            idx->line,
                            idx->fName,
                            idx->fTxt,
                            "Cannot modify index of type " + result->type,
                            c
                    ));
                }
            }
        }

        if (result == nullptr) {
            return res->failure(new RuntimeError(
                    idx->posStart,
                    idx->posEnd,
                    idx->line,
                    idx->fName,
                    idx->fTxt,
                    "Cannot index into null",
                    c
            ));
        }
        result = result->get(idx);

        if (left->type == TOK_TYPE::T_STRING) {
            if (((String<string> *) left)->rtError) {
                return res->failure(((String<string> *) left)->rtError);
            }
        } else if (left->type == TOK_TYPE::T_LIST) {
            if (((List<vector<BaseValue *>> *) left)->rtError) {
                return res->failure(((List<vector<BaseValue *>> *) left)->rtError);
            }
        } else if (left->type == TOK_TYPE::T_MAP) {
            if (((Map<map<BaseValue *, BaseValue *>> *) left)->rtError) {
                return res->failure(((Map<map<BaseValue *, BaseValue *>> *) left)->rtError);
            }
        }
    }
    return res->success(result->setPos(n->posStart, n->posEnd, n->line));
}

RuntimeResult *Interpreter::visitUnaryOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    UnaryOperationNode *opNode = (UnaryOperationNode *) n;
    Number<double> *num = (Number<double> *) rtRes->reg(visit(opNode->node, c));

    if (rtRes->shouldReturn()) return rtRes;

    if (opNode->op->type == TOK_TYPE::MINUS) {
        num = num->multiply(new Number<double>(-1, num->fName, num->fTxt));
    } else if (opNode->op->type == TOK_TYPE::NOT) {
        num = dynamic_cast<Number<double> *>(num->notted());
    }

    if (num->rtError) return rtRes->failure(num->rtError);

    return rtRes->success(num->setPos(n->posStart, n->posEnd, n->line));
}

RuntimeResult *Interpreter::visitAwaitNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *node = (AwaitNode *) n;

    shared_future<RuntimeResult *> result = async(launch::async, &Interpreter::visitCallNode, this, node->toCall, c).share();
    auto * fut = new Future<shared_future<RuntimeResult *>>(result, node->fName, node->fTxt);

    return res->success(fut);
}

RuntimeResult *Interpreter::visitImportNode(Node *n, Context *c) {
    auto *res = new RuntimeResult();
    auto *node = (ImportNode *) n;

    BaseValue *toImport = res->reg(visit(node->toImport, c));
    if (res->shouldReturn()) return res;

    if (toImport->type != TOK_TYPE::T_STRING) {
        return res->failure(new RuntimeError(
                toImport->posStart,
                toImport->posEnd,
                toImport->line,
                toImport->fName,
                toImport->fTxt,
                "Expected a string",
                c
        ));
    }

    auto *moduleName = (String<string> *) toImport;
    SymbolTable * sym = c->symbolTable;

    if (stdlib.count(moduleName->getValue()) > 0) {
        sym->set(moduleName->getValue(), stdlib[moduleName->getValue()]);
        return res->success(new Number<double>(0, "", ""));
    }

    string fullFilePath = moduleName->getValue();
    // Check if file exists on computer
    ifstream infile(fullFilePath);
    if (!infile.good()) {
        fullFilePath = pathRef + fullFilePath;
        infile = ifstream(fullFilePath);
        if (!infile.good()) {
            return res->failure(new RuntimeError(
                    toImport->posStart,
                    toImport->posEnd,
                    toImport->line,
                    toImport->fName,
                    toImport->fTxt,
                    "File not found, make sure to use an absolute or relative path",
                    c
            ));
        }
    }
    infile.close();

    if (node->specific){
        sym = new SymbolTable(c->symbolTable);
    }

    auto *ri = new RunInterface(sym, fs::path(fullFilePath).parent_path().string() + "/"); //Set a pathref if known
    RunResult r;
    r = ri->readFile("/" + fs::path(moduleName->getValue()).filename().string());

    if (node->specific){
        c->symbolTable->set(node->specific->getValueObject()->getValue(), sym->get(node->specific->getValueObject()->getValue()));
        delete sym;
    }

    if (r.second) {
        return res->failure(r.second);
    }

    return res->success(new Number<double>(0, "", ""));
}

RuntimeResult *Interpreter::visitReturnNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    ReturnNode *node = (ReturnNode *) n;

    BaseValue *value;

    if (node->toReturn) {
        value = res->reg(visit(node->toReturn, c));
        if (res->shouldReturn()) return res;
    } else {
        value = (new Number<double>(0, "", ""))->setContext(c);
    }
    return res->successReturn(value);
}

RuntimeResult *Interpreter::visitBreakNode(Node *n, Context *c) {
    return (new RuntimeResult())->successBreak();
}

RuntimeResult *Interpreter::visitContinueNode(Node *n, Context *c) {
    return (new RuntimeResult())->successContinue();
}