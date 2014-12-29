//
//  MyObjects.cpp
//  3dAlbum
//
//  Created by Osama Attia on 9/21/14.
//  ogamal [at] iastate.edu
//

#ifndef MyObjects_h
#define MyObjects_h

#include <iostream>

// 3D Point
class Point3D {
public:
    // Point position
    GLfloat x, y, z;
    
    // Set values
    inline void Set(GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    GLfloat * Getv() {
        GLfloat vec3[3];
        vec3[0] = x;
        vec3[1] = y;
        vec3[2] = z;
        
        return &vec3[0];
    }
};

// 2D Point
class Point2D {
public:
    // Point position
    GLfloat x, y;
    
    // Set values
    inline void Set(GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
    }
    
    GLfloat * Getv() {
        GLfloat vec2[2];
        vec2[0] = x;
        vec2[1] = y;
        
        return &vec2[0];
    }
};

// Image
class Image {
public:
    // Image's path and name
    std::string filename;

    // Position
    Point3D pos;
    
    // Image width, height, and number of components
    int w, h, comp;
    
    // ID referencing to image as texture
    GLuint texture;
    
    // Set parameters
    inline void Set(int w, int h, int comp, GLuint texture) {
        this->w = w;
        this->h = h;
        this->comp = comp;
        this->texture = texture;
    }
};

#endif
