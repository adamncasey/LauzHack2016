#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(1); 
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
