/*
This is a program which displays several primitives as well as animates objects.
Your task is to make the plane that makes a crash landing, but unlike the movies,
it doesn't burst into flames.The background contains a triangle for windmill.
You need to complete it using transformation then make it animate*/

#include <stdlib.h>
#include "GL/glut.h"
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
void landplane();
float windmillRotationAngle = 0.0;
float planeX = 245.0; // Initial X position of the plane
float planeY = 230.0; // Initial Y position of the plane
bool planeLanding = false; // Flag to indicate if the plane is landing





//void display()
//{
	//glClear(GL_COLOR_BUFFER_BIT);

	//drawlandscape();
	//drawplane();
	//drawwindmill();


	//glutSwapBuffers();


//}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawlandscape();

	glPushMatrix(); // Push the current matrix state
	glTranslatef(125.0, 90.0, 0.0); // Translate to the center of the windmill
	glRotatef(windmillRotationAngle, 0.0, 0.0, 1.0); // Apply windmill rotation
	glTranslatef(-125.0, -90.0, 0.0); // Translate back to the original position

	drawwindmill(); // Draw the windmill with wings
	glPopMatrix(); // Pop the previous matrix state

	//drawplane();
	glPushMatrix();
	glTranslatef(230.0, 150.0, 0.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glTranslatef(-230.0, -150.0, 0.0);

	landplane();
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

//void drawwindmill()   // complete windmill in this body
//{
	/* Draw a windmill */

	//drawWind();

//}

void drawwindmill()
{
	//glColor3f(0.6, 0.6, 0.0);

	// Draw the central body of the windmill
	//glBegin(GL_QUADS);
	//glVertex2f(145.0, 50.0);
	//glVertex2f(135.0, 100.0);
	//glVertex2f(115.0, 100.0);
	//glVertex2f(105.0, 50.0);
	//glEnd();

	// Draw the four wings of the windmill
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glTranslatef(125.0, 90.0, 0.0);
		//glTranslatef(125.0, 75.0, 0.0); // Translate to the center of the windmill
		glRotatef(i * 90.0, 0.0, 0.0, 1.0); // Rotate the wing
		glTranslatef(-125.0, -90.0, 0.0); // Translate back to the original position

		drawWind(); // Draw a single wing
		glPopMatrix();
	}
}




//void Timer(int value) // work in this function after completing windmill to animate it
//{
	//update variables here


	//display();
	//glutTimerFunc(30, Timer, 1);
//}

void Timer(int value)
{
	// Update the rotation angle for the windmill
	windmillRotationAngle += 4.0; // Adjust the rotation speed as needed

	// Keep the rotation angle within 360 degrees
	if (windmillRotationAngle >= 360.0)
	{
		windmillRotationAngle -= 360.0;
	}

	// Redisplay the scene
	glutPostRedisplay();

	// Set the next timer callback
	//display();
	glutTimerFunc(30, Timer, 1);

	if (planeY <= 50.0)
	{
		planeLanding = false;
	}
}


void landplane()
{
		glPushMatrix();
		glTranslatef(230.0, 210.0, 0.0);
		glRotatef(-60.0,0.0,0.0,1.0);
		glTranslatef(-230.0, -245.0, 0.0);

		drawplane();
		glPopMatrix();

	// Trigger the plane landing animation
	if (planeY > 50.0)
	{
		planeLanding = true;
	}
}



void drawplane()
{
	/* Draw a plane */

	if (planeLanding)
	{
		// If the plane is landing, move it downward smoothly
		planeY -= 2.0;
	}

	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(planeX, planeY);
	glVertex2f(planeX, planeY + 10.0);
	glVertex2f(planeX - 30.0, planeY);

	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(planeX - 1.0, planeY - 2.0);
	glVertex2f(planeX - 1.0, planeY + 5.0);
	glVertex2f(planeX - 17.0, planeY + 5.0);

	glEnd();
}


//void drawplane()// work in this function to animate and crash plane
//{
	/* Draw a plane 

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


}*/

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Windmill Lab");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(30, Timer, 1);
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

	if (key == 'q')
	{
		exit(0);
	}
}