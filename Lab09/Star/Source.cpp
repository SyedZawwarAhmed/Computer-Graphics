#include "Canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


#define M_PI  3.14157
using namespace std;

// display

Canvas cvs(800, 600, "Motifs drawing");


void starmotif()
{
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glVertex2i(3,3);
    glVertex2i(0,8);
    glVertex2i(-3, 0);
    glVertex2i(-2, -1);
    glVertex2i(0, 5);
    glVertex2i(2, 3);
    glVertex2i(3, 3);
    glEnd();
    glPopMatrix();
}

void drawStar()
{
    for (int i = 0; i < 5; i++)
    {
        starmotif();
        cvs.rotate2D(75.0);
    }
}

void display(void)
{
    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
    cvs.clearScreen(); //clear screen
    cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
    cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
    cvs.setViewport(10, 480, 10, 480);

    drawStar();
    glFlush();
}// end display

int main(int argc, char** argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
}//end main