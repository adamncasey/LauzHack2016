#include <megaheader.h>

AlphaDisruptColourTransform getColourAtPoint(const cv::Vec2i& coords, cv::Mat image) {

    cv::Mat imageHSV;
    cvtColor(image,imageHSV,CV_BGR2HSV);

    double hue = 0;
    double sat = 0;
    int idx = 0;
    int kernelSize = 8;
    for(int i = -kernelSize/2; i < kernelSize/2; i++) {
        for(int j = -4; j < 5; j++) {
            hue += (double)imageHSV.at<cv::Vec3b>(coords[1] + i ,coords[0] + j)[0];
            sat += (double)imageHSV.at<cv::Vec3b>(coords[1] + i ,coords[0] + j)[1];
            idx++;
        }
    }

    hue = hue/idx;
    sat = sat/idx;

    AlphaDisruptColourTransform colour = {hue,sat};
    return colour;

}
