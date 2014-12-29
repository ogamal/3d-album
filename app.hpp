//
//  app.hpp
//  3dAlbum
//
//  Created by Osama Attia on 9/21/14.
//  ogamal [at] iastate.edu
//

#ifndef APP_h
#define APP_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <windows.h>
    #include <gl/gl.h>
    #include <gl/glu.h>
    #include <gl/glut.h>
#endif

#include "config.h"         // App configurations
#include "MyObjects.h"      // My custom objects, classes, structs

#include <sys/types.h>
#include <dirent.h>         // Load files from directory

class App {
public:
    // Class Constructor/Destructor
    App();
    ~App();
    
    // Public functions (handle GLUT calls)
    void display(void);
    void init(void);
    void reshape(int width, int height);
    void mouseClick(int button, int state, int x, int y);
    void mouseMove(int x, int y);
    void mousePassiveMove(int x, int y);
    void keyStroke(unsigned char key, int x, int y);
    void specialKeyPos(int key, int x, int y);
    
private:
    // App state
    bool animBusy;
    bool mouseDown;
    Point2D mouseDownPos;
    enum State {ex1, ex2, ex3, ex4, ex5};
    App::State appState;
    
    // Camera position
    Point3D camera;
    Point3D cameraTarget;
    
    // Current view settings
    int currentImage;
    int prevImage;
    GLfloat viewAngle;
    int viewAngleDirection;
    
    // Images/Textures storage
    std::vector <Image> images;
    
    // Animation parameters
    double lambda;
    double lambda_step;
    
    // Private functions
    void loadImages(void);
    void initTexture(void);
    void initView(int width, int height);
    void initLight(void);
    void drawBackground(void);
    void example1(void);
    void drawImage1(int);
    void example2(void);
    void drawImage2(int);
    void example3(void);
    void drawImage3(int);
    void example4(void);
    void example5(void);
    void drawAxes(void);
    void printImageInfo(int i);
    void drawText(std::vector<std::string> lines, GLfloat x, GLfloat y, GLfloat z);
};
#endif

