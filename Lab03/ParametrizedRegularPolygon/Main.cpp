// Lab3

#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

using std::cout;
using std::fstream;
using std::ios;

const int screenWidth = 650;	   // width of screen window in pixels 
const int screenHeight = 450;	   // height of screen window in pixels

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
}

const double PI = 3.14159265358979323846;

struct Point {
    double x, y;
};

void ngon(int n, double cx, double cy, double radius, double rotAngle)
{
    if (n < 3)
    {
        return;
    }

    double angle = rotAngle * PI / 180;
    double angleInc = 2 * PI / n;

    glBegin(GL_POLYGON);

    for (int i = 0; i < n; ++i)
    {
        double x = cx + radius * cos(angle);
        double y = cy + radius * sin(angle);
        glVertex2f(x, y);
        angle += angleInc;
    }

    glEnd();
}

void drawArc(float center_x, float center_y, float radius, float startAngle, float sweep) {
    int numSegments = 100; // Number of line segments to approximate the arc

    glBegin(GL_LINE_STRIP);

    // Convert angles to radians
    float angleStart = startAngle * PI / 180;
    float angleEnd = (startAngle + sweep) * PI / 180;

    // Calculate the angle increment for each segment
    float angleInc = (angleEnd - angleStart) / numSegments;

    for (int i = 0; i <= numSegments; ++i) {
        float angle = angleStart + i * angleInc;
        float x = center_x + radius * cos(angle);
        float y = center_y + radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Set color to red

    int sides = 6;          // Number of sides in the polygon
    double centerX = 0.0;   // X-coordinate of the center
    double centerY = 0.0;   // Y-coordinate of the center
    double radius = 0.5;    // Radius of the polygon
    double rotation = 30.0; // Rotation angle in degrees

    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    ngon(sides, 0.0, 0.0, radius, 0.0);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("NGon Example");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


