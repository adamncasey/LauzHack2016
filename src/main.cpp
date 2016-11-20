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
			continue;
		}

		std::cout << "We detected a '" << key << "' pressed with correct finger" << std::endl;
		
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

