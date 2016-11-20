#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <unordered_map>

#include <megaheader.h>

using namespace cv;

int main(int argc, char** argv)
{

	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::unordered_map<char, cv::Vec2d> keysToLocationMap;
    cv::Mat image;
	//std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet);
    std::map<AlphaDisruptColourTransform, Finger> colorToFingerMap = calibrateColours(keysToLocationMap, image);
    bool isCorrect = checkForCorrectFinger(colorToFingerMap, 'd', keysToLocationMap, image);
    
    std::cout << "Used correct Finger? " << isCorrect << std::endl;
//    // Default camera ID.
//    int i = 0;
//
//    if(argc > 1) {
//	// Custom camera ID from argv.
//    	sscanf(argv[1], "%d", &i);
//    }
//
//    VideoCapture cap("/home/david/Desktop/LauzHack2016/data/WIN_20161119_13_30_14_Pro.mp4");
//    // cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
//    if(!cap.isOpened()){
//	std::cout << "Failed to open camera." << std::endl;
//        return -1;
//    }
//
//
//    for(;;){
//
//        Mat frame;
//        cap >> frame; // get a new frame from camera
//        imshow("frame",frame);
//
//        if(waitKey(30) >= 0) break;
//    }
//
//    return 0;
}
