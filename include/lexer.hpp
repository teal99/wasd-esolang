// lexer.hpp

#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>
#include <vector>

enum class TokenType {
    MOVE_UP, // W
    MOVE_DOWN, // S
    MOVE_RIGHT, // D
    MOVE_LEFT, // A
    INCREMENT, // click
    DECREMENT, // miss
    OUTPUT, // yap
    INPUT, // eavesdrop
    LOOP_START, // grind
    LOOP_END, // quit
    SET_CONSTANT
};

struct Token {
    TokenType type;
    size_t line;
    size_t count = 1;
    std::string identifier;
};

std::vector<Token> tokenize(const std::string& sourceCode);

#endif