cmake_minimum_required(VERSION 3.10)
project(advancedcalc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(
    advancedcalc
    main.cpp
    Calculator.cpp
    Token.cpp
    Parser.cpp
    Lexer.cpp
    TokenList.cpp
    Constants.cpp
    Helper.cpp
    Functions.cpp
)