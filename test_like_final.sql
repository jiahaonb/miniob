CREATE TABLE students (id INT, name CHAR(20));
INSERT INTO students VALUES (1, 'Alice');
INSERT INTO students VALUES (2, 'Bob'); 
INSERT INTO students VALUES (3, 'Charlie');
INSERT INTO students VALUES (4, 'David');

SELECT * FROM students;
SELECT * FROM students WHERE name LIKE 'A%';
SELECT * FROM students WHERE name LIKE '%a%';
SELECT * FROM students WHERE name LIKE 'B_b';
SELECT * FROM students WHERE name NOT LIKE 'A%';
SELECT id FROM students WHERE name LIKE 'Ch%'; 