import serial as sl
import time
import datetime

ser = sl.Serial('/dev/tty.usbmodem14201', 9600)
iter = 0
time.sleep(10)

with open('temp_record.csv', 'w') as f:
    header_line = "Date, Sensor Value, Temperature C,\n"
    f.write(header_line)
    while iter < 30:
        s_1 = str(ser.readline()).replace("'", "")
        s_2 = s_1.replace("\\r\\n", "")
        s_3 = s_2.replace("b", "")
        s_4 = s_3.split(",")

        line_ = f"{datetime.datetime.now()}, {s_4[0][-3:]}, {s_4[1][-5:]}\n"
        f.write(line_)
        iter += 1
    f.close
