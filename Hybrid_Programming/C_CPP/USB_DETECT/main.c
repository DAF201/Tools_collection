#include "usb_drive_for_c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char user_input[128];
    void *usb_dector = CREATE_USB_DRIVE_DETECTOR();
    while (1)
    {
        scanf("%s", &user_input);
        if (0 == strcmp("ready", user_input))
        {
            printf("%i\n", GET_USB_DRIVE_STATUS(usb_dector));
            continue;
        }
        if (0 == strcmp("name", user_input))
        {
            printf("%s\n", GET_USB_DRIVE_NAME(usb_dector));
            continue;
        }
        if (0 == strcmp("clear", user_input))
        {
            system("clear");
            continue;
        }
        if (0 == strcmp("exit", user_input))
        {
            exit(0);
        }
    }
    return 0;
}
