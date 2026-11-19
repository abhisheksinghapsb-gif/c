
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Abstract Base Class
class GameObject
{
public:
    virtual void draw() = 0;

    virtual void update()
    {
    }

    virtual ~GameObject()
    {
    }
};

// Derived Class
class Car : public GameObject
{
private:
    float x, y;
    float speed;
    bool automatic;

    // Draw wheel
    void drawWheel(float cx, float cy, float radius)
    {
        glColor3f(0.05f, 0.05f, 0.05f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for(int i = 0; i <= 360; i++)
        {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cx + radius * cos(angle),
                       cy + radius * sin(angle));
        }

        glEnd();

        // Inner wheel
        glColor3f(0.75f, 0.75f, 0.75f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for(int i = 0; i <= 360; i++)
        {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cx + radius * 0.45f * cos(angle),
                       cy + radius * 0.45f * sin(angle));
        }

        glEnd();
    }

public:

    // Constructor
    Car()
    {
        x = 300;
        y = 160;
        speed = 2;
        automatic = false;
    }

    // Draw car
    void draw() override
    {
        glPushMatrix();
        glTranslatef(x, y, 0);

        // Car body
        glColor3f(1.0f, 0.35f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2f(-110, 0);
            glVertex2f(-100, 30);
            glVertex2f(-65, 42);
            glVertex2f(-30, 75);
            glVertex2f(45, 75);
            glVertex2f(85, 35);
            glVertex2f(110, 25);
            glVertex2f(115, 0);
        glEnd();

        // Car roof
        glColor3f(0.85f, 0.15f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2f(-55, 42);
            glVertex2f(-25, 85);
            glVertex2f(40, 85);
            glVertex2f(75, 42);
        glEnd();

        // Left window
        glColor3f(0.3f, 0.8f, 1.0f);

        glBegin(GL_POLYGON);
            glVertex2f(-45, 47);
            glVertex2f(-20, 78);
            glVertex2f(5, 78);
            glVertex2f(5, 47);
        glEnd();

        // Right window
        glBegin(GL_POLYGON);
            glVertex2f(12, 47);
            glVertex2f(12, 78);
            glVertex2f(37, 78);
            glVertex2f(65, 47);
        glEnd();

        // Headlight
        glColor3f(1.0f, 1.0f, 0.3f);

        glBegin(GL_POLYGON);
            glVertex2f(95, 18);
            glVertex2f(112, 18);
            glVertex2f(108, 30);
            glVertex2f(92, 30);
        glEnd();

        // Front bumper
        glColor3f(0.2f, 0.2f, 0.2f);

        glBegin(GL_POLYGON);
            glVertex2f(95, 0);
            glVertex2f(115, 0);
            glVertex2f(112, 8);
            glVertex2f(95, 8);
        glEnd();

        // Wheels
        drawWheel(-65, 0, 22);
        drawWheel(65, 0, 22);

        glPopMatrix();
    }

    // Update car position
    void update() override
    {
        if(automatic)
        {
            x += speed;

            if(x > 850)
                x = -100;
        }
    }

    // Move car left
    void moveLeft()
    {
        x -= 10;

        if(x < -100)
            x = -100;
    }

    // Move car right
    void moveRight()
    {
        x += 10;

        if(x > 850)
            x = 850;
    }

    // Toggle automatic movement
    void toggleMovement()
    {
        automatic = !automatic;
    }

    // Reset car
    void reset()
    {
        x = 300;
        y = 160;
        automatic = false;
    }
};

// Create car object
Car car;

// Base class pointer
GameObject *objects[1] = { &car };

// Draw circle
void drawCircle(float x, float y, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.14159f / 180.0f;

        glVertex2f(x + radius * cos(angle),
                   y + radius * sin(angle));
    }

    glEnd();
}

// Draw background
void drawBackground()
{
    // Sky
    glColor3f(0.4f, 0.75f, 1.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0, 200);
        glVertex2f(800, 200);
        glVertex2f(800, 600);
        glVertex2f(0, 600);
    glEnd();

    // Sun
    glColor3f(1.0f, 0.85f, 0.1f);
    drawCircle(680, 500, 45);

    // Mountains
    glColor3f(0.35f, 0.45f, 0.55f);

    glBegin(GL_TRIANGLES);
        glVertex2f(0, 270);
        glVertex2f(160, 480);
        glVertex2f(320, 270);

        glVertex2f(200, 270);
        glVertex2f(420, 500);
        glVertex2f(650, 270);

        glVertex2f(500, 270);
        glVertex2f(680, 450);
        glVertex2f(800, 270);
    glEnd();

    // Green hills
    glColor3f(0.15f, 0.6f, 0.2f);

    glBegin(GL_POLYGON);
        glVertex2f(0, 200);
        glVertex2f(0, 300);
        glVertex2f(150, 340);
        glVertex2f(300, 270);
        glVertex2f(480, 330);
        glVertex2f(650, 280);
        glVertex2f(800, 330);
        glVertex2f(800, 200);
    glEnd();

    // Grass
    glColor3f(0.1f, 0.65f, 0.15f);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 230);
        glVertex2f(0, 230);
    glEnd();

    // Trees
    for(int i = 0; i < 4; i++)
    {
        float tx = 80 + i * 210;

        // Tree trunk
        glColor3f(0.4f, 0.2f, 0.05f);

        glBegin(GL_POLYGON);
            glVertex2f(tx - 8, 220);
            glVertex2f(tx + 8, 220);
            glVertex2f(tx + 8, 270);
            glVertex2f(tx - 8, 270);
        glEnd();

        // Tree leaves
        glColor3f(0.0f, 0.4f, 0.1f);

        glBegin(GL_TRIANGLES);
            glVertex2f(tx - 35, 265);
            glVertex2f(tx, 330);
            glVertex2f(tx + 35, 265);

            glVertex2f(tx - 30, 290);
            glVertex2f(tx, 350);
            glVertex2f(tx + 30, 290);
        glEnd();
    }

    // Road
    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 200);
        glVertex2f(0, 200);
    glEnd();

    // Road borders
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(4);

    glBegin(GL_LINES);
        glVertex2f(0, 15);
        glVertex2f(800, 15);

        glVertex2f(0, 185);
        glVertex2f(800, 185);
    glEnd();

    // Road divider
    glLineWidth(5);
    glBegin(GL_LINES);

    for(int i = 0; i < 800; i += 100)
    {
        glVertex2f(i, 100);
        glVertex2f(i + 50, 100);
    }

    glEnd();
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();

    // Draw objects using polymorphism
    for(int i = 0; i < 1; i++)
    {
        objects[i]->draw();
    }

    glutSwapBuffers();
}

// Timer function
void timer(int value)
{
    for(int i = 0; i < 1; i++)
    {
        objects[i]->update();
    }

    glutPostRedisplay();

    glutTimerFunc(16, timer, 0);
}

// Keyboard controls
void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        case ' ':
            car.toggleMovement();
            break;

        case 'r':
        case 'R':
            car.reset();
            break;

        case 'q':
        case 'Q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// Special keyboard controls
void specialKeys(int key, int mouseX, int mouseY)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            car.moveLeft();
            break;

        case GLUT_KEY_RIGHT:
            car.moveRight();
            break;
    }

    glutPostRedisplay();
}

// Initialize OpenGL
void init()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Experiment 7 - Moving Car using OOP");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(16, timer, 0);

    cout << "\n===== MOVING CAR CONTROLS =====\n";
    cout << "LEFT ARROW  - Move car left\n";
    cout << "RIGHT ARROW - Move car right\n";
    cout << "SPACE       - Start/Stop automatic movement\n";
    cout << "R           - Reset car position\n";
    cout << "Q           - Exit program\n";

    glutMainLoop();

    return 0;
}
