# 变量类型

| 变量类型         | 含义                                     |
|:------------:|:-------------------------------------- |
| char(n)      | 长度为N的定长字符串                             |
| varchar(n)   | 最大长度为n的不定长字符串                          |
| clob         | 字符串对象                                  |
| blob         | 二进制对象                                  |
| int          | 整型（4                                   |
| smallint     | 短整型（2                                  |
| bigint       | 长整型（8                                  |
| numeric(p,d) | 定点数，一共有p位数字，d位是小数点后面的                  |
| decimal(p,d) | 同numeric                               |
| dec(p,d)     | 同numeric                               |
| real         | 取决于机器精度的单精度浮点数                         |
| double       | 高精度浮点数                                 |
| boolean      | 逻辑布尔型                                  |
| date         | 日期，YYYY-MM-DD                          |
| time         | 时间，HH：MM：SS                            |
| timestamp    | 时间戳                                    |
| interval     | 时间间隔类型                                 |
| not null     | 非空                                     |
| primary key  | 主键，也可primary key (id)                  |
| foreign key  | 外键，forergn key(id) Reference table(id) |
| unique       | 唯一                                     |
| check        | sex char(2) check(sex in(1,2)          |

# 模式

```shell
create schema <模式名> authorization <用户名> [<视图> | <表定义句> | <授权>]

# 为用户TREE定义一个ST模式
create schema "ST" authorization Tree

# 定义一个ST模式后，创建一个表User
create schema "ST" authorization Tree
create table user( id int primary key , age int ,name varchar(255));

# 删除模式
# 删除模式, 其中 CASCADE 和RESTRICT 必须⼆选⼀, 
# CASCADE是(级联) 删除模式的同时也把该模式的所有数据库对象删除. 
# RESTRICT(限制) 如果该模式下有下属对象,⽐如表视图 就拒绝这个删除语句的执⾏
drop schema <模式名> <cascade | restrict>
```

# 表

```shell
create table <表名>(<属性>)


# 创建user表
create table user(name int, age int)

# 创建主键
create table course(
    id int not null primary key,
    time varchar(255)
);
create table course(
    id int not null,
    primary key(id),
    time varchar(255)
);

# 创建外键
create table course (
    id int,
    primary key(id),  # 声明主键
    # 声名外键 course表的id与c表的c_id是外键
    foreign key (id) references c(c_id)
)

# 删除表
# 默认是restrict
drop table <表名>[restrict | cascade]

# 修改表
alter table <表名>[add <约束>]

# 向user表增加S_time列，Date
alter table user add S_time date
# 修改user的sage为int
# mysql中式使用modify代替alter
alter table user alter sage int
```

# 索引

```shell
# CLUSTER :聚簇索引: 物理顺序与索引的逻辑顺序相同。⽐如书 
# UNIQUE  :唯⼀索引,
create [unique][cluster] index <索引名>

# 修改索引
alter index <旧索引名> rename to <新索引名>
alter index SCno rename to SCNO

# 删除
drop index <索引名>
```

# 查询

```shell
# 查询所有
select * from table
# 查询一列
select name from table
# 结果去重(+ distinct)
select distinct * from table
# 起别名
select uname 名称 from table
select uname as 名称 from table
select uname from table T
select uname from table as T
```

## where条件查询

![](D:\A-SYS-reject\whiteZe\文档笔记\数据库管理系统\images\4.png)

## 聚合函数使用

加上DISTINCT是去除列⾥⾯重复的 来计算

```shell
# 统计title的数量，count不忽略空值
select count(title) from table
# 去重统计
select count(distinct title) from table
# 求price列的平均值
select AVG(price) from table
# 求price列的最大值
select MAX(price) from table
# 求price列的最小值
select MIN(price) from table
#
```

# 分组查询

GROUP BY分组 ,如果要进⾏筛选,请使⽤Having

```shell
# 查询title字段从edu_course通过title分组
select title from edu_course GROUP by title
# 查询title字段从edu_course通过title分组，并筛选
select title from edu_course group by title Having title="ssss"
```

# 连接

```shell
# 等值连接，非等值连接，以where为关键字
select t.* c.* from edu_t as t, edu_c as c where t.id=c.id
# 自身连接
select c1.ver,c2.view from edu c1, edu c2 where c1.ver=c2.view
# 外连接，把保留所有结果,没有的填NULL
# 左外连接 A left outer join B, 保留A的所有
# 右外连接 A right outer join B, 保留B的所有
select * from student left outer join SC on(student.id=SC.id)
```

# 多表查询

```shell
select c.id id,* from edu_c c,edu_a cp where c.id=cp.id and c.id=cp.id
```

# 嵌套查询

```shell
select c.title from edu_c c where c.title in (
    select c2.title from edu_c c2 where c2.title="mysql"
)
```

# 带有any all的子查询

![](D:\A-SYS-reject\whiteZe\文档笔记\数据库管理系统\images\5.png)

```shell
# >any 大于最小值
# >all 大于最大值
select * from edu_course where price >Any (
    select price from edu_course
)
```

# 带EXISTS的子查询

```shell
# exists后面的子查询有值返回1，没有返回0
# not exists后面的子查询没有值返回1，有值返回0
select Sname from student where exists(
    select * from course where id =1
) 
```

# 集合查询

## 并 UNION

```shell
select * from student where sdept="cs" 
UNION
select * from student where sage<=19
```

## 交 INTERSECT

```shell
select * from student where sdept = "cs" 
INTERSECT
select * from student where sage <19
```

## 差 EXCEPT

```shell
select * from student where sdept="CS"
EXCEPT
select * from student where sage<19
```

# 插入

```shell
insert into <表名> [(字段列表)] values (值)

# 例
insert into student(id, name, age) values(1, liming, 19)
insert into student values(1, liming, 19)
# 插入多条数据
insert into student values(1, liming, 19),(2,zhangsan, 18)
```

# 修改

```shell
update <表名> set <属性名>=<值>

# 例
update stu set age=33, sex=1
```

# 删除

```shell
delete from <表名> [where 条件]

# 例
delete from stu where id=100;
```

# 视图

视图(VIEW)也被称作虚表，即虚拟的表，是⼀组数据的逻辑表示,其本质是对应于⼀条SELECT语句，结果集被赋予⼀个名字，即视图名字。

视图本身并不包含任何数据，它只包含映射到基表的⼀个查询语句，当基表数据发⽣变化，视图数据

⽬的: ⽅便,简化数据操作

当我们业务需求要查出多张表的数据,这时我们可能会关联多张表查询处理，如果这个查询sql复杂的话也影响了查询效率

```shell
create view <视图名> [(列名)] as <子查询> [with check option]

# 创建视图
create view IS as select * from student
# with check option保证插入删除更新时满足视图表达式条件
# 防止用户对不属于视图范围的数据进行操作
create view IS as select * from student with check option

# 删除视图
# 如果视图还导出了其他视图，使用cascade可删除所有相关视图
drop view <视图名> [cascade]

# 查询视图,IS 视图名
select * from IS

# 更新视图
# 由于视图是不存在的，所有直接更新表
update IS set name=“123” where id = 3
相当于
update student set name="123" where id=3
```

# 自主存取控制方法

Reference 允许创建外键

all privileges 所有权限

```shell
# 授权
grant <权限> on <表名> to <⽤户> [with grant option]
#
grant select on student to user
# 允许把自己的权限授予其他用户
grant select on student to user with grant option

# 撤销
revoke <权限> on table <表名> from <⽤户> [cascade]
#
revoke select on student from user
#收回user权限，同时收回user发放的权限
revoke select on student from user cascade

# 创建角色
create role <角色名>

# 给角色授权
grant <权限> on <对象> to <角色>
# 将student表上的select权限授予CEO
grant select on Student to CEO

# 将角色授予用户
grant <角色名> to <用户名> [with admin option]
# 将CEO角色分配给user
grant CEO to user
# 将CEO角色分配给user，同时允许user将CEO角色分配给别人
grant CEO to user with admin option
```

# 审计

```shell
# 对修改SC数据的操作进⾏审计  
audit update on SC 
# 取消对SC表的⼀切审计 
noaudit update on SC
```

# 断言

只有check条件为真才执行

```shell
# 创建断言
create assertion <断言名> ( check子句> )

# 限制每一门课最多60人选修
create assertion A check( 
    60>=ALL ( # 60大于select最大的值
        select count(*) from sc group by cno # 通过学号划分
    ) 
)

# 删除断言
drop assertion A
```

# 触发器

行级触发器，一次只更新一个元组，每一行触发一次

```shell
create trigger <触发名>
{before | after} # before在触发事件之前发生，after在触发事件完成之后发生
<触发事件> on <表名> # 触发事件例：update of grade ,更新grade字段
referencing 
    { oldrow, newrow } as <变量>
for each row
[when ( <触发条件> )] <触发动作> # 只有触发条件为真，才触发动作

# 例
create trigger SC_t
after update of grade on SC # 触发事件例：update of grade ,更新grade字段
referencing 
    oldrow as oldTuple
    newrow as newTuple
for each row
when ( newTuple.grade >=1.1* oldTuple.grade) # 触发条件，
    insert into sc_u values(oldTuple.sno, oldTuple.cno, newTuple.grade)
```

语句级触发器，整个表，只触发一次

```shell
create trigger <触发名>
{before | after} # before在触发事件之前发生，after在触发事件完成之后发生
<触发事件> on <表名>
referencing 
    { oldtable, newtable } as <变量>
for each statement
[when ( <触发条件> ) ] <触发动作> # 只有触发条件为真，才触发动作

#例
create trigger Student_1
after insert on student #在student表中的所有插入动作
referencing 
    newtable as delta
for each statement
    insert into student values()
```

删除

```shell
drop trigger <触发名> on <表名>
```
