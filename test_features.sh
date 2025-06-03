#!/bin/bash

OBSERVER="./build/bin/observer"
DB_DIR="./db_test"

# 清理并创建测试目录
rm -rf $DB_DIR
mkdir -p $DB_DIR

echo "启动数据库测试..."

# 测试CREATE VIEW（应该失败）
echo "=== 测试 CREATE VIEW（应该失败）==="
echo "CREATE VIEW test_view AS SELECT 1;" | $OBSERVER -f $DB_DIR

# 测试ORDER BY（应该失败）
echo "=== 测试 ORDER BY（应该失败）==="
echo "SELECT 1 ORDER BY 1;" | $OBSERVER -f $DB_DIR

# 测试GROUP BY（应该失败）
echo "=== 测试 GROUP BY（应该失败）==="
echo "SELECT COUNT(1) GROUP BY 1;" | $OBSERVER -f $DB_DIR

# 测试UNIQUE索引（应该失败）
echo "=== 测试 UNIQUE索引（应该失败）==="
echo "CREATE UNIQUE INDEX idx_test ON test_table (id);" | $OBSERVER -f $DB_DIR

# 测试仍应工作的功能

# 测试基本查询（应该成功）
echo "=== 测试基本查询（应该成功）==="
echo "SELECT 1;" | $OBSERVER -f $DB_DIR

# 测试聚合函数（应该成功）
echo "=== 测试聚合函数（应该成功）==="
echo "SELECT COUNT(1);" | $OBSERVER -f $DB_DIR

echo "测试完成!" 