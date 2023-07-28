#include <GL/glut.h>
#include <cmath>

int windowWidth = 1600;
int windowHeight = 900;

void initGL() {
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f); // Set clear color to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowWidth, 0, windowHeight); // Set the coordinate system
}

void drawLine(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
}

void drawRectangle(int x1, int y1, int x2, int y2) {
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

void drawFourSidedPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}
void drawFourSidedOutlinedPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}


void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void drawCircle(float centerX, float centerY, float radius) {
	int numSegments = 100; // Increase this value for a smoother circle

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY); // Center of the circle
	for (int i = 0; i <= numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // Calculate angle
		float x = centerX + radius * cosf(theta) * windowHeight / windowWidth; // Compute x-coordinate with center and radius
		float y = centerY + radius * sinf(theta); // Compute y-coordinate with center and radius
		glVertex2f(x, y); // Output vertex
	}
	glEnd();
}

void drawGradientSky()
{
	// Define the colors for the gradient sky
	float horizonColor[3] = { 1.0f, 0.4f, 0.0f };     // RGB - 255, 102, 0 (#FF6600)
	float horizonUpperColor[3] = { 1.0f, 0.6f, 0.2f }; // RGB - 255, 153, 51 (#FF9933)
	float zenithColor[3] = { 0.2f, 0.0f, 0.4f };       // RGB - 51, 0, 102 (#330066)
	float skyTopColor[3] = { 0.0f, 0.0f, 0.2f };       // RGB - 0, 0, 51 (#000033)

	glDisable(GL_DEPTH_TEST); // Disable depth testing to draw the sky as a background

	glBegin(GL_QUADS);

	// Draw the gradient rectangle representing the sky
	glColor3fv(horizonUpperColor);
	glVertex2f(-1.0f, 0.0f); // bottom-left
	glColor3fv(skyTopColor);
	glVertex2f(-1.0f, 1.0f);  // top-left
	glColor3fv(zenithColor);
	glVertex2f(1.0f, 1.0f);   // top-right
	glColor3fv(horizonColor);
	glVertex2f(1.0f, 0.0f);  // bottom-right

	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	// Draw the sky
	drawGradientSky();

	// Draw the sun
	glColor3f(1.0f, 0.694f, 0.176f);
	drawCircle(0, 0, 0.3f);

	// Draw the greenery
	glColor3f(0.15f, 0.55f, 0.3f); // Radiant green color for highway greenery
	drawRectangle(-1, -1, 1, 0);

	// Draw the bridge

	glColor3f(0.2f, 0.2f, 0.2f); // Dark grayish color for asphalt road
	drawTriangle(-1.3, -1, 1.3, -1, 0, 0);

	glColor3f(1.0f, 0.6745f, 0.0314f);
	drawTriangle(-0.08, -1, -0.025, -1, 0, 0);

	glColor3f(1.0f, 0.6745f, 0.0314f);
	drawTriangle(0.08, -1, 0.025, -1, 0, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFourSidedPolygon(-1, -0.95, -1, -0.9, 0, 0, 0, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFourSidedPolygon(1, -0.95, 1, -0.9, 0, 0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glFlush(); // Render the scene
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Lab 02");
	initGL();
	glutDisplayFunc(display); // Set the display callback function
	glutMainLoop(); // Start the main GLUT loop
	return 0;
}
