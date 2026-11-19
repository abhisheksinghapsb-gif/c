
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Global variables
int startX, startY, endX, endY;
int clickCount = 0;
int lineStyle = 1;

// Bresenham's Line Drawing Algorithm
void Bresenham(int xa, int ya, int xb, int yb)
{
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);

    // Check whether line is steep
    bool steep = (dy > dx);

    // Swap coordinates for steep lines
    if (steep)
    {
        swap(xa, ya);
        swap(xb, yb);
    }

    // Ensure left to right drawing
    if (xa > xb)
    {
        swap(xa, xb);
        swap(ya, yb);
    }

    dx = abs(xb - xa);
    dy = abs(yb - ya);

    int yStep = (ya < yb) ? 1 : -1;

    int p = 2 * dy - dx;
    int y = ya;

    glBegin(GL_POINTS);

    for (int i = 0; i <= dx; i++)
    {
        // Simple Line
        if (lineStyle == 1)
        {
            if (steep)
                glVertex2i(y, xa + i);
            else
                glVertex2i(xa + i, y);
        }

        // Dotted Line
        else if (lineStyle == 2)
        {
            if (i % 5 == 0)
            {
                if (steep)
                    glVertex2i(y, xa + i);
                else
                    glVertex2i(xa + i, y);
            }
        }

        // Dashed Line
        else if (lineStyle == 3)
        {
            if ((i / 10) % 2 == 0)
            {
                if (steep)
                    glVertex2i(y, xa + i);
                else
                    glVertex2i(xa + i, y);
            }
        }

        // Update decision parameter
        if (p >= 0)
        {
            y += yStep;
            p -= 2 * dx;
        }

        p += 2 * dy;
    }

    glEnd();
}

// Draw coordinate axes
void drawAxes()
{
    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_LINES);

    // X-axis
    glVertex2i(-400, 0);
    glVertex2i(400, 0);

    // Y-axis
    glVertex2i(0, -300);
    glVertex2i(0, 300);

    glEnd();
}

// Display Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    if (clickCount == 2)
    {
        glColor3f(1.0, 0.0, 0.0);

        Bresenham(startX, startY, endX, endY);
    }

    glFlush();
}

// Mouse Function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert screen coordinates to Cartesian coordinates
        int wx = x - 400;
        int wy = 300 - y;

        if (clickCount == 0)
        {
            startX = wx;
            startY = wy;

            clickCount = 1;
        }
        else if (clickCount == 1)
        {
            endX = wx;
            endY = wy;

            clickCount = 2;
        }

        glutPostRedisplay();
    }
}

// Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        lineStyle = 1;
        clickCount = 0;
        cout << "Simple Line Selected" << endl;
    }
    else if (key == '2')
    {
        lineStyle = 2;
        clickCount = 0;
        cout << "Dotted Line Selected" << endl;
    }
    else if (key == '3')
    {
        lineStyle = 3;
        clickCount = 0;
        cout << "Dashed Line Selected" << endl;
    }
    else if (key == 'r' || key == 'R')
    {
        clickCount = 0;
        cout << "Screen Reset" << endl;
    }

    glutPostRedisplay();
}

// Main Function
int main(int argc, char** argv)
{
    cout << "BRESENHAM LINE DRAWING ALGORITHM" << endl;
    cout << "--------------------------------" << endl;

    cout << "1. Simple Line" << endl;
    cout << "2. Dotted Line" << endl;
    cout << "3. Dashed Line" << endl;

    cout << "Select Line Style: ";
    cin >> lineStyle;

    if (lineStyle < 1 || lineStyle > 3)
    {
        cout << "Invalid choice! Selecting Simple Line." << endl;
        lineStyle = 1;
    }

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Bresenham Line Drawing Algorithm");

    // White background
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Centre origin (0,0)
    gluOrtho2D(-400, 400, -300, 300);

    glPointSize(2.0);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}


