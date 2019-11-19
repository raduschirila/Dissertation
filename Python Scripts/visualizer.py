# -*- coding: utf-8 -*-
"""
Created on Tue Nov 12 18:51:01 2019

@author: radus
"""

import serial 
import cv2
import numpy as np
import matplotlib.pyplot as plt
import time

def visual(img,row,col):
    cv2.circle(img,(row, col), 20, (2,255,0), -1)
    cv2.imshow("da",img);
    time.sleep(1);


in1 = [1,2,3,4,5];
img = cv2.imread("hand.png",0);
run = True;
print(img.shape)
cv2.imshow("init",img);

visual(img,310,100)

cv2.waitKey(0);
cv2.destroyAllWindows();