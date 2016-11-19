#pragma once

#include <string>
#include <unordered_map>

#include <opencv2/opencv.hpp>

enum class Finger
{
	SMALL_LEFT,
	RING_LEFT,
	MIDDLE_LEFT,
	POINTING_LEFT,
    POINTING_RIGHT,
    MIDDLE_RIGHT,
    RING_RIGHT,
    SMALL_RIGHT
};


struct AlphaDisruptColourTransform{
    double hue;
    double saturation;
    char key;
    double distanceToDetectedColor;
    
    bool operator<(const AlphaDisruptColourTransform &b) const {
        return sqrt(pow(this->hue,2) + pow(this->saturation, 2)) < sqrt(pow(b.hue,2) + pow(b.saturation, 2));
    };

};

std::vector <char> leftKeyboardSide{'q','a','z','w','s','x','e','d','c','r','f','v','t','g','b'};
std::vector<char> rightKeyboardSide{'z','h','n','u','j','m','i','k','o','l','p',';'};


AlphaDisruptColourTransform getColourAtPoint(const cv::Vec2i& coords, cv::Mat image);

std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::map<AlphaDisruptColourTransform, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i>, cv::Mat frame);
Finger getFinger(std::map<AlphaDisruptColourTransform, Finger> colorToFingerMap, char pressedKey, std::unordered_map<char, cv::Vec2d> keysToLocationMap, cv::Mat image);
