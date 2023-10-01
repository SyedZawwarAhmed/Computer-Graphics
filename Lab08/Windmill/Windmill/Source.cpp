/*
This is a program which displays several primitives as well as animates objects.
Your task is to make the plane that makes a crash landing, but unlike the movies,
it doesn't burst into flames.The background contains a triangle for windmill.
You need to complete it using transformation then make it animate*/

#include<iostream>
#include<gl/glut.h>
using namespace std;
#define PI 3.141592

void display(void); // draw everything
void drawWind(void);  // draw single blade 
void drawwindmill(void); //complete this to complete windmill i.e. call drawWind() in it
void drawplane();  // work in this function
//  for crash landing of plane i.e. animate and collision with land 

void drawlandscape();// do nothing with it 
void Timer(int value); // update varible for animation here

void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

float angle = 0;
//float t = 0;
//float vy = 0;
//float dvy = -9.8;
//float vx = 4;
//float dvx = 3;
//float y = vy + (-9.8 * t);
//float x = vx + (6 * t);


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawlandscape();

	/*glPushMatrix();
	glTranslatef(215.0 - x, 230.0 + y, 0.0);
	glTranslatef(-215,-230, 0.0);*/
	drawplane();
	/*if (-y < 300) {
		vy += dvy;
		vx += dvx;
		t += 1;
		y = vy + (-9.8 * t);
		x = vx + (12 * t);
	}*/
	/*else {
		x = 0; y = 0; t = 0;
	}*/
	// glPopMatrix();

	glPushMatrix();
	glTranslatef(125.0, 90.0, 0.0);
	glRotatef(angle * 5.0, 0.0, 0.0, 1.0);
	glTranslatef(-125.0, -90.0, 0.0);
	drawwindmill();
	glPopMatrix();

	glutSwapBuffers();


}


void drawWind() // single Triangle
{

	glBegin(GL_TRIANGLES);

	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(125.0, 90.0);
	glVertex2f(140.0, 120.0);
	glVertex2f(160.0, 120.0);
	glEnd();
}

void drawwindmill() // Complete Windmill
{
	glPushMatrix(); // Save the current transformation matrix

	for (int i = 0; i < 4; i++) {
		glTranslatef(125.0, 90.0, 0.0); // Translate to the center of the windmill
		glRotatef(i * 90.0, 0.0, 0.0, 1.0); // Rotate by 90 degrees
		glTranslatef(-125.0, -90.0, 0.0); // Translate back to the original position
		drawWind(); // Draw the blade
	}

	glPopMatrix(); // Restore the previous transformation matrix
}



void Timer(int value) // work in this function after completing windmill to animate it
{
	//update variables here


	display();
	angle++;
	glutTimerFunc(50, Timer, 1);
}


void drawplane()// work in this function to animate and crash plane
{
	/* Draw a plane */

	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(245.0, 230.0);
	glVertex2f(245.0, 240.0);
	glVertex2f(215.0, 230.0);

	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(244.0, 228.0);
	glVertex2f(244.0, 235.0);
	glVertex2f(228.0, 235.0);

	glEnd();


}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("BSCS 514 Lab #8");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(50, Timer, 1);
	glutMainLoop();
}



void drawlandscape()
{
	/* Draw a box of grass */
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(250.0, 0.0);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2f(250.0, 50.0);
	glColor3f(0.0, 0.8, 0.0);
	glVertex2f(0.0, 50.0);
	glColor3f(0.0, 0.7, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	/* An attempt at a few snow covered mountains */

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.6);
	glVertex2f(250.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(200.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(150.0, 50.0);

	//glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(200.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(150.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(100.0, 50.0);

	glColor3f(0.0, 0.0, 0.7);
	glVertex2f(150.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(100.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(50.0, 50.0);

	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(100.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(50.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(0.0, 50.0);

	glEnd();

	/* Draw the body of a windmill */
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.0);
	glVertex2f(145.0, 50.0);
	glVertex2f(135.0, 100.0);
	glVertex2f(115.0, 100.0);
	glVertex2f(105.0, 50.0);
	glEnd();

}

void init()
{
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 250.0, 0.0, 250.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 250.0, 0.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}





void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}