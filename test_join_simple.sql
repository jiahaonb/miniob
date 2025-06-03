-- 创建测试表
CREATE TABLE table1(id int, name char);
CREATE TABLE table2(id int, value int);

-- 插入测试数据
INSERT INTO table1 VALUES (1, 'a');
INSERT INTO table1 VALUES (2, 'b');
INSERT INTO table1 VALUES (3, 'c');

INSERT INTO table2 VALUES (1, 100);
INSERT INTO table2 VALUES (2, 200);
INSERT INTO table2 VALUES (4, 400);

-- 简单的JOIN测试
SELECT * FROM table1 INNER JOIN table2 ON table1.id = table2.id; 