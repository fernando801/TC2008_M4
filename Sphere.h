#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include <random>
#include <iomanip>
#include <GL/glut.h>
#include <iostream>

using namespace std;

class Sphere
{
    public:
        float size = 10.0;
        float radius = size;
        float Position[3] = {0.0, size, 0.0};
        float Direction[3] = {0.0, size, 0.0};

        Sphere(int, float);
        ~Sphere();
        void draw();
        void update();

    protected:

    private:
        float vertexCoords[24] = {  // Coordinates for the vertices of a cube.
                   1,1,1,   1,1,-1,   1,-1,-1,   1,-1,1,
                  -1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1  };

        float vertexColors[24] = {  // An RGB color value for each vertex
                   1,1,1,   1,0,0,   1,1,0,   0,1,0,
                   0,0,1,   1,0,1,   0,0,0,   0,1,1  };

        int elementArray[24] = {  // Vertex number for the six faces.
                  0,1,2,3, 0,3,7,4, 0,4,5,1,
                  6,2,1,5, 6,5,4,7, 6,7,3,2  };

        //Vector de direccion
        float Color[3] = {0.0, 1.0, 1.0};
        int DimBoard;

};

#endif // Sphere_H