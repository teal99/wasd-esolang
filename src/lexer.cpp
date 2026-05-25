// lexer.cpp

#include "../include/lexer.hpp"
#include <string_view>
#include <cctype>

void flushBuffer(std::string& buffer, std::vector<Token>& tokens, size_t line) {
    if (buffer.empty()) return;

    if (buffer == "yap")        tokens.push_back({TokenType::OUTPUT, line, 1});
    else if (buffer == "eavesdrop") tokens.push_back({TokenType::INPUT, line, 1});
    else if (buffer == "grind")     tokens.push_back({TokenType::LOOP_START, line, 1});
    else if (buffer == "quit")      tokens.push_back({TokenType::LOOP_END, line, 1});

    buffer.clear();
}

std::vector<Token> tokenize(const std::string& sourceCode) {
    std::vector<Token> tokens;
    tokens.reserve(sourceCode.size() / 4); 
    
    std::string currentWord;
    currentWord.reserve(16);
    size_t currentLine = 1;

    bool insideComment = false;
    bool expectingSecondSlash = false;

    for (char rawChar : sourceCode) {
        if (insideComment) {
            if (rawChar == '\n') {
                currentLine++;
                insideComment = false;
            }
            continue;
        }
        if (expectingSecondSlash) {
            expectingSecondSlash = false;
            if (rawChar == '/') {
                flushBuffer(currentWord, tokens, currentLine);
                insideComment = true;
                continue;
            } else {
                currentWord += '/';
            }
        }
        if (rawChar == '#') {
            flushBuffer(currentWord, tokens, currentLine);
            insideComment = true;
            continue;
        }
        if (rawChar == '/') {
            expectingSecondSlash = true;
            continue;
        }

        char c = std::tolower(static_cast<unsigned char>(rawChar));
    
        if (c == '\n') {
            flushBuffer(currentWord, tokens, currentLine);
            currentLine++;
        } else if (c == ' ' || c == '\t' || c == '\r') {
            flushBuffer(currentWord, tokens, currentLine);
        } else if ((c == 'w' || c == 'a' || c == 's' || c == 'd') && currentWord.empty()) {
            TokenType type;
            if (c == 'd')      type = TokenType::MOVE_RIGHT;
            else if (c == 'a') type = TokenType::MOVE_LEFT;
            else if (c == 'w') type = TokenType::INCREMENT;
            else               type = TokenType::DECREMENT;
    
            if (!tokens.empty() && tokens.back().type == type && tokens.back().line == currentLine) {
                tokens.back().count++;
            } else {
                tokens.push_back({ type, currentLine, 1 });
            }
        } else {
            currentWord += c;
        }
    }    
    
    flushBuffer(currentWord, tokens, currentLine);
    return tokens;
}