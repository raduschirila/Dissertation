import cv2
import numpy as np
import threading
import sys
import serial
import time
pic = serial.Serial('/dev/tty.usbmodem141201')  # open serial port
pic.baudrate=9600;
option = -1;


def get():
    while 1:
        data = pic.read(pic.in_waiting);
        if data:
            processed = str(data.decode('utf-8'))  # str(data).replace('\\r\\n','').encode('utf-8').decode('utf-8')
            print(str(data));
            processed2 = str(processed)
            processed2 = processed.replace('\\r\\n', '').replace("Received data: ", '');
            print(processed2)

            processed3 = int(processed2)
            if processed3 == 22:
                sys.exit();
            else:
                visualizer(processed3);

def visualizer(option):
    positions = [(190, 330), (310, 100), (440, 60), (550, 85),(630, 185)]
    img = cv2.imread("hand.png",1) #read greyscale image
    cv2.imshow("s", img)
    cv2.waitKey(1)
    copy = cv2.imread("hand.png",1)
    cv2.circle(copy,(positions[option][0],positions[option][1]),20,(255,0,0),thickness = -1);
    cv2.imshow("s", copy);
    cv2.waitKey(1)





if __name__ == "__main__":
    get()




