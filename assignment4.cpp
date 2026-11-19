
#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

// Clipping window
const float xmin = 200;
const float ymin = 150;
const float xmax = 600;
const float ymax = 450;

struct Point
{
    float x, y;
};

vector<Point> polygon;
vector<Point> clippedPolygon;

bool isClipped = false;

// Check whether point is inside a boundary
bool inside(Point p, int edge)
{
    if (edge == 0) return p.x >= xmin; // Left
    if (edge == 1) return p.x <= xmax; // Right
    if (edge == 2) return p.y >= ymin; // Bottom
    if (edge == 3) return p.y <= ymax; // Top

    return false;
}

// Find intersection point
Point intersection(Point p1, Point p2, int edge)
{
    Point p;

    float m;

    if (edge == 0 || edge == 1)
    {
        float x = (edge == 0) ? xmin : xmax;

        m = (p2.y - p1.y) / (p2.x - p1.x);

        p.x = x;
        p.y = p1.y + m * (x - p1.x);
    }
    else
    {
        float y = (edge == 2) ? ymin : ymax;

        m = (p2.x - p1.x) / (p2.y - p1.y);

        p.y = y;
        p.x = p1.x + m * (y - p1.y);
    }

    return p;
}

// Sutherland-Hodgman polygon clipping
vector<Point> clipBoundary(vector<Point> input, int edge)
{
    vector<Point> output;

    if (input.empty())
        return output;

    Point S = input.back();

    for (int i = 0; i < (int)input.size(); i++)
    {
        Point P = input[i];

        bool S_inside = inside(S, edge);
        bool P_inside = inside(P, edge);

        if (S_inside && P_inside)
        {
            output.push_back(P);
        }
        else if (S_inside && !P_inside)
        {
            output.push_back(intersection(S, P, edge));
        }
        else if (!S_inside && P_inside)
        {
            output.push_back(intersection(S, P, edge));
            output.push_back(P);
        }

        S = P;
    }

    return output;
}

// Perform clipping against all four boundaries
void performClipping()
{
    if (polygon.size() < 3)
    {
        cout << "Please draw a polygon with at least 3 points." << endl;
        return;
    }

    clippedPolygon = polygon;

    for (int edge = 0; edge < 4; edge++)
    {
        clippedPolygon = clipBoundary(clippedPolygon, edge);
    }

    isClipped = true;

    cout << "Polygon clipping completed!" << endl;
}

// Draw rectangular clipping window
void drawWindow()
{
    glColor3f(0.0, 0.0, 1.0);

    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    glLineWidth(1.0);
}

// Draw original polygon
void drawOriginalPolygon()
{
    if (polygon.empty())
        return;

    glColor3f(0.8, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < (int)polygon.size(); i++)
    {
        glVertex2f(polygon[i].x, polygon[i].y);
    }

    glEnd();
}

// Draw only the clipped polygon
void drawClippedPolygon()
{
    if (!isClipped || clippedPolygon.size() < 3)
        return;

    // Fill clipped polygon
    glColor3f(0.0, 0.8, 0.2);

    glBegin(GL_POLYGON);

    for (int i = 0; i < (int)clippedPolygon.size(); i++)
    {
        glVertex2f(clippedPolygon[i].x,
                   clippedPolygon[i].y);
    }

    glEnd();

    // Draw clipped polygon boundary
    glColor3f(0.0, 0.0, 0.0);

    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < (int)clippedPolygon.size(); i++)
    {
        glVertex2f(clippedPolygon[i].x,
                   clippedPolygon[i].y);
    }

    glEnd();

    glLineWidth(1.0);
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawWindow();

    if (isClipped)
    {
        drawClippedPolygon();
    }
    else
    {
        drawOriginalPolygon();
    }

    glFlush();
}

// Mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!isClipped)
        {
            Point p;

            p.x = x;
            p.y = HEIGHT - y;

            polygon.push_back(p);

            glutPostRedisplay();
        }
    }
}

// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'c' || key == 'C')
    {
        performClipping();
        glutPostRedisplay();
    }

    else if (key == 'r' || key == 'R')
    {
        polygon.clear();
        clippedPolygon.clear();

        isClipped = false;

        glutPostRedisplay();

        cout << "Screen Reset!" << endl;
    }

    else if (key == 8)
    {
        if (!polygon.empty())
            polygon.pop_back();

        glutPostRedisplay();
    }
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Polygon Clipping Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    cout << "\nPOLYGON CLIPPING ALGORITHM\n";
    cout << "--------------------------\n";
    cout << "Left Click : Draw polygon\n";
    cout << "C          : Perform clipping\n";
    cout << "R          : Reset screen\n";
    cout << "Backspace  : Remove last point\n";

    glutMainLoop();

    return 0;
}
