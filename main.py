import cv2
import time

import serial
import hand_detect as htm

portNO = 'COM13'

ser = serial.Serial(portNO, 9600)
print('--------- Connected----------')

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

overlayList = []
pTime = 0
figers = [0, 0, 0, 0, 0]
detector = htm.handDetector(detectionCon=0.75)

tipIds = [4, 8, 12, 16, 20]

while True:
    success, img = cap.read()
    imgshow = img
    img = detector.findHands(img)
    lmList = detector.findPosition(img, draw=False)
    # print(lmList)
    if len(lmList) != 0:
        fingers = []

        # ngon cai
        if lmList[tipIds[0]][1] > lmList[tipIds[0] - 1][1]:
            fingers.append(1)
            figers[0] = 1
        else:
            fingers.append(0)
            figers[0] = 0
        ## ngon tro
        if lmList[tipIds[1]][2] < lmList[tipIds[1] - 2][2]:
            figers[1] = 1
        else:
            figers[1] = 0

        if lmList[tipIds[2]][2] < lmList[tipIds[2] - 2][2]:
            figers[2] = 1
        else:
            figers[2] = 0

        if lmList[tipIds[3]][2] < lmList[tipIds[3] - 2][2]:
            figers[3] = 1
        else:
            figers[3] = 0

        if lmList[tipIds[4]][2] < lmList[tipIds[4] - 2][2]:
            figers[4] = 1
        else:
            figers[4] = 0

    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime

    string = str(int(figers[0])) + "." + str(int(figers[1])) + "^" + str(int(figers[2])) + '*' + str(
        int(figers[3])) + '?' + str(int(figers[4])) + '&'

    try:
        ser.write(string.encode())
        time.sleep(3)
        print(string)
    except:
        pass

    cv2.putText(imgshow, f'FPS: {int(fps)}', (400, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 0), 3)
    cv2.imshow("Image", imgshow)
    cv2.waitKey(1)