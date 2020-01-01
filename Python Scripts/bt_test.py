import serial

s = serial.Serial("COM5");
s.baudrate = 9600;

while 1:
    value = str(s.read(10)).encode('utf-8').decode('utf-8').replace("\\r\\n",'').replace("b'",'');
    print(value)
