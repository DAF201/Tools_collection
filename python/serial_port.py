#!python
import time
import threading
import serial #pyserial not serial
import random

ser = serial.Serial(
    'COM4', timeout=None, baudrate=115000, xonxoff=False, rtscts=False, dsrdtr=False
)


def ser_read():
    while True:
        data_raw = ser.readline()
        print(data_raw)


def ser_cmd():
    while True:
        if bool(random.getrandbits(1)):
            ser.write(b'root\r')
            time.sleep(1)
            ser.write(b'boot\r')
        else:
            ser.write(b'root\r')
            time.sleep(1)
            ser.write(b'reboot\r')
        time.sleep(random.randrange(1, 10))


read_thread = threading.Thread(target=ser_read)
write_thread = threading.Thread(target=ser_cmd)

read_thread.start()
write_thread.start()
