#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include <cmath>

int windowWidth = 1600;
int windowHeight = 900;
int dot_x = -1;
int dot_y = -1;

void initGL() {
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f); // Set clear color to black
	glColor3f(1, 0, 0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0, windowWidth, 0, windowHeight); // Set the coordinate system
}

void drawDot(int x, int y) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (dot_x != -1 && dot_y != -1) {
		drawDot(dot_x, dot_y); 
	}
	glFlush();
}


void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)windowWidth, 0.0, (GLdouble)windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardHandler(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
		exit(0);
	case 's':
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		dot_x = x;
		dot_y = windowHeight - y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glutPostRedisplay();
}

void motionHandler(int x, int y) {
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Lab 03");
	initGL();
	glutDisplayFunc(display); // Set the display callback function
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardHandler);
	glutMouseFunc(mouseHandler);
	glutMotionFunc(motionHandler);
	glutMainLoop(); // Start the main GLUT loop
	return 0;
}
