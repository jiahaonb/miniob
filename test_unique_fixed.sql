-- 测试修复后的unique索引功能
drop table test_unique_fixed;
create table test_unique_fixed (id int, name char(10), age int);

-- 测试1: 创建unique索引
create unique index idx_unique_id on test_unique_fixed(id);

-- 测试2: 插入数据
insert into test_unique_fixed values (1, 'Alice', 20);
insert into test_unique_fixed values (2, 'Bob', 25);

-- 测试3: 查看数据
select * from test_unique_fixed;

-- 测试4: 尝试插入重复的id，应该失败
insert into test_unique_fixed values (1, 'Charlie', 30);

-- 测试5: 查看数据，应该还是只有两条记录
select * from test_unique_fixed;

-- 测试6: 插入新的唯一id，应该成功
insert into test_unique_fixed values (3, 'David', 35);

-- 测试7: 最终查看数据
select * from test_unique_fixed;

-- 测试8: 测试带条件的查询（之前崩溃的地方）
select * from test_unique_fixed where id = 2;
select * from test_unique_fixed where id = 55;

-- 清理
drop table test_unique_fixed; 