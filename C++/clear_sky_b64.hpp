#ifndef CODING_HPP
#define CODING_HPP
#include <string>
using namespace std;

//repalcement of memset since I dont want to include string.h
void set_mem(void *p, char data, int size)
{
    for (int i = 0; i < size; i++)
        ((char *)p)[i] = data;
}

// convertion
const char int_to_string_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// dictionary
const char bytes_to_char_dict[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-";

// convert a byte to a visible char
char byte_to_char(char c)
{
    return bytes_to_char_dict[c];
}

// convert a visible chat to byte
char char_to_byte(char c)
{
    if (c == '+')
        return 62;
    if (c == '-')
        return 63;
    if (c < 48 || c > 122)
        return -1;
    if (c < 58)
        return c - 48;
    if (c < 91)
        return c - 55;
    else
        return c - 61;
}

struct __bytes
{
    int size;
    char *data;
};

string clear_sky_b_encode(unsigned char *data, int size)
{

    // pad to a length divided by 3
    int padded_length = size;
    while (padded_length % 3 != 0)
        padded_length++;

    // get a space divided by 3 and filled with 0
    char *padded_data = (char *)malloc(padded_length);
    set_mem(padded_data, 0, padded_length);

    // number of padding bytes at front
    string res;
    res = (int_to_string_table[padded_length - size]);

    // convert 3 bytes of 8 bits to 4 bytes of 6 bits then use the index to allocate something
    for (int i = 0; i < size; i = i + 3)
    {
        res = res + byte_to_char((data[i] & 0b11111100) >> 2) +
              byte_to_char((((data[i] & 0b00000011) << 4) | ((data[i + 1] & 0b11110000) >> 4))) +
              byte_to_char(((data[i + 1] & 0b00001111) << 2) | ((data[i + 2] & 0b11000000) >> 6)) +
              byte_to_char(data[i + 2] & 0b00111111);
    }
    return res;
}

__bytes clear_sky_b_decode(string data)
{
    // get number of paddding bytes
    int pad_size = data[0] - 48;
    // create char buffer to store result
    char *final_result_buffer = (char *)malloc((data.length() - 1) / 4 * 3);
    __bytes result;
    result.size = ((data.length() - 1) / 4 * 3) - pad_size;
    string buffer;
    data = data.substr(1);
    char char_buffer[3];
    int result_index = 0;
    // for each 4 characters
    for (int i = 0; i < data.length(); i += 4)
    {
        buffer = data.substr(i, i + 4);
        char_buffer[0] = ((char_to_byte(buffer[0]) << 2) | (char_to_byte(buffer[1]) & 0b00110000) >> 4);
        char_buffer[1] = ((char_to_byte(buffer[1]) << 4) | (char_to_byte(buffer[2]) & 0b00111100) >> 2);
        char_buffer[2] = ((((char_to_byte(buffer[2])) & 0b00000011) << 6) | (char_to_byte(buffer[3]) & 0b00111111));
        for (int i = 0; i < 3; i++)
        {
            final_result_buffer[result_index++] = char_buffer[i];
        }
    }

    result.data = final_result_buffer;

    return result;
}

#endif
