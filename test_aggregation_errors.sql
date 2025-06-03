CREATE TABLE aggregation_func(num int, price float, addr char);
INSERT INTO aggregation_func VALUES (1, 1.5, 'A');
INSERT INTO aggregation_func VALUES (2, 2.5, 'B');

-- Test valid queries
SELECT count(*) FROM aggregation_func;
SELECT count(num) FROM aggregation_func;
SELECT sum(num) FROM aggregation_func;

-- Test error cases that should output FAILURE
-- 1. Error with redundant columns (multiple arguments)
SELECT count(*,num) FROM aggregation_func;
SELECT min(num,price) FROM aggregation_func;

-- 2. Error with empty columns (no arguments)
SELECT count() FROM aggregation_func;
SELECT min() FROM aggregation_func;
SELECT max() FROM aggregation_func;

-- 3. Error with * for non-count functions
SELECT min(*) FROM aggregation_func;
SELECT max(*) FROM aggregation_func;
SELECT avg(*) FROM aggregation_func;

-- 4. Error with non-existent columns
SELECT count(id2) FROM aggregation_func;
SELECT min(id2) FROM aggregation_func;

-- 5. Unknown function
SELECT unknown_func(num) FROM aggregation_func; 