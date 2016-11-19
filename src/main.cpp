#include "opencv2/opencv.hpp"

#include <calibrate.h>

using namespace cv;

int main(int argc, char** argv)
{
	calibrate::runCalibration();

    // Default camera ID.
    int i = 0;
    
    if(argc > 1) {
	// Custom camera ID from argv.
    	sscanf(argv[1], "%d", &i);
    }

    VideoCapture cap(i);
    cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
    if(!cap.isOpened()){
	std::cout << "Failed to open camera." << std::endl;
        return -1;
    }

    for(;;){
        Mat frame;
        cap >> frame; // get a new frame from camera
       
        imshow("frame", frame);
        if(waitKey(30) >= 0) break;
    }

    return 0;
}
