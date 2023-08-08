#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

using std::cout;
using std::fstream;
using std::ios;

const int screenWidth = 650;	   // width of screen window in pixels 
const int screenHeight = 450;	   // height of screen window in pixels

void drawPolyLineFile(const char* fileName)
{
	fstream inStream;

	inStream.open(fileName, ios::in);	// open the file

	if (inStream.fail())
	{
		cout << "can't open it!"; return;
	}

	glClear(GL_COLOR_BUFFER_BIT);      // clear the screen

	//GLint numpolys, numPoints, x ,y;

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
	glFlush();
	inStream.close();
}

void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);//dino window
	gluOrtho2D(left, right, bottom, top);
	glViewport(0, 0, screenWidth, screenHeight);
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
	setWindow(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);//dino window
	//glViewport(0, 0, screenWidth, screenHeight);

}

void myDisplay(void)
{
	//drawPolyLineFile("birdhead.dat");		   // send all output to display
	//drawPolyLineFile("house.dat");

	setWindow(0.0, 640.0, 0.0, 480.0);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			glViewport(i * 64, j * 44, 64, 44);
			drawPolyLineFile("dino.dat");
		}
	glutSwapBuffers();
}

int main(int argc, char** argv)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(10, 10); // set window position on screen
	glutCreateWindow("Dino Line Drawing"); // open the screen window
	glutDisplayFunc(myDisplay);     // register redraw function
	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
	return 1;
}