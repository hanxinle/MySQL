# 数据库从小白到进阶
### 小工报到

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

  
  
  
  

