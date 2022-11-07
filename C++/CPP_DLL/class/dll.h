#ifndef __DLL_H__
#define __DLL_H__
#include <iostream>

class __declspec(dllexport) cout_something
{
public:
    void cout(char *string);
    void cout(std::string string);
};

#endif