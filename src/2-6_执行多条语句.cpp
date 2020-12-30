#include <iostream>
#include <mysql.h>
#include <thread>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main() {
    MYSQL mysql;
    mysql_init(&mysql);

    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *passwd = "123";
    const char *db = "hanxinle";

    if (mysql_real_connect(&mysql, host, user, passwd, db, 3306, 0, CLIENT_MULTI_STATEMENTS)) {
        cout << "mysql connect success!" << endl;
    }
    else {
        cout << "mysql connect failure!" << endl;
    }

    string sql = "";

    // 1 创建表
    sql =
        "CREATE TABLE IF NOT EXISTS `t_image`  ( \
		`id` int AUTO_INCREMENT,\
		`name` varchar(1024),\
		`path` varchar(2046),\
		`size` int,\
		PRIMARY KEY(`id`)\
		) ;";

    //清空数据，并恢复自增id从1开始
    sql += "truncate t_image;";

    // 2 插入数据 CLIENT_MULTI_STATEMENTS
    for (int i = 0; i < 100; i++) {
        // sql = "insert `t_image` (`name`,`path`,`size`)
        // values('test.jpg','d:/img/test.jpg',10240)";
        stringstream ss;
        ss << "insert `t_image` (`name`,`path`,`size`)values('image";
        ss << i << ".jpg','d:/img/', '10240');";
        sql += ss.str();
    }

    // 3 修改数据
    // update t_image set `name`="test2.png",size=2000 where id=1
    sql += "update t_image set `name`='test3.png',size=2000 where id=1;";
    // 4 删除数据
    sql += "delete from t_image where id=1;";
    //实际清理了空间
    sql += "select * from t_image;";

    //执行sql语句立刻返回，但语句并没有全部执行好，需要获取结果
    //把sql整个发送给mysql server，server一条条执行，返回结果
    int re = mysql_query(&mysql, sql.c_str());
    if (re != 0) {
        cout << "mysql_query failed!" << mysql_error(&mysql) << endl;
    }

    //有多个返回结果
    do {
        cout << "[result]";
        MYSQL_RES *result = mysql_store_result(&mysql);
        if (result)  // SELECT
        {
            cout << "SELECT mysql_num_rows = " << mysql_num_rows(result)
                << endl;
            mysql_free_result(result);
        }
        else  // INSERT UPDATE DELETE CREATE DROP truncate
        {
            // SELECT 出错 有字段无结果
            if (mysql_field_count(&mysql) > 0) {
                cout << "Not retrieve result! " << mysql_error(&mysql) << endl;
            }
            else  // INSERT UPDATE DELETE CREATE DROP truncate
            {
                //等待服务器的处理结果
                cout << mysql_affected_rows(&mysql) << " rows affected!"
                    << endl;
            }
        }

    }

    //取下一条结果 0表示有结果
    while (mysql_next_result(&mysql) == 0);

    {
        sql = "select * from t_image";
        int re = mysql_query(&mysql, sql.c_str());
        if (re != 0) {
            cout << "mysql_query failed!" << mysql_error(&mysql) << endl;
        }
    }

    mysql_close(&mysql);
    mysql_library_end();
    std::cout << "Mysql 8.0 API!\n";

    return 0;
}
