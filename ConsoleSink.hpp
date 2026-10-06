#pragma once
#include "LogRecord.hpp"
#include <iostream>

class ConsoleSink {
public:
    void write(const LogRecord& record) {
        std::cout << "[IP: " << record.clientIp 
                  << "] [Time: " << record.timestamp 
                  << "] [Method: " << record.method 
                  << " Path: " << record.path 
                  << "] [Status: " << record.status 
                  << "] [Bytes: " << record.bytes << "]" << std::endl;
    }
};
