
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

const float PI = 3.14159265;

int depth = 5;

// Draw cubic Bezier curve
void drawBezier(float x0, float y0,
                float x1, float y1,
                float x2, float y2,
                float x3, float y3)
{
    glBegin(GL_LINE_STRIP);

    for(float t = 0; t <= 1.001; t += 0.02)
    {
        float u = 1 - t;

        float x = u*u*u*x0
                + 3*u*u*t*x1
                + 3*u*t*t*x2
                + t*t*t*x3;

        float y = u*u*u*y0
                + 3*u*u*t*y1
                + 3*u*t*t*y2
                + t*t*t*y3;

        glVertex2f(x, y);
    }

    glEnd();
}

// Recursive Bezier fractal branches
void bezierFractal(float x, float y,
                   float angle, float length,
                   int level)
{
    if(level == 0)
        return;

    float rad = angle * PI / 180.0;

    float xEnd = x + length * cos(rad);
    float yEnd = y + length * sin(rad);

    float x1 = x + length * 0.30 * cos(rad + 0.25);
    float y1 = y + length * 0.30 * sin(rad + 0.25);

    float x2 = x + length * 0.70 * cos(rad - 0.25);
    float y2 = y + length * 0.70 * sin(rad - 0.25);

    glColor3f(0, 1, 0);
    glLineWidth(2);

    drawBezier(x, y, x1, y1, x2, y2, xEnd, yEnd);

    // Create two smaller branches
    bezierFractal(xEnd, yEnd, angle + 35,
                  length * 0.68, level - 1);

    bezierFractal(xEnd, yEnd, angle - 35,
                  length * 0.68, level - 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Starting branch
    bezierFractal(0, -250, 90, 130, depth);

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == '+' && depth < 9)
        depth++;

    if(key == '-' && depth > 1)
        depth--;

    if(key == 'r' || key == 'R')
        depth = 5;

    glutPostRedisplay();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-400, 400, -300, 300);
}

int main(int argc, char** argv)
{
    cout << "===== BEZIER FRACTAL PATTERN =====\n";
    cout << "Initial recursion depth: " << depth << endl;
    cout << "Press + to increase depth\n";
    cout << "Press - to decrease depth\n";
    cout << "Press R to reset\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Bezier Fractal Pattern");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
