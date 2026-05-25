// interpreter.cpp

#include "../include/interpreter.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <stack>

void interpret(const std::vector<Token>& tokens) {
    if (tokens.empty()) return;

    const size_t TAPE_SIZE = 30000;
    std::vector<uint8_t> tape(TAPE_SIZE, 0);
    size_t ptr = 0;
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
            case TokenType::MOVE_RIGHT: 
                ptr = (ptr + token.count) % TAPE_SIZE; 
                break;
            case TokenType::MOVE_LEFT: {
                long long targetPtr = static_cast<long long>(ptr) - token.count;
                if (targetPtr < 0) {
                    ptr = (TAPE_SIZE - ((-targetPtr) % TAPE_SIZE)) % TAPE_SIZE;
                } else {
                    ptr = targetPtr % TAPE_SIZE;
                }
                break;
            }
            case TokenType::INCREMENT:   
                tape[ptr] += static_cast<uint8_t>(token.count); 
                break;
            case TokenType::DECREMENT:   
                tape[ptr] -= static_cast<uint8_t>(token.count); 
                break;
            case TokenType::OUTPUT: {
                for(size_t i = 0; i < token.count; ++i) {
                    std::cout << static_cast<char>(tape[ptr]);
                }
                std::cout << std::flush;
                break;
            }
            case TokenType::INPUT:       
                tape[ptr] = std::cin.get(); 
                break;
            case TokenType::LOOP_START:
                if (tape[ptr] == 0) ip = loopMap[ip]; 
                break;
            case TokenType::LOOP_END:
                if (tape[ptr] != 0) ip = loopMap[ip]; 
                break;
        }
        ip++;
    }

    // std::cout << "\n[DEBUG]: Interpreter finished execution cleanly.\n";
}