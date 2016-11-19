#include <megaheader.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

std::map<AlphaDisruptColourTransform, Finger> calibrateColours(std::unordered_map<char, cv::Vec2d> keysToLocationMap, cv::Mat frame){
    
    std::map<AlphaDisruptColourTransform, Finger> calibrationMap;
    std::map<char, Finger> calibrationKeys {{'a',Finger::SMALL_LEFT},{'a',Finger::SMALL_LEFT},{'s',Finger::RING_LEFT},{'d',Finger::MIDDLE_LEFT},{'f',Finger::POINTING_LEFT},{'j',Finger::POINTING_RIGHT},{'k',Finger::MIDDLE_RIGHT},{'l',Finger::RING_RIGHT},{';',Finger::SMALL_RIGHT}};
    double i = 0.0;
    
    for(std::map<char, Finger>::iterator it = calibrationKeys.begin(); it != calibrationKeys.end(); it++){
        AlphaDisruptColourTransform colour {
            2+i,
            3,
            (*it).first
        };//getColourAtPoint((*keysToLocationMap.find(*it.first)), frame);
        calibrationMap.insert({colour, (*it).second});
        i +=1;
        std::cout << colour.hue << " -> " << (int)(*it).second << (*it).first << std::endl;
    }
    
    return calibrationMap;
    
}


Finger getFinger(std::map<AlphaDisruptColourTransform, Finger> colorToFingerMap, char pressedKey, std::unordered_map<char, cv::Vec2d> keysToLocationMap, cv::Mat image){
    cv::Vec2d coords = keysToLocationMap.find(pressedKey)->second;
    AlphaDisruptColourTransform colour = getColourAtPoint(coords, image);
    std::map<AlphaDisruptColourTransform, Finger> smallestTwoValues;
    for(std::map<AlphaDisruptColourTransform, Finger>::iterator it = colorToFingerMap.begin(); it != colorToFingerMap.end(); it++){
        it->first.distanceToDetectedColor = sqrt(pow(*it->first.hue - colour.hue, 2) + pow(*it->first.saturation- colour.saturation,2));
        if(smallestTwoValues.size < 2){
            smallestTwoValues.insert(*it);
        }else{
            std::map<AlphaDisruptColourTransform, Finger>::iterator toDelete;
            bool errorIsSmaller = false;
            for(std::map<AlphaDisruptColourTransform, Finger>::iterator innerIt = smallestTwoValues.begin(); innerIt != smallestTwoValues.end(); innerIt++){
                toDelete = innerIt;
                if(*it.distanceToDetectedColor < innerIt->first.distanceToDetectedColor){
                    errorIsSmaller = true;
                    break;
                }
                
            }
            if(errorIsSmaller){
                smallestTwoValues.erase(toDelete);
                smallestTwoValues.insert(*it);
            }
        }
        
    }
    bool isLeftSide = std::find(leftKeyboardSide.begin(),leftKeyboardSide.end(), pressedKey) != leftKeyboardSide.end();
    if(isLeftSide){
        for(std::map<AlphaDisruptColourTransform, Finger>::iterator innerIt = smallestTwoValues.begin(); innerIt != smallestTwoValues.end(); innerIt++){
            if(std::find(leftKeyboardSide.begin(), leftKeyboardSide.end(), innerIt->first.key) != leftKeyboardSide.end()){
                return innerIt->second;
            }
        }
    }else{
        for(std::map<AlphaDisruptColourTransform, Finger>::iterator innerIt = smallestTwoValues.begin(); innerIt != smallestTwoValues.end(); innerIt++){
            if(std::find(rightKeyboardSide.begin(), rightKeyboardSide.end(), innerIt->first.key) != rightKeyboardSide.end()){
                return innerIt->second;
            }
        }
    }
    
}

