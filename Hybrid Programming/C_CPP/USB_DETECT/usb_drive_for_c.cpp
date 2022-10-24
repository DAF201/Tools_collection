#include "usb_drive_for_c.h"
#include "usb_drive.hpp"

extern void *CREATE_USB_DRIVE_DETECTOR()
{
    return new USB_DRIVE::usb_drive();
}

extern void UPDATE_USB_DRIVE_STATUS(void *usb_drive)
{
    USB_DRIVE::usb_drive *temp_usb = (USB_DRIVE::usb_drive *)usb_drive;

    temp_usb->update_usb_status();
}

extern int GET_USB_DRIVE_STATUS(void *usb_drive)
{
    USB_DRIVE::usb_drive *temp_usb = (USB_DRIVE::usb_drive *)usb_drive;

    temp_usb->update_usb_status();

    return (int)temp_usb->usb_status();
}

extern const char *GET_USB_DRIVE_NAME(void *usb_drive)
{
    USB_DRIVE::usb_drive *temp_usb = (USB_DRIVE::usb_drive *)usb_drive;

    temp_usb->update_usb_status();

    return (temp_usb->usb_name());
}
