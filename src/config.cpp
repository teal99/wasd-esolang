// config.cpp

#include "../include/config.hpp"
#include <iostream>
#include <fstream>
#include <string>

RuntimeConfig g_Config;

void loadConfiguration() {
    std::ifstream file("config.json");
    if (!file.is_open()) {
        g_Config.enableFileDebug = false;
        g_Config.enableTokenDebug = false;
        g_Config.enableExecutionDebug = false;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("\"enableFileDebug\"") != std::string::npos) {
            g_Config.enableFileDebug = (line.find("true") != std::string::npos);
        }
        else if (line.find("\"enableTokenDebug\"") != std::string::npos) {
            g_Config.enableTokenDebug = (line.find("true") != std::string::npos);
        }
        else if (line.find("\"enableExecutionDebug\"") != std::string::npos) {
            g_Config.enableExecutionDebug = (line.find("true") != std::string::npos);
        }
    }
    file.close();
}