import sys
import cv2 as cv
import numpy as np

ALPHA = 2.0

src = cv.imread('sample.jpg')
if src is None:
    print('Image load failed')
    exit()

avg = np.average(src)

dst = cv.convertScaleAbs(src, alpha = 1 + ALPHA, beta = -avg * ALPHA)

cv.imwrite('contrast.jpg', dst)