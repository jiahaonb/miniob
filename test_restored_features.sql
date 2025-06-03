-- 测试恢复的ORDER BY和GROUP BY功能

CREATE TABLE employees (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    department CHAR(20) NOT NULL,
    salary INT NOT NULL,
    age INT NULL
);

INSERT INTO employees VALUES (1, 'Alice', 'Engineering', 80000, 25);
INSERT INTO employees VALUES (2, 'Bob', 'Sales', 60000, 30);
INSERT INTO employees VALUES (3, 'Charlie', 'Engineering', 90000, 35);
INSERT INTO employees VALUES (4, 'Diana', 'Sales', 65000, 28);
INSERT INTO employees VALUES (5, 'Eve', 'Engineering', 75000, 26);

-- 基本查询（应该能工作）
SELECT * FROM employees;

-- 测试ORDER BY功能（应该能工作）
SELECT * FROM employees ORDER BY salary DESC;
SELECT name, salary FROM employees ORDER BY age ASC;

-- 测试GROUP BY功能（应该能工作）
SELECT department, COUNT(*) FROM employees GROUP BY department;
SELECT department, AVG(salary) FROM employees GROUP BY department;

-- 测试GROUP BY + HAVING功能（应该能工作）
SELECT department, COUNT(*) FROM employees GROUP BY department HAVING COUNT(*) > 1;

-- 测试ORDER BY + GROUP BY组合（应该能工作）
SELECT department, AVG(salary) FROM employees GROUP BY department ORDER BY AVG(salary) DESC;

-- 清理
DROP TABLE employees; 