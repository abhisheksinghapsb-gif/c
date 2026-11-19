
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

struct Point
{
    int x, y;
};

vector<Point> polygon;
vector<unsigned char> pixels;

bool polygonClosed = false;
bool fillMode = false;
bool filled = false;

// Draw polygon boundary
void drawPolygon()
{
    if (polygon.empty())
        return;

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(polygonClosed ? GL_LINE_LOOP : GL_LINE_STRIP);

    for (int i = 0; i < polygon.size(); i++)
    {
        glVertex2i(polygon[i].x, polygon[i].y);
    }

    glEnd();
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (filled)
    {
        glRasterPos2i(0, 0);

        glDrawPixels(WIDTH, HEIGHT,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     &pixels[0]);
    }
    else
    {
        drawPolygon();
    }

    glFlush();
}

// Flood Fill Algorithm (4-connected)
void floodFill(int sx, int sy)
{
    // Draw polygon before reading pixels
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();

    // Read screen pixels
    pixels.resize(WIDTH * HEIGHT * 4);

    glReadPixels(0, 0, WIDTH, HEIGHT,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 &pixels[0]);

    vector<Point> stack;

    Point start;
    start.x = sx;
    start.y = sy;

    stack.push_back(start);

    while (!stack.empty())
    {
        Point p = stack.back();
        stack.pop_back();

        int x = p.x;
        int y = p.y;

        if (x < 0 || x >= WIDTH ||
            y < 0 || y >= HEIGHT)
            continue;

        int index = (y * WIDTH + x) * 4;

        // Check whether pixel is white
        if (pixels[index] == 255 &&
            pixels[index + 1] == 255 &&
            pixels[index + 2] == 255)
        {
            // Change pixel to red
            pixels[index] = 255;
            pixels[index + 1] = 0;
            pixels[index + 2] = 0;
            pixels[index + 3] = 255;

            // Add four neighbouring pixels
            stack.push_back({x + 1, y});
            stack.push_back({x - 1, y});
            stack.push_back({x, y + 1});
            stack.push_back({x, y - 1});
        }
    }

    filled = true;

    cout << "Flood Fill completed!" << endl;

    glutPostRedisplay();
}

// Close polygon
void closePolygon()
{
    if (polygon.size() >= 3)
    {
        polygonClosed = true;
        fillMode = false;

        cout << "Polygon closed." << endl;

        glutPostRedisplay();
    }
    else
    {
        cout << "Select at least 3 points." << endl;
    }
}

// Mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON &&
        state == GLUT_DOWN)
    {
        int wx = x;
        int wy = HEIGHT - 1 - y;

        // Select polygon points
        if (!polygonClosed)
        {
            Point p;
            p.x = wx;
            p.y = wy;

            polygon.push_back(p);
        }
        // Select seed point
        else if (fillMode && !filled)
        {
            if (wx >= 0 && wx < WIDTH &&
                wy >= 0 && wy < HEIGHT)
            {
                floodFill(wx, wy);
                fillMode = false;
            }
        }

        glutPostRedisplay();
    }
}

// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'c' || key == 'C')
    {
        closePolygon();
    }
    else if (key == 'f' || key == 'F')
    {
        if (polygonClosed && !filled)
        {
            fillMode = true;
            cout << "Click inside polygon to fill." << endl;
        }
    }
    else if (key == 'r' || key == 'R')
    {
        polygon.clear();
        pixels.clear();

        polygonClosed = false;
        fillMode = false;
        filled = false;

        cout << "Reset completed." << endl;
    }

    glutPostRedisplay();
}

// Right-click menu
void menu(int option)
{
    switch (option)
    {
        case 1:
            closePolygon();
            break;

        case 2:
            if (polygonClosed && !filled)
            {
                fillMode = true;
                cout << "Click inside polygon." << endl;
            }
            break;

        case 3:
            polygon.clear();
            pixels.clear();

            polygonClosed = false;
            fillMode = false;
            filled = false;

            glutPostRedisplay();
            break;

        case 4:
            exit(0);
    }
}

// Main function
int main(int argc, char** argv)
{
    cout << "FLOOD FILL ALGORITHM" << endl;
    cout << "--------------------" << endl;

    cout << "Left Click : Draw polygon" << endl;
    cout << "C          : Close polygon" << endl;
    cout << "F          : Select flood fill" << endl;
    cout << "Left Click : Select seed point" << endl;
    cout << "R          : Reset" << endl;
    cout << "Right Click: Open menu" << endl;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Flood Fill Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    // Create right-click menu
    glutCreateMenu(menu);

    glutAddMenuEntry("Close Polygon", 1);
    glutAddMenuEntry("Flood Fill", 2);
    glutAddMenuEntry("Reset", 3);
    glutAddMenuEntry("Exit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}

