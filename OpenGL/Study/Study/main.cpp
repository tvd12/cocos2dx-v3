#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "hw5.h"

using namespace std;

#define MIN_LINEAR 0
#define MIN_NEAREST 1
#define MAG_LINEAR 2
#define MAG_NEAREST 3
#define S_REPEAT 4
#define S_CLAMP 5
#define T_REPEAT 6
#define T_CLAMP 7
#define ENV_MODULATE 8
#define ENV_REPLACE 9

static int minFilter = GL_LINEAR;
static int magFilter = GL_LINEAR;
static int wrapS = GL_REPEAT;
static int wrapT = GL_REPEAT;
static int envMode = GL_MODULATE;

void menuCallback(int);
void setCamera(void);
void drawScene(void);

static int win = 0;
static GLfloat whiteLight[3] = {1.0f, 1.0f, 1.0f};
static GLfloat greenLight[3] = {0.0f, 1.0f, 0.0f};
static GLfloat lightPosition[4] = {0.0f, 0.0f, 0.0f, 1.0f};
static GLuint teaTex;

void loadTextures()
{
    generate_texture();
    
    glGenTextures(2, &teaTex);
    glBindTexture(GL_TEXTURE_2D, teaTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, envMode);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPopMatrix();
    
    setCamera();
    
    drawScene();
    
    glutSwapBuffers();
}

void drawScene()
{
    // Draw Teapot
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, greenLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidTeapot(1.0f);
    glPopMatrix();
    
    // Draw Floor
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(2.0f, 0.0f, -2.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(-2.0f, 0.0f, -2.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f);
    glEnd();
    glPopMatrix();
}

void idle()
{
    glutPostRedisplay();
}

void setCamera()
{
    glTranslatef(0.0f,-0.75f, -2.0f);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
}

void makeMenu()
{
    int menu, min, mag, sDir, tDir, env;
    
    min = glutCreateMenu(menuCallback);
    glutAddMenuEntry("linear", MIN_LINEAR);
    glutAddMenuEntry("nearest", MIN_NEAREST);
    
    mag = glutCreateMenu(menuCallback);
    glutAddMenuEntry("linear", MAG_LINEAR);
    glutAddMenuEntry("nearest", MAG_NEAREST);
    
    sDir = glutCreateMenu(menuCallback);
    glutAddMenuEntry("repeat", S_REPEAT);
    glutAddMenuEntry("clamp", S_CLAMP);
    
    tDir = glutCreateMenu(menuCallback);
    glutAddMenuEntry("repeat", T_REPEAT);
    glutAddMenuEntry("clamp", T_CLAMP);
    
    env = glutCreateMenu(menuCallback);
    glutAddMenuEntry("modulate", ENV_MODULATE);
    glutAddMenuEntry("replace", ENV_REPLACE);
    
    menu = glutCreateMenu(menuCallback);
    glutAddSubMenu("texture min filter", min);
    glutAddSubMenu("texture mag filter", mag);
    glutAddSubMenu("wrap s direction", sDir);
    glutAddSubMenu("wrap t direction", tDir);
    glutAddSubMenu("texture env mode", env);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuCallback(int option)
{
    switch (option) {
        case MIN_LINEAR:
            minFilter = GL_LINEAR;
            break;
        case MIN_NEAREST:
            minFilter = GL_NEAREST;
            break;
        case MAG_LINEAR:
            magFilter = GL_LINEAR;
            break;
        case MAG_NEAREST:
            magFilter = GL_NEAREST;
            break;
        case S_REPEAT:
            wrapS = GL_REPEAT;
            break;
        case S_CLAMP:
            wrapS = GL_CLAMP;
            break;
        case T_REPEAT:
            wrapT = GL_REPEAT;
            break;
        case T_CLAMP:
            wrapT = GL_CLAMP;
            break;
        case ENV_MODULATE:
            envMode = GL_MODULATE;
            break;
        case ENV_REPLACE:
            envMode = GL_REPLACE;
            break;
        default:
            break;
    }
    
    glDeleteTextures(1, &teaTex); // De-allocate current texture
    loadTextures(); // Re-load texture
    glutPostRedisplay();
}

void CreateGlutWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (512, 512);
    win = glutCreateWindow ("Butcher, Andrew");
}

void CreateGlutCallbacks()
{
    glutDisplayFunc(display);
    glutIdleFunc(idle);
}

void InitOpenGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    loadTextures();
    
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
    glEnable(GL_LIGHT0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void ExitGlut()
{
    glutDestroyWindow(win);
    exit(0);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv); 
    CreateGlutWindow();
    CreateGlutCallbacks();
    InitOpenGL();
    
    makeMenu();
    
    glutMainLoop();
    
    ExitGlut();
    return 0;		
}