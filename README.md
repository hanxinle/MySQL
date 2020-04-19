# 数据库从小白到进阶
### 小工报到

通过 vscode 安装插件连接 mysql 并且操作，在建立连接的时候，提示“Error: ER_NOT_SUPPORTED_AUTH_MODE: Client does not support authentication protocol requested by server; consider upgrading MySQL client”，解决方法是打开 >mysql，执行以下语句：

```ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'yourpassword';```

(运行 mysql -u root -h 127.0.0.1 -p 进入数据库)


* [0 安装(Ubuntu 16.04 LTS)](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/)

* 1 database 和table 指令

  * show databases 显示数据库
  * create database <database_name> 创建数据库
  * drop database <database_name>  删除数据库
  * use <database_name>  切换数据库
  * select database() 显示当前使用的数据库

  * create table <table_name> (<column1_name> <data_type> <data_feature>,<column2_name> <data_type> <data_feature>)

     [data type help](https://dev.mysql.com/doc/refman/5.7/en/data-types.html)

    * NOT NULL 必须有值,不能为空
    * AUTO_INCREMENT 自增 
    * PRIMARY KEY 值唯一,可以标识某个连续字段唯一
      * create table <table_name>(c1 type1,c2 type2,c3 type3,PRIMARY (c1,c2))
    * DEFAULT "<value>" 默认值 <value>
    * UNIQUE 值可以为NULL,只要有值的时候不重复

  * select * from <table_name>;   //查看table信息
  * insert into <table_name>  (<column1_name>,<column2_name>,) values ("<value1>","<value2>"),("<value3>","<value4>")
  * show tables
  * desc <table_name> show 与→一致columns from <table_name>
  * drop table <table_name>

  * dilimiter <符号> 用<符号>代替分号作为语句结束标记,执行 mysql语句

  * source xxx.sql 调用sql文件

* CRUD
  * C-reate 看第1节
  * R-ead select用法
  * U-pdate 结合set使用
  * D-elete 删除记录k
* 字符串
  * CONCAT 拼接两个字符串 CONCAT_WS(arg1,string1,string2) ==> "string1 arg1 string2"
  * SUBSTRING 截取字符串

  select CONCAT(first_name," ",last_name,"was hired on",SUBSTRING(hired_date,1,4)) as check from employee ;

  * REPLACE ("string1 string2","string2","string3") ==> string1 string3
  * REVERSE 反转

* select 结果进一步处理

  * 排序 ORDER BY

    select * from employee ORDER BY salary (desc); //desc 降序

    select * from employee ORDER BY 5 (desc);  //第5列 ,还是salary;

    selcet first_name,last_name,salary from employee ORDER BY 3; //以salary为准,再加数字则是在前一列基础上,对相同值的项再排序

   * 限制数量 LIMIT

     select * from employee ORDER BY salary LIMIT 3; //限制返回结果数量为3

     select * from employee ORDER BY salary LIMIT 3,5; //salary排第3+1项开始,返回5个结果 

   * 字符串过滤 LIKE

     select * from employee where last_name like "C%"; // % 匹配任意长度字符

     select * from employee where last_name like "__an"; // 两个_代表任意两个字符;

     PS : like中包含%的字符串,用\转义,如 "%\%%",转义\可以用于其它符号.
     
* 数据的聚合处理

    * 统计数量 count
    
        select count(*) from employee;
    
        ->select count(*) from employee
        ->where salary > 7000;
    
    * 统计唯一值 distinct
    
         打印 title 的种类 select distinct title from employee;
      
         统计 title 的种类数目 select count(distinct title) from employee;
      
    * 数据整合 GROUP BY 
    
         统计每个 title 下有多少个人
      
        select title from employee group by title; //结果类似与"打印 title 种类,实际上后面有隐含的统计信息
      
          select title,count(first_name) from employee group by title; //打印每个 title 下多少人
        
    * 求最值 MAX\MIN
    
         求每个 title 下工资最高的值
      
        select title from employee group by title;      // 先聚合
       
        select title,max(salary) from employee group by title;  //再统计
       
    * 求和及平均值 SUM\AVG 
      
         select sum(salary) from employee;
     
         select avg(salary) from employee;
    
         select title,avg(salary) from employee group by title;
         
    * 对聚合之后的结果进行过滤 HAVING
    
         select title,count(*) from employee group by title having title="Software Engineer";
         
         //where 只能对原始的 table进行过滤;
         
         select title,count(*) from employee where title="Software Engineer";
         
* [DATA Type - 数值类型](https://dev.mysql.com/doc/refman/5.7/en/numeric-types.html)
    
    * [Integer Types 整数类型](https://dev.mysql.com/doc/refman/5.7/en/integer-types.html)
        
        这一类别的集中类型的区别在于所占的空间及表示的范围,
        
        ```create table datatest0 (a tinyint,b smallint,c mediumint,d int,e bigint);```  //未设置a是正数
        
        desc datatest0;     //查看每列所占空间;
        
        insert datatest0(a) values(129);  //error,-128~127

         ```create table datatest1 (a tinyint unsigned,b smallint,c mediumint,d int,e bigint);```  //
         
        desc datatest1;
       
        insert datatest0(a) values(129);  //OK,0~255
        
    
    * [Fix-point Types 绝对数值类型](https://dev.mysql.com/doc/refman/5.7/en/fixed-point-types.html)
        
        这一类型用于需要精确数据的时候,例如涉及金钱的时候,
        
        salary DECIMAL(5,2) 第一个参数表示这个数字有多少位,第二个参数表示小数点后面的位数,-999.99 - 999.99,小数点后面两位也要占位.
        
        create table test (price decimal(5,2));
        
        insert into test(price) values (12);  //位数不够会补位,小数部分超了会截取,会四舍五入,正数部分超了就报错,有截取会报错,用
        
        show warnings;  //查看刚刚出现的警告信息;
        
        
    * [Float-point Types 浮点数类型](https://dev.mysql.com/doc/refman/5.7/en/floating-point-types.html)
        
        有 float 和 double 两种类型,会有实际存储数据与我们插入数据不相符的时候,具体原因在这个[链接](https://dev.mysql.com/doc/refman/5.7/en/problems-with-float.html)
    
    
    
    * [Bit value Type 位类型](https://dev.mysql.com/doc/refman/5.7/en/bit-type.html)
    
       在使用的时候,需要指明位数BIT(M),M的取值是1~64.
       
       create table test2 (a bit);//默认是1
       create table test3 (a bit(12));
       
       insert into test3(a) values(11);
       
       select 可能显示不出来数据,
       
       select a+0 from test3;  //十进制显示
       
       select bin(a+0) from test3;  //二进制显示
       
       select hex(a+0) from test3;  //十六进制显示
       
       insert into test3(a) values(b'11111111'); //插入二进制'255'的方法;
       
            
* [DATE and Time Type - 日期类型](https://dev.mysql.com/doc/refman/5.7/en/date-and-time-types.html)
          
    * DATE 
    
      范围:1000-01-01 到 9999-12-31;

    * TIME
    
       范围:-838:59:59 到 838:59:59
       
       create table test(a date);
       
       insert into table (a) values('2010-10-30'); //OK
       
       insert into table (a) values ('20101030');  //OK
       
       有缺省则会报错.但是可以为NULL.
       
       create table test(a time);
       
       insert into test(a) values('12:12:12')\values('121212')\values(121212); //time的几种形式;
       
       time 缺省会补全,补全的单位不是按单位大小排列,要实验.
      
    * YEAR or YEAR(4)

       4 digital number 和 4 digital string 时范围都是1901-2155,string值在values("xxx")用双引号;
       
       number类型时,如果插入1-69,默认为2001-2069,如果是70-99,默认是1970-1999.
       
       为string 类型时,情况又有所不同.
       
       
    * DATETIME AND TIMESTAMP
    
       二者是date和time的结合,有不同的范围,TIMESTAMP创建时有默认值(系统当前时间),并且它的值会随着时区的改变而改变,在更新table时,TIMESTAMP的值会更自动改为当前系统时间,二者存储所占字节不同,index速度也不同.
       
       select now();  //查看当前系统时间
       
       更改mysql timezone:
       
       show variables like "%time_zone%";
       
        +------------------+--------+
        
        | Variable_name    | Value  |
        
        +------------------+--------+
        
        | system_time_zone | CST    |
        
        | time_zone        | SYSTEM |
        
        +------------------+--------+
      
        
        
       create table timetest(a datetime,b timestamp);
       
       insert into timetest(a,b) values(now(),now());
       
       set time_zone="-12:00" ;  //比当前时间少12小时,美国时间,注意时间的格式是UTC时间,因为是string类型
       
       set time_zone="system";    //改回来
        
       PS:[这里](https://dev.mysql.com/doc/refman/5.7/en/date-and-time-functions.html)是关于时间的函数

* [String Type - 字符类型]
  
    * CHAR\VARCHAR
    
      char 0-255,varchar长度可变,0-65535,
      
    * BINARY\VARBINARY
    
      见[文档](https://dev.mysql.com/doc/refman/5.7/en/binary-varbinary.html)  
      
    * BLOB\TEXT 
      
      见[文档](https://dev.mysql.com/doc/refman/5.7/en/storage-requirements.html),BLOB对应非常大的BINARY对象,TEXT对应的是
      
      非常大的CHAR,比如存储一篇博客.
      
    * ENUM 
        
      string object ,其取值从list中获取,如性别,尺码.
      
      create table shirts (name varchar(40),size enum('x-small','small','medium','large','x-large'));
      
      insert into shirts values("test","small");
      
      insert into shirts values("test",1);  //不论插入或者查询,enum都比较快
      
    * SET 集合
        
      最大有64个成员,
      
      create table set1(a set(' one','two','three'));
      
      insert into set1 values('one,three');
      
      insert into set1 values(1);
      
      insert into set1 values(2);
      
      ...
      
      insert into set1 values(7);
      
      取值范围是2的n次方,n为set个数,其组织类似于机器学习中的虚拟编码的方式.
    
* 修改column名字\类型
     
+----------+-------------+------+-----+---------+-------+

| Field    | Type        | Null | Key | Default | Extra |

+----------+-------------+------+-----+---------+-------+

| username | varchar(15) | YES  |     | NULL    |       |

| password | varchar(20) | YES  |     | NULL    |       |

+----------+-------------+------+-----+---------+-------+

ALTER TABLE user CHANGE username user_name varchar(20);

+-----------+-------------+------+-----+---------+-------+

| Field     | Type        | Null | Key | Default | Extra |

+-----------+-------------+------+-----+---------+-------+

| user_name | varchar(20) | YES  |     | NULL    |       |

| password  | varchar(20) | YES  |     | NULL    |       |

+-----------+-------------+------+-----+---------+-------+
  

* 逻辑操作符

  * Equal(=) 和 NOT equal(!= or not xx=yy)  
  
  * Like(where xx like "N%") 和 NOT like (where xxx not like "xx%") 
  
  * Greater Than 和 Less Than (>= \ <=) 逻辑符号也是认的
  
  * AND 和 or (对语句的判断)
  
  * between (where xx between mm and kk) mm <= xx <= kk
  
  * IN 和 NOT IN (where xx in (111,222,333)
  
  * Case Statement (产生新的列及值的方法)
    
    select first_name, last_name,
        
        case
            
            when salary > 7000 then "high"
            else "low"
            
        end as tag
        
    from employee;      
   
   
* 内置函数(此处举例,具体用法去查函数表)

  * 字符串(见上面例子)
  
  * 数值 
   
      ceil 和 floor 取整数,div,mod,power,round
  
  * 时间
       
      now,curdate,curtime,date_format,interval date_add(now(),xx day\xx week),datediff
       
  * 信息 (mysql软件相关)
  
  * 集合函数 (max,min等) 
  
  * 加密函数(MD5,Password)
    
    password 修改 mysql 密码,
    
        set password=password('abc123456');
        
    MD5('passwd')  加密字符串    
   
* 关系

不同的表可以有效率地表达信息，减少单个表信息的冗余，当需要的时候，可以通过联结表征更多信息。关系有一对多、多对多几种，用新的表的形式组织，联结的对象是table，联结有内部联结（inner join）、外部联结（left join、left join）。