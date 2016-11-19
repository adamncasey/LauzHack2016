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

double getColourAtPoint(const cv::Vec2i& coords);
std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string keys);
std::unordered_map<double, std::vector<Finger>> calibrateColours(std::unordered_map<char, cv::Vec2i>);
