#ifndef array_tools_H
#define array_tools_H
#include <iostream>
#include <random>
#include <ctime>
#include <type_traits>

#define arr_size(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define arr_right(arr) (arr_size(arr) - 1)
#define arr_and_bounds(arr) arr, 0, arr_size(arr) - 1
#define arr_and_size(arr) arr, arr_size(arr)
#define rand_range(low, high) (rand() % (high - low) + low + 1)
#define mid(left, right) (left + (right - left) / 2)

template <typename T>
void swapping(T &element_1, T &element_2)
{
    T buffer = element_2;
    element_2 = element_1;
    element_1 = buffer;
}

template <typename T>
void print_arr(T *arr, int size)
{
    std::cout << "{";
    for (int i = 0; i < size - 1; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[size - 1] << "}" << std::endl;
}

template <typename T>
void randomize(T *arr, int size)
{
    srand(time(0));
    if (std::is_same<T, int>::value)
    {
        for (int i = 0; i < size; i++)
        {
            int val = rand();
            val % 2 == 0 ? arr[i] = val : -1 * val;
        }
        return;
    }
    if (std::is_same<T, char>::value)
    {
        for (int i = 0; i < size; i++)
            arr[i] = (char)rand_range(0, 128);
        return;
    }
    if (std::is_same<T, unsigned int>::value)
    {
        for (int i = 0; i < size; i++)
            arr[i] = rand();
        return;
    }
    if (std::is_same<T, float>::value)
    {
        for (int i = 0; i < size; i++)
        {
            int rand_1 = rand();
            int rand_2 = rand();
            rand_1 % 2 == 0 ? arr[i] = rand_1 / (double)rand_2 : -1 * rand_1 / (double)rand_2;
        }
        return;
    }
}

template <typename T>
void fill_arr(T *arr, int left, int right, T value)
{
    for (int i = left; i <= right; i++)
        arr[i] = value;
}

template <typename T>
void fill_arr_ordered(T *arr, int left, int right)
{
    if (std::is_same<T, int>::value)
        for (int i = left; i <= right; i++)
            arr[i] = i;
    else
        for (int i = left; i <= right && i < 128; i++)
            arr[i] = (char)i;
}

template <typename T>
void copy_arr(T *src_arr, T *dest_arr, int size)
{
    memcpy(dest_arr, src_arr, size * sizeof(T));
}

template <typename T>
void copy_arr(T *src_arr, int src_left, int src_right, T *dest_arr, int dest_left)
{
    memcpy(&dest_arr[dest_left], &src_arr[src_left], (src_right - src_left + 1) * sizeof(T));
}

// array created by this function cannot use arr_size cuase the return is a pointer
template <typename T>
T *expand_arr(T *arr, int size_to_copy, int new_size)
{
    T *new_arr = new T[new_size];
    fill_arr(new_arr, 0, new_size, 0);
    copy_arr(arr, new_arr, size_to_copy);
    return new_arr;
}

template <typename T>
void arr_insert(T *arr, int size, int index, T value)
{
    // will discard last element if any
    copy_arr(arr, index, size - 2, arr, index + 1);
    arr[index] = value;
    return;
}
#endif
