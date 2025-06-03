-- 测试CREATE VIEW功能

CREATE TABLE products (
    id INT NOT NULL,
    name CHAR(30) NOT NULL,
    price FLOAT NOT NULL,
    category CHAR(20) NOT NULL,
    stock INT NOT NULL
);

INSERT INTO products VALUES (1, 'Laptop', 999.99, 'Electronics', 50);
INSERT INTO products VALUES (2, 'Mouse', 25.50, 'Electronics', 200);
INSERT INTO products VALUES (3, 'Desk', 199.99, 'Furniture', 30);
INSERT INTO products VALUES (4, 'Chair', 89.99, 'Furniture', 40);
INSERT INTO products VALUES (5, 'Phone', 599.99, 'Electronics', 100);

-- 基本查询（验证数据）
SELECT * FROM products;

-- 测试CREATE VIEW功能
CREATE VIEW electronics_view AS SELECT id, name, price FROM products WHERE category = 'Electronics';

-- 测试查询视图
SELECT * FROM electronics_view;

-- 测试CREATE VIEW with column list
CREATE VIEW expensive_products (product_id, product_name, product_price) AS SELECT id, name, price FROM products WHERE price > 100;

-- 测试查询带列名的视图
SELECT * FROM expensive_products;

-- 测试DROP VIEW功能
DROP VIEW electronics_view;
DROP VIEW expensive_products;

-- 清理
DROP TABLE products; 