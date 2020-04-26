import cv2
from PIL import ImageTk
from PIL import Image
import tkinter as tk

import numpy as np
import threading
import sys
import serial
import time
s = serial.Serial("COM5");
s.baudrate = 19200;

def update_angles(info):
    text = "Angles: \n\n\n\n Thumb: " + info.split(' ')[0] + "  degrees\n" + "Index: " + info.split(' ')[1] + "  degrees\n" + "Middle finger: " + info.split(' ')[2] + "  degrees\n" + "Ring finger: " + info.split(' ')[3] + "  degrees\n" + "Pinky finger: " + info.split(' ')[4] + "  degrees\n"
    angles.configure(text = text)

def get():
    pad = False;
    index = 0;
    buf = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    while 1:
        try:
            value = str(s.readline(), "utf-8")
            value = value.replace('\\r', '').replace('\\n', '')
        except:
            value = "Sensors: 0 0 0 0 0"
        if value.find("Sensors") != -1:
            value = value.replace("Sensors: ",'');
            update_angles(value)
            print(value)
            #print(value);
        elif value.find("Motors") != -1:
            value = value.replace("Motors: ",'');
            value = value.replace("\\r",'').replace("\\n",'')
            for i in range(len(buf)):
                try:
                    buf[i] = int(value[i]);
                except:
                    buf[i] = 1
                #print(buf)
            visualizer(buf);
            buf = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        value = ''
        time.sleep(0.1);


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

    copy = Image.fromarray(copy)
    image = ImageTk.PhotoImage(copy);
    panel.configure(image = image)
    root.update()
    #cv2.imshow("result", copy);
    #cv2.waitKey(1);

def exit(event):
    s.close()
    root.destroy();



if __name__ == "__main__":
    img = cv2.imread("hand.png", 1)  # read greyscale image
    root = tk.Tk();
    root.bind("<Escape>", exit)
    imgg = Image.fromarray(img)
    img1 = ImageTk.PhotoImage(imgg)
    panel = tk.Label(image=img1)
    panel.image = img1
    panel.pack(side="left")
    angles = tk.Label(text = "0");
    angles.pack(side="right")
    get();
    #option = [2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1] ;
    #visualizer(option);



