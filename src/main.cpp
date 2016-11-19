#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <unordered_map>

#include <megaheader.h>

using namespace cv;

char readKeyboardInput() {
	return 'a';
}

bool filterFingersForKey(const char key, const std::vector<Finger>& possible, Finger* output) {
	return false;
}

int main(int argc, char** argv)
{
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz:";
    std::unordered_map<char, cv::Vec2i> keysToLocationMap {{'a',cv::Vec2i(0,0)},{'a',cv::Vec2i(0,0)},{'s',cv::Vec2i(0,0)},{'d',cv::Vec2i(0,0)},{'f',cv::Vec2i(0,0)},{'j',cv::Vec2i(0,0)},{'k',cv::Vec2i(0,0)},{'l',cv::Vec2i(0,0)},{';',cv::Vec2i(0,0)}};
    cv::Mat frame;
    std::map<AlphaDisruptColourTransform, Finger> colourFingerMapping = calibrateColours(keysToLocationMap, frame);
    /*for(std::unordered_map<double, Finger>::iterator colourFingerIterator = colourFingerMapping.begin(); colourFingerIterator != colourFingerMapping.end(); colourFingerIterator++){
        std::cout << (*colourFingerIterator).first << " -> " << (int)(*colourFingerIterator).second << std::endl;
    }
	std::unordered_map<char, cv::Vec2i> keyPointMap = calibrateKeyboard(alphabet);

	typedef std::unordered_map<double, std::vector<Finger>> ColourFingerMap;
	ColourFingerMap colourFingerMap = calibrateColours(keyPointMap);

	while (true) {
		const char key = readKeyboardInput();

		std::unordered_map<char, cv::Vec2i>::const_iterator pointIt = keyPointMap.find(key);

		if (pointIt == keyPointMap.end()) {
			std::cout << "Unknown key pressed: " << key << std::endl;
			continue;
		}

		const cv::Vec2i point = pointIt->second;

		const double colour = getColourAtPoint(point);

		ColourFingerMap::const_iterator fingersIt = colourFingerMap.find(colour);

		if (fingersIt == colourFingerMap.end()) {
			std::cout << "Could not find finger for colour: " << colour << std::endl;
			continue;
		}

		const std::vector<Finger> possibleFingers = fingersIt->second;

		Finger finalFinger;

		if (!filterFingersForKey(key, possibleFingers, &finalFinger)) {
			std::cout << "Could not resolve fingers for key: " << key << ". Possible fingers: ";
			for_each(possibleFingers.begin(), possibleFingers.end(), [&](auto fng) {
				std::cout << (int)fng << " " << std::endl;
			});
		}
		
	}*/
    
    return 0;
}

// Not used
void davidStuff(int argc, char** argv) {
	// Default camera ID.
	int i = 0;

	if (argc > 1) {
		// Custom camera ID from argv.
		sscanf(argv[1], "%d", &i);
	}

	VideoCapture cap("/home/david/Desktop/LauzHack2016/data/WIN_20161119_13_30_14_Pro.mp4");
	cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
	if (!cap.isOpened()) {
		std::cout << "Failed to open camera." << std::endl;
		return;
	}


	for (;;) {

		Mat frame;
		cap >> frame; // get a new frame from camera
		imshow("frame", frame);

		if (waitKey(30) >= 0) break;
	}
}
