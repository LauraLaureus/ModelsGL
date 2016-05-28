#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#define WINDOW_ANCHO 1000
#define WINDOW_ALTO 1000

#include "Model_PLY.h"
#include "OBJLoader.hpp"

// Espacio para las variables globales de la ventana
float gl_fovy = 60.0f;
float gl_fovy_min = 10.0f, gl_fovy_max = 90.0f, gl_fovy_paso = 1.0f;
float gl_cerca=1.0f, gl_lejos=300.0f;
float gl_center = 7.0f; // centro donde pondremos los objetos


// Espacio para otras variables globales
double theta = M_PI_2, phi=0.0;
double radio = 7.0;
Model_PLY* modelo;
//Model_OBJ* model;

// Espacio para la declaraciÛn de funciones
void InitGL();
void Display();
void ReshapeSize(int ancho, int alto);
void PosicionRaton(int x, int y);
void RuedaRaton(int key, int x, int y);

//main
int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_ANCHO, WINDOW_ALTO);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("OpenGL Practica 11 Laura ");
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutMotionFunc(PosicionRaton);
    glutSpecialFunc(RuedaRaton);
    
    modelo = new Model_PLY();
    modelo->Load("/Users/lala/ModelsFromFile/ModelsFromFile/cow.ply");
    //modelo->Load("/Users/lala/ModelsFromFile/ModelsFromFile/bun_zipper.ply");
    //modelo->Load("/Users/lala/ModelsFromFile/ModelsFromFile/turbine.ply");
    //modelo->Load("/Users/lala/ModelsFromFile/ModelsFromFile/street_lamp.ply");
    //modelo->Load("/Users/lala/ModelsFromFile/ModelsFromFile/sandal.ply");
    
    
    //model = new Model_OBJ();
    //model->Load("/Users/lala/ModelsFromFile/ModelsFromFile/teapot.obj");
    
    glutMainLoop(); // bucle principal
    
    return 0;
}

void setViewport(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
}

void setProjection(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(gl_fovy, (float)ancho / (float)alto, gl_cerca, gl_lejos);
}

void setModelView(){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void setLight0(){
    
    float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse[4] = {1.0f,1.0f,1.0f,1.0f};
    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f };
    
    float position[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float direction[4] = { -1.0f, -1.0f, -1.0f, 1.0f };
    float cut_off = 90.0f;
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cut_off);
    
    glEnable(GL_LIGHT0);
}



void InitGL(){
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    // para cambiar el criterio de lo que se ve.
    // LESS es el de defecto: se ve lo que tiene menor profundidad
    glDepthFunc(GL_LESS);
    // TO DO
    
    setViewport();
    setProjection();
    
    glEnable(GL_LIGHTING);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    
    setLight0();
}

// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
void ReshapeSize(int ancho, int alto){
    
    setViewport();
    setProjection();
    glutPostRedisplay();
}

void PosicionRaton(int x, int y){
    
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    
    theta = M_PI*(double)y / (double)alto;
    phi = - M_PI + 2*M_PI * (double)x / (double)ancho;
    glutPostRedisplay();
}

void RuedaRaton(int key, int x, int y){
    float sentido = 0.0;
    if(key == GLUT_KEY_UP) sentido = 1;
    if(key == GLUT_KEY_DOWN) sentido = -1;
    if(key == GLUT_KEY_UP || key == GLUT_KEY_DOWN ){
        gl_fovy -= gl_fovy_paso*(float)sentido;
        if (gl_fovy < gl_fovy_min) gl_fovy = gl_fovy_min;
        if (gl_fovy > gl_fovy_max) gl_fovy = gl_fovy_max;
        setProjection();
    }
    glutPostRedisplay();
}

void setMaterial(){
    
    const GLfloat ambient[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat diffuse[4] = { 0.7f, 0.0f, 0.0f, 1.0f };
    const GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat shininess = 100.0f;
    
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

// funciÛn de gestion de ventana
void Display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
    setModelView();
    
    // poicionamos el centro de coordenadas
    glTranslatef(0.0f, 0.0f, -gl_center);
    
    // el eje cenital es el Y
    float x = (float)(radio*sin(theta)*sin(phi));
    float y = (float)(radio*cos(theta));
    float z = (float)(radio*sin(theta)*cos(phi))+100;
    gluLookAt(x,y,z,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f); // mira al (0,0,0)
    
    setMaterial();
    // TO DO
    modelo->Draw();
    //model->Draw();
    
    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}

