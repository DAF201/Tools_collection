#include "src/db.hpp"
#define DEBUG_CONFIG_PATH "/home/nei/Clear_Sky/db/db_config.txt"
const char *ACCOUNT_UID = "account_uid";
const char *ACCOUNT_NAME = "account_name";
const char *ACCOUNT_PASSWORD = "account_password";
int main()
{
    map<std::string, std::string> *config;
    config = read_database_config(DEBUG_CONFIG_PATH);
    connect_to_db(config);
    std::string uid, name, pw;
    uid = ACCOUNT_UID;
    name = ACCOUNT_NAME;
    pw = ACCOUNT_PASSWORD;
    std::string *schema[] = {&uid, &name, &pw};
    map<std::string, void *> res = database_query_result_resolve(database_execute_query("clear_sky_b", "select * from account"), schema, "sss");
    for (auto const &x : res)
    {
        std::cout << x.first
                  << ':'
                  << ((std::string *)x.second)->c_str()
                  << std::endl;
    }
}
/*
nei@DAF201:~/Clear_Sky$ g++ main.cpp -lmariadbcpp
nei@DAF201:~/Clear_Sky$ ./a.out 
account_name:test account 00
account_password:no password
account_uid:000000000000
nei@DAF201:~/Clear_Sky$ 
*/
