#!/usr/bin/python

import opencv.cv as cv
import opencv.highgui as oh
import sys

try:
    oh.cvNamedWindow("LiveVideo", oh.CV_WINDOW_AUTOSIZE)
    cam = oh.cvCreateCameraCapture( 0 )

    while(1):
        f = oh.cvQueryFrame(cam)
        f0 = cv.cvCloneImage(f)
        oh.cvShowImage("LiveVideo",f0)

except:
    cv.cvReleaseCapture(cam)
    oh.cvDestroyWindow("LiveVideo")
    print sys.exc_info()
