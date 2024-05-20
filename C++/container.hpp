#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "array_tool.hpp"
using namespace std;

typedef void *(*void_pointer_function)(void *);
#define get_func(container, attribute, arguement) ((void_pointer_function)((*container)[#attribute].content))((void *)arguement);

const char container_spliter[] = {0x1C, 0x1D, 0x1E, 0x1F};

struct attribute
{
    char name[32];
    void *content;
    unsigned long content_size;
    char type[32] = "unknown";
    bool is_func = false;
    friend ostream &operator<<(ostream &os, const attribute &a)
    {
        os << "\nname: " << a.name << "\ntype: " << a.type << "\ncontent address: ";
        try
        {
            os << a.content;
        }
        catch (...)
        {
        }
        os << "\n";
        return os;
    }

    bool operator==(char *name)
    {
        // compare name
        return strcmp(this->name, name) == 0;
    }

    bool operator==(attribute *temp_attribute)
    {
        // compare by value
        if (strcmp(this->name, name) != 0)
            return false;
        if (this->content_size != temp_attribute->content_size)
            return false;
        if (memcmp(this->content, temp_attribute->content, this->content_size))
            return false;
        if (strcmp(this->type, temp_attribute->type) != 0)
            return false;
        return true;
    }

    bool operator&&(attribute *temp_attribute)
    {
        // compare by bytes
        return memcmp(this, temp_attribute, sizeof(attribute)) == 0;
    }
};

attribute create_attribute(char *name, void *content, unsigned long content_size, char *type = "unknown", bool is_func = false)
{
    // create an attribute
    attribute a;
    strcpy(a.name, name);
    a.content = content;
    a.content_size = content_size;
    strcpy(a.type, type);
    a.is_func = is_func;
    return a;
}

class container
{
public:
    container(char *container_name)
    {
        // a container saves attributes
        this->container_size = 1;
        this->container_occupied = 1;
        this->container_content = (attribute *)malloc(sizeof(attribute));
        this->container_content[0] = attribute{"container_name", container_name, strlen(container_name) + 1};
    }

    char *get_container_name()
    {
        return (char *)this->container_content[0].content;
    }

    // excluding the container name
    void print_attributes()
    {
        if (this->container_occupied == 1)
            return;
        print_arr(this->container_content, this->container_occupied, 1);
    }

    // excluding the container name
    unsigned int get_attributes_size()
    {
        return this->container_occupied - 1;
    }

    // list of all attributes,excluding the container name
    char **get_attributes_list()
    {
        if (this->container_occupied == 1)
        {
            return nullptr;
        }

        char **attribute_names = (char **)malloc(sizeof(char **) * this->container_occupied);
        for (int i = 1; i < this->container_occupied; i++)
        {
            attribute_names[i - 1] = this->container_content[i].name;
        }
        return attribute_names;
    }

    // add new attribute
    container *operator+(attribute new_attribute)
    {
        for (int i = 1; i < this->container_occupied; i++)
        {
            // if a attribute already exist
            if (strcmp(this->container_content[i].name, new_attribute.name) == 0)
            {
                this->container_content[i] = new_attribute;
                return this;
            }
        }

        // if full, double the size and copy data to the new one
        if (this->container_occupied == this->container_size)
        {
            this->container_size += 2;
            attribute *temp_attributes = (attribute *)malloc(sizeof(attribute) * this->container_size);
            char **temp_attribute_names = (char **)malloc(sizeof(char *) * this->container_size);
            memcpy(temp_attributes, this->container_content, sizeof(attribute) * this->container_occupied);
            delete this->container_content;
            this->container_content = temp_attributes;
        }
        // save attribute
        this->container_content[this->container_occupied] = new_attribute;
        this->container_occupied++;
        return this;
    };

    attribute operator[](char *name_attribute)
    {
        attribute attribute_buffer;
        for (int i = 1; i < this->container_occupied; i++)
        {
            // if a attribute already exist
            if (strcmp(this->container_content[i].name, name_attribute) == 0)
            {
                attribute_buffer = container_content[i];
                break;
            }
        }
        return attribute_buffer;
    }

    // overload cout behavior, but still I recommand use get_attributes_list or print_attributes instead
    friend ostream &operator<<(ostream &os, const container &c)
    {
        if (c.container_occupied == 1)
        {
            return os;
        }
        os << c.container_content[0].name << ": " << (char *)c.container_content[0].content << "\n"
           << "container_size: " << c.container_occupied - 1;
        if (c.container_occupied != 0)
        {
            os << "\n"
               << "[ ";
            for (int i = 1; i < c.container_occupied; i++)
            {
                os << c.container_content[i].name << " ";
            }
            os << "]";
        }
        return os;
    }

    void operator>>(char *file_path)
    {
        fstream file_stream;
        file_stream.open(file_path, ios::binary | ios::out);
        if (!file_stream.is_open())
            return;

        file_stream.write(this->get_container_name(), strlen(this->get_container_name()));
        file_stream.write(container_spliter, 4);

        for (int i = 1; i < this->get_attributes_size() + 1; i++)
        {
            if (this->container_content[i].is_func == true)
                continue;
            unsigned char attribute_name_size = strlen(this->container_content[i].name);
            file_stream.write(reinterpret_cast<const char *>(&attribute_name_size), 1);
            file_stream.write(this->container_content[i].name, strlen(this->container_content[i].name));
        }
        file_stream.write(container_spliter, 4);
        for (int i = 1; i < this->get_attributes_size() + 1; i++)
        {
            if (this->container_content[i].is_func == true)
                continue;
            unsigned long attribute_content_size = this->container_content[i].content_size;
            file_stream.write((char *)(&attribute_content_size), 4);
            file_stream.write((char *)(this->container_content[i].content), attribute_content_size);
        }
    }

    void operator<<(char *file_path)
    {
        fstream file_stream;
        file_stream.open(file_path, ios::binary | ios::in);
        if (!file_stream.is_open())
            return;
    }

private:
    unsigned int container_size;
    unsigned int container_occupied;
    attribute *container_content;
};

#endif