// lexer.hpp

#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>
#include <vector>

enum class TokenType {
    MOVE_RIGHT, // D
    MOVE_LEFT, // A
    INCREMENT, // W
    DECREMENT, // S
    OUTPUT, // yap
    INPUT, // eavesdrop
    LOOP_START, // grind
    LOOP_END // quit
};

struct Token {
    TokenType type;
    size_t line;
    size_t count = 1;
};

std::vector<Token> tokenize(const std::string& sourceCode);

#endif