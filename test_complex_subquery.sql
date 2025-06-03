-- 测试复杂子查询功能 (complex-sub-query)

-- 创建测试表
CREATE TABLE departments (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    budget INT NOT NULL
);

CREATE TABLE employees (
    id INT NOT NULL,
    name CHAR(20) NOT NULL,
    dept_id INT NOT NULL,
    salary INT NOT NULL,
    age INT NOT NULL
);

CREATE TABLE projects (
    id INT NOT NULL,
    name CHAR(30) NOT NULL,
    dept_id INT NOT NULL,
    budget INT NOT NULL
);

-- 插入测试数据
INSERT INTO departments VALUES (1, 'Engineering', 500000);
INSERT INTO departments VALUES (2, 'Sales', 300000);
INSERT INTO departments VALUES (3, 'Marketing', 200000);

INSERT INTO employees VALUES (1, 'Alice', 1, 80000, 28);
INSERT INTO employees VALUES (2, 'Bob', 2, 60000, 32);
INSERT INTO employees VALUES (3, 'Charlie', 1, 90000, 35);
INSERT INTO employees VALUES (4, 'Diana', 2, 65000, 29);
INSERT INTO employees VALUES (5, 'Eve', 3, 55000, 26);
INSERT INTO employees VALUES (6, 'Frank', 1, 85000, 31);

INSERT INTO projects VALUES (1, 'WebProject', 1, 100000);
INSERT INTO projects VALUES (2, 'MobileApp', 1, 150000);
INSERT INTO projects VALUES (3, 'SalesPortal', 2, 80000);
INSERT INTO projects VALUES (4, 'Campaign', 3, 50000);

-- 基本查询验证数据
SELECT 'Departments:' AS info;
SELECT * FROM departments;
SELECT 'Employees:' AS info;
SELECT * FROM employees;
SELECT 'Projects:' AS info;
SELECT * FROM projects;

-- 测试复杂子查询功能

-- 1. 简单子查询 - 查找工资高于平均工资的员工
SELECT name, salary FROM employees WHERE salary > (SELECT AVG(salary) FROM employees);

-- 2. 相关子查询 - 查找在各自部门中工资最高的员工
SELECT e1.name, e1.dept_id, e1.salary 
FROM employees e1 
WHERE e1.salary = (SELECT MAX(e2.salary) FROM employees e2 WHERE e2.dept_id = e1.dept_id);

-- 3. IN子查询 - 查找在有项目的部门工作的员工
SELECT name, dept_id FROM employees WHERE dept_id IN (SELECT DISTINCT dept_id FROM projects);

-- 4. EXISTS子查询 - 查找有员工的部门
SELECT d.name FROM departments d WHERE EXISTS (SELECT 1 FROM employees e WHERE e.dept_id = d.id);

-- 5. 多层嵌套子查询 - 查找在预算最高的部门工作的员工
SELECT name FROM employees WHERE dept_id = (SELECT id FROM departments WHERE budget = (SELECT MAX(budget) FROM departments));

-- 6. 复杂条件子查询 - 查找工资高于其部门平均工资且年龄小于30的员工
SELECT e1.name, e1.salary, e1.age, e1.dept_id
FROM employees e1 
WHERE e1.salary > (SELECT AVG(e2.salary) FROM employees e2 WHERE e2.dept_id = e1.dept_id) 
  AND e1.age < 30;

-- 7. 子查询与聚合函数结合 - 查找员工数量超过2的部门
SELECT d.name, d.budget 
FROM departments d 
WHERE d.id IN (SELECT dept_id FROM employees GROUP BY dept_id HAVING COUNT(*) > 2);

-- 8. 多表子查询 - 查找部门预算超过该部门所有项目预算总和的部门
SELECT d.name AS dept_name, d.budget AS dept_budget
FROM departments d 
WHERE d.budget > (SELECT COALESCE(SUM(p.budget), 0) FROM projects p WHERE p.dept_id = d.id);

-- 清理测试数据
DROP TABLE projects;
DROP TABLE employees;
DROP TABLE departments; 