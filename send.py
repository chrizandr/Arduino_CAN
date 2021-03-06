import serial
import numpy as np
from cv2 import imread,imshow,waitKey, destroyAllWindows,resize
import pdb,time

img = imread("test.png",0)
new_img = img/8
new_img = new_img.astype(np.uint8)

with serial.Serial() as ser:
	ser.port = '/dev/ttyACM0'
	ser.baudrate = 115200
	ser.open()
	for i in range(32):
		for j in range(32):
			ser.write(chr(new_img[i,j]).encode())
		time.sleep(.04)

img = resize(img,(0,0),fx=8,fy=8)
imshow("Input",img)
waitKey(0)
destroyAllWindows()
