 # LauzHack2016

Touch Typing Tutorial
=====================
Project Overview/Plan:
1. Read webcam data
2. Detect location of each key
    1. Light up key, detect that on the video
3. On key press:
    1. Get image of key as it was pressed
    1. Identify which finger it was that pressed it (Coloured finger nails?)

Build/Run Requirements
---------

 - Windows (x64)
 - Visual Studio 2015 setup for C++
    - Only VS 2015 has been tested, others may work
 - OpenCV installed as CMake dependency
   - See https://github.com/opencv/opencv
 - Logitech per-key LED keyboard.
   - Tested to work with the Logitech G810 Orion Spectrum
 - Webcam

Build Instructions
---------

1. `git clone` this repository
2. `mkdir build; cd build`
3. `cmake -G "Visual Studio 14 Win64" ..`
4. Open the generated Visual Studio Solution
5. Switch the active project to `main`
6. Build & run

Notes
-----
The webcam used in the project is hard coded to index 1. This is specified in `main.cpp`
