-- 简单的CREATE VIEW测试

-- 创建基础表
CREATE TABLE students (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    age INT NOT NULL,
    grade CHAR(10) NOT NULL
);

-- 插入测试数据
INSERT INTO students VALUES (1, 'Alice', 20, 'A');
INSERT INTO students VALUES (2, 'Bob', 21, 'B');
INSERT INTO students VALUES (3, 'Charlie', 19, 'A');

-- 查看原始数据
SELECT * FROM students;

-- 创建简单视图
CREATE VIEW good_students AS SELECT id, name FROM students WHERE grade = 'A';

-- 查询视图
SELECT * FROM good_students;

-- 创建带列名的视图
CREATE VIEW student_info (student_id, student_name, student_age) AS SELECT id, name, age FROM students;

-- 查询带列名的视图
SELECT * FROM student_info;

-- 删除视图
DROP VIEW good_students;
DROP VIEW student_info;

-- 删除表
DROP TABLE students; 