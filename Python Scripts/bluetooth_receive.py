import serial

ser = serial.Serial('/dev/tty.Bluetooth-Incoming-Port',9600, timeout = 0);

while 1:
    response = ser.read(ser.in_waiting)
    if response != b'':
        response = str(response)
        print (response)

