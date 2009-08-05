#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>


int
main (int argc, char* argv[])
{
    CvCapture* capture =
	(argc > 1)? cvCaptureFromFile (argv[1]) : cvCaptureFromCAM(CV_CAP_ANY);
    if (!capture) {
	throw "ERROR: capture is NULL \n";
    }

    cvNamedWindow ("Prb", CV_WINDOW_AUTOSIZE);
    IplImage* last = NULL;
    IplImage* res = NULL;
    while (true) {
	if (!cvGrabFrame (capture))
	    break;

	IplImage* img = cvRetrieveFrame (capture);

	// version en gris y sin ruido
	IplImage* gray = cvCreateImage (cvSize(img->width,img->height),
					IPL_DEPTH_8U, 1);
	cvCvtColor (img, gray, CV_BGR2GRAY);
	cvEqualizeHist (gray, gray);
	cvSmooth (gray, gray);
	
	// diferencia con la ultima (solo diferencias grandes)
	if (!last)
	    last = cvCloneImage (gray);

	if (!res) {
	    res = cvCreateImage (cvSize(img->width,img->height),
				 IPL_DEPTH_8U, 1);
	    cvSetZero( res );
	}
	cvAbsDiff (gray, last, res);
	cvThreshold(res, res, 70, 255, CV_THRESH_BINARY);
	cvReleaseImage (&last);
	last = gray;

	cvShowImage ("Prb", res);
	cvReleaseImage (&res);

	int c = (cvWaitKey(10) & 255);
	if (c == 27) break;
    }

    cvReleaseCapture (&capture);
    cvDestroyWindow ("Prb");
    return 0;
}
