//
//  config.h
//  3dAlbum
//
//  Created by Osama Attia on 9/21/14.
//  ogamal [at] iastate.edu
//

#ifndef config_h
#define config_h

// Force Redraw timer
#define TIMER 16.6          // 60 frame per second

// Window settings
#define WINTITLE "3D Album ~ By Osama Attia"
const int WINWIDTH  = 1024;
const int WINHEIGHT = 600;
const int WIN_MIN_WIDTH  = 300;
const int WIN_MIN_HEIGHT = 300;

// Background colors
const GLfloat bgColor1[] = {0.8f, 0.8f, 0.8f};
const GLfloat bgColor2[] = {1.0f, 1.0f, 1.0f};

// Colors
const GLfloat blueColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
const GLfloat redColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
const GLfloat greenColor[] = {0.0f, 1.0f, 0.0f, 1.0f};
const GLfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat blackColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat yellowColor[] = {1.0f, 1.0f, 0.0f, 1.0f};

// Transparent color that I use in making reflections
const GLfloat myReflectionColor1[] = {0.7f, 0.7f, 0.7f, 0.2f};
const GLfloat myReflectionColor2[] = {1.0f, 1.0f, 1.0f, 0.0f};

// Image spacing
const GLfloat SPACING_H = 4.3f;

// Drawing text parameters
const GLfloat textColor[] = {0.6f, 0.6f, 0.6f, 0.2f};
const GLfloat LINE_SPACING = 0.2f;

// Other
const int CIRCLE_SEGMENTS = 50;
const double tile_size = 1.2;

#endif
