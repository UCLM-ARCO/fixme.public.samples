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


#define WSIZE cvSize(160,120)
#define minNorm 0.1

void
showImages(const char* title, IplImage *img, IplImage *cres)
{
    // DispImage - the image in which input images are to be copied
    IplImage *DispImage = cvCloneImage (img);
    cvSetImageROI (DispImage, cvRect(6, 6, cres->width, cres->height));

    cvCopy (cres, DispImage);

    // Reset the ROI in order to display the next image
    cvResetImageROI(DispImage);

    // Create a new window, and show the Single Big Image
    cvShowImage (title, DispImage);

    // Release the Image Memory
    cvReleaseImage(&DispImage);
}

int
main (int argc, char* argv[])
{
    static int imgCounter;

    CvCapture* capture =
	(argc > 1)? cvCaptureFromFile (argv[1]) : cvCaptureFromCAM(CV_CAP_ANY);
    if (!capture) {
	throw "ERROR: capture is NULL \n";
    }

    cvNamedWindow ("Prb", CV_WINDOW_AUTOSIZE);
    IplImage* res = cvCreateImage(WSIZE, IPL_DEPTH_8U, 1);
    cvSetZero( res );

    IplImage* last = NULL;
    while (true) {
	if (!cvGrabFrame (capture))
	    break;

	IplImage* img = cvRetrieveFrame (capture);

	// version en gris
	IplImage* gray = cvCreateImage (cvSize(img->width,img->height),
					IPL_DEPTH_8U, 1);
	cvCvtColor (img, gray, CV_BGR2GRAY);

	// tamanno normalizado
	IplImage* small_img = cvCreateImage (WSIZE, IPL_DEPTH_8U, 1);
	cvResize (gray, small_img, CV_INTER_LINEAR);
	cvReleaseImage (&gray);

	// ecualizar y blur para eliminar ruido
	cvEqualizeHist (small_img, small_img);
	cvSmooth (small_img, small_img);
	
	// diferencia con la ultima (solo diferencias grandes)
	if (!last)
	    last = cvCloneImage (small_img);
	cvAbsDiff (small_img, last, last);
	cvConvertScale (last, last, 0.005); // cvThreshold

	// oscurecemos lo que ya teniamos
	cvConvertScale (res, res, 0.9, -0.5);
	// ponemos los cambios de este frame
	cvSet (res, cvScalar(255), last);

         
	// ahora la ultima es este frame
	cvReleaseImage (&last);
	last = small_img;

	// version color
	// la componte roja es res directamente
	IplImage* cres = cvCreateImage (WSIZE, IPL_DEPTH_8U, 3);
	cvSetZero (cres);
	cvMerge (0, 0, res, 0, cres); // BGR
	// la componente azul es 255 - res
	IplImage* blue = cvCreateImage(WSIZE, IPL_DEPTH_8U, 1);
	cvSetZero (blue);
	cvSubRS (res, cvScalar(255), blue, res);
	cvMerge (blue, 0, 0, 0, cres); // BGR
	cvReleaseImage (&blue);
	
	showImages ("Prb", img, cres);

	int c = (cvWaitKey(10) & 255);
	if (c == 27) break;

	cvReleaseImage (&cres);
    }

    cvReleaseCapture (&capture);
    cvDestroyWindow ("Prb");
    return 0;
}
