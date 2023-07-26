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
    Font.cpp
    CalcError.cpp
)
target_link_directories(advancedcalc PUBLIC ./deps/AAGL/build ./deps/glfw/build/src)
target_include_directories(advancedcalc PUBLIC ./deps/AAGL ./deps/glfw/include ./deps/glm ./include)

target_link_libraries(advancedcalc PUBLIC glfw3 AAGL "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
target_compile_definitions(advancedcalc PUBLIC GL_SILENCE_DEPRECATION)
