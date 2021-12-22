cmake_minimum_required(VERSION 3.20)
project(Boa)

set(CMAKE_CXX_STANDARD 14)
set(
        SOURCE_FILES
        includes/Token/Token.cpp includes/Token/Token.h
        includes/Values/BaseValues/Value.cpp includes/Values/BaseValues/Value.h
        includes/Nodes/Node.cpp includes/Nodes/Node.h
        includes/Context/Context.cpp includes/Context/Context.h
        includes/Errors/Error.cpp includes/Errors/Error.h
        includes/Errors/RuntimeError.cpp includes/Errors/RuntimeError.h
        includes/Values/Number.cpp includes/Values/Number.h
        includes/Nodes/CallNode.cpp includes/Nodes/CallNode.h
        includes/Nodes/ForNode.cpp includes/Nodes/ForNode.h
        includes/Nodes/FuncDefNode.cpp includes/Nodes/FuncDefNode.h
        includes/Nodes/IfNode.cpp includes/Nodes/IfNode.h
        includes/Nodes/NumberNode.cpp includes/Nodes/NumberNode.h
        includes/Nodes/UnaryOperationNode.cpp includes/Nodes/UnaryOperationNode.h
        includes/Nodes/VarAccessNode.cpp includes/Nodes/VarAccessNode.h
        includes/Nodes/VarAssignNode.cpp includes/Nodes/VarAssignNode.h
        includes/Nodes/WhileNode.cpp includes/Nodes/WhileNode.h
        includes/Nodes/BinaryOperationNode.cpp includes/Nodes/BinaryOperationNode.h
        includes/Parser/ParseResult.cpp includes/Parser/ParseResult.h
        includes/RuntimeResult/RuntimeResult.cpp includes/RuntimeResult/RuntimeResult.h
        includes/SymbolTable/SymbolTable.cpp includes/SymbolTable/SymbolTable.h
        includes/Parser/Parser.cpp includes/Parser/Parser.h
        includes/Lexer/Lexer.cpp includes/Lexer/Lexer.h
        includes/Interpreter/Interpreter.cpp includes/Interpreter/Interpreter.h
        includes/Token/BaseToken.cpp includes/Token/BaseToken.h includes/Values/BaseValues/BaseValue.cpp includes/Values/BaseValues/BaseValue.h includes/Values/String.cpp includes/Values/String.h includes/Values/Functions/Function.cpp includes/Values/Functions/Function.h includes/Nodes/StringNode.cpp includes/Nodes/StringNode.h includes/Nodes/ListNode.cpp includes/Nodes/ListNode.h includes/Values/List.cpp includes/Values/List.h includes/Nodes/MapNode.cpp includes/Nodes/MapNode.h includes/Values/Map.cpp includes/Values/Map.h includes/Values/Constants.h includes/Values/Functions/BaseFunction.cpp includes/Values/Functions/BaseFunction.h)
add_executable(
        Boa main.cpp
        ${SOURCE_FILES}
)