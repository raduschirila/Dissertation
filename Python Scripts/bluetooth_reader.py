import serial
s = serial.Serial("COM9");
s.baudrate = 19200;
while 1:
     value = str(s.read(3), "utf-8")
     value = value.replace('\\r', '').replace("\\n", '');
     if value.strip():
         result = int(value) * 10;
     value = str(s.read(), "utf-8")
     value = value.replace('\\r', '').replace("\\n", '');
     if value.strip():
         result += int(value);
     print(result)