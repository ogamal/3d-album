3d-album:
=========

- A minimalistic and clean 3D Album using OpenGL and C++.
- This project was intended to serve as a small course project for CprE 557 at ISU.
- XCode project file could be found in the ./build directory.
- You can use cmake to generate the project for QT. Make sure to change the data path "dirName variable" in "app.cpp".
- Currently, the project loads all PNGs in the data folder, but it could be changed easily to open any image type. Check the App::loadImages() function.

Usage:
======
- Click the keyboard keys '1', '2', or '3' to change view modes (first view mode is autoplay).
- Click and drag with mouse to change view angle.
- In view modes 2 and 3, click left/right keys to navigate between images.
- Click the keyboard key 'q' to quit application.

Screenshot:
===========

![Screenshot](https://raw.githubusercontent.com/ogamal/3d-album/master/Screen%20Shot%202014-12-29%20at%201.00.58%20AM.jpg)
