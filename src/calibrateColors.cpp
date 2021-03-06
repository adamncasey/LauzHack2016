#include <megaheader.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

std::map<AlphaDisruptColourTransform, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i> keysToLocationMap, cv::Mat frame){
    
    std::map<AlphaDisruptColourTransform, Finger> calibrationMap;
    std::map<char, Finger> calibrationKeys {{'a',Finger::SMALL_LEFT},{'w',Finger::RING_LEFT},{'e',Finger::MIDDLE_LEFT},{'f',Finger::POINTING_LEFT},{'j',Finger::POINTING_RIGHT},{'i',Finger::MIDDLE_RIGHT},{'o',Finger::RING_RIGHT},{';',Finger::SMALL_RIGHT}};
	cv::Mat debugCopy;
	frame.copyTo(debugCopy);
    
    for(auto&& entry : calibrationKeys) {
		AlphaDisruptColourTransform colour = getColourAtPoint(keysToLocationMap[entry.first], frame);
		cv::circle(debugCopy, keysToLocationMap[entry.first], 100, cv::Scalar(255, 0, 0), 10);
        calibrationMap.insert({colour, entry.second});
        std::cout << colour.hue << " -> " << (int)entry.second << entry.first << std::endl;
    }
	//cv::imshow("debug", debugCopy);
    return calibrationMap;
    
}

bool checkForCorrectFinger(std::map<AlphaDisruptColourTransform, Finger> colorToFingerMap, char pressedKey, std::unordered_map<char, cv::Vec2i> keysToLocationMap, cv::Mat image) {
    
	std::unordered_map<char, cv::Vec2i>::const_iterator it = keysToLocationMap.find(pressedKey);

	if (it == keysToLocationMap.end()) {
		std::cout << "Unknown key pressed" << std::endl;
		return false;
	}

	cv::Vec2d coords = it->second;
	AlphaDisruptColourTransform colour = getColourAtPoint(coords, image);

    std::vector<AlphaDisruptColourTransform> orderedValues;

    for(std::map<AlphaDisruptColourTransform, Finger>::iterator it = colorToFingerMap.begin(); it != colorToFingerMap.end(); it++){
        double distanceToDetectedColor = sqrt(pow(it->first.hue - colour.hue, 2) + pow(it->first.saturation- colour.saturation,2));
		AlphaDisruptColourTransform colorTransform;
		colorTransform.hue = it->first.hue;
		colorTransform.saturation = it->first.saturation;
		colorTransform.key = it->first.key;
		colorTransform.finger = it->second;
		colorTransform.distanceToDetectedColor = distanceToDetectedColor;

        orderedValues.push_back(colorTransform);
    }
    
    std::sort(orderedValues.begin(), orderedValues.end());
    
    /*for(std::vector<AlphaDisruptColourTransform>::iterator it = orderedValues.begin(); it != orderedValues.end(); it++){
        std::cout << "Hue:" << it->hue << " Saturation:" << it->saturation << " key:" << it->key << " finger:" << (int)it->finger << " distanceToReference: " <<it->distanceToDetectedColor << std::endl;
    }*/
    Finger correctFinger = keyToFinger(pressedKey);
    //std::cout << "Correct Finger: " << (int) correctFinger << " Finger suggestion one: " << (int) orderedValues[0].finger << " Finger suggestion two: " << (int) orderedValues[1].finger << std::endl;
    return correctFinger == orderedValues[0].finger || correctFinger == orderedValues[1].finger;    
}

