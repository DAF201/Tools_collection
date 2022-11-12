import serial
import serial.tools.list_ports
from tkinter import *
from tkinter import ttk
import serial_port
ICON = 'AAABAAEAICAAAAEAIACoEAAAFgAAACgAAAAgAAAAQAAAAAEAIAAAAAAAABAAABILAAASCwAAAAAAAAAAAAD+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8//78/P/+/Pz//vz8///8/P///Pz///z8///8/P/+/Pz//vz8//78/P/+/Pz///39///9/f///f3//vz8///8/P///P3///z8//78/P/+/Pz///39///9/f///f3///39//78/P/+/Pz//vz8//78/P/+/Pz///39///9/f///f3///39///9/f///f3/9/X2//b09v/29Pb/9vT2//b19//29ff/9vX1//b09P/08fH/9PHw//Tw7//28vP/9fT0//Py8f/18/P/+PP0//n09f/07/D/8ezt//Pw7//z7+//9vHy//by8//28vP/9vLz//fz9P/18fD/9PDv//Tw8P/08PD/9PDw//Tv8P/b1dL/3NfT/9jX0f/Y19H/1tXP/9bVzv/Y2ND/29rW/+Xm5P/n5+j/6uvr/97g4P/d2dr/6uXh/+Le2//f2tv/29bX//Dr7P//+/r/7erm//Ds6//n4uP/5N/g/+Xg4f/m4eL/4t3e/+vn5f/v7Oj/7uvn/+7r5//u6+f/7uvn/7Cspv+wraX/qqeh/6WinP+gnZf/o6Ca/4eEf/9tdnj/vM7W/7PCz/+mt8H/V1NU/3dfYf+Jb2//l3p7/1hNT/9HQ0T/UkxP/62qq//8+/n/8vHv/3JucP+DfH3/hn+A/4N+f/9fXV3/6eXl//Pu7v/v7On/8O3p//Dt6f/w7en/+fb4//r1+P/79vj/+/f5//v2+P///v//4uHh/3R8g/+70d3/s83Z/5Wqs/9HOzv/h2ho/5Jycf+Lbm7/TUZH/0A8PP9sa23/naGk/5GRkf+9vbz/UEtN/4N7fP+AeHn/a2Vm/25ubv/9+fr/7unp//Dt6f/w7en/8O3p//Dt6f/u6un/7urp/+7q6f/u6un/7eno/+/s7P/BwsL/kZKT/3B+hP+nvsz/m7K7/1NWV/9iTUz/clpc/z81Nv86ODj/MSws/3Jzdf//////trq7/0tKSf9VUU//dm5v/4mBgv9bVVb/n52d///8+//t6ef/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/y7+v/6ejm/3Z2d//JyMf/zMnM/2hobP+Ji4f/xcrE/09OTv9NSkv/ZmVl/725uv/k4d//p6Wj/5uhpf+7wMH/MjEt/4qHgv9sZWX/iICB/1JOTv/MyMj/+fXy/+7r5//w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7uro//z3+P+7ubr/lpaW/7Ozs/+ioqL/jo2J/////f/Avrn/XVda/2FbXP/Bvr//z87O/7Szs//j4uH/paam/4qKiv+Vko//t7Sw/25paf94cnP/XVla/+/r7P/x7er/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/u6uj/+/b3/5aVlf+bm5v/lJSU/4iJif+tq6f/zcrH/29sa/9eWlz/bmlq/8XDw/9gYGD/R0dG/+Xl5f+mpqz/WVdW/9jU0f/v7Oj/c25v/2JdXv+YlZb///z8/+3p5v/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p/+7s6f/n5uf/iIiI/8zMzP94eHj/mpua/35/ff+ZnZ3/t7y9/7/DxP+NjY7/goGC/1tbXP9cXF3/uLax/2diSf9JRE3/vLm3//bz7/9fW1v/JSAh/3Nzc//w7u7/8e3q//Dt6P/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/u6ef//////9bX1/+MjIz/w8PD/2NmZ/+kqqz/7/X5/9DW2P+1ur7/vsTI/8zQ1v/IzdH/vcDG/52hpf8/P0L/lYwm/4qDRv+uq67/+/jz/3x5eP9taWn/RkVF/6WkpP//+/n/7enn//Dt6f/w7en/8O3p//Dt6f/w7en/7+vo//bz9P+5tLX/c29w/66vr//Pzs7/vb+///r9//+Ghoz/ra+x/97g5v/09/n/+P////f9/v/9////6Ons/66wt/9KTEL/SkMQ/7i2tf/69/L/k5KR/3Vvdf9oYmT/mZmZ///8/f/t6en/8O3p//Dt6f/w7en/8O3p/+7r5//69vP/wL+//2dQUf9XQUT/ZWVl/8HBwf+anp3/gIKA/25sbf+fpKL/aYV0/6CoqP/4/P//8vj//8jP0f9rgXf/dpaC/4aUjv+BgIz/srCr//v49f+am5D/gHhs/1NLTv+urKz//vr6/+7q6P/w7en/8O3p//Dt6f/w7en/7urm//j49P+IgIH/i2xs/2xXV/8cFxf/IyMj/1BQT//Iy8T/cW9v/4KXjP+m4cH/hJKN//b4///y9///iZWR/6fYu/+f1LX/oKik/8zMzv+5tbH/+vf1/6Cdj/9eVzP/dXBx/+zp6f/x7ev/8O3p//Dt6f/w7en/8O3p//Dt6f/v7Of/9fTx/3ttb/+Lam3/aFJU/1lER/9APD3/hYaE/7/Buf9qamz/fI6G/32pkP92g37/+fr//+Lk6v+EopL/q+K+/4/GqP+Nn5n/u7vA/8LAvP/39O7/mZiX/3Jzd//49vf/8+/v/+/s6f/w7en/8O3p//Dt6f/w7en/8O3p/+/r5//18/D/xsTF/2NWWP9CNTf/Rz0+/7Wzs/+WmZb/vL+2/4+Pkf/4/v//pKyt/4+Rkv//////xsjO/4CRi/+MpZf/hpWM/6+1tP/Dw8b/ysfE//Lv6v+XmJP/g4OE//Pv8P/w6+z/8O3q//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p/+7r6P/8+/v/V1hX/xQVFf+qqan//fv8/4eIhv/U187/cnNw/7S3uf/Jy9L/8vP1/7Czs/+xtbP/x8jM//T3+v/z9vv/+v3//6SlqP/Y1tH/7Onk/42Oif+Cg4D/9vPz/+/r6v/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7+zp//Tv8P+/vLz/nZyc/+no6P/28fL/j4+N/9DSzP/Kzcb/iImG/5eUkv96e33/mZuY/+Xo3f+ZmJL/fYGB/9ne4/+2u73/kZGM/+bj3f/j4Nz/fH14/5ycmv/7+fb/7erm//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7er/7+vr//n29f/9/Pv/8e3t//r3+P9iYWH/wcC7//T17f++vbf/5eHd/727uP+Uk4//8PDp/+Ti2/+wsK3/g4SD/8PDv//Ixb//49/c/+jm4f9/f33/x8XG//r28//u6+f/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7uvn/+3p5v/v7er/lJSN/29tZv9yb2v/9PHs/+nm4v/g3dn/6+fj/+Pg3P/m4+D/7enm//f27//IzMP/5OTc/+Pg2//v7Oj/ysfC/39/fv/18fH/7+zp//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7+zo//Px7/+eoJj/6urK/6mpkf9/fnr/4ODb//Hv6//o5eH/5ePf/+Lf2//My8b/t7aw/8/Rxv/i4tr/8e7q/66sqv9PTk3/29nY//bz8f/u6+f/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/t6ub//vv6/7m6tv/X1bX/9vbZ/5KUjP+ChH//sa+r/9fU0P/18u//w7+7/6enkP/Ky6//zc2y/9DQvv/g3Nr/e3p5/+fn5//39fL/7uvn//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7+zo//j08P/Nzcr/m5uO//Hqzf/Dwqr/6uvg/87Nxv9YVVX/nZmZ/52alv+Pi4v/lJGA////4//v8Mv/y828/5CPjv+tq6z///3+/+vo5v/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/v7Oj/9fLu/9rY1v9sbWj/o6SZ/728s//U0sn/bGln/+Lf4P/8+Pj/6+fl/7m3tf+trJf/+fnR/+rqyf+hopT/e3x8//n29v/v6ur/8O3q//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p/+/s6P/39O//1dPS/5mamf/5/Pb/paeh/3d0c//Z1df/+fb0/+nl4////P3/raqo/4eHef+3t6b/0c7E/11ZWP/h3+D/9fHw/+/r6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7+zo//n18f/Ny8r/dXZ0/5aXk/+VlZT/7+3t//j09P/t6ub/7uvo//z3+P+8urr/pqek/+3u6v9qamr/y8nK//v3+P/u6uf/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8e7p/+zq6P/JyMj/4N3d//35+v/y7u3/7uvo//Dt6f/u6+f/+/b3/8TCw/+SlI//hIOB/8TCwv/9+fj/7Onm//Dt6v/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8e3r//r09f/18PD/7unq//Ds6v/w7en/8O3p/+/s6f/18PD/4t7f/4ODg//a2Nj//fj6/+3p5//w7un/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/7uvo//Ds6f/w7er/8O3p//Dt6f/w7en/8O3p//Ds6f/y7+z//vv4//Xy7//t6uf/8O3q//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p/+/s6P/t6ub/7+zo//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/8O3p//Dt6f/w7en/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA='


class GUI(Tk):
    def __init__(self):
        super().__init__()
        self.title('serial port tool')
        self.geometry('768x512')
        try:
            self.iconbitmap('icon.ico')
        except:
            self.icon = PhotoImage(ICON)
            self.iconbitmap(self.icon)
        self.resizable(False, False)
        self.bind('<Return>', self.send)
        self.content_init()
        self.mainloop()

    def content_init(self):
        ports = [x.device for x in serial.tools.list_ports.comports()]
        # select port text
        self.port_options_text = Label(
            self, text='port', width=10)
        self.port_options_text.grid(row=0, column=0)
        # select port options
        self.port_options = ttk.Combobox(self, width=10)
        self.port_options['value'] = ports
        if len(ports) != 0:
            self.port_options.current(0)
        self.port_options.grid(column=0)
        # set baud text
        self.port_baud_text = Label(
            self, text='baud', width=10)
        self.port_baud_text.grid(column=0)
        # set baud input box
        self.port_baud = Entry(self, width=14)
        self.port_baud.insert(0, 115000)
        self.port_baud.grid(column=0)
        # set timeout text
        self.port_time_out_text = Label(self, text='time out(s)', width=10)
        self.port_time_out_text.grid(row=5, column=0)
        # set timeout options
        self.port_time_out = ttk.Combobox(self, width=10)
        self.port_time_out['value'] = [x*5 for x in range(0, 25)]
        self.port_time_out.current(0)
        self.port_time_out.grid(column=0)
        # set xonxoff text
        port_xonxoff_text = Label(self, text='xonxoff', width=10)
        port_xonxoff_text.grid(column=0)
        # set xonxoff options
        self.port_xonxoff = ttk.Combobox(self, width=10)
        self.port_xonxoff['value'] = ['off', 'on']
        self.port_xonxoff.current(0)
        self.port_xonxoff.grid(column=0)
        # set rtscts text
        self.port_rtscts_text = Label(self, text='rtscts', width=10)
        self.port_rtscts_text.grid(column=0)
        # set rtscts options
        self.port_rtscts = ttk.Combobox(self, width=10)
        self.port_rtscts['value'] = ['off', 'on']
        self.port_rtscts.current(0)
        self.port_rtscts.grid(column=0)
        # set dsrdtr text
        self.port_dsrdtr_text = Label(self, text='dsrdtr', width=10)
        self.port_dsrdtr_text.grid(column=0)
        # set dsrdtr options
        self.port_dsrdtr = ttk.Combobox(self, width=10)
        self.port_dsrdtr['value'] = ['off', 'on']
        self.port_dsrdtr.current(0)
        self.port_dsrdtr.grid(column=0)
        # # blank place holder to have one line empty
        # self.blank = Label(self, text='', width=10)
        # self.blank.grid(column=0)
        # confirm button
        self.comfirm_button = Button(self, text='comfirm',
                                     width=10, command=self.comfirm)
        self.comfirm_button.grid(column=0)
        # reset button
        self.reset_button = Button(self, text='reset', width=10,
                                   command=self.reset)
        self.reset_button.grid(column=0)
        # clear screen button
        self.clear = Button(self, text='clear', width=10,
                            command=self.clear_screen)
        self.clear.grid(column=0)
        # recv_test
        self.recv_text = Label(self, text='recv', width=10)
        self.recv_text.grid(row=0, column=1, columnspan=20)
        # scrollable display
        self.port_recv_buffer = Text(self)
        self.port_recv_buffer.grid(row=1, column=1, rowspan=20)
        # send test
        self.send_text = Label(self, text='send', width=10)
        self.send_text.grid(column=0, columnspan=2)
        # input box
        self.port_send_buffer = Text(self, height=5)
        self.port_send_buffer.grid(column=0, columnspan=2)

    def comfirm(self):
        port_name = self.port_options.get()
        try:
            time_out = int(self.port_time_out.get())
        except:
            time_out = None
        baud = int(self.port_baud.get())
        xonxoff = self.port_xonxoff.get() == 'on'
        rtscts = self.port_rtscts.get() == 'on'
        dsrdtr = self.port_dsrdtr.get() == 'on'
        self.serial = serial_port.serial_port_x(
            self, port_name, timeout=time_out, baudrate=baud, xonxoff=xonxoff, rtscts=rtscts, dsrdtr=dsrdtr)

    def reset(self):
        try:
            del self.serial
        except:
            pass
        for widget in self.winfo_children():
            widget.destroy()
        self.content_init()

    def clear_screen(self):
        self.port_recv_buffer.delete("1.0", "end")
        self.port_send_buffer.delete("1.0", "end")

    def send(self, *args):
        cmd = self.port_send_buffer.get("1.0", END)
        self.serial.serial_send(cmd=cmd)
        self.serial.clear(target="send")


if __name__ == '__main__':
    app = GUI()
