#ifndef MATH_HPP
#define MATH_HPP

#ifndef TOOLS_HPP
#include <math.h>
#include <float.h>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

// copied from tools.hpp, needed for debug
void bits_print(void *v, int size)
{
    cout << "Lower bits -> Higher bits" << endl;
    for (int i = 0; i < size; i++)
    {
        char temp_byte;
        memcpy(&temp_byte, (char *)v + i, 1);
        for (int j = 0; j < 8; j++)
        {
            cout << ((temp_byte >> j) & 1);
        }
        cout << " ";
    }
    cout << endl;
}
#endif

namespace mess // mess->math
{

    // for filling mem space
    const static int ZERO = 0;

    inline int RAND_INT(int seed = 0, int lower = INT32_MAX, int upper = INT32_MIN)
    {
        if (!seed)
            srand(time(NULL));
        else
            srand(seed);
        if (lower > upper)
            return rand();
        else
            return lower + (rand() % (upper - lower));
    }

    inline float RAND_DOUBLE(int seed = 0, float lower = DBL_MAX, float upper = DBL_MIN)
    {
        if (!seed)
            srand(time(NULL));
        else
            srand(seed);
        if (lower > upper)
            return RAND_INT() + (float)rand() / RAND_MAX;
        else
            return RAND_INT(0, (int)lower, (int)upper - 1) + RAND_DOUBLE();
    }

#define hash(value) bytes_hash(value, sizeof(value))
    // lower byte -> higher byte
    static unsigned char hash_seed[] = {0xB4, 0x66, 0xC5, 0x0F}; // 264595124, from random int generator
    static unsigned char hash_key = 0x00;

    inline void seed()
    {
        cout << hash_key << endl;
        cout << hash_seed << endl;
    }

    inline void set_hash_seed(int *seed)
    {
        memcpy(hash_seed, seed, 4);
        hash_key = hash_seed[0] ^ hash_seed[1] ^ hash_seed[2] ^ hash_seed[3];
    }

    // pad to 4k bytes with hash key, then copy data into it and do xor for each 4 bytes iteratively using hash seed as init value
    string bytes_hash(void *value, int size)
    {
        unsigned char *buffer = (unsigned char *)malloc(size + (4 - size % 4));
        int char_to_int_convert_buffer;
        int res;
        memcpy(&res, hash_seed, 4);
        memcpy(buffer + (size + (4 - size % 4)) - ((4 - size % 4)), &hash_key, (4 - size % 4));
        memcpy(buffer, value, size);
        for (int i = 0; i < size + (4 - size % 4); i += 4)
        {
            memcpy(&char_to_int_convert_buffer, buffer + i, 4);
            res ^= char_to_int_convert_buffer;
        }
        char c_hex[9];
        sprintf(c_hex, "%X", res); // Uppercase hex
        string s_hex(c_hex);
        return s_hex;
    }

    inline int factor(int number)
    {
        for (int i = (int)floor(pow(number, 0.5)); i > 0; i--)
            if (number % i == 0)
                return i;
        return 1;
    }

    // end of basic functions

    // fraction functions
    inline float extract_fraction(float value)
    {
        return abs(value - floor(value));
    }

    inline int number_length(float value)
    {
        return to_string(value).length();
    }

    inline int decimal_length(float value)
    {
        return to_string(floor(value)).length();
    }

    inline int fraction_length(float value)
    {
        if (value == floor(value))
            return 0;
        string fraction_str = to_string(value);
        fraction_str = fraction_str.substr(fraction_str.find('.') + 1);
        while (fraction_str.back() == '0')
            fraction_str = fraction_str.substr(0, fraction_str.length() - 1);
        return fraction_str.length();
    }

    // end of fraction functions
}
#endif
