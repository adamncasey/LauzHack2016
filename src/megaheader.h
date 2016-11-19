#pragma once

#include <string>
#include <unordered_map>

#include <opencv2/opencv.hpp>

enum class Finger
{
	SMALL,
	RING,
	MIDDLE,
	POINTING
};

cv::Vec2d getColourAtPoint(const cv::Vec2i& coords, cv::Mat image);
std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::unordered_map<double, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i>);
