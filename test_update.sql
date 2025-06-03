-- 测试UPDATE功能
create table test_update (id int, name char(10), age int);
create unique index idx_id on test_update(id);

-- 插入测试数据
insert into test_update values (1, 'Alice', 20);
insert into test_update values (2, 'Bob', 25);
insert into test_update values (3, 'Charlie', 30);

-- 查看初始数据
select * from test_update;

-- 测试简单更新
update test_update set age = 21 where id = 1;
select * from test_update;

-- 测试更新唯一索引列，应该成功
update test_update set id = 4 where name = 'Bob';
select * from test_update;

-- 测试违反唯一约束的更新，应该失败
update test_update set id = 1 where name = 'Charlie';
select * from test_update;

-- 测试更新所有记录
update test_update set age = age + 1;
select * from test_update;

-- 清理
drop table test_update; 