#!/usr/bin/env python

import opencv as cv
import opencv.highgui as gui


capture = gui.cvCreateCameraCapture(gui.CV_CAP_ANY)
last = None
res = None

gui.cvNamedWindow ("Prb", gui.CV_WINDOW_AUTOSIZE)

while True:
    if not gui.cvGrabFrame(capture):
        break
    img = gui.cvRetrieveFrame (capture)

    # version en gris y sin ruido
    gray = cv.cvCreateImage (cv.cvSize(img.width, img.height),
                             cv.IPL_DEPTH_8U, 1)
    cv.cvCvtColor (img, gray, cv.CV_BGR2GRAY)
    cv.cvEqualizeHist (gray, gray)
    cv.cvSmooth (gray, gray, cv.CV_GAUSSIAN, 9, 9)
	
    # diferencia con la ultima
    if last == None:
        last = cv.cvCloneImage (gray)

    if res == None:
        res = cv.cvCreateImage (cv.cvSize(img.width, img.height),
                                cv.IPL_DEPTH_8U, 1)
        cv.cvSetZero(res)

    res = gray - last
    cv.cvThreshold(res, res, 128, 255, cv.CV_THRESH_BINARY)
    cv.cvReleaseImage (last)
    last = gray

    color = cv.CV_RGB(100, 100, 100)
    r = cv.cvBoundingRect(res, 0)
    cv.cvRectangle(res, 
                   cv.cvPoint(r.x, r.y), 
                   cv.cvPoint(r.x+r.width, r.y+r.height), 
                   color)

    gui.cvShowImage ("Prb", res)
    cv.cvReleaseImage(res)

    c = gui.cvWaitKey(10)
    if c == '\x1b':
        break

cv.cvReleaseCapture (capture);
gui.cvDestroyWindow ("Prb");
