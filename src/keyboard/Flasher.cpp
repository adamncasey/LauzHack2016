#include <keyboard/Flasher.h>

#include <iostream>
#include <stdexcept>

namespace keyboard {

#ifdef _WIN32
#include <LogitechLEDLib.h>


	

namespace {
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
			case ':':
				return LogiLed::SEMICOLON;
		}
		
		return LogiLed::ESC;
	}
	
	static const int RED = 100;
	static const int GREEN = 0;
	static const int BLUE = 0;
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


#else

Flasher::Flasher() {
	std::cout << "Not initialising keyboard as not built for windows" << std::endl;
}
Flasher::~Flasher() {}
void Flasher::flashKey(KeyNum key, DurationMs duration) {
	
}


#endif
}
