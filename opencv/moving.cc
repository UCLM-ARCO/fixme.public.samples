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


void 
myMouseCallback(int event, int x, int y, int flags, void* param)
{
    if (event == CV_EVENT_LBUTTONDOWN) {
	IplImage** res = (IplImage**) param;
	cout << "Target: " << x << ", " << y << endl;
    }
}

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

    IplImage* last = NULL;
    IplImage* res = NULL;

    cvNamedWindow ("Prb", CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("Prb", myMouseCallback, &res);

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

	CvScalar color = CV_RGB(100, 255, 100);
	CvRect r = cvBoundingRect(res, 0);
	//cvRectangle(res, cvPoint(r.x, r.y), 
	//            cvPoint(r.x+r.width, r.y+r.height), color);
	//cvShowImage ("Prb", res);

	static CvPoint current = cvPoint(0,0);
	if (r.width != 0 && r.height != 0)
	    current = cvPoint(r.x+r.width/2, r.y+r.height/2);

	// user feedback
	IplImage* out = cvCloneImage (img);
	cvCircle(out, current, 10, color, 3);
	cvLine(out, cvPoint(current.x, current.y - 15), 
	       cvPoint(current.x, current.y + 15), color, 3);
	cvLine(out, cvPoint(current.x - 15, current.y), 
	       cvPoint(current.x + 15, current.y), color, 3);
	cvRectangle(out, cvPoint(r.x, r.y),
	            cvPoint(r.x+r.width, r.y+r.height), color);
	cvShowImage ("Prb", out);
	cvReleaseImage (&out);
	
	cvReleaseImage (&res);

	int c = (cvWaitKey(10) & 255);
	if (c == 27) break;
    }

    cvReleaseCapture (&capture);
    cvDestroyWindow ("Prb");
    return 0;
}
