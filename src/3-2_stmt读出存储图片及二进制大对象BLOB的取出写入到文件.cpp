//#include <iostream>
//#include <mysql.h>
//#include <thread>
//#include <string>
//#include <sstream>
//#include <map>
//#include <chrono>
//#include <fstream>
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
//    //1 创建好存放二进制数据的表 t_data
//    sql = "CREATE TABLE IF NOT EXISTS `t_data` (\
//		`id` int AUTO_INCREMENT,\
//		`name` varchar(1024),\
//		`data` blob,\
//		`size` int,\
//		PRIMARY KEY(`id`))";
//
//    int re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cout << mysql_error(&mysql) << endl;
//    }
//
//    //2 清空表 truncate t_data
//    sql = "truncate t_data";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cerr << mysql_error(&mysql) << endl;
//    }
//
//    //3 初始化stmt mysql_stmt_init
//    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
//    if (!stmt) {
//        cerr << "mysql_stmt_init failed!" << mysql_error(&mysql) << endl;
//    }
//
//    //4 预处理sql语句
//    sql = "INSERT INTO `t_data` (name,data,size) VALUES(?,?,?)";
//    if (mysql_stmt_prepare(stmt, sql.c_str(), sql.size())) {
//        cerr << "mysql_stmt_prepare failed!" << mysql_stmt_error(stmt) << endl;
//    }
//
//    //5 打开并读取文件
//    string filename = "mysql.jpg";
//
//
//
//    //读取二进制
//    fstream in(filename, ios::in | ios::binary);
//    if (!in.is_open()) {
//        cerr << "file " << filename << " open failed!" << endl;
//    }
//    //文件指针移动到结尾处
//    in.seekg(0, ios::end);
//    //文件大小和文件二进制地址
//    int filesize = in.tellg();
//    //回到开头
//    in.seekg(0, ios::beg);
//
//    char *data = new char[filesize];
//    int readed = 0; //已经读了多少
//    while (!in.eof()) {
//        in.read(data + readed, filesize - readed);
//        //读取了多少字节
//        if (in.gcount() <= 0)
//            break;
//        readed += in.gcount();
//    }
//
//    in.close();
//
//    //6 绑定字段
//    MYSQL_BIND bind[3] = { 0 };
//    bind[0].buffer_type = MYSQL_TYPE_STRING;  //name 文件名
//    bind[0].buffer = (char*)filename.c_str();
//    bind[0].buffer_length = filename.size();
//
//    bind[1].buffer_type = MYSQL_TYPE_BLOB;   //data 文件二进制内容
//    bind[1].buffer = data; //二进制文件
//    bind[1].buffer_length = filesize;
//
//    //文件大小
//    bind[2].buffer_type = MYSQL_TYPE_LONG;
//    bind[2].buffer = &filesize;
//
//    if (mysql_stmt_bind_param(stmt, bind) != 0) {
//        cerr << "mysql_stmt_bind_param failed! " << mysql_stmt_error(stmt) << endl;
//    }
//
//    //7 执行stmt sql
//    if (mysql_stmt_execute(stmt) != 0) {
//        cerr << "mysql_stmt_execute failed! " << mysql_stmt_error(stmt) << endl;
//    }
//    delete data;
//    mysql_stmt_close(stmt);
//
//
//    //8 查询二进制数据，并保存问文件
//    sql = "select * from t_data";
//    re = mysql_query(&mysql, sql.c_str());
//    if (re != 0) {
//        cerr << "mysql query failed!" << mysql_error(&mysql) << endl;
//    }
//    //获取结果集
//    MYSQL_RES  *res = mysql_store_result(&mysql);
//    if (!res) {
//        cerr << "mysql_store_result failed!" << mysql_error(&mysql) << endl;
//    }
//    //取一行数据
//    MYSQL_ROW row = mysql_fetch_row(res);
//    if (!row) {
//        cerr << "mysql_fetch_row failed!" << mysql_error(&mysql) << endl;
//    }
//    cout << row[0] << " " << row[1] << " " << row[3] << endl;
//
//    //获取每列数据的大小
//    unsigned long *lens = mysql_fetch_lengths(res);
//    int fnum = mysql_num_fields(res);
//    for (int i = 0; i < fnum; i++) {
//        cout << "[" << lens[i] << "]";
//    }
//    filename = "out_";
//    filename += row[1];
//    fstream out(filename, ios::out | ios::binary);
//    if (!out.is_open()) {
//        cerr << "open file  " << filename << " failed!" << endl;
//    }
//    out.write(row[2], lens[2]);
//    out.close();
//
//
//    mysql_close(&mysql);
//    mysql_library_end();
//    std::cout << "Mysql 8.0 API!\n";
//    getchar();
//}
//
