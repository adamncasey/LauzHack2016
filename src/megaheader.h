#pragma once

#include "keyboard/Key.h"
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
    Finger finger;
    double distanceToDetectedColor = -1;
    
    bool operator<(const AlphaDisruptColourTransform &b) const {
        //needed since we don't ahve a reference in the calibration phase
        if(this->distanceToDetectedColor == -1) return sqrt(pow(this->hue,2) + pow(this->saturation, 2)) < sqrt(pow(b.hue,2) + pow(b.saturation, 2));
        return this->distanceToDetectedColor < b.distanceToDetectedColor;
    };

};





AlphaDisruptColourTransform getColourAtPoint(const cv::Vec2i& coords, cv::Mat image);

std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::map<AlphaDisruptColourTransform, Finger> calibrateColours(std::unordered_map<char, cv::Vec2d>, cv::Mat frame);




Finger getFinger(std::map<AlphaDisruptColourTransform, Finger>, char pressedKey, std::unordered_map<char, cv::Vec2i> keysToLocationMap);

Finger keyToFinger(keyboard::KeyNum keyNum);

Finger getFinger(std::map<AlphaDisruptColourTransform, Finger> colorToFingerMap, char pressedKey, std::unordered_map<char, cv::Vec2d> keysToLocationMap, cv::Mat image);

