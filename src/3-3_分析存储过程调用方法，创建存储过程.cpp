#include <iostream>
#include <mysql.h>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

int main() {
    //初始化mysql上下文
    MYSQL mysql;
    //单线程模式 mysql_init自动调用 mysql_library_init 线程不安全
    mysql_init(&mysql);
    const char *host = "127.0.0.1";
    //const char *host = "192.168.0.203";
    const char *user = "root";
    const char *pass = "123456";
    const char *db = "laoxiaketang";		//数据库名称

    //CLIENT_MULTI_STATEMENTS 支持多条sql语句
    if (!mysql_real_connect(&mysql, host, user, pass, db, 3306, 0, CLIENT_MULTI_STATEMENTS))
        //if (!mysql_real_connect(&mysql, host, user, pass, db, 3306, 0, 0))
    {
        cout << "mysql connect failed!" << mysql_error(&mysql) << endl;
    }
    else {
        cout << "mysql connect success!" << endl;
    }
    string sql = "";


    //1 创建存储过程
    // SELECT 打印参数， SET 设置参数
    sql = "CREATE PROCEDURE `p_test` (IN p_in INT,OUT p_out INT,INOUT  p_inout INT)\
	BEGIN\
	SELECT p_in,p_out,p_inout;\
	SET p_in = 100, p_out = 200,p_inout=300; \
	SELECT p_in,p_out,p_inout;\
	END";
    int re = mysql_query(&mysql, sql.c_str());
    if (re != 0) {
        cout << mysql_error(&mysql) << endl;
    }
    //2 定义变量并复制
    cout << "IN in=1 out=2 inout=3" << endl;
    sql = "SET @A=1;SET @B=2;SET @C=3;";
    re = mysql_query(&mysql, sql.c_str());
    if (re != 0) {
        cout << mysql_error(&mysql) << endl;
    }
    do {
        cout << "SET affect " << mysql_affected_rows(&mysql) << endl;
    }
    //0 还有结果， -1 没有结果 >1错误
    while (mysql_next_result(&mysql) == 0);

    //3 调用存储过程 call 
    sql = "call p_test(@A,@B,@C)";
    re = mysql_query(&mysql, sql.c_str());
    if (re != 0) {
        cout << mysql_error(&mysql) << endl;
    }
    cout << "In Proc:";
    do {
        MYSQL_RES *res = mysql_store_result(&mysql);
        if (!res)
            continue;

        //字段数量
        int fcount = mysql_num_fields(res);

        //打印结果集
        for (;;) {
            //提取一行记录
            MYSQL_ROW row = mysql_fetch_row(res);
            if (!row) break;
            for (int i = 0; i < fcount; i++) {

                if (row[i]) {
                    cout << row[i] << " ";
                }
                else
                    cout << "NULL" << " ";
            }
            cout << endl;

        }
        mysql_free_result(res);
    }
    //0 还有结果， -1 没有结果 >1错误
    while (mysql_next_result(&mysql) == 0);


    //4 获取存储过程的结果
    sql = "select @A,@B,@C";
    re = mysql_query(&mysql, sql.c_str());
    if (re != 0) {
        cout << mysql_error(&mysql) << endl;
    }
    MYSQL_RES *res = mysql_store_result(&mysql);
    cout << "out: ";
    MYSQL_ROW row = mysql_fetch_row(res);
    cout << " in=" << row[0];
    cout << " out=" << row[1];
    cout << " inout=" << row[2];
    mysql_free_result(res);
    cout << endl;


    mysql_close(&mysql);
    mysql_library_end();
    std::cout << "Mysql 8.0 API!\n";
    getchar();
}

