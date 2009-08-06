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

using namespace std;

int
main (int argc, char* argv[])
{
    CvCapture* capture = (argc > 1)
	? cvCaptureFromFile (argv[1]) 
	: cvCaptureFromCAM(CV_CAP_ANY);
    if (!capture) {
	cerr << "ERROR: capture is NULL \n";
	exit(1);
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
	cvSmooth (gray, gray, CV_GAUSSIAN, 9, 9);
	
	// diferencia con la ultima (solo diferencias grandes)
	if (!last)
	    last = cvCloneImage (gray);

	if (!res) {
	    res = cvCreateImage (cvSize(img->width,img->height),
				 IPL_DEPTH_8U, 1);
	    cvSetZero( res );
	}
	cvSub (gray, last, res);
	cvThreshold(res, res, 128, 255, CV_THRESH_BINARY);
	cvReleaseImage (&last);
	last = gray;

	CvScalar color = CV_RGB(100, 100, 100);
	CvRect r = cvBoundingRect(res, 0);
	cvRectangle(res, 
		    cvPoint(r.x, r.y), 
		    cvPoint(r.x+r.width, r.y+r.height), 
		    color);

	cvShowImage ("Prb", res);
	cvReleaseImage (&res);

	int c = (cvWaitKey(10) & 255);
	if (c == 27) break;
    }

    cvReleaseCapture (&capture);
    cvDestroyWindow ("Prb");
    return 0;
}
