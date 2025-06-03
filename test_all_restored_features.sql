-- 综合测试恢复的所有功能

-- 测试基础表和数据
CREATE TABLE employees (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    department CHAR(20) NOT NULL,
    salary INT NOT NULL,
    age INT NOT NULL
);

INSERT INTO employees VALUES (1, 'Alice', 'Engineering', 80000, 25);
INSERT INTO employees VALUES (2, 'Bob', 'Sales', 60000, 30);
INSERT INTO employees VALUES (3, 'Charlie', 'Engineering', 90000, 35);
INSERT INTO employees VALUES (4, 'Diana', 'Sales', 65000, 28);
INSERT INTO employees VALUES (5, 'Eve', 'Marketing', 75000, 26);
INSERT INTO employees VALUES (6, 'Frank', 'Engineering', 85000, 32);

-- 测试 ALIAS 功能
SELECT id AS emp_id, name AS emp_name, salary AS emp_salary FROM employees;
SELECT e.id, e.name, e.department AS dept FROM employees e WHERE e.age > 28;

-- 测试 AGGREGATION 功能
SELECT COUNT(*) AS total_employees FROM employees;
SELECT department, COUNT(*) AS dept_count, AVG(salary) AS avg_salary FROM employees GROUP BY department;
SELECT MAX(salary) AS max_salary, MIN(age) AS min_age FROM employees;

-- 测试 ORDER BY 和 GROUP BY 组合
SELECT department AS dept, AVG(salary) AS avg_sal FROM employees GROUP BY department ORDER BY avg_sal DESC;

-- 测试 COMPLEX SUB-QUERY 功能
SELECT * FROM employees WHERE salary > (SELECT AVG(salary) FROM employees);
SELECT * FROM employees WHERE department IN (SELECT department FROM employees WHERE salary > 70000);
SELECT name FROM employees WHERE age > (SELECT AVG(age) FROM employees WHERE department = 'Engineering');

-- 测试 CREATE TABLE AS SELECT (create-table-select) 功能
CREATE TABLE high_earners AS SELECT id, name, salary FROM employees WHERE salary > 70000;
SELECT * FROM high_earners;

CREATE TABLE dept_summary AS SELECT department, COUNT(*) AS emp_count, AVG(salary) AS avg_salary FROM employees GROUP BY department;
SELECT * FROM dept_summary;

-- 测试 VIEW 功能与 ALIAS 结合
CREATE VIEW emp_summary (emp_id, emp_name, dept_name, salary_amount) AS 
SELECT id, name, department, salary FROM employees WHERE age < 30;
SELECT * FROM emp_summary;

-- 测试复杂子查询与别名结合
SELECT e1.name AS emp_name, e1.salary AS emp_salary 
FROM employees e1 
WHERE e1.salary > (SELECT AVG(e2.salary) FROM employees e2 WHERE e2.department = e1.department);

-- 清理测试数据
DROP VIEW emp_summary;
DROP TABLE dept_summary;
DROP TABLE high_earners;
DROP TABLE employees; 