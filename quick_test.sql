CREATE TABLE test_users (id INT, name CHAR(20));
INSERT INTO test_users VALUES (1, 'Alice');
INSERT INTO test_users VALUES (2, 'Bob');
SELECT * FROM test_users WHERE name LIKE 'A%';
exit;
