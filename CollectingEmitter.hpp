#pragma once
#include "LogRecord.hpp"
#include <vector>

class CollectingEmitter {
private:
    std::vector<LogRecord> records;
    int errorCount = 0;

public:
    void emit(const LogRecord& record) {
        records.push_back(record);
    }

    void addError() {
        errorCount++;
    }

    const std::vector<LogRecord>& getRecords() const { return records; }
    int getErrorCount() const { return errorCount; }
    
    void clear() {
        records.clear();
        errorCount = 0;
    }
};
