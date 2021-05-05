#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

const float xC = 5.0;
const float yC = 5.0;
const float zC = 0.0;

const float radius = 1.5;

const float xS = 5.0;
const float yS = 5.0;
const float zS = 10.0;

const float xSt = 8.0;
const float ySt = 3.0;
const float zSt = 10.0;

const float xP0 = 6.0;
const float yP0 = 1.0;
const float zP0 = 0.0;

const float xP1 = 9.0;
const float yP1 = 2.0;
const float zP1 = 2.0;

const float xP2 = 8.0;
const float yP2 = 5.0;
const float zP2 = 1.0;

float t = 1.0;
float tT = 1.0;

void lighting();
void redraw();
void keypress(unsigned char key, int x, int y);
bool raySphereIntersec(float xC, float yC, float zC, float xD, float yD, float zD, float xS, float yS, float zS);
bool rayTriangleIntersec(float xP0, float yP0, float zP0, float xP1, float yP1, float zP1, float xP2, float yP2, float zP2,
 float xD, float yD, float zD, float xSt, float ySt, float zSt);


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("4");
    glutPositionWindow(100,100);
    glutReshapeWindow(128,128);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,10.0,0.0,10.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}

void redraw(void) {

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting();

    glBegin(GL_POINTS);
    for (int i=0; i<128; i++) {
        for (int j=0; j<128; j++) {
            float x = i/12.8;
            float y = j/12.8;
            float z = -10.0;
            float xD = x - xS;
            float yD = y - yS;
            float zD = z - zS;
            float normalize = sqrt((xD*xD)+(yD*yD)+(zD*zD));
            float xDnormal = xD/normalize;
            float yDnormal = yD/normalize;
            float zDnormal = zD/normalize;
            bool intersect = raySphereIntersec(xC,yC,zC,xDnormal,yDnormal,zDnormal,xS,yS,zS);
            if (intersect == true) {
                float newi = xS + t*xDnormal;
                float newj = yS + t*yDnormal;
                float newk = zS + t*zDnormal;

                glColor3f(0.7,0.2,0.1);
                glNormal3f(newi-xC,newj-yC,newk-zC);
                glVertex3f(newi,newj,newk);
            }
        }
    }
    glEnd();


    glBegin(GL_POINTS);
    for (int i=0; i<128; i++) {
        for (int j=0; j<128; j++) {
            float x = i/12.8;
            float y = j/12.8;
            float z = -10.0;
            float xD = x - xSt;
            float yD = y - ySt;
            float zD = z - zSt;
            float normalize = sqrt((xD*xD)+(yD*yD)+(zD*zD));
            float xDnormal = xD/normalize;
            float yDnormal = yD/normalize;
            float zDnormal = zD/normalize;
            bool intersect = rayTriangleIntersec(xP0,yP0,zP0,xP1,yP1,zP1,xP2,yP2,zP2,xDnormal,yDnormal,zDnormal,xSt,ySt,zSt);
            if (intersect == true) {
                float newi = xSt + tT*xDnormal;
                float newj = ySt + tT*yDnormal;
                float newk = zSt + tT*zDnormal;

                glColor3f(0.1,0.2,0.8);
                glNormal3f(newi-7.0,newj-3.5,newk+1.0);
                glVertex3f(newi,newj,newk);
            }
        }
    }
    glEnd();

    glutSwapBuffers();
}

bool raySphereIntersec(float xC, float yC, float zC, float xD, float yD, float zD, float xS, float yS, float zS) {
    float xM = xS - xC;
    float yM = yS - yC;
    float zM = zS - zC;
    float M = xM + yM + zM;
    float DdotM = (xD*xM) + (yD*yM) + (zD*zM);
    float discriminant = (DdotM*DdotM)-((M*M)-(radius*radius));
    if (discriminant < 0) {
        return false;
    }
    else {
        if (discriminant == 0) {
            t = -1*DdotM;
        }
        else {
            float t1 = (-1*DdotM) + sqrt(discriminant);
            float t2 = (-1*DdotM) - sqrt(discriminant);
            if (t1 < t2) {
                t = t1;
            }
            else {
                t = t2;
            }
        }
        return true;
    }
}

bool rayTriangleIntersec(float xP0, float yP0, float zP0, float xP1, float yP1, float zP1, float xP2, float yP2, float zP2,
 float xD, float yD, float zD, float xSt, float ySt, float zSt) {
    float xE0 = xP1 - xP0;
    float yE0 = yP1 - yP0;
    float zE0 = zP1 - zP0;
    float xE1 = xP2 - xP1;
    float yE1 = yP2 - yP1;
    float zE1 = zP2 - zP1;
    float xE2 = xP0 - xP2;
    float yE2 = yP0 - yP2;
    float zE2 = zP0 - zP2;
    float xnormal = (yE0*zE1) - (zE0*yE1);
    float ynormal = -((xE0*zE1)-(zE0*xE1));
    float znormal = (xE0*yE1) - (yE0*xE1);
    float normalize = sqrt((xnormal*xnormal) + (ynormal*ynormal) + (znormal*znormal));
    xnormal /= normalize;
    ynormal /= normalize;
    znormal /= normalize;
    float k = (xnormal*xP0) + (ynormal*yP0) + (znormal*zP0);
    float PdotN = (xnormal*xSt) + (ynormal*ySt) + (znormal*zSt);
    float DdotN = (xnormal*xD) + (ynormal*yD) + (znormal*zD);
    tT = (k-PdotN)/DdotN;
    float xR = xSt + tT*xD;
    float yR = ySt + tT*yD;
    float zR = xSt + tT*zD;
    float xRminP0 = xR - xP0;
    float yRminP0 = yR - yP0;
    float zRminP0 = zR - zP0;
    float xRminP1 = xR - xP1;
    float yRminP1 = yR - yP1;
    float zRminP1 = zR - zP1;
    float xRminP2 = xR - xP2;
    float yRminP2 = yR - yP2;
    float zRminP2 = zR - zP2;
    float xE0crossRminP0 = (yE0*zRminP0) - (zE0*yRminP0);
    float yE0crossRminP0 = -((xE0*zRminP0) - (zE0*xRminP0));
    float zE0crossRminP0 = (xE0*yRminP0) - (yE0*xRminP0);
    float xE1crossRminP1 = (yE1*zRminP1) - (zE1*yRminP1);
    float yE1crossRminP1 = -((xE1*zRminP1) - (zE1*xRminP1));
    float zE1crossRminP1 = (xE1*yRminP1) - (yE1*xRminP1);
    float xE2crossRminP2 = (yE2*zRminP2) - (zE2*yRminP2);
    float yE2crossRminP2 = -((xE2*zRminP2) - (zE2*xRminP2));
    float zE2crossRminP2 = (xE2*yRminP2) - (yE2*xRminP2);
    float NdotE0crossRminP0 = (xnormal*xE0crossRminP0) + (ynormal*yE0crossRminP0) + (znormal*zE0crossRminP0);
    float NdotE1crossRminP1 = (xnormal*xE1crossRminP1) + (ynormal*yE1crossRminP1) + (znormal*zE1crossRminP1);
    float NdotE2crossRminP2 = (xnormal*xE2crossRminP2) + (ynormal*yE2crossRminP2) + (znormal*zE2crossRminP2);
    if ((NdotE0crossRminP0 > 0) && (NdotE1crossRminP1 > 0) && (NdotE2crossRminP2 > 0)) {
        return true;
    }
    else {
        return false;
    }
 }


void lighting() {
    const GLfloat light_ambient[] = {0.5f,0.5f,0.7f,1.0f};
    const GLfloat light_diffuse[] = {0.4f,0.5f,0.5f,1.0f};
    const GLfloat light_specular[] = {0.5f,0.5f,0.5f,1.0f};
    const GLfloat light_position[] = {10.0f,10.0f,5.0f,1.0f};

    const GLfloat mat_ambient[] = {0.9f,0.0f,0.0f,1.0f};
    const GLfloat mat_diffuse[] = {1.0f,0.8f,0.5f,1.0f};
    const GLfloat mat_specular[] = {1.0f,0.8f,0.0f,1.0f};
    const GLfloat mat_shininess[] = {3.0f};

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //gluLookAt(0,0,1,0,0,1,0,0,1);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

