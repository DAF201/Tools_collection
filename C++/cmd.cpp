#include "cmd.h"
extern "C" __declspec(dllexport) void cmd(char *buffer)
{
    system(buffer);
}