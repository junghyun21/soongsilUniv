import sys
import cv2 as cv
import numpy as np

# 이미지 회색조로 오픈
src = cv.imread('sample.jpg', cv.IMREAD_GRAYSCALE)
if src is None:
    print('Image load failed')
    exit()

dst = np.empty(src.shape, dtype = src.dtype)

avg = np.average(src)

for y in range(src.shape[0]):
    for x in range(src.shape[1]):
        if src[y, x] < avg:
            dst[y, x] = 0
        else:
            dst[y, x] = src[y, x]

cv.imwrite('output.jpg', dst)