#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <unordered_map>
#include <chrono>

#include <megaheader.h>

using namespace cv;

char readKeyboardInput() {
	return waitKey();
}

typedef std::map<AlphaDisruptColourTransform, Finger> ColourFingerMap;

bool getFingerForKeyPress(const char key, const std::unordered_map<char, cv::Vec2i>& keyPointMap,
	const ColourFingerMap& colourFingerMap,
	VideoCapture& capture);

int main(int argc, char** argv)
{
    std::map<char, int> keyMap;
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz;";

	VideoCapture capture(1);
	capture.set(cv::CAP_PROP_AUTOFOCUS, 0);
	capture.set(cv::CAP_PROP_BUFFERSIZE, 1);
	capture.set(cv::CAP_PROP_FPS, 30);

	std::cout << "Camera FPS: " << capture.get(cv::CAP_PROP_FPS) << std::endl;

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.

	cv::Mat frame;
	// remove the first few frames of rubbish
	for (int i = 0; i < 10; i++) {
		capture >> frame;
	}
    
	const std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet, capture);

	std::cout << "Keyboard Calibrated. Please place your hands on these keys: (a, w, e, f) and (j, i, o, ;)" << std::endl;
	std::cout << "Press any key to continue" << std:: endl;
	waitKey();

	for (int i = 1; i < 20; i++) {
		capture >> frame;
	}
	std::map<AlphaDisruptColourTransform, Finger> colourFingerMap = calibrateColours(keyPointMap, frame);

	double correctProp = 0;
	int numTries = 0;
	double numCorrect = 0;

	while (true) {
		int key = cv::waitKey(15);
		if (key == -1) {
			continue;
		}
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		std::cout << duration_ms.count() << std::endl;

		capture >> frame;
		std::cout << "video ms: " << capture.get(cv::CAP_PROP_POS_MSEC) << std::endl;

		capture >> frame;
		capture >> frame;
		capture >> frame;
		capture >> frame;

		numTries++;

		if (!getFingerForKeyPress(key, keyPointMap, colourFingerMap, capture)) {
			std::cout << "Failed to find a finger for a key: " << key << std::endl;
            std::map<char, int>::iterator currentKeyIt = keyMap.find((char)key);
            if(currentKeyIt == keyMap.end()){
                keyMap.insert({(char)key, 1});
            }else{
                keyMap.insert({(char) key, currentKeyIt->second+1});
            }
            continue;
		}

		numCorrect += 1.0;
		correctProp = numCorrect/numTries;
		std::cout << "Correct! '" << key << "' pressed with correct finger. " << (correctProp*100) << "%" << std::endl;
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


