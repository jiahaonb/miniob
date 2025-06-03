#include "sql/parser/parse.h"
#include "common/log/log.h"
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> test_queries = {
        // 应该失败的查询
        "CREATE VIEW test_view AS SELECT 1;",
        "SELECT 1 ORDER BY 1;",
        "SELECT COUNT(1) GROUP BY 1;",
        "CREATE UNIQUE INDEX idx_test ON test_table (id);",
        "SELECT t.id FROM test_table AS t;",
        "SELECT UPPER('test');",
        "SELECT * FROM test_table WHERE id IN (SELECT id FROM other_table);",
        "CREATE TABLE new_table AS SELECT * FROM test_table;",
        
        // 应该成功的查询
        "SELECT 1;",
        "SELECT COUNT(1);",
        "SELECT * FROM test_table;",
        "SELECT * FROM test_table WHERE name LIKE 'test%';",
        "UPDATE test_table SET name = 'new_name' WHERE id = 1;",
        "SELECT * FROM test_table WHERE name IS NULL;"
    };
    
    for (const auto& query : test_queries) {
        std::cout << "\n测试查询: " << query << std::endl;
        
        ParsedSqlResult result;
        RC rc = parse(query.c_str(), &result);
        
        if (rc == RC::SUCCESS) {
            std::cout << "  结果: ✅ 解析成功" << std::endl;
        } else {
            std::cout << "  结果: ❌ 解析失败 (期望的屏蔽功能)" << std::endl;
        }
        
        // 检查是否有错误消息
        if (result.sql_nodes().size() > 0) {
            auto& node = result.sql_nodes()[0];
            if (node->flag == SCF_ERROR) {
                std::cout << "  错误信息: " << node->error.error_msg << std::endl;
            }
        }
    }
    
    return 0;
} 