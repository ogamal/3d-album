//
//  main.cpp
//  3dAlbum
//
//  Created by Osama Attia on 9/21/14.
//  ogamal [at] iastate.edu
//

#include <iostream>
#include <assert.h>
#include <math.h>
#include <vector>
#include <iostream>

#if defined(__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
	#include "glut.h"
    #include <windows.h>
    #include <gl/gl.h>
    #include <gl/glu.h>
    #include <gl/glut.h>
#endif

#include "app.hpp"

//// Use STB_Image for loading images
//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_ASSERT(x)
//#include "stb_image.h"

App myApp;

// Define the display function
void myDisplay() {
    myApp.display();
}

// Define the reshape function
void myReshape(int width, int height) {
    myApp.reshape(width, height);
}

// Define the mouse click events
void myMouseClick(int button, int state, int x, int y) {
    myApp.mouseClick(button, state, x, y);
}

// Define the mouse drag events
void myMouseMove(int x, int y) {
    myApp.mouseMove(x, y);
}

// Define the mouse drag events
void myMousePassiveMove(int x, int y) {
    myApp.mousePassiveMove(x, y);
}

// Define keystroke events
void myKeyStroke(unsigned char key, int x, int y) {
    myApp.keyStroke(key, x, y);
}

void mySpecialKeyStroke(int key, int x, int y) {
    myApp.specialKeyPos(key, x, y);
}

// The main function here
int main(int argc, char ** argv) {
    // Init display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);

    // Init glut
    glutInit(&argc, argv);
    
	// Init window size, position, title
	glutInitWindowSize(WINWIDTH, WINHEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(WINTITLE);
    
	// Init game
    myApp.init();

	// Draw scene
	glutDisplayFunc(myDisplay);
	// Handle reshape
	glutReshapeFunc(myReshape);
	// Handle mouse clicks
	glutMouseFunc(myMouseClick);
	// Handle mouse motion
    glutMotionFunc(myMouseMove);
    glutPassiveMotionFunc(myMousePassiveMove);
	// Handle keyboard strokes
	glutKeyboardFunc(myKeyStroke);
	// specify keyboard special key input events
	glutSpecialFunc(mySpecialKeyStroke);
	// Enter the opengl event processing loop
	glutMainLoop();

	return 0;
}
