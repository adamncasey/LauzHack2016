#include <megaheader.h>
#include <unordered_map.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

std::unordered_map<double, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i> keysToLocationMap, cv::Mat frame){
    
    std::unordered_map<double, Finger> calibrationMap;
    std::map<char, Finger> calibrationKeys {{'a',SMALL_LEFT},{'a',SMALL_LEFT},{'s',RING_LEFT},{'d',MIDDLE_LEFT},{'f',POINTING_LEFT},{'j',POINTING_RIGHT},{'k',MIDDLE_RIGHT},{'l',RING_RIGHT},{';',SMALL_RIGHT}};
    for(std::map<char, Finger>::iterator it = calibrationKeys.begin(); it != calibrationKeys.end(); it++){
        double colour = 2.0;//getColourAtPoint((*keysToLocationMap.find(*it.first)), frame);
        calibrationMap.insert({colour, *it.second});
        
    }
    
    return calibrationMap;
    
}
