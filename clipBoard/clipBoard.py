from tkinter import Tk
import time


def setClipBoard(text_input: str):
    r = Tk()
    r.withdraw()
    r.clipboard_clear()
    r.clipboard_append(text_input)
    r.update()
    r.destroy()


a = ''
while(1):
    try:
        setClipBoard('test from python')
        time.sleep(1)
        if(Tk().clipboard_get() == 'I guess it worked'):
            break
    except:
        pass
print(Tk().clipboard_get())
