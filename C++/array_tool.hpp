#ifndef array_tools_H
#define array_tools_H
#include <iostream>
#include <cstring>
#include <random>
#include <ctime>
#include <type_traits>

#define arr_size(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define arr_right(arr) (arr_size(arr) - 1)
#define arr_and_bounds(arr) arr, 0, arr_size(arr) - 1
#define arr_and_size(arr) arr, arr_size(arr)
#define rand_range(low, high) (rand() % (high - low) + low + 1)
#define mid(left, right) (left + (right - left) / 2)

#define UNSIGNED_INT_MAX 4294967295
#define FALSE UNSIGNED_INT_MAX
#define TRUE 4294967294

template <typename T>
void swapping(T &element_1, T &element_2)
{
    T buffer = element_2;
    element_2 = element_1;
    element_1 = buffer;
}

template <typename T>
void print_arr(T *arr, int size, int start = 0)
{
    std::cout << "{";
    for (int i = start; i < size - 1; i++)
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

// delete part of array
template <typename T>
T *delt_arr(T *arr, int arr_size, int target_index, int target_size)
{
    if (target_size + target_index > arr_size)
        return nullptr;
    T *buffer = (T *)malloc((arr_size - target_size) * sizeof(T));
    memcpy(buffer, arr, target_index * sizeof(T));
    memcpy(buffer + target_index, arr + target_index + target_size, (arr_size - target_index) * sizeof(T));
    return buffer;
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

template <typename T>
unsigned int exist(T *arr, unsigned int arr_size, T element, bool sorted = false)
{
    bool is_str = std::is_same<T, char *>::value;
    if (!arr_size)
        return -1;

    // unsorted or is string
    if (!sorted || is_str)
    {
        // check string
        if (is_str)
        {
            for (int i = 0; i < arr_size; i++)
                if (strcmp(arr[i], element) == 0)
                    return i;
        }
        else
        {
            for (int i = 0; i < arr_size; i++)
                if (arr[i] == element)
                    return i;
        }
        return FALSE;
    }
    // sorted, not string
    else
    {
        return (arr[0] < arr[arr_size - 1]) ? binary_search(arr, element, arr_size) : binary_search(arr, element, arr_size, false);
    }
}

template <typename T>
unsigned int binary_search(T *arr, T target, unsigned array_size, bool ascending = true)
{
    unsigned int left = 0;
    unsigned int right = array_size;
    unsigned int mid;
    // check index 0
    if (arr[0] == target)
        return 0;
    // I want to remove the brackets, but this also excludes mid == 0
    while (left <= right && (mid = left + (right - left) / 2))
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            if (ascending)
                right = mid - 1;
            else
                left = mid + 1;
        else if (ascending)
            left = mid + 1;
        else
            right = mid - 1;
    // FALSE == 4294967295(unsigned int max)
    return FALSE;
}
#endif