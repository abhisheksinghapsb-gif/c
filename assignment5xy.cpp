
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

class Point
{
public:
    float x, y;

    Point(float a = 0, float b = 0)
    {
        x = a;
        y = b;
    }

    // Translation operator
    Point operator+(Point p)
    {
        return Point(x + p.x, y + p.y);
    }

    // Scaling operator
    Point operator*(float s)
    {
        return Point(x * s, y * s);
    }

    // Rotation operator
    Point operator^(float angle)
    {
        float rad = angle * 3.14159 / 180.0;

        return Point(
            x * cos(rad) - y * sin(rad),
            x * sin(rad) + y * cos(rad)
        );
    }
};

// Original square
Point original[4] = {
    Point(-50, -50),
    Point(50, -50),
    Point(50, 50),
    Point(-50, 50)
};

Point result[4];

int choice = 0;

// Draw square
void drawSquare(Point p[], float r, float g, float b)
{
    glColor3f(r, g, b);

    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < 4; i++)
        glVertex2f(p[i].x, p[i].y);

    glEnd();
}

// Display graphics
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Coordinate axes
    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_LINES);
    glVertex2f(-400, 0);
    glVertex2f(400, 0);
    glVertex2f(0, -300);
    glVertex2f(0, 300);
    glEnd();

    // Original square in white
    drawSquare(original, 1, 1, 1);

    // Apply selected transformation
    for(int i = 0; i < 4; i++)
    {
        if(choice == 1)
        {
            // Translation
            result[i] = original[i] + Point(80, 150);
        }
        else if(choice == 2)
        {
            // Rotation
            result[i] = original[i] ^ 35;
        }
        else if(choice == 3)
        {
            // Scaling
            result[i] = original[i] * 1.7;
        }
    }

    // Transformed square in green
    if(choice != 0)
        drawSquare(result, 0, 1, 0);

    glFlush();
}

// Initialize OpenGL
void init()
{
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-400, 400, -300, 300);
}

int main(int argc, char** argv)
{
    int choice;

    // Console menu
    cout << "\n================================\n";
    cout << "       2D TRANSFORMATIONS\n";
    cout << "================================\n";

    cout << "\n1. Translation";
    cout << "\n2. Rotation";
    cout << "\n3. Scaling";
    cout << "\n0. Reset (Original Square Only)";

    cout << "\n\nEnter your choice: ";
    cin >> choice;

    // Display selected operation
    cout << "\n--------------------------------\n";

    if(choice == 1)
    {
        cout << "Selected Operation: Translation\n";
        cout << "Translation: tx = 80, ty = 150\n";
    }
    else if(choice == 2)
    {
        cout << "Selected Operation: Rotation\n";
        cout << "Rotation Angle: 35 degrees\n";
    }
    else if(choice == 3)
    {
        cout << "Selected Operation: Scaling\n";
        cout << "Scaling Factor: 1.7\n";
    }
    else if(choice == 0)
    {
        cout << "Selected Operation: Reset\n";
    }
    else
    {
        cout << "Invalid Choice!\n";
        return 0;
    }

    cout << "--------------------------------\n";

    // Initialize GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("2D Transformations");

    init();

    glutDisplayFunc(display);

    // Assign console choice to graphics
    ::choice = choice;

    glutMainLoop();

    return 0;
}
