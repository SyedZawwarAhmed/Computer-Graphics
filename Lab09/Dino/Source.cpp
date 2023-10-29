#include "Canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


#define M_PI  3.14157
using namespace std;

// display

Canvas cvs(800, 600, "Motifs drawing");

void drawPolyLineFile(const char* fileName)
{
    fstream inStream;
    inStream.open(fileName, ios::in);	// open the file

    if (inStream.fail())
    {
        cout << "can't open it!"; return;
    }

    GLfloat numpolys, numPoints, x, y;
    inStream >> numpolys;		           // read the number of polylines

    for (int j = 0; j < numpolys; j++)  // read each polyline
    {
        inStream >> numPoints;       //number of points in first PolyLine  
        glBegin(GL_LINE_STRIP);	     // draw the next polyline
        for (int i = 0; i < numPoints; i++)
        {
            inStream >> x >> y;        // read the next x, y pair
            glVertex2f(x, y);
        }
        glEnd();
    }
    inStream.close();
}

void drawDinoTable() {
    int numDinosaurs = 12;
    int tableRadius = 100; // Adjust the radius as needed
    int viewportWidth = 128; //128
    int viewportHeight = 88;// Adjust the viewport size as needed

    for (int i = 0; i < numDinosaurs; i++) {
        double angle = 2.0 * M_PI * i / numDinosaurs;
        double rotate_angle = angle - (M_PI / 2);
        double x = 300 + tableRadius * cos(angle);
        double y = 300 + tableRadius * sin(angle);

        double rx = x + cos(rotate_angle);
        double ry = y + sin(rotate_angle);

        int viewportLeft = rx - viewportWidth / 2;
        int viewportRight = rx + viewportWidth / 2;
        int viewportBottom = ry - viewportHeight / 2;
        int viewportTop = ry + viewportHeight / 2;


        cvs.setViewport(viewportLeft, viewportRight, viewportBottom, viewportTop);
        cvs.initCT();


        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); // Push the current matrix onto the stack
        glLoadIdentity(); // Load the identity matrix
        glTranslated(viewportLeft, viewportBottom, 0); // Translate to the dinosaur's position
        glRotated(rotate_angle * 180.0 / M_PI, 0, 0, 1); // Rotate around the Z-axis
        glTranslated(-viewportLeft, -viewportBottom, 0);
        drawPolyLineFile("dino.dat");
        glPopMatrix();
    }
}


//>>>>>>>>>USE THIS DISPLAY FOR DINASOR<<<<<<<<<<<<<<
void display(void)
{
    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
    cvs.clearScreen(); //clear screen
    cvs.setColor(0.0, 0.0, 0.0); //drawing color is red 
    cvs.setWindow(0, 640, 0, 480);

    drawDinoTable();
    glFlush();
}

int main(int argc, char** argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
}//end main