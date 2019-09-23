# 数据库相关
### 小工

(运行 mysql -u root -h 127.0.0.1 -p 进入数据库)

* [0 安装(Ubuntu 16.04 LTS)](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/)

* 1 database 和table 指令

  * show databases 显示数据库
  * create database <database_name> 创建数据库
  * drop database <database_name>  删除数据库
  * use <database_name>  切换数据库
  * select database() 显示当前使用的数据库
  
  * show tables
  * desc <table_name> show 与→一致columns from <table_name>
  * drop table <table_name>
  
  * dilimiter <符号> 用<符号>代替分号作为语句结束标记,执行 mysql语句

