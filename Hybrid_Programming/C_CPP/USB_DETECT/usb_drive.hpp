#ifndef USB_DRIVE_HPP
#define USB_DRIVE_HPP

#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
#include <dirent.h>
#include <cstddef>
#include <cstdio>
#include <stdio.h>

#define DEVICE_PATH "/dev"
#define MEDIA_PATH "/media"

namespace USB_DRIVE
{
    using namespace std;
    class usb_drive
    {
        bool last_usb_status = false;
        string usb_drive_name = "NO USB";
        bool usb_mounted = false;
        bool usb_is_vaild = false;

        bool usb_status_update()
        {
            try
            {
                bool current_usb_status = usb_exist();
                if (current_usb_status && last_usb_status == false)
                {
                    last_usb_status = true;
                    cout << "usb pluged in" << endl;
                    usb_drive_name = get_usb_drive_name();
                    if (usb_drive_name != "")
                    {
                        if (__execute("sudo mount /dev/" + usb_drive_name + " /media") != "")
                        {
                            cout << "fail to mount usb" << endl;
                            last_usb_status = false;
                            usb_mounted = false;
                            usb_is_vaild = false;
                            usb_is_vaild = false;
                            return false;
                        }
                        else
                        {
                            cout << "usb " + usb_drive_name + " mounted at /media" << endl;
                            usb_mounted = true;
                            usb_is_vaild = usb_vaild();
                            return true;
                        }
                    }
                    else
                    {
                        last_usb_status = false;
                        usb_mounted = false;
                        usb_is_vaild = false;
                        return false;
                    }
                }

                if (!current_usb_status && last_usb_status == true)
                {
                    last_usb_status = false;
                    cout << "usb unpluged" << endl;
                    __execute("sudo umount /media");
                    usb_drive_name = "NO USB";
                    usb_mounted = false;
                    usb_is_vaild = false;
                    return false;
                }

                return false;
            }
            catch (...)
            {
                last_usb_status = false;
                __execute("sudo umount /media");
                usb_drive_name = "NO USB";
                usb_mounted = false;
                usb_is_vaild = false;
                return false;
            }
        }

        bool usb_exist()
        {
            DIR *dev_directory;
            struct dirent *object;
            dev_directory = opendir(DEVICE_PATH);
            regex usb_drive_pattern("sd\\w{2,2}");
            while (object = readdir(dev_directory))
            {
                if (regex_match(string(object->d_name), usb_drive_pattern))
                {
                    closedir(dev_directory);
                    return true;
                }
            }
            closedir(dev_directory);
            return false;
        }

        string get_usb_drive_name()
        {
            DIR *dev_directory;
            struct dirent *object;
            dev_directory = opendir(DEVICE_PATH);
            regex usb_drive_pattern("sd\\w{2,2}");
            while (object = readdir(dev_directory))
            {
                if (regex_match(string(object->d_name), usb_drive_pattern))
                {
                    closedir(dev_directory);
                    return string(object->d_name);
                }
            }
            closedir(dev_directory);
            return "";
        }

        bool usb_vaild()
        {
            DIR *media_directory;
            struct dirent *object;
            media_directory = opendir(MEDIA_PATH);
            while (object = readdir(media_directory))
            {
                if (string(object->d_name) == "tybr_update")
                {
                    closedir(media_directory);
                    return true;
                }
            }
            closedir(media_directory);
            return false;
        }

        string __execute(string command)
        {
            char pipe_buffer[128];
            string execution_result = "";
            FILE *pipe = popen(command.c_str(), "r");

            if (!pipe)
            {
                return "popen failed!";
            }

            while (!feof(pipe))
            {
                if (fgets(pipe_buffer, 128, pipe) != NULL)
                    execution_result += pipe_buffer;
            }

            pclose(pipe);
            return execution_result;
        }

    public:
        void update_usb_status()
        {
            usb_status_update();
        }

        bool usb_status()
        {
            return usb_mounted && usb_is_vaild;
        }

        const char *usb_name()
        {
            return (usb_drive_name.c_str());
        }
    };
}

#endif
