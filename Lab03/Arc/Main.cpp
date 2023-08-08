#include <GL/glut.h>
#include <cmath>

const double PI = 3.14159265358979323846;

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    float centerX = 0.0;    // X-coordinate of the center
    float centerY = 0.0;    // Y-coordinate of the center
    float radius = 0.5;     // Radius of the arc
    float startAngle = 30;  // Starting angle in degrees
    float sweepAngle = 120; // Sweep angle in degrees

    drawArc(centerX, centerY, radius, startAngle, sweepAngle);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Arc Example");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
