cmake_minimum_required(VERSION 3.20)
project(Boa)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(FetchContent)

# ——————————————————————
# 1) GLAD & CPR via FetchContent
# ——————————————————————
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        v0.1.35
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/whoshuu/cpr.git
        GIT_TAG        db351ffbbadc6c4e9239daaa26e9aefa9f0ec82d
)
FetchContent_MakeAvailable(cpr)

# ——————————————————————
# 2) IXWebSocket via FetchContent
# ——————————————————————
# turn off samples/tests so it only builds the core library
set(IXWEBSOCKET_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_EXAMPLE_SERVER OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_EXAMPLE_CLIENT OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_SSL_TESTS OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        ixwebsocket
        GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(ixwebsocket)

# ——————————————————————
# 3) System libraries
# ——————————————————————
find_package(OpenSSL REQUIRED)
find_package(CURL    REQUIRED)
find_package(Boost   REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(FLTK    REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

# ——————————————————————
# 4) Your sources & executable
# ——————————————————————
set(
        SOURCE_FILES
        "Extern Libs/glad.c"
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
        includes/Token/BaseToken.cpp includes/Token/BaseToken.h
        includes/Values/BaseValues/BaseValue.cpp includes/Values/BaseValues/BaseValue.h
        includes/Values/String/String.cpp includes/Values/String/String.h includes/Values/Functions/Function.cpp
        includes/Values/Functions/Function.h "includes/Nodes/Value Nodes/StringNode.cpp"
        "includes/Nodes/Value Nodes/StringNode.h" "includes/Nodes/Value Nodes/ListNode.cpp"
        "includes/Nodes/Value Nodes/ListNode.h" includes/Values/List/List.cpp includes/Values/List/List.h
        "includes/Nodes/Value Nodes/MapNode.cpp" "includes/Nodes/Value Nodes/MapNode.h"
        includes/Values/Map/Map.cpp includes/Values/Map/Map.h
        includes/Values/Constants.h includes/Values/Functions/BaseFunction.cpp includes/Values/Functions/BaseFunction.h includes/Values/Functions/BuiltInFunction.cpp includes/Values/Functions/BuiltInFunction.h "includes/Nodes/Control Flow/IterateNode.cpp" "includes/Nodes/Control Flow/IterateNode.h" "includes/Nodes/Statements/Branching Statements/ReturnNode.cpp" "includes/Nodes/Statements/Branching Statements/ReturnNode.h" "includes/Nodes/Statements/Branching Statements/ContinueNode.cpp" "includes/Nodes/Statements/Branching Statements/ContinueNode.h" "includes/Nodes/Statements/Branching Statements/BreakNode.cpp" "includes/Nodes/Statements/Branching Statements/BreakNode.h" includes/Nodes/Statements/ImportNode.cpp includes/Nodes/Statements/ImportNode.h includes/RunInterface.cpp includes/RunInterface.h includes/Values/String/StringFunction.cpp includes/Values/String/StringFunction.h includes/Values/List/ListFunction.cpp includes/Values/List/ListFunction.h includes/Values/Number/NumberFunction.cpp includes/Values/Number/NumberFunction.h includes/Modules/Random/Random.cpp includes/Modules/Random/Random.h includes/Modules/Random/RandomFunction.cpp includes/Modules/Random/RandomFunction.h includes/Nodes/IndexNode.cpp includes/Nodes/IndexNode.h "includes/Nodes/Control Flow/ClassDefNode.cpp" "includes/Nodes/Control Flow/ClassDefNode.h" includes/Values/Class/Class.cpp includes/Values/Class/Class.h includes/Values/Class/ClassFunction.cpp includes/Values/Class/ClassFunction.h includes/Values/Class/UsableClass.cpp includes/Values/Class/UsableClass.h "includes/Nodes/Control Flow/TryCatchNode.cpp" "includes/Nodes/Control Flow/TryCatchNode.h" "includes/Nodes/Control Flow/EitherNode.cpp" "includes/Nodes/Control Flow/EitherNode.h" includes/Values/File/File.cpp includes/Values/File/File.h includes/Values/File/FileFunction.cpp includes/Values/File/FileFunction.h
        includes/Modules/Requests/Requests.cpp includes/Modules/Requests/Requests.h includes/Modules/Requests/RequestsFunction.cpp includes/Modules/Requests/RequestsFunction.h includes/Modules/Json/Json.cpp includes/Modules/Json/Json.h includes/Modules/Json/JsonFunction.cpp includes/Modules/Json/JsonFunction.h includes/Nodes/Statements/AwaitNode.cpp includes/Nodes/Statements/AwaitNode.h includes/Values/Future/Future.cpp includes/Values/Future/Future.h includes/Values/Future/FutureFunction.cpp includes/Values/Future/FutureFunction.h includes/Modules/Requests/Socket/Socket.cpp includes/Modules/Requests/Socket/Socket.h includes/Modules/Requests/Socket/SocketFunction.cpp includes/Modules/Requests/Socket/SocketFunction.h includes/Values/Map/MapFunction.cpp includes/Values/Map/MapFunction.h includes/Modules/Time/Time.cpp includes/Modules/Time/Time.h includes/Modules/Time/TimeFunction.cpp includes/Modules/Time/TimeFunction.h
        includes/Modules/Requests/Websocket/Websocket.cpp includes/Modules/Requests/Websocket/Websocket.h includes/Modules/Requests/Websocket/WebsocketFunction.cpp includes/Modules/Requests/Websocket/WebsocketFunction.h
        includes/Modules/GUI/GUI.cpp includes/Modules/GUI/GUI.h includes/Modules/Time/TimeValue/TimeValue.cpp includes/Modules/Time/TimeValue/TimeValue.h "includes/Modules/GUI/FLTK wrappers/Window/WindowObj.cpp" "includes/Modules/GUI/FLTK wrappers/Window/WindowObj.h" "includes/Modules/GUI/FLTK wrappers/Window/WindowFunction.cpp" "includes/Modules/GUI/FLTK wrappers/Window/WindowFunction.h" includes/Modules/GUI/GUIFunction.cpp includes/Modules/GUI/GUIFunction.h
        #[["Extern Libs/cpptk/cpptk.cc" "Extern Libs/cpptk/cpptk.h"
        "Extern Libs/cpptk/base/cpptkbase.cc"
        "Extern Libs/cpptk/base/cpptkbase.h"
        "Extern Libs/cpptk/cpptkconstants.x"
        "Extern Libs/cpptk/cpptkoptions.x"]]
        includes/Modules/SQLite/SQLite3.cpp includes/Modules/SQLite/SQLite3.h includes/Modules/SQLite/SQLite3Function.cpp includes/Modules/SQLite/SQLite3Function.h includes/Modules/SQLite/Database/SQLiteDB.cpp includes/Modules/SQLite/Database/SQLiteDB.h includes/Modules/SQLite/Database/SQLiteDBFunction.cpp includes/Modules/SQLite/Database/SQLiteDBFunction.h
        "includes/Modules/GUI/FLTK wrappers/Text/Text.cpp" "includes/Modules/GUI/FLTK wrappers/Text/Text.h" "includes/Modules/GUI/FLTK wrappers/TextInput/TextInput.cpp" "includes/Modules/GUI/FLTK wrappers/TextInput/TextInput.h" "includes/Modules/GUI/FLTK wrappers/TextInput/TextInputFunction.cpp" "includes/Modules/GUI/FLTK wrappers/TextInput/TextInputFunction.h" "includes/Modules/GUI/FLTK wrappers/Text/TextFunction.cpp" "includes/Modules/GUI/FLTK wrappers/Text/TextFunction.h" "includes/Modules/GUI/FLTK wrappers/Widget.cpp" "includes/Modules/GUI/FLTK wrappers/Widget.h" "includes/Modules/GUI/FLTK wrappers/WidgetFunction.cpp" "includes/Modules/GUI/FLTK wrappers/WidgetFunction.h" "includes/Modules/GUI/FLTK wrappers/Button/Button.cpp" "includes/Modules/GUI/FLTK wrappers/Button/Button.h")

add_executable(Boa main.cpp ${SOURCE_FILES})

target_include_directories(Boa PRIVATE
        ${CURL_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Boa PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
        CURL::libcurl
        ${Boost_LIBRARIES}
        SQLite::SQLite3
        ${FLTK_LIBRARIES}
        glad
        cpr::cpr
        ixwebsocket::ixwebsocket      # <-- pulls in IXWebSocket
)

if(APPLE)
    target_link_libraries(Boa PRIVATE "-framework OpenGL")
endif()