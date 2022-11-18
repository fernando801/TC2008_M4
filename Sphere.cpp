#include "Sphere.h"

Sphere::Sphere(int dim, float vel)
{
    DimBoard = dim;
    //srand(time(nullptr));
    int c;

    //Se inicializa una posicion aleatoria dentro del tablero
    Position[0] = (float)(rand()%(2*DimBoard)) - DimBoard;
    Position[2] = (float)(rand()%(2*DimBoard)) - DimBoard;
    //Se inicializa el vector de direccion con un valor aleatorio
    Direction[0] = rand();
    Direction[1] = rand();
    Direction[2] = rand();
    //Se normaliza el vector de direccion
    float m = sqrt(Direction[0]*Direction[0] + Direction[1]*Direction[1] + Direction[2]*Direction[2]);
    Direction[0] /= m;
    Direction[1] /= m;
    Direction[2] /= m;
    //se multiplica el vector de direccion por la magnitud de la velocidad
    Direction[0] *= vel;
    Direction[1] *= vel;
    Direction[2] *= vel;

    // cout << Direction[0] << endl;
    // cout << Direction[1] << endl;
    // cout << Direction[2] << endl;
}

Sphere::~Sphere()
{
    //dtor
}

void Sphere::draw()
{
    glPushMatrix();
    glTranslatef(Position[0], Position[1], Position[2]);
    glScaled(size,size,size);
    //Se dibuja el Sphere
    glColor3f(Color[0],Color[1],Color[2]);
    glutSolidSphere(1, 50, 50);

    glPopMatrix();
}

void Sphere::update()
{    
    float new_x = Position[0] + Direction[0];
    float new_z = Position[2] + Direction[2];

    if (abs(new_x) <= DimBoard)
        Position[0] = new_x;
    else {
        Direction[0] *= -1.0;
        Position[0] += Direction[0];
    }

    if (abs(new_z) <= DimBoard)
        Position[2] = new_z;
    else {
        Direction[2] *= -1.0;
        Position[2] += Direction[2];
    }

}