--（1）DDL语句
--创建table：
create table emp(
workno varchar(10) comment 'Number',
name varchar(10) comment 'Name',
gender char(10) comment 'Gender',
age tinyint unsigned comment 'Age',
idcard char(18) comment 'Id',
entrydate date comment 'EntryDate'
)comment 'itcast';

--添加行
alter table emp add nickname varchar(20) comment 'otherName';

--修改行
--1.修改数据类型
alter table emp modify nickname char(15);
--2.修改字段名和字段类型
alter table emp change nickname username varchar(30) comment 'Username';

--删除行
alter table emp drop username;

--修改表名
alter table emp rename to employee;

--删除表
drop table if exists employee;

--删除指定表并重新创建表
truncate table employee;



--（2）DML语句
--添加数据：
--!: 插入数据指定字段顺序需要与值顺序一致； 字符串和日期型数据应该包含在引号中； 插入数据大小应该在规定范围内
--1.给指定字段赋值
insert into employee workno value(10086);
--2.给全部字段添加数据
insert into employee(workno,name,gender,age,idcard,entrydate) value(001,'Zixin','Male','19','0723','2004-07-23');
--3.批量添加数据//不在括号内写入任何参数意味着为表中所有字段赋值
insert into employee value(001,'Zixin','Male','19','0723','2004-07-23'),(002,'QwQ','Female','20','1103','2004-11-03');

--修改数据：
update employee set name = 'Itman' where workno = 1;
update employee set name ='Shirui',gender='Female' where workno =1;
update employee set entrydate = '2008-01-01';

--删除数据
delete from employee where gender ='Female';
delete from employee;



--（3）DQL语句
 create table emp(
    workno varchar(10) comment 'Number',
    name varchar(10) comment 'Name',
    gender char(10) comment 'Gender',
    age tinyint unsigned comment 'Age',
    idcard char(18) comment 'Id',
    entrydate date comment 'EntryDate'
 )comment 'Employee';
 
 insert into emp(workno,name,gender,age,idcard,entrydate)
 values('001','zixin','Male',19,'6647','2004-07-23'),
       ('002','JackCheng','Male',19,'6638','2004-11-03'),
       ('003','Shirui','Female',19,'5516','2004-11-31'),
       ('004','Arona','Female',14,'2211','2004-07-23'),
       ('005','Haruna','Female',13,'2345','2008-05-11'),
       ('006','Kokona','Female',13,'5567','2010-09-14'),
       ('007','Yuka','Female',16,'9981','2005-03-21'),
       ('008','Sensei01','Male',19,'6640','2004-07-23'),
       ('009','Sensei02','Male',14,'6639','2004-07-23'),
       ('010','Sensei03','Male',13,'6637','2004-07-23'),
       ('011','Sensei04','Male',12,'6636','2004-07-23'),
       ('012','Sensei05','Male',11,'6635','2004-07-23');

--基本查询
select name,workno,age from emp;
select * from emp; -- * = 所有字段 但是尽量不要写*
select name as '姓名' from emp;
select distinct entrydate from emp; --取消重复元素

--条件查询
select * from emp where age <=15;
select * from emp where idcard is null;
select * from emp where idcard is not null;
select * from emp where age between 15 and 20;
select * from emp where gender = 'Female' and age < 15;
select * from emp where age=13 or age=16 or age=19; --=in(13,16,20)
select * from emp where name like '______';--一个下划线代表一个字符
select * from emp where idcard like '%1';

--聚合函数
select count(idcard) from emp;
select avg(age) from emp;
select max(age) from emp;
select min(age) from emp;
select sum(age) from emp where gender='Female'; 

--分组查询
select gender,count(*) from emp group by gender;
select gender,avg(age) from emp group by gender;
select gender,count(*) gender_count from emp where age<15 group by gender having gender_count > 3; 
--having 在分组后判断 执行顺序：where>聚合函数>having

--排序查询
select * from emp order by age asc;--升序（可省略asc）
select * from emp order by age desc;--降序
select * from emp order by age asc, entrydate desc;

--分页查询
select * from emp limit 1,10; --第一个参数是起始行数，第二的是一页展示行数



--(3)DCL语句
--用户管理
--创建用户
create user 'Zixin'@'localhost' identified by '123456';
create user 'White01'@'%' identified by '123456'; --任意主机可以访问

--修改密码
alter user 'White01'@'%' identified with mysql_native_password by '123123';

--删除用户
drop user 'Zixin'@'localhost';

--权限管理
--查询权限
show grants for 'White01'@'%';

--授予权限
grant all on itcast.* to 'White01'@'%';

--撤销权限
revoke all on itcast.* from 'White01'@'%';



--(4)函数
--字符串函数
select concat('Hello','World'); --字符串拼接
select lower('Hello');--全变为小写
select upper('Hello');--全变为大写
select lpad('01',5,'-')--生成一个总长度为5的字符串，即在01前用---填充
select rpad('01',5,'-')--在后面填充
select trim('  Hello world   ');--去除两边空格（输出‘Hello world’
select substring('Hello world',1,5);--截取字符串 （截取字符串，初始位置【从1开始】，截取长度）
--填充workno
update emp set workno = lpad(workno,5,'0');

--数值函数
select ceil(1.1);--向上取整
select floor(1.5);--向下取整
select mod(6,4);--6%4
select rand();--生成0-1随机数
select round(2.345,2);--四舍五入并保留多少位小数
--生成六位验证码
select lpad(round(rand()*1000000,0),6,0);

--日期函数
select curdate();--获得日期
select curtime();--获得时间
select now();--获得上述之和
select YEAR(now());--获得当前年
select MONTH(now());--获得当前月
select DAY(now());--获得当前日  上三个now（）可用data数据替换
select date_add(now(),INTERVAL 70 DAY);--计算从当前时间后多少_
select datediff('2021-12-01','2021-11-01');--计算两个日期差距
--查找员工入职天数排序
select name,datediff(curdate(),entrydate) as dayin from emp order by dayin desc;

--流程函数
select if(VALUE,'ok','Error');--VALUE 如果为true返回'ok',否则返回'Error'
select ifnull(null,'Default');--第一个参数如果不为为空则返回第一个字符串，否则返回第二个
--展示员工姓名和年龄，如果年龄>=18返回‘老东西’,<18返回‘老婆’
select name, case when age<18 then '老婆' when age>=18 then '老东西' else '不是人的东西' end from emp;



--（5）约束
--NOT NULL     ——限制字段数据不能为null
--UNIQUE       ——保证字段数据唯一不重复
--PRIMARY KEY  ——为一行数据唯一标识，非空且唯一
--DEFAULT      ——保存数据时，未指定给字段值则采取默认值
--CHECK        ——保证字段满足某一条件
--FOREIGN KEY  ——让两张表数据建立连接，保证数据一致性和完整性
create table user(
   id int primary key auto_increment comment '主键',
   name varchar(10) not null unique comment 'Name',
   gender char(10) comment 'Gender',
   age int check (age>0 && age<=120) comment 'Age',
   status char(1) default '1' comment 'Stauts'
)comment 'User table'
insert into user(name,age,gender,status) values
       ('zixin',19,'Male','0'),
       ('Mika',19,'Female','1'),
       ('Shirui',19,'Female','0'),
       ('Arona',14,'Female','1'),
       ('Haruka',13,'Female','0'),
       ('Kokona',13,'Female','1'),
       ('Yuka',16,'Female','0'),
       ('Shiroi',19,'Female','1'),
       ('Zoe',14,'Male','0'),
       ('Bill',13,'Male','1');

--外键演示
--NO ACTION      ——在父表更新记录时候，检查是否有对应外键，有则不允许删除
--RESTRICT       ——在父表更新记录时候，检查是否有对应外键，有则不允许删除
--CASCADE        ——在父表更新记录时候，检查是否有对应外键，有则也删除子表对应记录
--SET NULL       ——在父表更新记录时候，检查是否有对应外键，有则设置子表该外键值为null
--SET DEFAULT    ——父表有变更时，子表将外键列设置为一个默认值

-- 准备数据
create table dept(
    id   int auto_increment comment 'ID' primary key,
    name varchar(50) not null comment '部门名称'
)comment '部门表';
create table emp(
    id  int auto_increment comment 'ID' primary key,
    name varchar(50) not null comment '姓名',
    age  int comment '年龄',
    job varchar(20) comment '职位',
    salary int comment '薪资',
    entrydate date comment '入职时间',
    managerid int comment '直属领导ID',
    dept_id int comment '部门ID'
)comment '员工表';
-- 添加外键
--                                                   子表：外键名         父表： 主表名（主表列名）
alter table emp add constraint fk_emp_dept_id foreign key (dept_id) references dept(id) on update cascade on delete cascade;
alter table emp add constraint fk_emp_dept_id foreign key (dept_id) references dept(id) on update set null on delete set null;
INSERT INTO dept (id, name) VALUES (1, '研发部'), (2, '市场部'),(3, '财务部'), (4, '销售部'), (5, '总经办'), (6, '人事部');
INSERT INTO emp (id, name, age, job,salary, entrydate, managerid, dept_id) VALUES
            (1, '金庸', 66, '总裁',20000, '2000-01-01', null,5),

            (2, '张无忌', 20, '项目经理',12500, '2005-12-05', 1,1),
            (3, '杨逍', 33, '开发', 8400,'2000-11-03', 2,1),
            (4, '韦一笑', 48, '开发',11000, '2002-02-05', 2,1),
            (5, '常遇春', 43, '开发',10500, '2004-09-07', 3,1),
            (6, '小昭', 19, '程序员鼓励师',6600, '2004-10-12', 2,1),

            (7, '灭绝', 60, '财务总监',8500, '2002-09-12', 1,3),
            (8, '周芷若', 19, '会计',48000, '2006-06-02', 7,3),
            (9, '丁敏君', 23, '出纳',5250, '2009-05-13', 7,3),

            (10, '赵敏', 20, '市场部总监',12500, '2004-10-12', 1,2),
            (11, '鹿杖客', 56, '职员',3750, '2006-10-03', 10,2),
            (12, '鹤笔翁', 19, '职员',3750, '2007-05-09', 10,2),
            (13, '方东白', 19, '职员',5500, '2009-02-12', 10,2),

            (14, '张三丰', 88, '销售总监',14000, '2004-10-12', 1,4),
            (15, '俞莲舟', 38, '销售',4600, '2004-10-12', 14,4),
            (16, '宋远桥', 40, '销售',4600, '2004-10-12', 14,4),
            (17, '陈友谅', 42, null,2000, '2011-10-12', 1,null);
--删除外键
alter table emp drop foreign key fk_emp_dept_id;



--(6)多表查询
--一对多：如上表
--一对一：和一对多类似，但要在外键添加unique保证唯一
--多对多：通过中间表维护
create table student(
   id int auto_increment primary key comment 'ID',
   name varchar(10) comment 'Name',
   num varchar(4) comment 'Number'  
)comment 'Student table'
insert into student(name,num) values
       ('Mika','2200'),
       ('Shirui','2201'),
       ('Arona','2202'),
       ('Haruka','2203'),
       ('Kokona','2204'),
       ('Yuka','2205'),
       ('Shiroi','2206'),
       ('Zoe','2207'),
       ('Bill','2208');
create table course(
   id int auto_increment primary key comment 'Id',
   name varchar(10) comment 'Name'
)comment 'Course table'
insert into course(name) values('Chinese'),('Math'),('English'),('Computer');
create table student_course(
   id int auto_increment comment 'ID' primary key,
   studentId int not null comment 'StudentId',
   courseId int not null comment 'CourseId',
   constraint fk_courseId foreign key (courseId) references course(id),
   constraint fk_studentid foreign key (studentId) references student(id)
)comment '中间表';
insert into student_course(studentId,courseId) values(1,1),(1,4),(2,3),(2,1),(3,2),(2,4),(4,1),(4,2),(5,3),(5,4),(6,2),(6,1),(7,4),
                                                     (7,2),(8,1),(8,3),(9,4),(9,1)

---- 多表查询 -- 笛卡尔积
--查询每一个员工对应部门，消除无效笛卡尔积
select * from emp , dept where emp.dept_id = dept.id;
-- 内连接演示  ——查询交集
-- 1. 查询每一个员工的姓名 , 及关联的部门的名称 (隐式内连接实现)
-- 表结构: emp , dept
-- 连接条件: emp.dept_id = dept.id
select emp.name , dept.name from emp , dept where emp.dept_id = dept.id ;
--为表起别名方便实用，但是不能再通过表名限制字段
--select e.name,d.name from emp e , dept d where e.dept_id = d.id;

-- 2. 查询每一个员工的姓名 , 及关联的部门的名称 (显式内连接实现)  --- INNER JOIN ... ON ...
-- 表结构: emp , dept
-- 连接条件: emp.dept_id = dept.id
select e.name, d.name from emp e inner join dept d  on e.dept_id = d.id;
--inner可以省略
--select e.name, d.name from emp e join dept d  on e.dept_id = d.id; 


-- 外连接演示
--包括两张表没有交集的部分，左表是left左边那张
-- 1. 查询emp表的所有数据, 和对应的部门信息(左外连接)
-- 表结构: emp, dept
-- 连接条件: emp.dept_id = dept.id
select e.*, d.name from emp e left outer join dept d on e.dept_id = d.id;
--outer可以省略
--select e.*, d.name from emp e left join dept d on e.dept_id = d.id;

-- 2. 查询dept表的所有数据, 和对应的员工信息(右外连接)
select d.*, e.* from emp e right outer join dept d on e.dept_id = d.id;
--可以把右外连接改为左外
select d.*, e.* from dept d left outer join emp e on e.dept_id = d.id;


-- 自连接
-- 1. 查询员工 及其 所属领导的名字
-- 表结构: emp
select a.name , b.name from emp a , emp b where a.managerid = b.id;

-- 2. 查询所有员工 emp 及其领导的名字 emp , 如果员工没有领导, 也需要查询出来
-- 表结构: emp a , emp b
select a.name '员工', b.name '领导' from emp a left join emp b on a.managerid = b.id;


-- union all , union
--！：表的列数必须保持一致，而且字段类型也需要保持一致
--将薪资低于 5000 的员工 , 和 年龄大于 50 岁的员工全部查询出来.（并集）
select * from emp where salary < 5000
union all
select * from emp where age > 50;
--去除重复部分
select * from emp where salary < 5000
union
select * from emp where age > 50;


-- ------------------- 子查询 ------------------------
-- 标量子查询
-- 1. 查询 "销售部" 的所有员工信息
-- a. 查询 "销售部" 部门ID
select id from dept where name = '销售部';
-- b. 根据销售部部门ID, 查询员工信息
select * from emp where dept_id = (select id from dept where name = '销售部');

-- 2. 查询在 "方东白" 入职之后的员工信息
-- a. 查询 方东白 的入职日期
select entrydate from emp where name = '方东白';
-- b. 查询指定入职日期之后入职的员工信息
select * from emp where entrydate > (select entrydate from emp where name = '方东白');

--IN        ——在指定集合范围内多选一
--NOT IN    ——不在指定集合范围内
--ANY       ——子查询返回列表中，有一个满足即可
--SOME      ——与ANY相同
--ALL       ——子查询返回列表的所有值都必须满足
-- 列子查询   ——返回结果是一列（可以说多行）
-- 1. 查询 "销售部" 和 "市场部" 的所有员工信息
-- a. 查询 "销售部" 和 "市场部" 的部门ID
select id from dept where name = '销售部' or name = '市场部';
-- b. 根据部门ID, 查询员工信息
select * from emp where dept_id in (select id from dept where name = '销售部' or name = '市场部');

-- 2. 查询比 财务部 所有人工资都高的员工信息
-- a. 查询所有 财务部 人员工资
select id from dept where name = '财务部';
select salary from emp where dept_id = (select id from dept where name = '财务部');
-- b. 比 财务部 所有人工资都高的员工信息
select * from emp where salary > all ( select salary from emp where dept_id = (select id from dept where name = '财务部') );

-- 3. 查询比研发部其中任意一人工资高的员工信息
-- a. 查询研发部所有人工资
select salary from emp where dept_id = (select id from dept where name = '研发部');
-- b. 比研发部其中任意一人工资高的员工信息
select * from emp where salary > some ( select salary from emp where dept_id = (select id from dept where name = '研发部') );


-- 行子查询 ——返回结果是一行（可以是多列）
-- 1. 查询与 "张无忌" 的薪资及直属领导相同的员工信息 ;
-- a. 查询 "张无忌" 的薪资及直属领导
select salary, managerid from emp where name = '张无忌';

-- b. 查询与 "张无忌" 的薪资及直属领导相同的员工信息 ;
select * from emp where (salary,managerid) = (select salary, managerid from emp where name = '张无忌');


-- 表子查询  ——返回结果是多行多列
-- 1. 查询与 "鹿杖客" , "宋远桥" 的职位和薪资相同的员工信息
-- a. 查询 "鹿杖客" , "宋远桥" 的职位和薪资
select job, salary from emp where name = '鹿杖客' or name = '宋远桥';
-- b. 查询与 "鹿杖客" , "宋远桥" 的职位和薪资相同的员工信息
select * from emp where (job,salary) in ( select job, salary from emp where name = '鹿杖客' or name = '宋远桥' );

-- 2. 查询入职日期是 "2006-01-01" 之后的员工信息 , 及其部门信息
-- a. 入职日期是 "2006-01-01" 之后的员工信息
select * from emp where entrydate > '2006-01-01';
-- b. 查询这部分员工, 对应的部门信息;
select e.*, d.* from (select * from emp where entrydate > '2006-01-01') e left join dept d on e.dept_id = d.id ;



--（7）事务操作【在两个事务同时开启可能会引起脏读，幻读，不可重复读问题】
--查看事务提交方式
select @@autocommit;
--设置手动提交
select @@autocommit = 0;
--提交
commit;
--回滚操作（撤销提交
rollback;

--开启事务
start transcation; --begin; 也可以
 
--事务隔离级别
--查看当前隔离级别
select @@transcation_isolation;

set session transcation isolation level read uncommitted;



--------------------------------------------------------------Linux-----------------------------------------------------------------
--（1）索引
--索引结构
--常用B+Tree索引和hash索引（底层数据结构根据哈希表，不支持范围查询，只有Memory支持）
--B+Tree：每个元素都在叶子结点，叶子结点形成一个单向链表=_=
--hash  ：每个元素对应hash值对应的hash表位置，出现hash碰撞用链表解决。hash索引效率高但是不支持范围查询

--索引语法
create table tb_user(
	id int primary key auto_increment comment '主键',
	name varchar(50) not null comment '用户名',
	phone varchar(11) not null comment '手机号',
	email varchar(100) comment '邮箱',
	profession varchar(11) comment '专业',
	age tinyint unsigned comment '年龄',
	gender varchar(10) comment '性别',
	status char(1) comment '状态',
	createtime datetime comment '创建时间'
) comment '系统用户表';
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('吕布', '17799990000', 'lvbu666@163.com', '软件工程', 23, '1', '6', '2001-02-02 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('曹操', '17799990001', 'caocao666@qq.com', '通讯工程', 33, '1', '0', '2001-03-05 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('赵云', '17799990002', '17799990@139.com', '英语', 34, '1', '2', '2002-03-02 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('孙悟空', '17799990003', '17799990@sina.com', '工程造价', 54, '1', '0', '2001-07-02 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('花木兰', '17799990004', '19980729@sina.com', '软件工程', 23, '2', '1', '2001-04-22 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('大乔', '17799990005', 'daqiao666@sina.com', '舞蹈', 22, '2', '0', '2001-02-07 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('露娜', '17799990006', 'luna_love@sina.com', '应用数学', 24, '2', '0', '2001-02-08 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('程咬金', '17799990007', 'chengyaojin@163.com', '化工', 38, '1', '5', '2001-05-23 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('项羽', '17799990008', 'xiaoyu666@qq.com', '金属材料', 43, '1', '0', '2001-09-18 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('白起', '17799990009', 'baiqi666@sina.com', '机械工程及其自动化', 27, '1', '2', '2001-08-16 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('韩信', '17799990010', 'hanxin520@163.com', '无机非金属材料工程', 27, '1', '0', '2001-06-12 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('荆轲', '17799990011', 'jingke123@163.com', '会计', 29, '1', '0', '2001-05-11 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('兰陵王', '17799990012', 'lanlinwang666@126.com', '工程造价', 44, '1', '1', '2001-04-09 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('狂铁', '17799990013', 'kuangtie@sina.com', '应用数学', 43, '1', '2', '2001-04-10 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('貂蝉', '17799990014', '84958948374@qq.com', '软件工程', 40, '2', '3', '2001-02-12 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('妲己', '17799990015', '2783238293@qq.com', '软件工程', 31, '2', '0', '2001-01-30 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('芈月', '17799990016', 'xiaomin2001@sina.com', '工业经济', 35, '2', '0', '2000-05-03 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('嬴政', '17799990017', '8839434342@qq.com', '化工', 38, '1', '1', '2001-08-08 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('狄仁杰', '17799990018', 'jujiamlm8166@163.com', '国际贸易', 30, '1', '0', '2007-03-12 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('安琪拉', '17799990019', 'jdodm1h@126.com', '城市规划', 51, '2', '0', '2001-08-15 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('典韦', '17799990020', 'ycaunanjian@163.com', '城市规划', 52, '1', '2', '2000-04-12 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('廉颇', '17799990021', 'lianpo321@126.com', '土木工程', 19, '1', '3', '2002-07-18 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('后羿', '17799990022', 'altycj2000@139.com', '城市园林', 20, '1', '0', '2002-03-10 00:00:00');
INSERT INTO itcast.tb_user (name, phone, email, profession, age, gender, status, createtime) VALUES ('姜子牙', '17799990023', '37483844@qq.com', '工程造价', 29, '1', '4', '2003-05-26 00:00:00');

--查看table index_type展示了table的索引方式 默认BTree
show index from tb_user;
--创建索引
create index idx_user_name on tb_user(name);
create index idx_user_email on tb_user(email);
--创建唯一索引
create unique index idx_user_phone on tb_user(phone);
--创建联合索引
create index idx_user_pro_age_sta on tb_user(profession,age,status);
--删除索引
drop index idx_user_name on tb_user;

--索引性能查询
--查看服务器状态信息
show global status like 'com_______';--下划线有7个
--慢查询日志（默认>10s)
show variables like 'slow_query_log'; --查看慢查询日志状态(如果是关闭状态需要修改配置文件)
--profile详情
select @@have_profiling;--查看是否支持
select @@profiling;--查看是否开启
set profiling=1;--开启profiling
show profiles;--查看所有sql语句耗时情况
show profile for query 1;--查看固定指令的详情
--explain——在执行语句前加explain
explain select * from tb_user;
--id:             sql语句中执行顺序，id从大到小顺序执行
--select_type:    查询类型
--type：          表示连接类型，性能从好到差：NULL、system、const、eq_ref、ref、range、index、all             ！！！important
--possible_key:   可能用在表上的索引                                                                        ！
--key:            实际用到的索引                                                                           ！
--key_len:        用到的索引长度                                                                           !      
--rows:           预估查询行数
--filtered：      结果行数占所需读取行数百分比（越大性能越好

--索引失效：
--1.最左前缀法则：当多个字段形成联合索引左边的字段失效(不存在)则再往后索引失效
explain select * from tb_user where age = 31 and status ='0';--因为profession不存在
--2.使用大于，范围查询右侧字段索引失效（推荐使用>=
--3.字符串不加‘’索引失效
--4.模糊索引：尾部模糊索引加%索引不会失效，头部模糊会失效

--sql提示
explain select * from tb_user use index(idx_user_pro) where profession ='软件工程';     --use index() 建议使用指定索引
explain select * from tb_user ignore index(idx_user_pro) where profession ='软件工程';  --ignore index() 禁止使用指定索引
explain select * from tb_user force index(idx_user_pro) where profession ='软件工程';   --forece index() 强制使用指定索引

--覆盖索引
--前缀索引
select count(distinct substring(email,1,5))/count(*) from tb_user;
create index idx_email_5 on tb_user(email(5));



--(2)sql优化
--批量插入
--手动提交事务
--主键顺序插入

--load大批量插入数据
create database Zixin;
select @@local_infile;
set global local_infile =1;
CREATE TABLE `tb_user` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(50) NOT NULL,
  `password` VARCHAR(50) NOT NULL,
  `name` VARCHAR(20) NOT NULL,
  `birthday` DATE DEFAULT NULL,
  `sex` CHAR(1) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_user_username` (`username`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 ;
load data local infile '/root/load_user_100w_sort.sql' into table tb_user fields terminated by ',' lines terminated by '\n';

--主键优化   ！！创建索引时 注意最左前缀法则
--页分裂 页合并
--order by 优化   （using filesort效率低） 尽量使用覆盖索引
create index idx_user_age_phone on tb_user(age,phone);
explain selext id,age,phone from tb_user order by age desc,phone desc;
--!会出现额外排序
explain selext id,age,phone from tb_user order by age asc,phone desc;
--解决方法：在创建一个索引;
create index idx_user_age_pho_ad on tb_user(age asc,phone desc);

--group by优化     （using temporary效率低）
create index idx_user_pro_age_sta on tb_user(profession,age,status);

--limit优化 （数据量极大的情况下，越靠后性能越低）
select s.* from tb_sku s, (select id from tb_sku order by id limit 9000000,10) a where s.id = a.id;

--count优化
--count（*）>count(1)>count(主键id)>count(字段)

--update优化
--进行更新时候根据索引字段innoDB加行锁，根据无索引字段加的是表锁，会导致更新效率低
--解决方法：创建索引



--(3)视图--保证数据私密性，数据独立
--创建视图
create or replace view stu_v_1 as select id,name from student where id < 10;
--查询视图
show create view stu_v_1;--查看语句
select * from stu_v_1;--查看数据
--修改视图
create or replace view stu_v_1 as select id,name,num from student where id < 10;
alter view stu_v_1 as select id,name from student where id<=10;
--删除视图
drop view if exists stu_v_1;
--检查选项
create or replace view stu_v_1 as select id,name from student where id < 10 with cascaded check option;--防止错误数据插入，提供报错（如果有底层视图也会检查）
--插入数据
insert into stu_v_1 values(20,'Tom','1111');
--！：视图中有聚合函数或者窗口函数，distinct，group by，having，union或者union all的时候不能更新



--（4）存储过程--sql语句封装，方便调用
--存储过程创建
create procedure p1()
begin
   select count(*) from student;
end;
--调用
call p1();
--查看
select * from information_schema.ROUTINES where ROUTINE_SCHEMA = 'itcast';
show create procedure p1;
--删除
drop procedure if exists p1;
--设置结束符号(               命令行中使用
delimiter $$
create procedure p1()
begin
   select count(*) from student;
end$$;
delimiter ;

--系统变量
--查看系统变量
show session variables like 'auto%';
select @@global.autocommit;

--设置系统变量
set session autocommit = 0;--关闭自动提交(设置为1开启)    会话级别
set global autocommit =0; --                            全局级别

--自定义变量  在当前会话使用
set @var_name = 'Itcast';
set @var_age := 10;
set @gender = 'Male',@status := 1;
select @color := 'red';
select count(*) into @gender from tb_user;
--使用
select @var_name,@var_age,@gender,@status;

--局部变量  declare声明
create procedure p2()
begin
   declare stu_count int default 0;
   select count(*) into stu_count from student;
   select stu_count;
end;

--存储语法+传参(in 传入；out 输出)   //传入传出的参数一样（更新），则使用inout: 例 p4（inout score double）
--if
create procedure Score_judge(in score int,out result varchar(10))
begin 
  declare score int default 58;
  declare result varchar(10);
  if score >= 85 then
      set result := 'A';
  elseif score >= 60 then
      set result := 'B';
  else
      set result := 'F';
  end if;
end;
call Score_judge(62,@result);
select @result;

--case
create procedure Season_judge(in month int)
begin
   declare result varchar(10);
   case
      when month >= 1 and month <= 3 then
         set result := '1';
      when month >= 4 and month <= 6 then
         set result := '2';
      when month >= 7 and month <= 9 then
         set result := '3';
      when month >= 10 and month <= 12 then
         set result := '4';
      else
         set result := 'illegal';
   end case;
      select concat('Month: ',month,'  Season: ',result);
end;
call Season_judge(4);

--while
create procedure sumAdd(in n int)
begin
   declare total int default 0;
   while n>0 do
      set total := total + n;
      set n := n - 1;
   end while;
   select total;
end;
call sumAdd(7);

--repeat 
create procedure sumAdd(in n int)
begin
   declare total int default 0;
  repeat
      set total := total + n;
      set n := n - 1;
   until n<=0;
   end repeat;
   select total;
end;
call sumAdd(7);

--loop
create procedure sumAdd(in n int)
begin
   declare total int default 0;
   sum:loop
   if n<= 0 then
      leave sum;
   end if;

   if n%2 = 1 then
      set n := n - 1;
      iterate sum;--跳出循环
   end if;

   set total := total + n;
   set n:n-1;
   end loop sum;
   select total;
end;
call sumAdd(7);

--cursor 游标   handler 条件处理程序
--从表中读取数据载入另一张表

--handler_action 有两种continue和exit
--handler 条件值
--SQLSTATE    ：sql状态码
--SQLWARNING  ：01开头的SQLSTATE简写
--NOT FONUD   ：02开头的SQLSTATE简写
--SQLEXCEPTION：所有没有被SQLWARNING或者NOT FOUND捕获的SQLSTATE代码的简写

create procedure readName(in uage int)
begin 
   declare uname varchar(100);
   declare upro varchar(100);
   declare u_cursor cursor for select name,profession from tb_user age <= uage;
   declare exit handler for SQLSTATE '02000' close u_cursor; --如果出现sql状态码为02000时退出并关闭游标（不加时候会报错，状态码为02000，原因是fetch无法抓取到数据）
   create table if not exists tb_user_pro(
       id int primary key auto_increment;
       name varchar(100),
       profession varchar(100)
   );
   open u_cursor;
   while true do
     fetch u_cursor into uname,upro;
     insert int tb_user_pro values(null,uname,upro);
   end while;
   close u_cursor;
end;


--存储函数  默认是in
create function fun1(n int)
returns int deterministic
begin 
   declare total int default 0;
   while n>0 do
      set total := total + n;
      set n := n - 1;
   end while;
   return total;
end;


--触发器
--插入
create trigger tb_user_insert_trigger
   after insert on tb_user for each row--在语句执行前还是执行后(在向tb_user插入数据后执行触发器语句)  行级触发器 影响几行调用几次
begin 
   insert into user_logs(id,operation,operation_time,operate_id,operate_params) values
   (null,'insert',now(),new.id,concat('插入新数据:id:',new.id,' name:',new.name,' phone:',new.phone,' email:',new.eamil,' proffesion:',new.profession));
end;
--查看触发器
show triggers;
--删除触发器
drop trigger tb_user_insert_trigger;

--更新
create trigger tb_user_update_trigger
   after update on tb_user for each row
begin 
   insert into user_logs(id,operation,operation_time,operate_id,operate_params) values
   (null,'update',now(),new.id,
   concat('更新前数据:id:',old.id,' name:',old.name,' phone:',old.phone,' email:',old.eamil,' proffesion:',old.profession,
   '|更新后数据:id:',new.id,' name:',new.name,' phone:',new.phone,' email:',new.eamil,' proffesion:',new.profession));
end;

--删除
create trigger tb_user_delete_trigger
   after delete on tb_user for each row
begin 
   insert into user_logs(id,operation,operation_time,operate_id,operate_params) values
   (null,'update',now(),new.id,
   concat('删除数据:id:',old.id,' name:',old.name,' phone:',old.phone,' email:',old.eamil,' proffesion:',old.profession));
end;


--锁
--全局锁  只能读取不能写入力  实现数据备份（备份前加锁 备份后解除）
--加全局锁
flush tables with read lock;
--数据备份(cmd)
mysqldump -h root -p 123456 user > C:/user.sql-- -h后面加主机ip地址 在命令行运行
--释放全局锁
unlock tables;

--表级锁  分为共享读锁和独占写锁
--读锁（只能读不能写）
--加锁
lock tables score read;
--写锁（不能读不能写）
lock tables score write;

--元数据锁  自动加 避免DML与DDL冲突
--意向锁    表锁不用逐行检测行锁         意向共享锁（IS）：与表锁中的read兼容，write互斥【select…… lock in share mode;】     意向排他锁：都互斥【insert update delete……for update】
--查看意向锁和行锁状态
select object_schema,object_name,index_name,lock_type,lock_mode,lock_data from performance_schema.data_locks;

--行锁  共享锁（S）：共享锁间兼容，与排他锁互斥   排他锁（X）：与所有锁互斥
--除了select（正常）不加锁和select……lock in share mode加共享锁外，其余操作都加排他锁
--！：select……lock in share mode 和 select……for update 需要手动加锁'
--！：不通过索引检索，InnoDB会对所有数据加锁形成表锁
--间隙锁-临键锁
--间隙锁防止别的事务插手当前事务，不会阻止其他事务在同一个间隙加锁
--临键锁