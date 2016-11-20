#include <megaheader.h>

Finger keyToFinger(keyboard::KeyNum keyNum) {

    if(keyNum == 'q' || keyNum == 'a' || keyNum == 's') return Finger::SMALL_LEFT;
    if(keyNum == 'w' || keyNum == 's' || keyNum == 'x') return Finger::RING_LEFT;
    if(keyNum == 'e' || keyNum == 'd' || keyNum == 'c') return Finger::MIDDLE_LEFT;
    if(keyNum == 'r' || keyNum == 'f' || keyNum == 'v' || keyNum == 't' || keyNum == 'g' || keyNum == 'b') return Finger::POINTING_LEFT;
    if(keyNum == 'y' || keyNum == 'h' || keyNum == 'n' || keyNum == 'u' || keyNum == 'j' || keyNum == 'm') return Finger::POINTING_RIGHT;
    if(keyNum == 'i' || keyNum == 'k' || keyNum == ',') return Finger::MIDDLE_RIGHT;
    if(keyNum == 'o' || keyNum == 'l' ) return Finger::RING_RIGHT;
    if(keyNum == 'p') return Finger::SMALL_RIGHT;

}