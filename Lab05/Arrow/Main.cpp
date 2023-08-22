#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include <math.h>

const float PI = 3.1415926536;

class GLintPoint
{
public:
	GLint x, y;
};

class Point2
{
public:
	float x, y;

	void set(float dx, float dy)
	{
		x = dx;
		y = dy;
	}

	void set(Point2& p)
	{
		x = p.x;
		y = p.y;
	}

	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	}

	Point2()
	{
		x = y = 0;
	}
};

Point2 currPos;
Point2 CP;

void moveTo(Point2 p)
{
	CP.set(p);
}

void lineTo(Point2 p)
{
	glBegin(GL_LINES);
	glVertex2f(CP.x, CP.y);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
	CP.set(p);
}

void moveRel(float dx, float dy) {
	CP.set(CP.x + dx, CP.y + dy);
}

void lineRel(float dx, float dy) {
	glBegin(GL_LINES);
	glVertex2f(CP.x, CP.y);
	Point2 p2(CP.x + dx, CP.y + dy);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
	CP.set(p2);
}

void myInit(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(0, 0, 1);
}

void drawAxis() {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glFlush();
}
void arrow(float height, float width) {
	glColor3f(0, 1, 1);
	moveRel(width * 0.2, 0);
	lineRel(width * 0.8, 0);
	lineRel(-width, height / 2.0f);
	lineRel(-width, -height / 2.0);
	lineRel(width * 0.8, 0);
	lineRel(0, -height / 2.0f);
	lineRel(width * 0.2 * 2, 0);
	lineRel(0, height / 2.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(10, 10, 640, 640);
	drawAxis();
	float height = 0.8, width = 0.3;
	arrow(height, width);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(640, 640);
	glutCreateWindow("Arrow");
	glutDisplayFunc(render);
	myInit();
	glutMainLoop();
	return 0;
}