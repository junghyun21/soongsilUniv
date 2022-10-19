import sys
import time
import cv2 as cv
import numpy as np

cap = cv.VideoCapture(0)
if not cap.isOpened():
    print("Camera open failed")
    exit()

fourcc = cv.VideoWriter_fourcc('M', 'J', 'P', 'G')

w = round(cap.get(cv.CAP_PROP_FRAME_WIDTH))
h = round(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

out = cv.VideoWriter('output.avi', fourcc, 10, (w, h))
if not out.isOpened():
    print("File open failed")
    exit()

old_avg = 1000
end_time = 0

while True:
    ret, gray = cap.read()
    if not ret:
        break

    # gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    new_avg = np.average(gray)
    
    if end_time > time.time():
        gray = ~gray

    elif old_avg != 1000 and abs(new_avg - old_avg) > 30:
        end_time = time.time() + 3
        gray = ~gray

    old_avg = new_avg

    # cv.imshow('gray', gray)
    out.write(gray)
    if cv.waitKey(1) & 0xFF == 27:
                break

cap.release()
out.release()

cv.destroyAllWindows()