#pragma once
#include "LogRecord.hpp"
#include "CollectingEmitter.hpp"
#include <string>
#include <regex>

class ParserStage {
public:
    bool processLine(const std::string& rawLine, CollectingEmitter& emitter) {
        // Boþ satýr veya sadece boþluk içeren satýr kontrolü
        if (rawLine.empty() || rawLine.find_first_not_of(" \t\n\r") == std::string::npos) {
            emitter.addError();
            return false;
        }

        // CLF formatý için Düzenli Ýfade (Regex)
        std::regex clfRegex(R"(^(\S+) \S+ \S+ \[(.*?)\] \"([A-Z]+) ([^\"]*?) HTTP[/\d\.]*\" (\d{3}) (\d+)(?: \"([^\"]*)\")?)");
        std::smatch matches;

        if (std::regex_search(rawLine, matches, clfRegex)) {
            try {
                LogRecord record;
                record.clientIp = matches[1];
                record.timestamp = matches[2];
                record.method = matches[3];
                record.path = matches[4];
                record.status = std::stoi(matches[5]);
                record.bytes = std::stoll(matches[6]);
                record.userAgent = matches[7].matched ? matches[7].str() : "";
                record.raw = rawLine;

                emitter.emit(record);
                return true;
            } catch (...) {
                // Sayýsal dönüþüm hatalarýnda (status veya bytes bozuksa)
                emitter.addError();
                return false;
            }
        }

        // Eþleþme saðlanamadýysa hatalý satýr sayacýný artýr
        emitter.addError();
        return false;
    }
};
