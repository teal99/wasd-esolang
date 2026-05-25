// interpreter.cpp

#include "../include/interpreter.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <stack>

struct Coordinate {
    long long x;
    long long y;

    bool operator<(const Coordinate& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

void interpret(const std::vector<Token>& tokens) {
    if (tokens.empty()) return;

    std::map<Coordinate, uint8_t> gridTape;
    Coordinate playerPos = {0, 0};
    size_t ip = 0;

    std::vector<size_t> loopMap(tokens.size(), 0);
    std::stack<size_t> loopStack;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == TokenType::LOOP_START) {
            loopStack.push(i);
        } else if (tokens[i].type == TokenType::LOOP_END) {
            if (loopStack.empty()) {
                std::cerr << "[ERROR]: Unmatched 'quit' keyword on line " << tokens[i].line << "!\n";
                exit(1);
            }
            size_t start = loopStack.top();
            loopStack.pop();
            loopMap[start] = i;
            loopMap[i] = start;
        }
    }

    if (!loopStack.empty()) {
        std::cerr << "[ERROR]: Missing 'quit' keyword for loop started on line " << tokens[loopStack.top()].line << "!\n";
        exit(1);
    }

    // std::cout << "[DEBUG]: Starting optimized interpreter execution loop...\n";

    while (ip < tokens.size()) {
        const auto& token = tokens[ip];
        
        switch (token.type) {
            case TokenType::MOVE_RIGHT: playerPos.x += token.count; break;
            case TokenType::MOVE_LEFT:  playerPos.x -= token.count; break;
            case TokenType::MOVE_UP:    playerPos.y += token.count; break;
            case TokenType::MOVE_DOWN:  playerPos.y -= token.count; break;

            case TokenType::INCREMENT: gridTape[playerPos] += static_cast<uint8_t>(token.count); break;
            case TokenType::DECREMENT: gridTape[playerPos] -= static_cast<uint8_t>(token.count); break;
            
            case TokenType::OUTPUT: {
                for(size_t i = 0; i < token.count; ++i) {
                    std::cout << static_cast<char>(gridTape[playerPos]);
                }
                std::cout << std::flush;
                break;
            }
            case TokenType::INPUT:       
                gridTape[playerPos] = std::cin.get(); 
                break;
            case TokenType::LOOP_START:
                if (gridTape[playerPos] == 0) ip = loopMap[ip]; 
                break;
            case TokenType::LOOP_END:
                if (gridTape[playerPos] != 0) ip = loopMap[ip]; 
                break;
        }
        ip++;
    }

    // std::cout << "\n[DEBUG]: Interpreter finished execution cleanly.\n";
}