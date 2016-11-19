#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

    VideoCapture cap("/home/david/Desktop/LauzHack2016/data/WIN_20161119_13_30_14_Pro.mp4");
    cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
    if(!cap.isOpened()){
	std::cout << "Failed to open camera." << std::endl;
        return -1;
    }

    Mat temp, firstFrame;
    cap >> temp;


    for(;;){

        Mat frame, imgray, imageBin;
        cap >> frame; // get a new frame from camera
        cvtColor(temp,firstFrame,CV_RGB2GRAY);

        blur(frame,imgray,Size(3,3));

        /// Canny detector
        Canny(imgray,imgray, 50, 150, 3);

        imshow("Test",imgray);
        /// Using Canny's output as a mask, we display our result
//        dst = Scalar::all(0);
//
//        src.copyTo( dst, imgray);

//        cvtColor(frame,imgray,CV_RGB2GRAY);
//        Mat test = imgray - firstFrame;
//        threshold(test,imageBin,100,250,cv::THRESH_BINARY);
//        imshow("ok",imageBin);

        //cvtColor(frame,imgray,CV_RGB2GRAY);


//

//        std::vector<Vec4i> hierarchy;
//        std::vector<std::vector<Point> > contours;
//        findContours(imageBin, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
//
//        Mat drawing = Mat::zeros(imageBin.size(), CV_8UC3);
//        for( int i = 0; i< contours.size(); i++ ) {
//             Scalar color = Scalar(255,255,255);
//             drawContours(drawing,contours,i,color,2,8);
//        }

        if(waitKey(30) >= 0) break;
    }

    return 0;
}
