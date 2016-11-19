#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <unordered_map>

#include <megaheader.h>

using namespace cv;

int main(int argc, char** argv)
{
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet);

    // Default camera ID.
    int i = 0;
    
    if(argc > 1) {
	// Custom camera ID from argv.
    	sscanf(argv[1], "%d", &i);
    }

    VideoCapture cap("/home/david/Desktop/LauzHack2016/data/testVid_singePresses.mp4");
    cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
    if(!cap.isOpened()){
	std::cout << "Failed to open camera." << std::endl;
        return -1;
    }


    for(;;){

        Mat frame;
        cap >> frame; // get a new frame from camera



        cv::Vec2i coords(280,200);
        std::cout << "h " <<  getColourAtPoint(coords,frame)[0]/255*360 << std::endl;

        circle(frame, coords, 8, Scalar(255,255,255), 1, 8);
        imshow("frame",frame);
        waitKey();
        //if(waitKey(30) >= 0) break;
    }

    return 0;
}
