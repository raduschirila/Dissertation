import cv2
import numpy as np
import threading
import sys
option = -1


def get():
    while 1:
        option = int(input("option: "))
        if option == 22:
            sys.exit();
        else:
            visualizer(option)

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



