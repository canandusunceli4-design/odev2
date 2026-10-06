#include <iostream>
#include <cassert>
#include "ParserStage.hpp"
#include "CollectingEmitter.hpp"

// Test yardýmcý makrosu
#define RUN_TEST(test_func) \
    do { \
        test_func(); \
        std::cout << "[BASARILI] " << #test_func << std::endl; \
    } while (0)

// 1. Geçerli satýr testi
void testValidLine() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "127.0.0.1 - - [10/Oct/2000:13:55:36 -0700] \"GET /index.html HTTP/1.0\" 200 2326 \"Mozilla/5.0\"";
    
    bool result = parser.processLine(line, emitter);
    assert(result == true);
    assert(emitter.getRecords().size() == 1);
    assert(emitter.getErrorCount() == 0);
    assert(emitter.getRecords()[0].status == 200);
}

// 2. Eksik alan testi
void testMissingField() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "127.0.0.1 - - [10/Oct/2000:13:55:36 -0700] \"GET /index.html\"";
    
    bool result = parser.processLine(line, emitter);
    assert(result == false);
    assert(emitter.getErrorCount() == 1);
}

// 3. Hatalý zaman damgasý testi
void testMalformedTimestamp() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "127.0.0.1 - - 10/Oct/2000:13:55:36 \"GET /index.html HTTP/1.0\" 200 2326";
    
    bool result = parser.processLine(line, emitter);
    assert(result == false);
    assert(emitter.getErrorCount() == 1);
}

// 4. Hatalý durum kodu testi
void testMalformedStatusCode() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "127.0.0.1 - - [10/Oct/2000:13:55:36 -0700] \"GET /index.html HTTP/1.0\" ABC 2326";
    
    bool result = parser.processLine(line, emitter);
    assert(result == false);
    assert(emitter.getErrorCount() == 1);
}

// 5. Boþ satýr testi
void testEmptyLine() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "";
    
    bool result = parser.processLine(line, emitter);
    assert(result == false);
    assert(emitter.getErrorCount() == 1);
}

// 6. Fazladan boþluk / whitespace testi
void testExtraWhitespaceLine() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "   \t   ";
    
    bool result = parser.processLine(line, emitter);
    assert(result == false);
    assert(emitter.getErrorCount() == 1);
}

// 7. Boþluk içeren týrnaklý user agent testi
void testUserAgentWithSpacesInQuotes() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "192.168.1.1 - - [10/Oct/2000:13:55:36 -0700] \"POST /submit HTTP/1.1\" 201 512 \"Mozilla/5.0 (Windows NT 10.0; Win64; x64)\"";
    
    bool result = parser.processLine(line, emitter);
    assert(result == true);
    assert(emitter.getRecords()[0].userAgent == "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
}

// 8. Sorgu dizesi (query string) içeren bir satýr testi
void testLineWithQueryString() {
    ParserStage parser;
    CollectingEmitter emitter;
    std::string line = "10.0.0.1 - - [10/Oct/2000:13:55:36 -0700] \"GET /search?q=logflow&sort=asc HTTP/1.1\" 200 1024";
    
    bool result = parser.processLine(line, emitter);
    assert(result == true);
    assert(emitter.getRecords()[0].path == "/search?q=logflow&sort=asc");
}

int main() {
    std::cout << "=== LogFlow Artim 2 Testleri Basliyor ===" << std::endl;
    
    RUN_TEST(testValidLine);
    RUN_TEST(testMissingField);
    RUN_TEST(testMalformedTimestamp);
    RUN_TEST(testMalformedStatusCode);
    RUN_TEST(testEmptyLine);
    RUN_TEST(testExtraWhitespaceLine);
    RUN_TEST(testUserAgentWithSpacesInQuotes);
    RUN_TEST(testLineWithQueryString);
    
    std::cout << "========================================" << std::endl;
    std::cout << "Tum testler basariyla gecti!" << std::endl;
    return 0;
}
