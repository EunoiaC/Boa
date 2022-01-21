//
// Created by Preeti Thorat on 1/14/22.
//

#include "RunInterface.h"

RunInterface::RunInterface(SymbolTable *symbolTable, string pathRef) {
    this->globalSymbolTable = symbolTable;
    this->pathRef = pathRef;
}

RunResult RunInterface::readFile(string filePath) {
    filePath = pathRef + filePath;
    string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);

    //File
    ifstream file(filePath);

    //Reading file
    string fileText;
    string line;

    while (getline(file, line)) {
        line += "\n";
        lines.push_back(line);
        fileText += line;
    }

    file.close();

    l = new Lexer(fileText, fileName, lines);
    vector<BaseToken *> v = l->makeTokens();
    if (v.empty()) {
        return make_pair(nullptr, l->error);
    }
    p = new Parser(v, fileName, lines);
    res = p->parse();
    if (res->error) {
        return make_pair(nullptr, res->error);
    } else {
        //cout << "AST: " + res->node->toString() << endl;
    }
    auto *i = new Interpreter(fileName, lines);
    i->pathRef = pathRef;
    auto *ctx = new Context("<program>");
    ctx->symbolTable = globalSymbolTable;
    RuntimeResult *result = i->visit(res->node, ctx);
    if (result->error) {
        return make_pair(nullptr, result->error);
    }
    return make_pair(result->value, nullptr);
}

void RunInterface::run(string fileName) {
    clock_t start = clock();
    RunResult run = readFile(fileName);
    if (run.second) {
        cout << run.second->toString() << endl;
    } else {
        clock_t stop = clock();
        cout << "Execution time: " << (stop - start) / (double) CLOCKS_PER_SEC << " seconds" << endl;
    }
}
