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
    bool operator<(const AlphaDisruptColourTransform &b) const {
        return sqrt(pow(this->hue,2) + pow(this->saturation, 2)) < sqrt(pow(b.hue,2) + pow(b.saturation, 2));
    };

};



cv::Vec2d getColourAtPoint(const cv::Vec2i& coords, cv::Mat image);

std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::map<AlphaDisruptColourTransform, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i>, cv::Mat frame);
Finger getFinger(std::map<AlphaDisruptColourTransform, Finger>, char pressedKey, std::unordered_map<char, cv::Vec2i> keysToLocationMap);
