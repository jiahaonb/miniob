#include <iostream>
#include <string>

extern "C" {
    struct ParsedSqlResult;
    int sql_parse(const char *s, ParsedSqlResult *sql_result);
}

int main() {
    std::cout << "测试被屏蔽的SQL功能..." << std::endl;
    return 0;
} 