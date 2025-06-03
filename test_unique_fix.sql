CREATE TABLE unique_table1(id int, score int, name char(20));
CREATE UNIQUE INDEX index_id on unique_table1(id);
INSERT INTO unique_table1 VALUES (2,1,1);
INSERT INTO unique_table1 VALUES (3,2,1);
INSERT INTO unique_table1 VALUES (1,2,1);
INSERT INTO unique_table1 VALUES (1,3,1);
SELECT * FROM unique_table1; 