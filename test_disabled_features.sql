-- 测试屏蔽的功能

-- 测试CREATE VIEW（应该失败）
CREATE VIEW test_view AS SELECT * FROM test_table;

-- 测试ORDER BY（应该失败）
SELECT * FROM test_table ORDER BY id;

-- 测试GROUP BY（应该失败）
SELECT COUNT(*) FROM test_table GROUP BY name;

-- 测试UNIQUE索引（应该失败）
CREATE UNIQUE INDEX idx_unique ON test_table (id);

-- 测试别名（应该失败）
SELECT t.id FROM test_table AS t;

-- 测试非聚合函数（应该失败）
SELECT UPPER(name) FROM test_table;

-- 测试子查询（应该失败）
SELECT * FROM test_table WHERE id IN (SELECT id FROM other_table);

-- 测试CREATE TABLE ... SELECT（应该失败）
CREATE TABLE new_table AS SELECT * FROM test_table;

-- 测试仍应工作的功能

-- 测试基本查询（应该成功）
SELECT * FROM test_table;

-- 测试LIKE操作（应该成功）
SELECT * FROM test_table WHERE name LIKE 'test%';

-- 测试聚合函数（应该成功）
SELECT COUNT(*), SUM(id), AVG(id), MAX(id), MIN(id) FROM test_table;

-- 测试JOIN（应该成功）
SELECT * FROM test_table t1 INNER JOIN test_table2 t2 ON t1.id = t2.id;

-- 测试基本UPDATE（应该成功）
UPDATE test_table SET name = 'new_name' WHERE id = 1;

-- 测试NULL相关（应该成功）
SELECT * FROM test_table WHERE name IS NULL; 