//#include <iostream>
//#include <mysql.h>
//#include <thread>
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
//    int time_out = 3;
//    int re = mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, &time_out);
//    if (re != 0) {
//        cout << "mysql_options failed!" << mysql_error(&mysql) << endl;
//    }
//    // 自动重连
//    int recon = 1;
//    re = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &recon);
//    if (re != 0) {
//        cout << "mysql_options failed!" << mysql_error(&mysql) << endl;
//    }
//    // 连接数据库
//    if (!mysql_real_connect(&mysql, host, user, passwd, db, 3306, 0, 0)) {
//        cout << "mysql connect failed!" << mysql_error(&mysql) << endl;
//    }
//    else {
//        cout << "mysql connect success!" << endl;
//    }
//
//    // 检测是否断开链接，断开连接则会自动重连
//    for (int i = 0; i < 1000; i++) {
//        int re = mysql_ping(&mysql);
//        if (re == 0) {
//            cout << host << ":mysql ping success!" << endl;
//        }
//        else {
//            cout << host << ":mysql ping failed! " << mysql_error(&mysql) << endl;
//        }
//        this_thread::sleep_for(1s);
//
//    }
//
//    mysql_close(&mysql);
//    mysql_library_end();
//
//    cout << "client connect " << host << " MySql server succeeded!\n";
//    return 0;
//}
