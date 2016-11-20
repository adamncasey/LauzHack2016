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


std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string alphabet, cv::VideoCapture& capture)
{
	using namespace std::chrono_literals;

	keyboard::Flasher flasher;

	std::this_thread::sleep_for(1s);

	Mat frame;

	std::unordered_map<char, cv::Vec2i> result;
	std::for_each(alphabet.begin(), alphabet.end(), [&](const char ch) {

        // TODO: Turn Keyboard lights off here and wait a bit

		LogiLedSetLightingForKeyWithKeyName(keyboard::mapFromKeyNum(ch), 100, 100, 100);
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_LED));

        Mat reference;
        capture >> reference;

        Mat referenceBw;
        cvtColor(reference,referenceBw, CV_RGB2GRAY);
        GaussianBlur(referenceBw,referenceBw,Size(5,5),0);

		LogiLedSetLightingForKeyWithKeyName(keyboard::mapFromKeyNum(ch), 0, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_LED));

		int count = 0;
		while (true) {
			capture >> frame;

			Mat frameBw;
			Mat frameGray;
			cvtColor(frame, frameBw, CV_RGB2GRAY);
			frameBw.copyTo(frameGray);
			GaussianBlur(frameBw, frameBw, Size(5,5), 0);

			absdiff(frameBw, referenceBw, frameBw);
			threshold(frameBw, frameBw, THRESH_OTSU, 255, THRESH_BINARY);

			int morph_size = 1;
			Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
			morphologyEx(frameBw, frameBw, MORPH_OPEN, element);

			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			findContours(frameBw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

			if (contours.size() <= 0) {
				std::cout << "No contours found. retrying" << std::endl;
			}

			vector<Moments> mu(contours.size());

			std::vector<double> colorIntensities(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				cv::Mat temp;
				frameGray.copyTo(temp);
				temp.setTo(0);
				drawContours(temp, contours, i, 255, CV_FILLED);
				colorIntensities[i] = cv::mean(frameGray, temp)[0];
				std::cout << "Color intensity: " << i << " :" << colorIntensities[i] << std::endl;
				mu[i] = moments(contours[i], false);
			}

			int mode = std::distance(colorIntensities.begin(), std::max_element(colorIntensities.begin(), colorIntensities.end()));




/*if (mu.size() == 0 || ( mu.size() > 2 ) ) {
				std::cout << "mu zero" << std::endl;
				count++;
				continue;
			}

			std::sort(mu.begin(), mu.end(), [&](auto lval, auto rval) {
				return lval.m00 < rval.m00;
			});*/

			double cx, cy;
			cx = mu[mode].m10 / mu[mode].m00;
			cy = mu[mode].m01 / mu[mode].m00;

			cout << cx << " " << cy << "mu.size(): " << mu.size() << endl;

			circle(frame, Point(cx, cy), 8, Scalar(255, 255, 255), 1, 8);


			cout << "found key: " << ch << endl;
			result.insert(std::pair<char, cv::Vec2i>(ch, { (int)cx, (int)cy }));

			imshow("Display window", frame);
			waitKey(50);
			break;
		}

    });

	return result;
}


