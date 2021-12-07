cmake_minimum_required(VERSION 3.20)
project(Boa)

set(CMAKE_CXX_STANDARD 14)
add_executable(
        Boa main.cpp
        includes/Token/Token.cpp
        includes/Values/Value.cpp
        includes/Nodes/Node.cpp
        includes/Context/Context.cpp
        includes/Errors/Error.cpp
        includes/Errors/RuntimeError.cpp
        includes/Values/Number.cpp
        includes/Nodes/CallNode.cpp
        includes/Nodes/ForNode.cpp
        includes/Nodes/FuncDefNode.cpp
        includes/Nodes/IfNode.cpp
        includes/Nodes/NumberNode.cpp
        includes/Nodes/UnaryOperationNode.cpp
        includes/Nodes/VarAccessNode.cpp
        includes/Nodes/VarAssignNode.cpp
        includes/Nodes/VarOperationNode.cpp
        includes/Nodes/WhileNode.cpp
        includes/Nodes/BinaryOperationNode.cpp
        includes/Parser/ParseResult.cpp
        includes/RuntimeResult/RuntimeResult.cpp
        includes/SymbolTable/SymbolTable.cpp
        includes/Parser/Parser.cpp
        includes/Lexer/Lexer.cpp
        includes/Interpreter/Interpreter.cpp
)