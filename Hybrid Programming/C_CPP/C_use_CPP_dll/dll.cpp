#include "dll.h"
void cout_something::cout(char *string)
{
    std::cout << string << std::endl;
}
void cout_something::cout(std::string string)
{
    std::cout << string << std::endl;
}