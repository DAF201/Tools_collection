#include <windows.h>
#include <stdio.h>
#include <iostream>
HANDLE handle;
std::string getCommandFromClipBoard()
{
    std::string returnValue;
    OpenClipboard(NULL);
    handle = GetClipboardData(CF_TEXT);
    returnValue = (std::string)(char *)handle;
    CloseClipboard();
    return returnValue;
}
void setClipBoard()
{
    const char *output = "I guess it worked";
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

int main()
{
    while (1)
    {
        if (("test from python" == getCommandFromClipBoard()))
        {
            setClipBoard();
            break;
        }
        Sleep(1000);
    }
    std::cout << getCommandFromClipBoard() << std::endl;
    return 0;
}
