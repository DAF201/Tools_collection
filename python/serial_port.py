import serial
import serial.tools.list_ports
from tkinter import *
from tkinter import ttk
import threading


class serial_port_x(serial.Serial):
    def __init__(self, window, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.window = window
        self.clear()
        self.window.port_recv_buffer.insert(END, 'connected\n')
        self.read_thread = threading.Thread(target=self.serial_read)
        self.read_thread.start()

    def serial_read(self):
        while True:
            try:
                data_raw = self.readline()
                if data_raw != b'':
                    print(data_raw)
                self.window.port_recv_buffer.insert(END, data_raw)
                self.window.port_recv_buffer.see('end')
            except Exception as e:
                print(e)
                break

    def serial_send(self, cmd):
        self.write(cmd.encode()+b'\r')

    def clear(self, target='recv'):
        if target == 'recv':
            self.window.port_recv_buffer.delete("1.0", "end")
        else:
            self.window.port_send_buffer.delete("1.0", "end")

    def __del__(self) -> None:
        self.window.port_recv_buffer.insert(END, 'disconnected\n')
        self.close()
        return super().__del__()
