//
//  OBJLoader.hpp
//  ModelsFromFile
//
//  Created by Laura del Pino Díaz on 18/4/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef OBJLoader_hpp
#define OBJLoader_hpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#endif /* OBJLoader_hpp */

#define KEY_ESCAPE 27

using namespace std;

class Model_OBJ
{
public:
    Model_OBJ();
    float* calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Load(char *filename);	// Loads the model
    void Draw();					// Draws the model on the screen
    void Release();				// Release the model
    
    float* normals;							// Stores the normals
    float* Faces_Triangles;					// Stores the triangles
    float* vertexBuffer;					// Stores the points which make the object
    long TotalConnectedPoints;				// Stores the total number of connected verteces
    long TotalConnectedTriangles;			// Stores the total number of connected triangles
    
};