-- Test LIKE functionality in miniob
CREATE TABLE test_like (id INT, name CHAR(20));

-- Insert test data
INSERT INTO test_like VALUES (1, 'apple');
INSERT INTO test_like VALUES (2, 'banana'); 
INSERT INTO test_like VALUES (3, 'cherry');
INSERT INTO test_like VALUES (4, 'date');
INSERT INTO test_like VALUES (5, 'elderberry');
INSERT INTO test_like VALUES (6, 'fig');
INSERT INTO test_like VALUES (7, 'grape');

-- Test basic LIKE patterns
SELECT * FROM test_like WHERE name LIKE 'a%';
SELECT * FROM test_like WHERE name LIKE '%e';
SELECT * FROM test_like WHERE name LIKE '%r%';
SELECT * FROM test_like WHERE name LIKE '_a%';

-- Test NOT LIKE patterns  
SELECT * FROM test_like WHERE name NOT LIKE 'a%';
SELECT * FROM test_like WHERE name NOT LIKE '%e';

-- Test UPDATE with LIKE conditions
UPDATE test_like SET name = 'APPLE' WHERE name LIKE 'apple';
SELECT * FROM test_like WHERE id = 1;

UPDATE test_like SET name = 'BANANA' WHERE name LIKE 'ban%';
SELECT * FROM test_like WHERE id = 2;

UPDATE test_like SET name = 'CHERRY' WHERE name LIKE '%erry';
SELECT * FROM test_like WHERE id = 3;

-- Test DELETE with LIKE conditions
DELETE FROM test_like WHERE name LIKE 'fig';
SELECT * FROM test_like;

-- Clean up
DROP TABLE test_like; 