//#include <iostream>
//#include <mysql.h>
//#include <sstream>
//using namespace std;
//
//int main() {
//    MYSQL mysql;
//    mysql_init(&mysql);
//
//    const char *host = "127.0.0.1";
//    const char *user = "root";
//    const char *passwd = "123";
//    const char *db = "hanxinle";
//
//    if (mysql_real_connect(&mysql, host, user, passwd, db, 3306, 0, 0)) {
//        cout << "mysql connect success!" << endl;
//    }
//    else {
//        cout << "mysql connect failure!" << endl;
//    }
//
//    // 1 创建表
//    string sql;
//    sql = "CREATE TABLE IF NOT EXISTS `t_image`  ( \
//		`id` int AUTO_INCREMENT,\
//		`name` varchar(1024),\
//		`path` varchar(2046),\
//		`size` int,\
//		PRIMARY KEY(`id`)\
//		) ";
//    int re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << "t_image created failure! " << mysql_error(&mysql) << endl;
//    }
//    else {
//        cout << "t_image created succeeded!" << endl;
//    }
//    re = mysql_query(&mysql, sql.c_str());
//
//    // 2 插入数据
//
//    for (int i = 0; i < 1000; i++) {
//
//        //sql = "insert `t_image` (`name`,`path`,`size`) values('test.jpg','d:/img/test.jpg',10240)";
//        stringstream ss;
//        ss << "insert `t_image` (`name`,`path`,`size`)values('image";
//        ss << i << ".jpg','d:/img/', 10240)";
//        sql = ss.str();
//
//        re = mysql_query(&mysql, sql.c_str());
//        if (re == 0) {
//            int count = mysql_affected_rows(&mysql);
//            cout << "insert mysql_affected_rows " << count << endl;
//        }
//        else {
//            cout << "insert failed!" << mysql_error(&mysql) << endl;
//        }
//    }
//
//    // 3 更改数据
//
//    sql = "update t_image set `name`='test3.png',size=10240 where id=1";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re == 0) {
//        int count = mysql_affected_rows(&mysql);
//        cout << "update mysql_affected_rows " << count << endl;
//    }
//    else {
//        cout << "update failed!" << mysql_error(&mysql) << endl;
//    }
//
//    // 4 删除数据
//    // 删除可以只删除一条记录 或者
//    // drop table 及 delete from t_image 不会删除空间，只做了标志（可回滚，慢）或者
//    // 可以在delete 后调用 OPTIMIZE TABLE 清理空间，可以定期来做，有锁
//    // truncate 会清理空间
//    sql = "delete from t_image where id=1";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re == 0) {
//        int count = mysql_affected_rows(&mysql);
//        cout << "delete mysql_affected_rows " << count << endl;
//    }
//    else {
//        cout << "delete failed!" << mysql_error(&mysql) << endl;
//    }
//
//
//
//    // delete 不会实际删除空间，只做了标识
//    sql = "delete from t_image";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re == 0) {
//        int count = mysql_affected_rows(&mysql);
//        cout << "delete mysql_affected_rows " << count << endl;
//    }
//    else {
//        cout << "delete failed!" << mysql_error(&mysql) << endl;
//    }
//
//    sql = "truncate t_image";
//    re = mysql_query(&mysql, sql.c_str());
//    if (!re) {
//        cout << "truncate t_image failure !\n";
//    }
//
//    mysql_close(&mysql);
//    mysql_library_end();
//
//    return 0;
//}
