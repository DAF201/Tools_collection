template <typename T>
bool is_sub(T &source_1)
{
    if (std::is_same<T, string>::value)
    {
        printf("a\n");
    }
}

template <typename T>
bool is_sub(T &&source_1)
{
    if (std::is_same_v<const char *, T>)
    {
        printf("b\n");
    }
}

template <typename T, std::size_t N>
bool is_sub(T (&)[N])
{
    if (std::is_same_v<const char, T>)
    {
        printf("c\n");
    }
}

int main()
{
    string a = "0";
    is_sub("a");
    is_sub(a.c_str());
    is_sub(a);
}
