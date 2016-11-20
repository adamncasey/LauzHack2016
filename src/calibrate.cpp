#include <keyboard/Flasher.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <megaheader.h>

#include <LogitechLEDLib.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

#include <keyboard/Flasher.h>

using namespace cv;
using namespace std;

static const int WAIT_FOR_LED = 150;


std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string alphabet)
{
	using namespace std::chrono_literals;

	keyboard::Flasher flasher;

	std::this_thread::sleep_for(1s);

//    Mat reference;
//    reference = imread("/home/richard/projects/LauzHack2016/data/calibRef.png", CV_LOAD_IMAGE_COLOR);

	VideoCapture cap(1);

	Mat frame;
	for (int i = 0; i < 20; i++) {
		cap >> frame;
	}

	std::unordered_map<char, cv::Vec2i> result;
	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	std::for_each(alphabet.begin(), alphabet.end(), [&](const char ch) {

        // TODO: Turn Keyboard lights off here and wait a bit

		LogiLedSetLightingForKeyWithKeyName(keyboard::mapFromKeyNum(ch), 100, 100, 100);
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_LED));

        Mat reference;
        cap >> reference;

        Mat referenceBw;
        cvtColor(reference,referenceBw, CV_RGB2GRAY);
        GaussianBlur(referenceBw,referenceBw,Size(3,3),0);

		LogiLedSetLightingForKeyWithKeyName(keyboard::mapFromKeyNum(ch), 0, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_LED));

		while (true) {
			cap >> frame;

			Mat frameBw;
			cvtColor(frame, frameBw, CV_RGB2GRAY);
			GaussianBlur(frameBw, frameBw, Size(3, 3), 0);

			absdiff(frameBw, referenceBw, frameBw);
			threshold(frameBw, frameBw, THRESH_OTSU, 255, THRESH_BINARY);

			int morph_size = 2;
			Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
			morphologyEx(frameBw, frameBw, MORPH_OPEN, element);

			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			findContours(frameBw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

			vector<Moments> mu(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				mu[i] = moments(contours[i], false);
			}

			if (mu.size() <= 0) {
				std::cout << "mu zero" << std::endl;
				continue;
			}

			double cx, cy;
			cx = mu[0].m10 / mu[0].m00;
			cy = mu[0].m01 / mu[0].m00;

			cout << cx << " " << cy << "mu.size(): " << mu.size() << endl;

			circle(frame, Point(cx, cy), 8, Scalar(255, 255, 255), 1, 8);



			// TODO write position to output here

			cout << "found key: " << ch << endl;
			result.insert(std::pair<char, cv::Vec2i>(ch, { (int)cx, (int)cy }));

			imshow("Display window", frame);
			waitKey(50);
			/*imshow("Display window", reference);
			waitKey();*/
			break;
		}

    });

	waitKey();
	return result;
}


