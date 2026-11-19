
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int level = 3;

// Recursive Koch curve function
void koch(float x1, float y1,
          float x2, float y2,
          int n)
{
    if(n == 0)
    {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    // Calculate peak point
    float x4 = x1 + 2 * dx;
    float y4 = y1 + 2 * dy;

    float x5 = x3 + dx * cos(M_PI / 3)
                    - dy * sin(M_PI / 3);

    float y5 = y3 + dx * sin(M_PI / 3)
                    + dy * cos(M_PI / 3);

    // Recursively draw four segments
    koch(x1, y1, x3, y3, n - 1);
    koch(x3, y3, x5, y5, n - 1);
    koch(x5, y5, x4, y4, n - 1);
    koch(x4, y4, x2, y2, n - 1);
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 1, 0);
    glLineWidth(2);

    glBegin(GL_LINES);

    // Three sides of Koch snowflake
    koch(-180, -100, 0, 212, level);
    koch(0, 212, 180, -100, level);
    koch(180, -100, -180, -100, level);

    glEnd();

    glFlush();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if(key == '+' && level < 6)
        level++;

    if(key == '-' && level > 0)
        level--;

    if(key == 'r' || key == 'R')
        level = 3;

    glutPostRedisplay();
}

// Initialization
void init()
{
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-400, 400, -300, 300);
}

// Main function
int main(int argc, char** argv)
{
    cout << "===== KOCH SNOWFLAKE =====\n";
    cout << "Initial recursion level: " << level << endl;
    cout << "Press + to increase level\n";
    cout << "Press - to decrease level\n";
    cout << "Press R to reset\n";

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Koch Snowflake");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
