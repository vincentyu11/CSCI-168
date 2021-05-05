#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;
void redraw( void ) {
glDepthFunc(GL_LESS);
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//3-side
glColor3f(1, 0, 0);
glBegin(GL_TRIANGLES);
glVertex3f(1.0, 7.0, 0.0);
glVertex3f(3.0, 7.0, 0.0);
glVertex3f(2.0, (sqrt(3.0)/2)*2 + 7.0, 0.0);
glEnd();
//4-side
glColor4f(0, 0, 1, 0.5);
glBegin(GL_POLYGON);
glVertex3f(2.0, 6.0, 5.0);
glVertex3f(3.5, 6.0, 5.0);
glVertex3f(3.5, 7.5, 5.0);
glVertex3f(2.0, 7.5, 5.0);
glEnd();
//5-side
glColor3f(0, 1, 0);
glBegin(GL_POLYGON);
glVertex3f(5.0-(cos((M_PI/180)*-54)), 8.0-(sin((M_PI/180)*54)), 0.0);
glVertex3f(5.0+(cos((M_PI/180)*-54)), 8.0-(sin((M_PI/180)*54)), 0.0);
glVertex3f(5.0+(cos((M_PI/180)*18)), 8.0+(sin((M_PI/180)*18)), 0.0);
glVertex3f(5.0, 9.0, 0.0);
glVertex3f(5.0-(cos((M_PI/180)*18)), 8.0+(sin((M_PI/180)*18)), 0.0);
glEnd();
//6-side
glColor3f(0, 1, 1);
glBegin(GL_POLYGON);
glVertex3f(1.0, 3.0, 0.0);
glVertex3f(1.5, 3.0-(sqrt(3.0)/2), 0.0);
glVertex3f(2.5, 3.0-(sqrt(3.0)/2), 0.0);
glVertex3f(3.0, 3.0, 0.0);
glVertex3f(2.5, 3.0+(sqrt(3.0)/2), 0.0);
glVertex3f(1.5, 3.0+(sqrt(3.0)/2), 0.0);
glEnd();
//7-side
glColor3f(1, 1, 0);
glBegin(GL_POLYGON);
glVertex3f(5.0-sin((M_PI/180)*(360/14)), 3.0-cos((M_PI/180)*(360/14)), 0.0);
glVertex3f(5.0+sin((M_PI/180)*(360/14)), 3.0-cos((M_PI/180)*(360/14)), 0.0);
glVertex3f(5.0+(sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2), (3.0-cos((M_PI/180)*(360/14)))+sqrt(((sin((M_PI/180)*(360/14)))*(sin((M_PI/180)*(360/14))))+(((sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2)-(sin((M_PI/180)*(360/14))))*((sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2)-(sin((M_PI/180)*(360/14)))))), 0.0);
glVertex3f(5.0+(((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14)))), (4.0-sqrt(((2*sin((M_PI/180)*(360/14)))*(2*sin((M_PI/180)*(360/14))))-((((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14))))*(((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14))))))), 0.0);
glVertex3f(5.0, 4.0, 0.0);
glVertex3f(5.0-(((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14)))), (4.0-sqrt(((2*sin((M_PI/180)*(360/14)))*(2*sin((M_PI/180)*(360/14))))-((((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14))))*(((2*sin((M_PI/180)*(360/14))))*(sin((M_PI/180)*(900/14))))))), 0.0);
glVertex3f(5.0-(sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2), (3.0-cos((M_PI/180)*(360/14)))+sqrt(((sin((M_PI/180)*(360/14)))*(sin((M_PI/180)*(360/14))))+(((sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2)-(sin((M_PI/180)*(360/14))))*((sqrt(2-(2*cos((M_PI/180)*(1080/7))))/2)-(sin((M_PI/180)*(360/14)))))), 0.0);
glEnd();
//8-side
glColor3f(1, 0, 1);
glBegin(GL_POLYGON);
glVertex3f(8.0, 3.0, 0.0);
glVertex3f(8.0+(1/sqrt(2.0)), 4.0-(1/sqrt(2.0)), 0.0);
glVertex3f(9.0, 4.0, 0.0);
glVertex3f(8.0+(1/sqrt(2.0)), 4.0+(1/sqrt(2.0)), 0.0);
glVertex3f(8.0, 5.0, 0.0);
glVertex3f(8.0-(1/sqrt(2.0)), 4.0+(1/sqrt(2.0)), 0.0);
glVertex3f(7.0, 4.0, 0.0);
glVertex3f(8.0-(1/sqrt(2.0)), 4.0-(1/sqrt(2.0)), 0.0);
glEnd();

glutSwapBuffers();
}



int main(int argc, char *argv[]) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
glutCreateWindow("One triangle");
glutPositionWindow(10,10);
glutReshapeWindow(700,700);
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
