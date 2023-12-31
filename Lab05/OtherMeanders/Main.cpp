#include <gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

int screenWidth = 740;
int screenHeight = 480;

class Canvas {
public:
	float x, y;
	float angle;
	Canvas() {
		this->x = 150;
		this->y = 200;
	}
	void turnTo(float angle) {
		this->angle = angle;
	}
	void turn(float angle) {
		this->angle += angle;
	}
	void lineTo(float x, float y) {
		float t_x = x; float t_y = y;
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex2f(this->x, this->y);
		glVertex2f(x, y);
		glEnd();
		glFlush();
		moveTo(t_x, t_y);
	}
	void moveTo(float x, float y) {
		this->x = x;
		this->y = y;

	}
	
	void forward(float dist, int isVisible) {
		const float RadPerDeg = 0.017453393;
		float x = this->x + dist * cos(RadPerDeg * this->angle);
		float y = this->y + dist * sin(RadPerDeg * this->angle);
		if (isVisible >= 1 ) {
			lineTo(x, y);

		}
		else {
			moveTo(x, y);
		}
	}
};

float increment = 3;
Canvas cvs;


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	// 3.5.6  Drawing Elaborate Meanders.
	float L = 80.0;
	bool limitReached = false;
	for (int i = 0; i < 24; i++) {
		if (!limitReached && L == 0) {
			L = 10;
			cvs.forward(L, 1);
			cvs.turn(-90);
			limitReached = true;
		}
		if (!limitReached && L >= 10) {
			cout << i << L << endl;
			cvs.forward(L, 1);
			cvs.turn(90);
			cout << "curr-angle:" << cvs.angle << endl;
			L -= 10;
		}
		if (limitReached && L <= 80 + 10) {
			cout << i << L << endl;
			cvs.forward(L, 1);
			cvs.turn(-90);
			L += 10;
		}
	}
	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 5 | 3.5.5 - 3.5.9");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}