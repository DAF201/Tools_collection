import win32com.client
import pythoncom

def list_com_objects():
    context = pythoncom.CreateBindCtx(0)
    moniker_enum = pythoncom.GetRunningObjectTable().EnumRunning()

    while True:
        monikers = moniker_enum.Next(1)
        if not monikers:
            break
        display_name = monikers[0].GetDisplayName(context, None)
        print(display_name)

list_com_objects()
