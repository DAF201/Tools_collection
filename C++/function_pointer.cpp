#include <iostream>
#include <type_traits>
using namespace std;
typedef void (*void_void)();
typedef void (*void_int)(int);
void test()
{
    cout << "test 01" << endl;
}
void test(int num)
{
    cout << num << endl;
}
template <typename T>
void call(T func_ptr)
{
    if (is_same<T, void_void>::value)
    {
        void_void func;
        func = (void_void)func_ptr;
        func();
    }
    else
    {
        void_int func;
        // func = (void (*)(int))func_ptr;
        func = (void_int)func_ptr;
        func(2);
    }
}
int main()
{
    call((void_void)&test);
    call((void_int)&test);
    return 0;
}
