#pragma once
#include <string>
#include <map>

struct LogRecord {
    std::string timestamp;
    std::string clientIp;
    std::string method;
    std::string path;
    int status;
    long long bytes;
    std::string userAgent;
    std::map<std::string, std::string> attributes; // 5-7. haftalardaki geniþletme noktasý
    std::string raw;
};
