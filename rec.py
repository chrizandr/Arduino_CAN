import serial
import cv2
import numpy as np
import pdb
def getImage(string):
	string = string[1:]
	string = string.strip()[0:-1]
	string = string.split(',')
	string = [int(s) for s in string]
	img = list()
	for i in range(0,1024,32):
		img.append(string[i:i+32])
	img = np.array(img)
	img = img * 8
	img = img.astype(np.uint8)
	return img
			

ser = serial.Serial("/dev/ttyACM0",115200)
byte = list()
while(True):
	line = ser.readline()
	if(line[0]==ord('S')):
		ser.close()	
		print("Getting image")
		img = getImage(line.decode("utf-8"))
		new_img = cv2.resize(img,(0,0),fx = 8, fy = 8)
		cv2.imshow("Output",new_img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
