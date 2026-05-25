// lexer.cpp

#include "../include/lexer.hpp"
#include <string_view>
#include <cctype>
#include <algorithm>
#include <map>

void flushBuffer(std::string& buffer, std::vector<Token>& tokens, size_t line) {
    if (buffer.empty()) return;

    std::transform(buffer.begin(), buffer.end(), buffer.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    if (buffer == "yap")            tokens.push_back({ TokenType::OUTPUT, line, 1       });
    else if (buffer == "eavesdrop") tokens.push_back({ TokenType::INPUT, line, 1        });
    else if (buffer == "grind")     tokens.push_back({ TokenType::LOOP_START, line, 1   });
    else if (buffer == "quit")      tokens.push_back({ TokenType::LOOP_END, line, 1     });
    else if (buffer == "click")     tokens.push_back({ TokenType::INCREMENT, line, 1    });
    else if (buffer == "miss")      tokens.push_back({ TokenType::DECREMENT, line, 1    });
    else if (buffer == "set")       tokens.push_back({ TokenType::SET_CONSTANT, line, 1 });
    else {
        if (!tokens.empty() && (tokens.back().type == TokenType::SET_CONSTANT || tokens.back().identifier.empty())) {
            tokens.back().identifier = buffer;
        }
    }

    buffer.clear();
}

std::vector<Token> tokenize(const std::string& sourceCode) {
    std::vector<Token> rawTokens;
    std::string currentWord, numberBuffer;
    size_t currentLine = 1;
    bool insideComment = false, expectingSecondSlash = false, insideCharLiteral = false;

    auto finalizeNumber = [&]() {
        if (!numberBuffer.empty() && !rawTokens.empty()) {
            rawTokens.back().count = std::stoull(numberBuffer);
            numberBuffer.clear();
        }
    };

    for (char rawChar : sourceCode) {
        if (rawChar == '\'' && !insideComment) {
            finalizeNumber();
            flushBuffer(currentWord, rawTokens, currentLine);
            insideCharLiteral = !insideCharLiteral;
            continue;
        }

        if (insideCharLiteral) {
            if (!rawTokens.empty()) {
                rawTokens.back().count = static_cast<size_t>(rawChar);
            }
            continue;
        }

        if (insideComment) {
            if (rawChar == '\n') { currentLine++; insideComment = false; }
            continue;
        }

        if (expectingSecondSlash) {
            expectingSecondSlash = false;
            if (rawChar == '/') { finalizeNumber(); flushBuffer(currentWord, rawTokens, currentLine); insideComment = true; continue; }
            else currentWord += '/';
        }

        if (rawChar == '#' || rawChar == '/') {
            if (rawChar == '/') { expectingSecondSlash = true; continue; }
            finalizeNumber(); flushBuffer(currentWord, rawTokens, currentLine); insideComment = true; continue;
        }

        if (std::isdigit(static_cast<unsigned char>(rawChar))) {
            flushBuffer(currentWord, rawTokens, currentLine);
            numberBuffer += rawChar;
            continue;
        }

        if (!numberBuffer.empty()) finalizeNumber();

        char c = std::tolower(static_cast<unsigned char>(rawChar));
        if (c == '\n') { flushBuffer(currentWord, rawTokens, currentLine); currentLine++; }
        else if (c == ' ' || c == '\t' || c == '\r') { flushBuffer(currentWord, rawTokens, currentLine); }
        else if ((c == 'w' || c == 'a' || c == 's' || c == 'd') && currentWord.empty()) {
            TokenType type = (c == 'd') ? TokenType::MOVE_RIGHT : (c == 'a') ? TokenType::MOVE_LEFT : (c == 'w') ? TokenType::MOVE_UP : TokenType::MOVE_DOWN;
            if (!rawTokens.empty() && rawTokens.back().type == type && rawTokens.back().line == currentLine) rawTokens.back().count++;
            else rawTokens.push_back({type, currentLine, 1, ""});
        } else {
            currentWord += c;
        }
    }
    finalizeNumber(); flushBuffer(currentWord, rawTokens, currentLine);

    std::vector<Token> optimizedTokens;
    std::map<std::string, size_t> constantsTable;

    for (const auto& tok : rawTokens) {
        if (tok.type == TokenType::SET_CONSTANT) {
            constantsTable[tok.identifier] = tok.count;
        } else {
            Token cleanTok = tok;
            if (!tok.identifier.empty() && constantsTable.count(tok.identifier)) {
                cleanTok.count = constantsTable[tok.identifier];
            }
            optimizedTokens.push_back(cleanTok);
        }
    }
    return optimizedTokens;
}