cmake_minimum_required(VERSION 3.20)
project(Boa)

set(CMAKE_CXX_STANDARD 14)
set(
        SOURCE_FILES
        includes/Token/Token.cpp includes/Token/Token.h
        includes/Values/BaseValues/Value.cpp
        includes/Values/BaseValues/Value.h
        includes/Nodes/Node.cpp includes/Nodes/Node.h
        includes/Context/Context.cpp includes/Context/Context.h
        includes/Errors/Error.cpp includes/Errors/Error.h
        includes/Errors/RuntimeError.cpp includes/Errors/RuntimeError.h
        includes/Values/Number/Number.cpp includes/Values/Number/Number.h
        includes/Nodes/CallNode.cpp includes/Nodes/CallNode.h
        "includes/Nodes/Control Flow/ForNode.cpp" "includes/Nodes/Control Flow/ForNode.h"
        "includes/Nodes/Control Flow/FuncDefNode.cpp" "includes/Nodes/Control Flow/FuncDefNode.h"
        "includes/Nodes/Control Flow/IfNode.cpp" "includes/Nodes/Control Flow/IfNode.h"
        "includes/Nodes/Value Nodes/NumberNode.cpp" "includes/Nodes/Value Nodes/NumberNode.h"
        includes/Nodes/UnaryOperationNode.cpp includes/Nodes/UnaryOperationNode.h
        includes/Nodes/VarAccessNode.cpp includes/Nodes/VarAccessNode.h
        includes/Nodes/VarAssignNode.cpp includes/Nodes/VarAssignNode.h
        "includes/Nodes/Control Flow/WhileNode.cpp" "includes/Nodes/Control Flow/WhileNode.h"
        includes/Nodes/BinaryOperationNode.cpp includes/Nodes/BinaryOperationNode.h
        includes/Parser/ParseResult.cpp includes/Parser/ParseResult.h
        includes/RuntimeResult/RuntimeResult.cpp includes/RuntimeResult/RuntimeResult.h
        includes/SymbolTable/SymbolTable.cpp includes/SymbolTable/SymbolTable.h
        includes/Parser/Parser.cpp includes/Parser/Parser.h
        includes/Lexer/Lexer.cpp includes/Lexer/Lexer.h
        includes/Interpreter/Interpreter.cpp includes/Interpreter/Interpreter.h
        includes/Token/BaseToken.cpp includes/Token/BaseToken.h includes/Values/BaseValues/BaseValue.cpp includes/Values/BaseValues/BaseValue.h includes/Values/String/String.cpp includes/Values/String/String.h includes/Values/Functions/Function.cpp includes/Values/Functions/Function.h "includes/Nodes/Value Nodes/StringNode.cpp" "includes/Nodes/Value Nodes/StringNode.h" "includes/Nodes/Value Nodes/ListNode.cpp" "includes/Nodes/Value Nodes/ListNode.h" includes/Values/List/List.cpp includes/Values/List/List.h "includes/Nodes/Value Nodes/MapNode.cpp" "includes/Nodes/Value Nodes/MapNode.h" includes/Values/Map.cpp includes/Values/Map.h includes/Values/Constants.h includes/Values/Functions/BaseFunction.cpp includes/Values/Functions/BaseFunction.h includes/Values/Functions/BuiltInFunction.cpp includes/Values/Functions/BuiltInFunction.h "includes/Nodes/Control Flow/IterateNode.cpp" "includes/Nodes/Control Flow/IterateNode.h" "includes/Nodes/Statements/Branching Statements/ReturnNode.cpp" "includes/Nodes/Statements/Branching Statements/ReturnNode.h" "includes/Nodes/Statements/Branching Statements/ContinueNode.cpp" "includes/Nodes/Statements/Branching Statements/ContinueNode.h" "includes/Nodes/Statements/Branching Statements/BreakNode.cpp" "includes/Nodes/Statements/Branching Statements/BreakNode.h" includes/Nodes/Statements/ImportNode.cpp includes/Nodes/Statements/ImportNode.h includes/RunInterface.cpp includes/RunInterface.h includes/Values/String/StringFunction.cpp includes/Values/String/StringFunction.h includes/Values/List/ListFunction.cpp includes/Values/List/ListFunction.h includes/Values/Number/NumberFunction.cpp includes/Values/Number/NumberFunction.h includes/Modules/Random/Random.cpp includes/Modules/Random/Random.h includes/Modules/Random/RandomFunction.cpp includes/Modules/Random/RandomFunction.h includes/Nodes/IndexNode.cpp includes/Nodes/IndexNode.h "includes/Nodes/Control Flow/ClassDefNode.cpp" "includes/Nodes/Control Flow/ClassDefNode.h")
add_executable(
        Boa main.cpp
        ${SOURCE_FILES}
)