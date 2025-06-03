-- Test JOIN functionality
CREATE TABLE t1 (id INT, name CHAR(10));
CREATE TABLE t2 (id INT, age INT);

-- Insert test data
INSERT INTO t1 VALUES (1, 'Alice');
INSERT INTO t1 VALUES (2, 'Bob');
INSERT INTO t1 VALUES (3, 'Charlie');

INSERT INTO t2 VALUES (1, 25);
INSERT INTO t2 VALUES (2, 30);
INSERT INTO t2 VALUES (4, 35);

-- Test basic cross join (should work in basic version)
SELECT * FROM t1, t2;

-- Test join with where condition (should work in basic version)
SELECT * FROM t1, t2 WHERE t1.id = t2.id;

-- Clean up
DROP TABLE t1;
DROP TABLE t2; 