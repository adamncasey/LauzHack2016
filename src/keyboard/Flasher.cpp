#include <keyboard/Flasher.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef _WIN32
#include <LogitechLEDLib.h>	
#endif

namespace keyboard {

#ifdef _WIN32

	LogiLed::KeyName mapFromKeyNum(KeyNum key) {
		switch(key) {
			case 'a':
				return LogiLed::A;
			case 'b':
				return LogiLed::B;
			case 'c':
				return LogiLed::C;
			case 'd':
				return LogiLed::D;
			case 'e':
				return LogiLed::E;
			case 'f':
				return LogiLed::F;
			case 'g':
				return LogiLed::G;
			case 'h':
				return LogiLed::H;
			case 'i':
				return LogiLed::I;
			case 'j':
				return LogiLed::J;
			case 'k':
				return LogiLed::K;
			case 'l':
				return LogiLed::L;
			case 'm':
				return LogiLed::M;
			case 'n':
				return LogiLed::N;
			case 'o':
				return LogiLed::O;
			case 'p':
				return LogiLed::P;
			case 'q':
				return LogiLed::Q;
			case 'r':
				return LogiLed::R;
			case 's':
				return LogiLed::S;
			case 't':
				return LogiLed::T;
			case 'u':
				return LogiLed::U;
			case 'v':
				return LogiLed::V;
			case 'w':
				return LogiLed::W;
			case 'x':
				return LogiLed::X;
			case 'y':
				return LogiLed::Y;
			case 'z':
				return LogiLed::Z;
			case ';':
				return LogiLed::SEMICOLON;
		}
		
		return LogiLed::ESC;
	}
namespace {
	
	void setLightingForKeys(std::vector<LogiLed::KeyName>& keyName, int redPercentage, int greenPercentage, int bluePercentage) {
	    for(LogiLed::KeyName key:keyName) {
	        LogiLedSetLightingForKeyWithKeyName(key, redPercentage, greenPercentage, bluePercentage);
	    }
	}
	static const int RED = 100;
	static const int GREEN = 100;
	static const int BLUE = 100;
}

Flasher::Flasher() {
	if(!LogiLedInit()) {
		throw std::runtime_error("Unable to initialise logitech library");
	}
	std::cout << "Initialised logitech LED" << std::endl;
}

Flasher::~Flasher() {
	LogiLedShutdown();
}

void Flasher::flashKey(KeyNum key, DurationMs duration) {
	LogiLed::KeyName logitechKey = mapFromKeyNum(key);
	
	LogiLedFlashSingleKey(logitechKey, RED, GREEN, BLUE, duration, duration/2);
	
	std::cout << "flashed " << key << " for " << duration << " ms" << std::endl;
}

void Flasher::setFingerMap() {

    std::vector<LogiLed::KeyName> keyVec;

    keyVec.push_back(mapFromKeyNum('q'));
    keyVec.push_back(mapFromKeyNum('a'));
    keyVec.push_back(mapFromKeyNum('z'));
    setLightingForKeys(keyVec,100,0,0);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('w'));
    keyVec.push_back(mapFromKeyNum('s'));
    keyVec.push_back(mapFromKeyNum('x'));
    setLightingForKeys(keyVec,0,100,0);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('e'));
    keyVec.push_back(mapFromKeyNum('d'));
    keyVec.push_back(mapFromKeyNum('c'));
    setLightingForKeys(keyVec,0,0,100);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('r'));
    keyVec.push_back(mapFromKeyNum('f'));
    keyVec.push_back(mapFromKeyNum('v'));
    keyVec.push_back(mapFromKeyNum('t'));
    keyVec.push_back(mapFromKeyNum('g'));
    keyVec.push_back(mapFromKeyNum('b'));
    setLightingForKeys(keyVec,100,100,100);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('y'));
    keyVec.push_back(mapFromKeyNum('h'));
    keyVec.push_back(mapFromKeyNum('n'));
    keyVec.push_back(mapFromKeyNum('u'));
    keyVec.push_back(mapFromKeyNum('j'));
    keyVec.push_back(mapFromKeyNum('m'));
    setLightingForKeys(keyVec,100,50,0);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('i'));
    keyVec.push_back(mapFromKeyNum('k'));
    setLightingForKeys(keyVec,50,0,50);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('o'));
    keyVec.push_back(mapFromKeyNum('l'));
    setLightingForKeys(keyVec,0,50,50);
    keyVec.clear();

    keyVec.push_back(mapFromKeyNum('p'));
    setLightingForKeys(keyVec,50,50,0);
    keyVec.clear();

}

#else

Flasher::Flasher() {
	std::cout << "Not initialising keyboard as not built for windows" << std::endl;
}
Flasher::~Flasher() {}
void Flasher::flashKey(KeyNum key, DurationMs duration) {
	
}


#endif
}
