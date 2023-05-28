#include <iostream>
using namespace std;
void test()
{
    cout << "test 01" << endl;
}
void call(void *func_ptr)
{
    void (*func)();
    func = (void (*)())func_ptr;
    func();
}
int main()
{
    call((void *)&test);
    return 0;
}
