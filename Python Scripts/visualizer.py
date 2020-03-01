import cv2
import numpy as np
import threading
import sys
import serial
import time
s = serial.Serial("COM7");
s.baudrate = 9600;



def get():
    pad = False;
    index = 0;
    buf = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    while 1:
        value = str(s.read(), "utf-8");
        value = value.replace('\\r', '').replace("\\n", '');
        if value.strip():  # if it exists
            x = int(value);
            if index == 13:
                index = 0;
                print(buf)
                visualizer(buf);
                buf = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            if x == 0:  # we are in the padding region
                pad = True;
            if x != 0:
                # if it was pad now information transmission starts
                if pad == True:  # edge detect implementation
                    pad = False;
                    index = 0;
                    buf[index] = x;
                else:
                    index += 1;
                    buf[index] = x;

def visualizer(option):
    positions = [(190, 330), (310, 100), (440, 60), (550, 85), (630, 185),  #fingertips
                 (380, 330), (460, 330), (540, 360), #row 1
                 (380, 380), (460, 380), (540, 420),  # row 2
                 (380, 450), (460, 450), (520, 480) ] # row 3
    img = cv2.imread("hand.png",1) #read greyscale image
    #cv2.imshow("s", img)
    #cv2.waitKey(1)
    copy = cv2.imread("hand.png",1)

    for i in range(14):
        if option[i] == 2:
            cv2.circle(copy,positions[i],20,(255,0,0),-1);

    cv2.imshow("result", copy);
    cv2.waitKey(1);





if __name__ == "__main__":
    get();
    #option = [2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1] ;
    #visualizer(option);




