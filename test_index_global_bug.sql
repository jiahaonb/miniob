-- 初始化两个表
CREATE TABLE unique_table1(id INT, col1 INT, col2 INT);
CREATE TABLE unique_table2(id INT, col1 INT, col2 INT);

-- 向 unique_table1 中插入一行
INSERT INTO unique_table1 VALUES (1, 1, 1);

-- 在 unique_table1 上创建唯一索引
CREATE UNIQUE INDEX index_id ON unique_table1(id);

-- 再插入一行，合法，不冲突
INSERT INTO unique_table1 VALUES (2, 1, 1);

-- 在 unique_table2 上插入一行
-- 此时 unique_table2 没有任何索引，不应该校验唯一性！
INSERT INTO unique_table2 VALUES (2, 1, 1);

-- 查看数据是否插入
SELECT * FROM unique_table1;
SELECT * FROM unique_table2; 