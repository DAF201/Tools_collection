// discard, typename is really depends on machine, different machine may works differently. this is only the reference for my machine
#include <fstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>

/*
unsigned int : j
short int : s
long int : l
int : i
float : f
double : d
unsigned char : h
char : c
string : NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
bool : b
void pointer : Pv
char pointer : Pc
int pointer : Pi
structure : Z4mainE8a_struct
class : Z4mainE7a_class
int vector : St6vectorIiSaIiEE
char vector : St6vectorIcSaIcEE
bool vector : St6vectorIbSaIbEE
file_stream : St13basic_fstreamIcSt11char_traitsIcEE
infile_stream : St14basic_ifstreamIcSt11char_traitsIcEE
outfile_stream : St14basic_ofstreamIcSt11char_traitsIcEE
*/

using namespace std;
template <typename T>
void test(T &source, string name)
{
    cout << name << " : " << typeid(source).name() << endl;
}
int main()
{
    unsigned int a_us_int;
    short int a_short_int;
    long int a_long_int;

    int a_int;

    float a_float;

    double a_double;

    unsigned char a_us_char;
    char a_char;

    string a_string;

    bool a_bool;

    void *a_void_ptr;
    int *a_int_pointer;
    char *a_char_pointer;

    struct a_struct
    {
    } a_struct;

    class a_class
    {
    } a_class;

    vector<int> a_int_vector;
    vector<char> a_char_vector;
    vector<bool> a_bool_vector;

    fstream a_file_stream;
    ifstream a_in_filestream;
    ofstream a_out_filestream;

    test(a_us_int, "unsigned int");
    test(a_short_int, "short int");
    test(a_long_int, "long int");
    test(a_int, "int");
    test(a_float, "float");
    test(a_double, "double");
    test(a_us_char, "unsigned char");
    test(a_char, "char");
    test(a_string, "string");
    test(a_bool, "bool");
    test(a_void_ptr, "void pointer");
    test(a_char_pointer, "char pointer");
    test(a_int_pointer, "int pointer");
    test(a_struct, "structure");
    test(a_class, "class");
    test(a_int_vector, "int vector");
    test(a_char_vector, "char vector");
    test(a_bool_vector, "bool vector");
    test(a_file_stream, "file_stream");
    test(a_in_filestream, "infile_stream");
    test(a_out_filestream, "outfile_stream");
}
