import serial
import time
pic = serial.Serial('/dev/tty.Bluetooth-Incoming-Port',parity=serial.PARITY_ODD, rtscts=1)  # open serial port
pic.baudrate=38400;

while 1:
    data = int(input("Send to pic: "));
    try:
        for i in range(11):
            print(pic.write(str(data//10).encode('UTF-8')));
            print(pic.write(str(data%10).encode('UTF-8')));
            time.sleep(0.4)
        print("OK");
    except:
        print("Error");
        pic.close();
pic.close()

