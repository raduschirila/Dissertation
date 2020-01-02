import serial

s = serial.Serial("COM9");
s.baudrate = 9600;
pad = False;
index = 0;
buf = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
while 1:
    value = str(s.read(),"utf-8");
    value = value.replace('\\r','').replace("\\n",'');
    if value.strip(): #if it exists
        x = int(value);
        if index == 13:
            index = 0;
            print(buf)
            buf = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        if x == 0: # we are in the padding region
            pad = True;
        if x != 0:
            #if it was pad now information transmission starts
            if pad == True:#edge detect implementation
                pad = False;
                index = 0;
                buf[index]=x;
            else:
                index += 1;
                buf[index] = x;




