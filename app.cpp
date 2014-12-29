//
//  app.cpp
//  3dAlbum
//
//  Created by Osama Attia on 9/21/14.
//  ogamal [at] iastate.edu
//

#include "app.hpp"

// Use STB_Image for loading images
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"

using namespace std;

void recomputeFrame(int value);

App::App() {
}

App::~App() {
    images.clear();
}

void App::init() {
    // Init parameters
    currentImage = 0;
    prevImage = 1;
    mouseDown = false;
    viewAngle = 0;
    viewAngleDirection = 1;

    // Init animation parameters
    animBusy = false;
    lambda = 0.0;
    lambda_step = 0.05;
    
    // Set camera position
    camera.Set(0.0f, 0.0f, 10.0f);
    cameraTarget.Set(0.0f, 0.0f, 0.0f);
    
    // Init textures
    images.clear();
    loadImages();
    initTexture();

    // Init view
    initView(WINWIDTH, WINHEIGHT);
    
    // Init light
    initLight();
    
    // Set application to start in first view
    appState = App::ex1;
}

// Find images in the folder and add their names to images vector
void App::loadImages() {
    DIR *dir;
    string dirName = "data";
    string fname;
    struct dirent *ent;
    
    try {
        dir = opendir(dirName.c_str());
        if (!dir)
            throw(std::string("Failed to open textures folder (./data/)!"));
        
        while ((ent = readdir(dir)) != NULL) {
            string imgPath(dirName + "/" + ent->d_name);
            
            // Check image extension
            if(imgPath.substr(imgPath.find_last_of(".") + 1) == "png") {
                Image temp;
                temp.w = 0; temp.h = 0; temp.comp = 0; temp.filename = imgPath;
                images.push_back(temp);
            }
        }
        
        closedir (dir);
    } catch (std::string e) {
        cout << "Exception occurred: " << e << endl;
    }
    
}

// Open files in images vector, get their attributes, and load them as textures
void App::initTexture() {
    for (std::vector<Image>::iterator it = images.begin(); it != images.end(); ++it) {
        int w, h, comp;
        GLuint texture;
        unsigned char *image;
        
        try {
            // Open image file
            image = stbi_load(it->filename.c_str(), &w, &h, &comp, STBI_rgb_alpha);
            if (!image)
                throw(std::string("Failed to load texture"));
            
            // Enable textures
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            // Generate texture, allocate the memory and associate the texture with a variable
            glGenTextures(1, &texture);
            // Set the texture as active texture.
            glBindTexture(GL_TEXTURE_2D, texture);
            // Change the parameters of the texture
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            
            // Load the image as texture
            if (comp == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            } else if (comp == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            }
            
            // Save texture ID and parameters to use later
            it->Set(w, h, comp, texture);
            
            // Free image
            stbi_image_free(image);
        } catch (std::string e) {
            // Catch exception
            cout << "Exception occurred: " << e << endl;
        }
    }
    
    // List found images
    cout << "Found images:" << endl;
    for (std::vector<Image>::iterator it = images.begin(); it != images.end(); ++it) {
        cout << " " << it->comp << " " << it->w << "x" << it->h << " ./" << it->filename << endl;
    }
}

void App::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Draw my background
    drawBackground();
    
    // Enter modelview and load identity matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    // Animate
    if (animBusy == true && lambda < 1.0) {
        lambda += lambda_step;
    } else {
        animBusy = false;
        lambda = 0.0;
    }
    // Auto animate in Mode Ex3
    if (appState == ex1 && animBusy == false && currentImage < images.size() - 1) {
        animBusy = true;
        prevImage = currentImage;
        currentImage++;
    } else if (appState == ex1 && animBusy == false && currentImage == images.size() - 1) {
        animBusy = true;
        prevImage = currentImage;
        currentImage = 0;
    }
    
    // Choose view mode
    switch (appState) {
        case ex1:
            example1();
            break;
        case ex2:
            example2();
            break;
        case ex3:
            example3();
            break;
        default:
            appState = App::ex1;
            break;
    }
    
    // Draw axes (for guidance)
    //drawAxes();
    
    // Print current file info
    printImageInfo(currentImage);
    
    // Set timer
    glutTimerFunc(TIMER, recomputeFrame, 0);
    
    glutSwapBuffers();
}

void recomputeFrame(int value) {
    glutPostRedisplay();
}

void App::drawBackground() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    // Top color
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-20.0, 9.0, -10.0);
    glVertex3f(20.0, 9.0, -10.0);
    // Bottom color
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, -9.0f, -10.0);
    glVertex3f(-20.0, -9.0, -10.0);
    glEnd();
    glPopMatrix();
}

void App::example3() {
    
    // Camera position
    glLoadIdentity();
    gluLookAt(camera.x, camera.y, camera.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, 0.0, 1.0, 0.0);
    initLight();
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    // Enable Light0
    glEnable(GL_LIGHT0);
    
    // Enable depth
    glEnable(GL_DEPTH_TEST);
    
    // Camera, calcualte view angle
    glPushMatrix();
    glRotatef(viewAngle, 1.0, 0.0, 0.0);
    
    // Draw picture wall. Make sure to draw the current image first to avoid transparent reflection
    drawImage2(currentImage);
    for (int i = 0; i < images.size(); ++i) {
        if (i != currentImage)
            drawImage2(i);
    }
    
    glPopMatrix();
    
    // Disable Light0
    glDisable(GL_LIGHT1);
    
    // Disable the light
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void App::drawImage2(int i) {
    glPushMatrix();
    // Position picture in the wall
    glTranslatef(-currentImage*SPACING_H, 0, 0);
    glTranslatef(SPACING_H*i, 0, 0);
    
    // Image coordinates
    vector<Point3D> v(4);
    if (i == currentImage) {
        v[0].Set(-2.5, 2.5, 0.5);
        v[1].Set(2.5, 2.5, 0.5);
        v[2].Set(2.5, -2.5, 0.5);
        v[3].Set(-2.5, -2.5, 0.5);
    } else {
        v[0].Set(-2.0, 2.0, -0.5);
        v[1].Set(2.0, 2.0, -0.5);
        v[2].Set(2.0, -2.0, -0.5);
        v[3].Set(-2.0, -2.0, -0.5);
    }
    
    // Texture coordinates
    vector<Point2D> t(4);
    // Fix texture position if not a square image
    GLfloat diff = images[i].w - images[i].h;
    if (diff > 0) {
        GLfloat fix = diff / 2.0 / images[i].w;
        t[0].Set(fix, 0.0);
        t[1].Set(1.0 - fix, 0.0);
        t[2].Set(1.0 - fix, 1.0);
        t[3].Set(fix, 1.0);
    } else if (diff < 0) {
        GLfloat fix = diff / -2.0 / images[i].h;
        t[0].Set(0.0, fix);
        t[1].Set(1.0, fix);
        t[2].Set(1.0, 1.0 - fix);
        t[3].Set(0.0, 1.0 - fix);
    } else {
        t[0].Set(0.0, 0.0);
        t[1].Set(1.0, 0.0);
        t[2].Set(1.0, 1.0);
        t[3].Set(0.0, 1.0);
    }
    
    // Enable texture
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, images[i].texture);
    
    // Draw picture
    glBegin(GL_QUADS);
    glTexCoord2fv(t[0].Getv()); glVertex3fv(v[0].Getv());
    glTexCoord2fv(t[1].Getv()); glVertex3fv(v[1].Getv());
    glTexCoord2fv(t[2].Getv()); glVertex3fv(v[2].Getv());
    glTexCoord2fv(t[3].Getv()); glVertex3fv(v[3].Getv());
    glEnd();
    // Disable texture
    glDisable(GL_TEXTURE_2D);
    // Draw border
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glVertex3fv(v[0].Getv());
    glVertex3fv(v[1].Getv());
    glVertex3fv(v[2].Getv());
    glVertex3fv(v[3].Getv());
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Draw picture reflection
    glPushMatrix();
    // reflect scene
    glRotatef(180, 0.0, 0.0, 1.0);
    if (i == currentImage) {
        glTranslatef(0.0, 5.2, 0.0);
    } else {
        glTranslatef(0.0, 4.2, 0.0);
    }
    // Enable texture
    glEnable(GL_TEXTURE_2D);
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    // Draw reflected image
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor2);
    glTexCoord2fv(t[0].Getv()); glVertex3fv(v[0].Getv());
    glTexCoord2fv(t[1].Getv()); glVertex3fv(v[1].Getv());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glTexCoord2fv(t[2].Getv()); glVertex3fv(v[2].Getv());
    glTexCoord2fv(t[3].Getv()); glVertex3fv(v[3].Getv());
    glEnd();
    // Draw reflected border
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glVertex3fv(v[0].Getv());
    glVertex3fv(v[1].Getv());
    glVertex3fv(v[2].Getv());
    glVertex3fv(v[3].Getv());
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Disable transparency
    glDisable(GL_BLEND);
    glPopMatrix();
    
    // Disable texture
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void App::example2() {
    // Camera position
    glLoadIdentity();
    gluLookAt(camera.x, camera.y, camera.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, 0.0, 1.0, 0.0);
    initLight();
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    // Enable Light0
    glEnable(GL_LIGHT0);
    
    // Enable depth
    glEnable(GL_DEPTH_TEST);
    
    // Camera, calcualte view angle
    glPushMatrix();
    glRotatef(viewAngle, 1.0, 0.0, 0.0);
    
    // Draw picture wall. Make sure to draw the current image first to avoid transparent reflection
    drawImage1(currentImage);
    for (int i = 0; i < currentImage; ++i) {
        if (i != currentImage)
            drawImage1(i);
    }
    for (int i = images.size() - 1; i > currentImage ; --i) {
        if (i != currentImage)
            drawImage1(i);
    }
    
    glPopMatrix();
    
    // Disable Light0
    glDisable(GL_LIGHT1);
    
    // Disable Light0
    glDisable(GL_LIGHT1);
    
    // Disable the light
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

float interpolate(float x1, float x2, float lambda) {
    float y;
    
    if (x1 < x2)
        y = x1 + fabs(x2 - x1) * lambda;
    else
        y = x1 - fabs(x2 - x1) * lambda;
    
    return y;
}

void App::drawImage1(int i) {
    
    glPushMatrix();
    // Define image size
    GLfloat imgSize; // 2.0f for normal image, 2.5f for selected image
    if (i == currentImage) {
        imgSize = animBusy == true ? interpolate(2.0, 2.5, lambda) : 2.5f;
    } else if (i == prevImage) {
        imgSize = animBusy == true ? interpolate(2.5, 2.0, lambda) : 2.0f;
    } else {
        imgSize = 2.0f;
    }
    
    // Offset picture in the wall (X-axis)
    GLfloat offset, prev_offset;
    prev_offset = prevImage * SPACING_H / 2.0;
    offset = currentImage * SPACING_H / 2.0;
    if (animBusy == true) {
        glTranslatef(SPACING_H * i / 2.0 - interpolate(prev_offset, offset, lambda), 0, 0);
    } else {
        glTranslatef(SPACING_H * i / 2.0 - offset, 0, 0);
    }
    
    // Offset picture in the wall (Z-axis)
    GLfloat zoffset, prev_zoffset;
    if (i == currentImage) {
        zoffset = -1.0;
        prev_zoffset = -2.0-0.5*abs(i-prevImage-1);
    } else if (i == prevImage) {
        zoffset = -2.0-0.5*abs(i-currentImage-1);
        prev_zoffset = -1.0;
    } else {
        zoffset = -2.0-0.5*abs(i-currentImage-1);
        prev_zoffset = -2.0-0.5*abs(i-prevImage-1);
    }
    if (animBusy == true)
        zoffset = interpolate(prev_zoffset, zoffset, lambda);
    
    // Image coordinates
    vector<Point3D> v(4);
    v[0].Set(-imgSize, imgSize, zoffset);
    v[1].Set(imgSize, imgSize, zoffset);
    v[2].Set(imgSize, -imgSize, zoffset);
    v[3].Set(-imgSize, -imgSize, zoffset);
    
    // Rotate picture according to distance from current image
    GLfloat angle;
    if (i == currentImage && prevImage < currentImage)
        angle = animBusy == true ? interpolate(-20.0f, 0.0f, lambda) : 0.0f;
    else if (i == currentImage)
        angle = animBusy == true ? interpolate(20.0f, 0.0f, lambda) : 0.0f;
    else if (i == prevImage && prevImage < currentImage)
        angle = animBusy == true ? interpolate(0.0f, 20.0f, lambda) : 20.0f;
    else if (i == prevImage)
        angle = animBusy == true ? interpolate(0.0f, -20.0f, lambda) : -20.0f;
    else if (i < currentImage)
        angle = 20.0f;
    else
        angle = -20.0f;
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    
    // Texture coordinates
    vector<Point2D> t(4);
    // Fix texture position if not a square image
    GLfloat diff = images[i].w - images[i].h;
    if (diff > 0) {
        GLfloat fix = diff / 2.0 / images[i].w;
        t[0].Set(fix, 0.0);
        t[1].Set(1.0 - fix, 0.0);
        t[2].Set(1.0 - fix, 1.0);
        t[3].Set(fix, 1.0);
    } else if (diff < 0) {
        GLfloat fix = diff / -2.0 / images[i].h;
        t[0].Set(0.0, fix);
        t[1].Set(1.0, fix);
        t[2].Set(1.0, 1.0 - fix);
        t[3].Set(0.0, 1.0 - fix);
    } else {
        t[0].Set(0.0, 0.0);
        t[1].Set(1.0, 0.0);
        t[2].Set(1.0, 1.0);
        t[3].Set(0.0, 1.0);
    }
    
    // Enable texture
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, images[i].texture);
    
    // Draw picture
    glBegin(GL_QUADS);
    glTexCoord2fv(t[0].Getv()); glVertex3fv(v[0].Getv());
    glTexCoord2fv(t[1].Getv()); glVertex3fv(v[1].Getv());
    glTexCoord2fv(t[2].Getv()); glVertex3fv(v[2].Getv());
    glTexCoord2fv(t[3].Getv()); glVertex3fv(v[3].Getv());
    glEnd();
    // Disable texture
    glDisable(GL_TEXTURE_2D);
    // Draw border
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glVertex3fv(v[0].Getv());
    glVertex3fv(v[1].Getv());
    glVertex3fv(v[2].Getv());
    glVertex3fv(v[3].Getv());
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Draw picture reflection
    glPushMatrix();
    // reflect scene
    glRotatef(180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, imgSize * 2.0f + 0.2f, 0.0);

    // Enable texture
    glEnable(GL_TEXTURE_2D);
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    // Draw reflected image
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor2);
    glTexCoord2fv(t[0].Getv()); glVertex3fv(v[0].Getv());
    glTexCoord2fv(t[1].Getv()); glVertex3fv(v[1].Getv());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glTexCoord2fv(t[2].Getv()); glVertex3fv(v[2].Getv());
    glTexCoord2fv(t[3].Getv()); glVertex3fv(v[3].Getv());
    glEnd();
    // Draw reflected border
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myReflectionColor1);
    glVertex3fv(v[0].Getv());
    glVertex3fv(v[1].Getv());
    glVertex3fv(v[2].Getv());
    glVertex3fv(v[3].Getv());
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Disable transparency
    glDisable(GL_BLEND);
    glPopMatrix();
    
    // Disable texture
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void App::example1() {
    // Camera position
    glLoadIdentity();
    gluLookAt(camera.x, camera.y, camera.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, 0.0, 1.0, 0.0);
    initLight();
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    // Enable Light0
    glEnable(GL_LIGHT0);
    
    // Enable depth
    glEnable(GL_DEPTH_TEST);
    
    // Camera, calcualte view angle
    glPushMatrix();
    glRotatef(viewAngle, 1.0, 0.0, 0.0);
    
    // Draw picture wall. Make sure to draw the current image first to avoid transparent reflection
    drawImage1(currentImage);
    for (int i = 0; i < currentImage; ++i) {
        if (i != currentImage)
            drawImage1(i);
    }
    for (int i = images.size() - 1; i > currentImage ; --i) {
        if (i != currentImage)
            drawImage1(i);
    }
    
    glPopMatrix();
    
    // Disable Light0
    glDisable(GL_LIGHT1);
    
    // Disable Light0
    glDisable(GL_LIGHT1);
    
    // Disable the light
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void App::initLight() {
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    // Set the shading model
    glShadeModel(GL_SMOOTH);
    
    // Enable the depht test
    glEnable(GL_DEPTH_TEST);
    
    // Setup a direct light 0
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {5.0, 15.0, 25.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    
    // Setup a direct light 1
    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light1_position[] = {-10.0, 10.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    
    // Disable lighting
    glDisable(GL_LIGHTING);
}

void App::initView(int width, int height) {
    float ratio = 1.0 * width / height;
    
    // Set viewport to be the entire window
    glViewport(0, 0, (GLint)width, (GLint)height);
    // Switch to the projection matrix mode
    glMatrixMode(GL_PROJECTION);
    // Load an identity matrix
    glLoadIdentity();
    // Set the correct perspective.
    gluPerspective(45.0, ratio, 0.01f, 1000.0f);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    // load an identity matrix
    glLoadIdentity();
    
    glutPostRedisplay();
}

void App::drawAxes() {
    float tip = 0;
    float turn = 0;
    float ORG[3] = {0, 0, 0};
    float XP[3] = {2, 0, 0};
    float YP[3] = {0, 2, 0};
    float ZP[3] = {0, 0, 2};
    
    glPushMatrix();
    glTranslatef(5.5f, -3.2f, 1.2f);
    glRotatef(tip, 1.0f, 0.0f, 0.0f);
    glRotatef(turn, 0.0f, 1.0f, 0.0f);
    glScalef(0.25f, 0.25f, 0.25f);
    
    glLineWidth(2.0);
    
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X axis is red.
    glVertex3fv(ORG);
    glVertex3fv(XP);
    glColor3f(0.0f, 1.0f, 0.0f); // Y axis is green.
    glVertex3fv(ORG);
    glVertex3fv(YP);
    glColor3f(0.0f, 0.0f, 1.0f); // z axis is blue.
    glVertex3fv(ORG);
    glVertex3fv(ZP);
    glEnd();
    
    glPopMatrix();
}

std::string intToString (int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

void App::printImageInfo(int i) {
    int w, h;
    string temp;
    vector<string> lines;
    
    // Construct image info
    temp = string("Image number: ") + intToString(i+1) + " out of " + intToString(images.size());
    lines.push_back(temp);
    temp = string("Filename: ./") + images[i].filename;
    lines.push_back(temp);
    w = images[i].w;
    h = images[i].h;
    temp = string("Dimensions: ") + intToString(w) + " x " + intToString(h);
    lines.push_back(temp);
    temp = string("Click keys '1, 2, or 3' to switch views, 'q' to quit, and click/drag mouse for angle");
    lines.push_back(temp);
    
    // Draw image info
    drawText(lines, -6.2f, -3.0f, 1.1f);
}

void App::drawText(vector<string> lines, GLfloat x, GLfloat y, GLfloat z) {
    
    glPushMatrix();
    glColor4fv(textColor);
    // For each line
    for (string& line : lines) {
        // Set start position
        glRasterPos3f(x, y, z);
        // For each character
        for(char &c : line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
        // Move to new line
        y = y - LINE_SPACING;
    }
    glPopMatrix();
}

void App::reshape(int width, int height) {
    
    // force minimum height
    if (height < WIN_MIN_HEIGHT) {
        height = WIN_MIN_HEIGHT;
        glutReshapeWindow(width, height);
    }
    // force minimum width
    if (width < WIN_MIN_WIDTH) {
        width = WIN_MIN_WIDTH;
        glutReshapeWindow(width, height);
    }
    
    initView(width, height);
}

void App::mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        mouseDownPos.Set(x, y);
        cout << "Mouse down: " << x << ", " << y << endl;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseDown = false;
        cout << "Mouse up: " << x << ", " << y << endl;
    }
    
    // Force redraw
    glutPostRedisplay();
}


void App::mouseMove(int x, int y) {
    // Force redraw
    GLfloat diff = (y - mouseDownPos.y) / 10.0;
    if (mouseDown == true && diff > 0 && diff < 30) {
        viewAngle = diff * M_PI;
    } else if (mouseDown == true && diff < 0 && diff > -30) {
        viewAngle = diff * M_PI;
    } else {
        viewAngle = 0.0f;
    }
    glutPostRedisplay();
}

void App::mousePassiveMove(int x, int y) {
    // Force redraw
    glutPostRedisplay();
}

void App::keyStroke(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0); // Exit
            break;
        case '1':
            appState = App::ex1;
            break;
        case '2':
            appState = App::ex2;
            break;
        case '3':
            appState = App::ex3;
            break;
        case 27: // Esc button
            exit(0);
            break;
        default:
            break;
    }
}

void App::specialKeyPos(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_LEFT:
            if (currentImage > 0 && animBusy == false) {
                animBusy = true;
                prevImage = currentImage;
                currentImage--;
            } else if (currentImage <= 0 && animBusy == false) {
                animBusy = true;
                prevImage = currentImage;
                currentImage = images.size() - 1;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (currentImage < images.size() - 1 && animBusy == false) {
                animBusy = true;
                prevImage = currentImage;
                currentImage++;
            } else if (currentImage >= images.size() - 1 && animBusy == false) {
                animBusy = true;
                prevImage = currentImage;
                currentImage = 0;
            }
            break;
        default:
            break;
    }
}
