//#include <iostream>
//#include <mysql.h>
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
//    // 1 执行 select * from employee
//    // 查询结果有两个接口：mysql_real_query,mysql_query
//    const char * select_search = "select * from employee";
//    int re = mysql_real_query(&mysql, select_search, strlen(select_search));
//    if (re != 0) {
//        cout << "select * from employee failure! " << mysql_error(&mysql) << endl;
//    }
//    else {
//        cout << "select * from employee succeeded!" << endl;
//    }
//    // 2 获取结果集
//    // mysql_use_result 不立即数据
//    // mysql_store_result 读取所有数据
//    MYSQL_RES *result = mysql_use_result(&mysql);
//    if (!result) {
//        cout << "mysql select * return null" << mysql_error(&mysql) << endl;
//    }
//    // 3 获取表字段 field 就是 key
//    MYSQL_FIELD *field = 0;
//    while (field = mysql_fetch_field(result)) {
//        cout << "key: " << field->name << endl;
//    }
//    // 获取表字段数量
//    int fnum = mysql_num_fields(result);
//
//    // 4 遍历结果集
//    // row 按行访问查询结果，结果类似字符串向量
//    MYSQL_ROW row;
//    while (row = mysql_fetch_row(result)) {
//        for (int i = 0; i < fnum; i++) {
//            cout << mysql_fetch_field_direct(result, i)->name << ":";
//            if (row[i])
//                cout << row[i];
//            else
//                cout << "NULL";
//            cout << ",";
//        }
//        cout << endl;
//    }
//
//    //清理结果集
//    mysql_free_result(result);
//
//    mysql_close(&mysql);
//    mysql_library_end();
//
//    // cout << "client connect " << host << " MySql server succeeded!\n";
//    return 0;
//}
