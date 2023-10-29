#include "Canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


#define M_PI  3.14157
using namespace std;

// display

Canvas cvs(800, 600, "Motifs drawing");

void flakeMotif()
{
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f ,5.0f);
    glVertex2f(20.0f, 5.0f);
    glVertex2f(30.0f, 25.0f);
    glVertex2f(35.0f,18.0f);
    glVertex2f(25.0f, 5.0f);
    glVertex2f(30.0f, 5.0f);
    glVertex2f(45.0f, 15.0f);
    glVertex2f(50.0f, 13.0f);
    glVertex2f(35.0f, 5.0f);
    glVertex2f(55.0f, 5.0f);
    glVertex2f(60.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

void drawFlake() {
    for (int i = 0; i < 6; i++) {
        flakeMotif();
        cvs.scale2D(1.0, -1.0);
        flakeMotif();
        cvs.scale2D(1.0, -1.0);
        cvs.rotate2D(60.0);
    }
}

void display(void)
{
    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
    cvs.clearScreen(); //clear screen
    cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
    cvs.setWindow(-80.0, 80.0, -80.0, 80.0);
    cvs.setViewport(20, 580, 20, 580);

    drawFlake();
    glFlush();
}

int main(int argc, char** argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
}//end main