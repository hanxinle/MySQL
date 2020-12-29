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