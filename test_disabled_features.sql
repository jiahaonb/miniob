-- 测试基本功能（应该能工作）
CREATE TABLE test_table (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    age INT NULL
);

INSERT INTO test_table VALUES (1, 'Alice', 25);
INSERT INTO test_table VALUES (2, 'Bob', 30);
INSERT INTO test_table VALUES (3, 'Charlie', NULL);

SELECT * FROM test_table;
SELECT id, name FROM test_table WHERE age > 20;

-- 测试被屏蔽的功能（应该报错）

-- 测试ORDER BY（应该报错）
-- SELECT * FROM test_table ORDER BY age;

-- 测试GROUP BY（应该报错）
-- SELECT age, COUNT(*) FROM test_table GROUP BY age;

-- 测试HAVING（应该报错）
-- SELECT age FROM test_table GROUP BY age HAVING COUNT(*) > 1;

-- 测试CREATE VIEW（应该报错）
-- CREATE VIEW test_view AS SELECT id, name FROM test_table;

-- 测试别名（应该报错）
-- SELECT id AS user_id, name AS user_name FROM test_table;

-- 清理
DROP TABLE test_table; 