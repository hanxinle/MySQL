# mysql C++开发相关

## 1 安装配置参考资料

查看夏老师的课程视频吧，这些步骤有些繁琐，几句话叙述不清楚。Windows 安装 MySQL 8.0 后要配置系统服务，去安装目录下拷贝 bin，lib，include 三个目录的内容，在 VS 中设置项目。Ubuntu 需要安装 MySQL 相关服务端、客户端并且配置并启动服务，还需要apt-get install libmysqlclient-dev，编译程序时链接头文件路劲及这个库。

```g++ $^ -o $@ -I/usr/include/mysql -lmysqlclient```

开发文档：[英文](https://dev.mysql.com/doc/c-api/8.0/en/)、[中文](https://www.mysqlzh.com/doc/196/114.html)
## 2 MySQL API 初步

* 连接数据库
API链接：[mysql_real_connect](https://dev.mysql.com/doc/c-api/8.0/en/mysql-real-connect.html)
```c++
MYSQL * mysql_real_connect(MYSQL *mysql,
                   const char *host,
                   const char *user,
                   const char *passwd,
                   const char *db,
                   unsigned int port,
                   const char *unix_socket,
                   unsigned long client_flag)
```
超时处理：

单线程的情况防止阻塞，默认值是 30s，接口是 mysql_options()
```c++
int mysql_options(MYSQL *mysql,
              enum mysql_option option, // MYSQL_OPT_CONNECT_TIMEOUT
              const void *arg)
```

自动重连：

enum mysql_option option 取值为 MYSQL_OPT_RECONNECT，再执行 mysql_ping.

* 查询

查询分为 3 个步骤，1 是执行 MySQL 语句，2 是获取结果集，3 是遍历和清理结果集。

执行 MySQL 有两个接口 mysql_real_query,mysql_query，前者参数只能说字符串，后者遇到 \0 会断开，sql 命令不需要分号，每次执行必须获取，清理结果集，不然会出错。 

获取结果集接口有两个，其中 mysql_store_result 非常慢，马上读取到内存，默认大小是 64MB，数据量大的时候会有阻塞。
```c++
MYSQL_RES *mysql_use_result(MYSQL *mysql) 

MYSQL_RES *mysql_store_result(MYSQL *mysql)
```

遍历结果集 mysql_fetch_row 按行遍历,返回字符串向量, mysql_fetch_length 返回一行中每个向量的长度。

* 获取字段信息

字段信息就是 key。

* 表的创建及增删改查及执行多条语句的方法

统一的API　mysql_query().

```c++
int re = mysql_query(&mysql, sql.c_str());
```
插入、更改、删除一条数据要调用 mysql_affected_rows(),获取执行上条语句影响的行数。执行多条语句没执行一条语句，要通过 mysql_store_result 获取结果，判断执行结果，并且处理，然后再调用 mysql_next_result(&mysql) 执行下一条 SQL　语句。

## 3 事务性

事务性可以在代码层面完成，一般选择在 MySQL 层面做，它是一个程序执行单元，要么执行要么都不执行。事务能支持回滚，如果一系列操作中间有一个步骤出错断开了，能够将之前已经发生的操作撤销掉，这就是回滚。

MySQL 有两个引擎，MyISAM 和 InnoDB ，前者是表级锁，不支持 ROLLBACK，后者是 InnoDB，是行级锁，支持事务。锁表是因为很多 SQL 语句并不是原子性的，可能在处理过程被其他连接改变。行级别的锁就锁住一行，性能更高，不需要把整个表锁住。

插入操作，事务性进行批量操作最节省时间。

## 4 二进制图片的读取和 blob 插入mysql_stmt

见示例，就像常见的 API 加上 stmt 再执行。

## 5 MySql API 调用存储过程（选听）

存储过程就是一系列 SQL 语句的整合，多条 SQL 语句每一条都要编译，如果是存储过程来做，那么在数据库内部，存储过程全部都是编译好的，对于复杂的 SQL 语句，这样的作法效率更高。此外，存储过程使得业务和页面完全隔离。如短消息的自动回复。DBA 的工作效率也会更高。

开发者就是了解有这么一个提升效率的手段。

