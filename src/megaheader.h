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

double getColourAtPoint(const cv::Vec2i& coords);
std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::unordered_map<double, std::vector<Finger>> calibrateColours(std::unordered_map<char, cv::Vec2i>);
