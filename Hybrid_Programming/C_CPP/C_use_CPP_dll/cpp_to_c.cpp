#include "cpp_to_c.h"
#include "dll.h"
extern void cout(char *string)
{
    cout_something *temp = new cout_something;
    temp->cout(string);
    delete temp;
}