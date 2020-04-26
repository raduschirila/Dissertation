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


while 1:
    info = str(s.readline(),"utf-8").replace('\\r','').replace('\\n','')
    if info.find("Motors")!=-1:
        print(info);
    elif info.find("Sensors")!=-1:
        print(info);