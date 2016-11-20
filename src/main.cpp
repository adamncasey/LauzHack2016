#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <unordered_map>

#include <megaheader.h>

using namespace cv;

char readKeyboardInput() {
	return waitKey();
}

typedef std::map<AlphaDisruptColourTransform, Finger> ColourFingerMap;

Mat createGui(Mat im1, bool error);

bool getFingerForKeyPress(const char key, const std::unordered_map<char, cv::Vec2i>& keyPointMap,
	const ColourFingerMap& colourFingerMap,
	VideoCapture& capture);

int main(int argc, char** argv)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz;";

	VideoCapture capture(1);
	capture.set(cv::CAP_PROP_AUTOFOCUS, 0);

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.

	cv::Mat frame;
	// remove the first few frames of rubbish
	for (int i = 0; i < 10; i++) {
		capture >> frame;
	}
    
	const std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet, capture);

	std::cout << "Keyboard Calibrated. Please place your hands on the home keys." << std::endl;
	std::cout << "Press any home key to continue" << std:: endl;
	waitKey();

	for (int i = 1; i < 20; i++) {
		capture >> frame;
	}
	std::map<AlphaDisruptColourTransform, Finger> colourFingerMap = calibrateColours(keyPointMap, frame);

	while (true) {
		int key = cv::waitKey(15);
		if (key == -1) {
			continue;
		}
		capture >> frame;
		capture >> frame;
		capture >> frame;
		capture >> frame;
		capture >> frame;

		if (!getFingerForKeyPress(key, keyPointMap, colourFingerMap, capture)) {
			std::cout << "Failed to find a finger for a key: " << key << std::endl;

			frame = createGui(frame, 1)
			cv::imshow("Display window", frame);

			continue;
		}

		std::cout << "We detected a '" << key << "' pressed with correct finger" << std::endl;

		frame = createGui(frame, 0)
		cv::imshow("Display window", frame);
		
	}
    
    return 0;
}

bool getFingerForKeyPress(const char key, const std::unordered_map<char, cv::Vec2i>& keyPointMap,
	const ColourFingerMap& colourFingerMap,
	VideoCapture& capture)
{
	cv::Mat frame;
	capture.retrieve(frame);

	return checkForCorrectFinger(colourFingerMap, key, keyPointMap, frame);
}


Mat createGui(Mat im1, bool error) {

bool correctFinger = 0;
string greatText1 = "Practice your typing skills with our great tool";
string greatText2 = "Just type this text and the program will assess your";
string greatText3 = "ten finger typing technique";
string greatText4 = "The quick brown fox jumped over the lazy dog";

Size sz1 = im1.size();
Size sz2 = sz1;

Mat im2(sz2.height, sz2.width, CV_8UC3);

if (!error)
im2 = Scalar(0, 0, 255);
else
im2 = Scalar(0, 0, 0);

putText(im2, greatText1, cvPoint(30,30),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
putText(im2, greatText2, cvPoint(30,60),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
putText(im2, greatText3, cvPoint(30,90),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
putText(im2, greatText4, cvPoint(30,120),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);

Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
Mat left(im3, Rect(0, 0, sz1.width, sz1.height));

im1.copyTo(left);
Mat right(im3, Rect(sz1.width, 0, sz2.width, sz2.height));
im2.copyTo(right);

}


//#include <thread>
//#include <mutex>
//
//using namespace cv;
//
//std::mutex mtxCam;
//Mat frame;
//void CaptureFrames() {
//  VideoCapture capture(0);
//  if (!capture.isOpened()) {
//      std::cout << "cannot open camera" << std::endl;
//  }
//
//  while (true) {
//      mtxCam.lock();
//      // capture.grab();
//      capture >> mutex;
//      mtxCam.unlock();
//      if (waitKey(30) >= 0) { break; }
//  }
//}
//
//
//int main(int argc, char** argv[]) {
//    std::thread t1(CaptureFrames);
//
//  while(true) {
//      if (!mutex.empty()) {
//          mtxCam.lock();
//          // capture.retrieve(frame);
//          imshow("multithread test", frame);
//          mtxCam.unlock();
//      }
//    if(waitKey(30) >= 0) {break;}
//  }
//
//  return 0;
//}


