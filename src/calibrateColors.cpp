#include <megaheader.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

std::unordered_map<double, Finger> calibrateColours(std::unordered_map<char, cv::Vec2i>, cv::Mat frame){
    
    std::unordered_map<double, Finger> calibrationMap;
    std::map<char, Finger> calibrationKeys {{'a',Finger::SMALL_LEFT},{'a',Finger::SMALL_LEFT},{'s',Finger::RING_LEFT},{'d',Finger::MIDDLE_LEFT},{'f',Finger::POINTING_LEFT},{'j',Finger::POINTING_RIGHT},{'k',Finger::MIDDLE_RIGHT},{'l',Finger::RING_RIGHT},{';',Finger::SMALL_RIGHT}};
    double i = 0.0;
    for(std::map<char, Finger>::iterator it = calibrationKeys.begin(); it != calibrationKeys.end(); it++){
        double colour = 2.0+i;//getColourAtPoint((*keysToLocationMap.find(*it.first)), frame);
        calibrationMap.insert({colour, (*it).second});
        i +=1;
        std::cout << colour << " -> " << (int)(*it).second << (*it).first << std::endl;
    }
    
    return calibrationMap;
    
}
