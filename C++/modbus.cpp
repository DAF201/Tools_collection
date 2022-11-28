#include <string.h>
#include <iostream>
#include <vector>
std::vector<std::string> split(const std::string &str, int n)
{
    std::vector<std::string> substrings;

    for (size_t i = 0; i < str.size(); i += n)
    {
        substrings.push_back(str.substr(i, n));
    }

    return substrings;
}

unsigned short modbus(std::string data)
{
    unsigned short tmp = 0xffff;
    unsigned short ret1 = 0;
    std::vector<int> hex_data;
    std::vector<std::string> temp = split(data, 2);
    for (int i = 0; i < temp.size(); i++)
    {
        hex_data.insert(hex_data.end(), std::stoi(temp[i], 0, 16));
    }
    for (int n = 0; n < hex_data.size(); n++)
    {
        tmp = hex_data[n] ^ tmp;
        for (int i = 0; i < 8; i++)
        {
            if (tmp & 0x01)
            {
                tmp = tmp >> 1;
                tmp = tmp ^ 0xa001;
            }
            else
            {
                tmp = tmp >> 1;
            }
        }
    }
    ret1 = tmp >> 8;
    ret1 = ret1 | (tmp << 8);
    return ret1;
}

int main()
{
    std::cout << std::hex << modbus("01039C730005") << std::endl;
    return 0;
}
// modbus 01 03 9C 73 00 05 5A 42
