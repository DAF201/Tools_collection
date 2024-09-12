#include "src/db.hpp" // same as database.hpp, just renamed it to make more readable here

// include from definations.hpp
#define DEBUG_CONFIG_PATH "/home/nei/Clear_Sky/db/db_config.txt"
const char *ACCOUNT_UID = "account_uid";
const char *ACCOUNT_NAME = "account_name";
const char *ACCOUNT_PASSWORD = "account_password";
// end of include

int main()
{
    map<std::string, std::string> *config;
    config = read_database_config(DEBUG_CONFIG_PATH);
    connect_to_db(config);
    std::string uid = ACCOUNT_UID, name = ACCOUNT_NAME, pw = ACCOUNT_PASSWORD, pv = ACCOUNT_PRIVILEGE;
    std::string *schema[] = {
        &uid,
        &name,
        &pw,
        &pv};
    // database_execute("clear_sky_b", "insert into account(account_uid,account_name,account_password,account_privilege) values('0000000000000002','test_account 02','some password',0)");
    std::list<std::map<std::string, void *>> res = database_query_result_resolve(
        database_execute_query(
            "clear_sky_b",
            "select * from account"),
        schema, "sssi");
    for (auto const &y : res)
    {
        for (auto const &x : y)
        {
            std::cout << x.first
                      << ':';
            if (x.first != "account_privilege")
            {
                std::cout
                    << *(string *)x.second
                    << std::endl;
            }
            else
            {
                std::cout
                    << *(int *)x.second
                    << std::endl;
            }
        }
        std::cout << std::endl;
    }
    database_query_result_recycle(res);
}
/*
nei@DAF201:~/Clear_Sky$ ./compile.sh
nei@DAF201:~/Clear_Sky$ ./a.out 
account_name:test account 00
account_password:no password
account_privilege:9
account_uid:0000000000000000

account_name:test account 01
account_password:no password
account_privilege:9
account_uid:0000000000000001

account_name:test account 02
account_password:some password
account_privilege:0
account_uid:0000000000000002

nei@DAF201:~/Clear_Sky$ 
*/
