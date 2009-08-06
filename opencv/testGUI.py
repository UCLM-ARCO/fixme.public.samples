#!/usr/bin/python

import opencv as cv
import opencv.highgui as gui

capture = gui.cvCreateCameraCapture(gui.CV_CAP_ANY)
gui.cvNamedWindow ("Prb", gui.CV_WINDOW_AUTOSIZE)

while True:
    img = gui.cvQueryFrame (capture)
    gui.cvShowImage ("Prb", img)

    c = gui.cvWaitKey(10)
    if c == '\x1b':
        break

gui.cvDestroyWindow ("Prb");
