//#include <keyboard/Flasher.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <megaheader.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

using namespace cv;
using namespace std;



std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string alphabet)
{
	using namespace std::chrono_literals;

//	static const keyboard::DurationMs duration = 10;
//	keyboard::Flasher flasher;
//
//	std::this_thread::sleep_for(1s);

    Mat reference;
    reference = imread("/home/richard/projects/LauzHack2016/data/calibRef.png", CV_LOAD_IMAGE_COLOR);

    Mat referenceBw;
    cvtColor(reference,referenceBw, CV_RGB2GRAY);

    GaussianBlur(referenceBw,referenceBw,Size(3,3),0);


//	std::for_each(alphabet.begin(), alphabet.end(), [&](const char ch) {
//		keyboard::KeyNum key = ch;
//
//		flasher.flashKey(key, duration);
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(duration*2));

//        VideoCapture cap("/home/richard/projects/LauzHack2016/data/calib.mp4");

        Mat frame;
        frame = imread("/home/richard/projects/LauzHack2016/data/calibA.png", CV_LOAD_IMAGE_COLOR);

        Mat frameBw;
        cvtColor(frame,frameBw, CV_RGB2GRAY);

        GaussianBlur(frameBw,frameBw,Size(3,3),0);

        absdiff(frameBw, referenceBw, frameBw);

        threshold(frameBw, frameBw, THRESH_OTSU, 255, THRESH_BINARY);

        int morph_size = 2;
        Mat element = getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
        morphologyEx( frameBw, frameBw, MORPH_OPEN,  element);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours( frameBw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );


        vector<Moments> mu(contours.size() );
        for( int i = 0; i < contours.size(); i++ )
        { mu[i] = moments( contours[i], false ); }

        double cx, cy;
        cx = mu[0].m10 / mu[0].m00;
        cy = mu[0].m01 / mu[0].m00;

        cout << cx << " " << cy << endl;

        circle(frame, Point(cx,cy), 8, Scalar(255, 255, 255), 1, 8);

//        Mat labelImage(frameBw.size(), CV_16U);
//        int nLabels = connectedComponents(frameBw, labelImage, 8);

//        cout << sum(frameBw)[0] << endl;

        namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
        imshow( "Display window", frame );                   // Show our image inside it.
        waitKey();



//    });

	return std::unordered_map<char, cv::Vec2i>();
}


