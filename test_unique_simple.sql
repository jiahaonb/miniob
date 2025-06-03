CREATE TABLE unique_test2(id int, name char(20));
CREATE UNIQUE INDEX idx_id on unique_test2(id);
INSERT INTO unique_test2 VALUES (1, 'test1');
INSERT INTO unique_test2 VALUES (1, 'test2');
.quit 