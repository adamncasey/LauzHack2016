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
	Finger* outFinger,
	VideoCapture& capture);

int main(int argc, char** argv)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz;";

	VideoCapture capture(1);
	capture.set(cv::CAP_PROP_AUTOFOCUS, 0);

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.

	cv::Mat frame;
	// remove the first few frames of rubbish
	for (int i = 0; i < 20; i++) {
		capture >> frame;
	}
    
	const std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet, capture);

	std::cout << "Keyboard Calibrated. Please place your hands on the home keys." << std::endl;
	std::cout << "Press any home key to continue" << std::endl;
	waitKey();

	capture >> frame;
	std::map<AlphaDisruptColourTransform, Finger> colourFingerMap = calibrateColours(keyPointMap, frame);

	while (true) {
		const char key = readKeyboardInput();

		Finger finger;
		if (!getFingerForKeyPress(key, keyPointMap, colourFingerMap, &finger, capture)) {
			std::cout << "Failed to find a finger for a key: " << key << std::endl;
			continue;
		}

		std::cout << "We detected a '" << key << "' pressed with finger: " 
				  << (int)finger << std::endl;
		
	}
    
    return 0;
}

bool getFingerForKeyPress(const char key, const std::unordered_map<char, cv::Vec2i>& keyPointMap,
	const ColourFingerMap& colourFingerMap,
	Finger* outFinger,
	VideoCapture& capture)
{
	cv::Mat frame;
	capture >> frame;

	return checkForCorrectFinger(colourFingerMap, key, keyPointMap, frame);
}

