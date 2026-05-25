// config.hpp

struct RuntimeConfig {
    bool enableFileDebug = false;
    bool enableTokenDebug = false;
    bool enableExecutionDebug = false;
};

extern RuntimeConfig g_Config;

void loadConfiguration();