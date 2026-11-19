
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

int width = 800, height = 600;
int fillMode = 4;
bool filled = false;

struct Point
{
    int x, y;
};

// Boundary color: Black
float boundaryColor[3] = {0.0, 0.0, 0.0};

// Fill color: Red
float fillColor[3] = {1.0, 0.0, 0.0};

// Draw rectangle boundary
void drawBoundary()
{
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);
        glVertex2i(200, 150);
        glVertex2i(600, 150);
        glVertex2i(600, 450);
        glVertex2i(200, 450);
    glEnd();

    glFlush();
}

// Check pixel color
bool isSameColor(int x, int y, float color[3])
{
    unsigned char pixel[3];

    glReadPixels(x, y, 1, 1,
                 GL_RGB, GL_UNSIGNED_BYTE, pixel);

    return (pixel[0] == (unsigned char)(color[0] * 255) &&
            pixel[1] == (unsigned char)(color[1] * 255) &&
            pixel[2] == (unsigned char)(color[2] * 255));
}

// Boundary Fill Algorithm
void boundaryFill(int x, int y)
{
    vector<Point> points;

    points.push_back({x, y});

    glColor3f(fillColor[0], fillColor[1], fillColor[2]);

    while (!points.empty())
    {
        Point p = points.back();
        points.pop_back();

        if (p.x < 0 || p.x >= width ||
            p.y < 0 || p.y >= height)
            continue;

        if (!isSameColor(p.x, p.y, boundaryColor) &&
            !isSameColor(p.x, p.y, fillColor))
        {
            glBegin(GL_POINTS);
                glVertex2i(p.x, p.y);
            glEnd();

            glFlush();

            // 4-connected filling
            points.push_back({p.x + 1, p.y});
            points.push_back({p.x - 1, p.y});
            points.push_back({p.x, p.y + 1});
            points.push_back({p.x, p.y - 1});

            // Additional points for 8-connected filling
            if (fillMode == 8)
            {
                points.push_back({p.x + 1, p.y + 1});
                points.push_back({p.x - 1, p.y - 1});
                points.push_back({p.x + 1, p.y - 1});
                points.push_back({p.x - 1, p.y + 1});
            }
        }
    }

    glFlush();
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBoundary();

    if (filled)
    {
        boundaryFill(400, 300);
    }

    glFlush();
}

// Mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int wx = x;
        int wy = height - y;

        // Check whether click is inside rectangle
        if (wx > 200 && wx < 600 &&
            wy > 150 && wy < 450)
        {
            glFlush();
            boundaryFill(wx, wy);
            filled = true;
        }
    }
}

// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if (key == '4')
    {
        fillMode = 4;
        filled = false;
        glutPostRedisplay();
        cout << "4-connected Boundary Fill Selected" << endl;
    }
    else if (key == '8')
    {
        fillMode = 8;
        filled = false;
        glutPostRedisplay();
        cout << "8-connected Boundary Fill Selected" << endl;
    }
    else if (key == 'r' || key == 'R')
    {
        filled = false;
        glutPostRedisplay();
        cout << "Screen Reset" << endl;
    }
}

// Right-click menu
void menu(int option)
{
    if (option == 1)
    {
        fillMode = 4;
    }
    else if (option == 2)
    {
        fillMode = 8;
    }
    else if (option == 3)
    {
        filled = false;
    }

    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Boundary Fill Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    gluOrtho2D(0, width, 0, height);

    glPointSize(1.0);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("4-Connected Fill", 1);
    glutAddMenuEntry("8-Connected Fill", 2);
    glutAddMenuEntry("Reset", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    cout << "BOUNDARY FILL ALGORITHM" << endl;
    cout << "Left Click: Fill inside rectangle" << endl;
    cout << "Press 4: 4-connected fill" << endl;
    cout << "Press 8: 8-connected fill" << endl;
    cout << "Press R: Reset" << endl;
    cout << "Right Click: Open Menu" << endl;

    glutMainLoop();

    return 0;
}

