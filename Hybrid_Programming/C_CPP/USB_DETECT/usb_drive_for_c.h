#ifndef USB_DRIVE_FOR_C
#define USB_DRIVE_FOR_C

#ifdef __cplusplus
extern "C"
{
#endif

    extern void *CREATE_USB_DRIVE_DETECTOR();
    extern void UPDATE_USB_DRIVE_STATUS(void *usb_drive);
    extern int GET_USB_DRIVE_STATUS(void *usb_drive);
    extern const char *GET_USB_DRIVE_NAME(void *usb_drive);

#ifdef __cplusplus
}
#endif
#endif
