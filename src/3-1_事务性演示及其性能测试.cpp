//#include <iostream>
//#include <mysql.h>
//#include <thread>
//#include <string>
//#include <sstream>
//#include <map>
//#include <chrono>
//using namespace std;
//using namespace chrono;
//
//int main() {
//    //初始化mysql上下文
//    MYSQL mysql;
//    //单线程模式 mysql_init自动调用 mysql_library_init 线程不安全
//    mysql_init(&mysql);
//    const char *host = "127.0.0.1";
//    //const char *host = "192.168.0.203";
//    const char *user = "root";
//    const char *pass = "123";
//    const char *db = "hanxinle";		//数据库名称
//
//    //CLIENT_MULTI_STATEMENTS 支持多条sql语句
//    if (!mysql_real_connect(&mysql, host, user, pass, db, 3306, 0, CLIENT_MULTI_STATEMENTS))
//        //if (!mysql_real_connect(&mysql, host, user, pass, db, 3306, 0, 0))
//    {
//        cout << "mysql connect failed!" << mysql_error(&mysql) << endl;
//    }
//    else {
//        cout << "mysql connect success!" << endl;
//    }
//    string sql = "";
//
//    //1 创建表
//    sql = "CREATE TABLE IF NOT EXISTS `t_video`  ( \
//		`id` int AUTO_INCREMENT,\
//		`name` varchar(1024),\
//		`path` varchar(2046),\
//		`size` int,\
//		PRIMARY KEY(`id`)\
//		) ENGINE=InnoDB;";  //设置支持事务回滚的 InnoDB引擎
//    int re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//    //清理表数据
//    sql = "truncate t_video";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//
//    // 事务
//    //1 开始事务
//    //START TRANSACTION;
//    sql = "START TRANSACTION";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//
//    //2 设置为手动提交事务
//    //set autocommit = 0
//    sql = "set autocommit = 0";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//
//    //3 sql语句
//
//    //插入三条数据，回滚
//    for (int i = 0; i < 3; i++) {
//        sql = "insert into t_video (name) values('test three!')";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//    }
//
//    //4 回滚ROLLBACK MYISAM 不支持
//    sql = "ROLLBACK";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//    for (int i = 0; i < 1000; i++) {
//        sql = "insert into t_video (name) values('test three!')";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//    }
//
//    //5 COMMIT  
//    sql = "COMMIT";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//
//    //6 恢复自动提交 set autocommit = 1
//    sql = "set autocommit = 1";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//
//
//    sql = "select count(*) from t_video";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//    }
//    MYSQL_RES * res = mysql_store_result(&mysql);
//    if (res) {
//        //取得第一行数据
//        MYSQL_ROW row = mysql_fetch_row(res);
//        if (row) {
//            cout << "t_video count(*) = " << row[0] << endl;
//        }
//    }
//    auto start = system_clock::now();
//    //单条语句插入1千条数据
//    for (int i = 0; i < 1000; i++) {
//        sql = "insert into t_video (name,path) values('single','0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789')";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//    }
//    auto end = system_clock::now();
//    //转换为毫秒 1000
//    auto dur = duration_cast<milliseconds> (end - start);
//    cout << "1 单条语句插入1千条数据" << dur.count() / 1000. << "秒" << endl;
//
//    //多条语句插入1千条数据
//
//    {
//        auto start = system_clock::now();
//        sql = "";
//        //单条语句插入1千条数据
//        for (int i = 0; i < 1000; i++) {
//            sql += "insert into t_video (name,path) values('single','0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789');";
//        }
//
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//        do {
//            cout << mysql_affected_rows(&mysql) << flush;
//        } while (mysql_next_result(&mysql) == 0);
//        auto end = system_clock::now();
//        //转换为毫秒 1000
//        auto dur = duration_cast<milliseconds> (end - start);
//        cout << "2 多条语句插入1千条数据" << dur.count() / 1000. << "秒" << endl;
//    }
//
//
//    //事务插入1千条数据
//    {
//        //1 开始事务
//        //START TRANSACTION;
//        sql = "START TRANSACTION";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//        auto start = system_clock::now();
//        //单条语句插入1千条数据
//        for (int i = 0; i < 1000; i++) {
//            sql = "insert into t_video (name,path) values('single','0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789')";
//            re = mysql_query(&mysql, sql.c_str());
//            if (re != 0) {
//                cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//            }
//            else
//                cout << mysql_affected_rows(&mysql) << flush;
//
//        }
//
//
//        //2 设置为手动提交事务
//        //set autocommit = 0
//        sql = "set autocommit = 0";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//
//
//
//        sql = "COMMIT";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//        sql = "set autocommit = 1";
//        re = mysql_query(&mysql, sql.c_str());
//        if (re != 0) {
//            cout << "mysql_query failed! " << mysql_error(&mysql) << endl;
//        }
//
//        auto end = system_clock::now();
//        //转换为毫秒 1000
//        auto dur = duration_cast<milliseconds> (end - start);
//        cout << "3 事务插入1千条数据" << dur.count() / 1000. << "秒" << endl;
//
//    }
//
//
//
//
//    mysql_close(&mysql);
//    mysql_library_end();
//    std::cout << "Mysql 8.0 API!\n";
//    getchar();
//}
//
