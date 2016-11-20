#pragma once

#include <keyboard/Key.h>

#include <LogitechLEDLib.h>

namespace keyboard {

LogiLed::KeyName mapFromKeyNum(KeyNum key);

typedef int DurationMs;

class Flasher {
public:
	Flasher();
	virtual ~Flasher();

	void flashKey(KeyNum key, DurationMs duration);

	void setFingerMap();
	
};

}
