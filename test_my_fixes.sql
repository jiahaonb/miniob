-- 测试 UNIQUE INDEX 修复
CREATE TABLE test_unique_fix(id int, name char(10));
CREATE UNIQUE INDEX idx_id on test_unique_fix(id);

-- 这些插入应该成功
INSERT INTO test_unique_fix VALUES (1, 'Alice');
INSERT INTO test_unique_fix VALUES (2, 'Bob');
SELECT * FROM test_unique_fix;

-- 这个插入应该失败 (重复的id=1)
INSERT INTO test_unique_fix VALUES (1, 'Charlie');
SELECT * FROM test_unique_fix;

-- 测试 UPDATE 字符串截断修复
CREATE TABLE test_update_str(id int, name char(5));
INSERT INTO test_update_str VALUES (1, 'Al');
INSERT INTO test_update_str VALUES (2, 'Bob');

-- 这个UPDATE应该将字符串截断到5个字符
UPDATE test_update_str SET name = 'TooLongName' WHERE id = 1;
SELECT * FROM test_update_str;

DROP TABLE test_unique_fix;
DROP TABLE test_update_str; 