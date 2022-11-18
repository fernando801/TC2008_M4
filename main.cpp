
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <random>
#include <iomanip>

#include "Cubo.h"
#include "Sphere.h"

// Variables dimensiones de la pantalla
int WIDTH = 500;
int HEIGTH = 500;
// Variables para establecer los valores de gluPerspective
float FOVY = 60.0;
float ZNEAR = 0.01;
float ZFAR = 900.0;
// Variables para definir la posicion del observador
// gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X = 300.0;
float EYE_Y = 200.0;
float EYE_Z = 300.0;
float CENTER_X = 0;
float CENTER_Y = 0;
float CENTER_Z = 0;
float UP_X = 0;
float UP_Y = 1;
float UP_Z = 0;
// Variables para dibujar los ejes del sistema
float X_MIN = -500;
float X_MAX = 500;
float Y_MIN = -500;
float Y_MAX = 500;
float Z_MIN = -500;
float Z_MAX = 500;
// Size del tablero
int DimBoard = 200;

void *objects[10];

Cubo c1(DimBoard, 0.3);
Cubo c2(DimBoard, 0.6);
Cubo c3(DimBoard, 0.2);
Cubo c4(DimBoard, 1.0);

void drawAxis()
{
    glLineWidth(3.0);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(X_MIN, 0.0, 0.0);
    glVertex3f(X_MAX, 0.0, 0.0);
    glEnd();
    // Y axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0, Y_MIN, 0.0);
    glVertex3f(0.0, Y_MAX, 0.0);
    glEnd();
    // Z axis in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, Z_MIN);
    glVertex3f(0.0, 0.0, Z_MAX);
    glEnd();
    glLineWidth(1.0);
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH / HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X, EYE_Y, EYE_Z, CENTER_X, CENTER_Y, CENTER_Z, UP_X, UP_Y, UP_Z);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    srand(time(nullptr));
}

void display()
{
    bool move = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();
    glColor3f(0.3, 0.3, 0.3);
    // El piso es dibujado
    glBegin(GL_QUADS);
    glVertex3d(-DimBoard, 0.0, -DimBoard);
    glVertex3d(-DimBoard, 0.0, DimBoard);
    glVertex3d(DimBoard, 0.0, DimBoard);
    glVertex3d(DimBoard, 0.0, -DimBoard);
    glEnd();

    for (int i = 0; i < 5; i++)
    {
        move = true;
        for (int j = 0; j < 5; j++)
        {
            if (
                i != j && sqrt(
                    pow(((Cubo *)objects[i])->Position[0] + ((Cubo *)objects[i])->Direction[0] - ((Cubo *)objects[j])->Position[0], 2) +
                    pow(((Cubo *)objects[i])->Position[1] + ((Cubo *)objects[i])->Direction[1] - ((Cubo *)objects[j])->Position[1], 2) +
                    pow(((Cubo *)objects[i])->Position[2] + ((Cubo *)objects[i])->Direction[2] - ((Cubo *)objects[j])->Position[2], 2)
                ) < (((Cubo *)objects[i])->radius + ((Cubo *)objects[j])->radius))
            {
                move = false;
            }
        }

        for (int j = 5; j < 10; j++)
        {
            if (
                sqrt(
                    pow(((Cubo *)objects[i])->Position[0] + ((Cubo *)objects[i])->Direction[0] - ((Sphere *)objects[j])->Position[0], 2) +
                    pow(((Cubo *)objects[i])->Position[1] + ((Cubo *)objects[i])->Direction[1] - ((Sphere *)objects[j])->Position[1], 2) +
                    pow(((Cubo *)objects[i])->Position[2] + ((Cubo *)objects[i])->Direction[2] - ((Sphere *)objects[j])->Position[2], 2)
                ) < (((Cubo *)objects[i])->radius + ((Cubo *)objects[j])->radius))
            {
                move = false;
            }
        }

        if (move)
        {
            ((Cubo *)objects[i])->update();
        }
    }

    for (int i = 5; i < 10; i++)
    {
        move = true;
        for (int j = 0; j < 5; j++)
        {
            if (
                sqrt(
                    pow(((Sphere *)objects[i])->Position[0] + ((Sphere *)objects[i])->Direction[0] - ((Cubo *)objects[j])->Position[0], 2) +
                    pow(((Sphere *)objects[i])->Position[1] + ((Sphere *)objects[i])->Direction[1] - ((Cubo *)objects[j])->Position[1], 2) +
                    pow(((Sphere *)objects[i])->Position[2] + ((Sphere *)objects[i])->Direction[2] - ((Cubo *)objects[j])->Position[2], 2)
                ) < (((Sphere *)objects[i])->radius + ((Cubo *)objects[j])->radius))
            {
                move = false;
            }
        }

        for (int j = 5; j < 10; j++)
        {
            if (
                i != j && sqrt(
                    pow(((Sphere *)objects[i])->Position[0] + ((Sphere *)objects[i])->Direction[0] - ((Sphere *)objects[j])->Position[0], 2) +
                    pow(((Sphere *)objects[i])->Position[1] + ((Sphere *)objects[i])->Direction[1] - ((Sphere *)objects[j])->Position[1], 2) +
                    pow(((Sphere *)objects[i])->Position[2] + ((Sphere *)objects[i])->Direction[2] - ((Sphere *)objects[j])->Position[2], 2)
                ) < (((Sphere *)objects[i])->radius + ((Sphere *)objects[j])->radius))
            {
                move = false;
            }
        }

        if (move)
        {
            ((Sphere *)objects[i])->update();
        }
    }

    for (int i = 0; i < 5; i++)
    {
        ((Cubo *)objects[i])->draw();
    }

    for (int i = 5; i < 10; i++)
    {
        ((Sphere *)objects[i])->draw();
    }

    glutSwapBuffers();
}

void idle()
{
    display();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    { // SOLID
    case 's':
    case 'S':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glShadeModel(GL_FLAT);
        break;
    // INTERPOL
    case 'i':
    case 'I':
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;

    case 'w':
    case 'W':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;

    case 27: // escape
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 5; i++)
    {
        objects[i] = new Cubo(DimBoard, 1);
    }

    for (int i = 5; i < 10; i++)
    {
        objects[i] = new Sphere(DimBoard, 1);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Cubo 1");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
