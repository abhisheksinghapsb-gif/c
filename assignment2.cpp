
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

using namespace std;

int xc, yc, radius;
int clickCount = 0;

// Midpoint Circle Drawing Algorithm
void midpointCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;

    int p = 1 - r;

    glBegin(GL_POINTS);

    while (x <= y)
    {
        // Eight-way symmetry
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);

        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);

        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);

        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        x++;

        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
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

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    if (clickCount == 2)
    {
        glColor3f(1.0, 0.0, 0.0);

        midpointCircle(xc, yc, radius);
    }

    glFlush();
}

// Mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert screen coordinates to Cartesian coordinates
        int wx = x - 400;
        int wy = 300 - y;

        if (clickCount == 0)
        {
            // First click: Circle centre
            xc = wx;
            yc = wy;

            clickCount = 1;

            cout << "Centre selected: "
                 << xc << ", " << yc << endl;
        }
        else
        {
            // Second click: Calculate radius
            int dx = wx - xc;
            int dy = wy - yc;

            radius = round(sqrt(dx * dx + dy * dy));

            clickCount = 2;

            cout << "Radius: " << radius << endl;
        }

        glutPostRedisplay();
    }
}

// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        clickCount = 0;
        cout << "Reset. Select a new centre." << endl;
    }

    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv)
{
    cout << "MIDPOINT CIRCLE DRAWING ALGORITHM" << endl;
    cout << "---------------------------------" << endl;
    cout << "Instructions:" << endl;
    cout << "1. First click to select circle centre." << endl;
    cout << "2. Second click to select circle radius." << endl;
    cout << "3. Press R to draw another circle." << endl;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Midpoint Circle Drawing Algorithm");

    // White background
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Set coordinate system
    gluOrtho2D(-400, 400, -300, 300);

    glPointSize(2.0);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

