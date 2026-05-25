// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/lexer.hpp"
#include "../include/interpreter.hpp"
#include "../include/config.hpp"

int main(int argc, char* argv[]) {
    loadConfiguration();

    if (argc < 2) {
        std::cerr << "Usage Error: Please provide a source file!\n";
        std::cerr << "Example: ./wasd examples/hello_world.wasd\n";
        return 1;
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "File Error: Could not open file '" << filePath << "'\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();
    file.close();

    if (g_Config.enableFileDebug) {
        std::cout << "[DEBUG]: File Size Read: " << sourceCode.length() << " characters.\n";
        std::cout << "[DEBUG]: Raw Contents:\n---\n" << sourceCode << "\n---\n";
    }

    std::vector<Token> tokens = tokenize(sourceCode);

    if (g_Config.enableTokenDebug) {
        std::cout << "[DEBUG]: Lexer found " << tokens.size() << " unique compressed token nodes.\n";
    }

    if (tokens.empty()) {
        if (g_Config.enableTokenDebug) {
            std::cout << "[DEBUG]: Process stopped because token list was empty.\n";
        }
        return 0;
    }

    if (g_Config.enableTokenDebug) {
        std::cout << "[DEBUG]: Token Stream Detail:\n";
        for (size_t i = 0; i < tokens.size(); ++i) {
            std::cout << "  [" << i << "] Type: " << static_cast<int>(tokens[i].type) 
                      << " | Count: " << tokens[i].count 
                      << " | Line: " << tokens[i].line << "\n";
        }
        std::cout << "---\n";
    }

    interpret(tokens);

    return 0;
}