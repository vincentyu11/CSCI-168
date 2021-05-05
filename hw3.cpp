#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

float xVertexC = 5.0;
float yVertexC = 5.0;
float xVertex2[4] = {7.0, 3.0, 3.0, 7.0};
float yVertex2[4] = {7.0, 7.0, 3.0, 3.0};
float xVertex3[4] = {3.0, 3.0, 7.0, 7.0};
float yVertex3[4] = {7.0, 3.0, 3.0, 7.0};

float threshold = 0.15;

int clicked = 0;
int vertexChosen;

enum MouseState {
    MOUSE_NONE,
    LEFT_BUTTON_DOWN
};
MouseState mouseState;

void redraw(void) {
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i=0;i<4;i++) {
        srand(i);
        glColor3f(0.01*float(rand()%100), 0.01*float(rand()%100), 0.01*float(rand()%100));
        glBegin(GL_TRIANGLES);
        glVertex3f(xVertexC, yVertexC, 0.0);
        glVertex3f(xVertex2[i], yVertex2[i], 0.0);
        glVertex3f(xVertex3[i], yVertex3[i], 0.0);
        glEnd();
    }

    for (int i=0;i<4;i++) {
        glLineWidth(3);
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex3f(xVertexC, yVertexC, 1.0);
        glVertex3f(xVertex2[i], yVertex2[i], 1.0);
        glVertex3f(xVertex2[i], yVertex2[i], 1.0);
        glVertex3f(xVertex3[i], yVertex3[i], 1.0);
        glEnd();
    }

    for (int i=0;i<4;i++) {
        glPointSize(7);
        glBegin(GL_POINTS);
        glVertex3f(xVertex2[i], yVertex2[i], 2.0);
        glEnd();
    }
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex3f(xVertexC, yVertexC, 2.0);
    glEnd();

    glutSwapBuffers();
}

void mousebutton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (y>=0 && y<=500){
            cout << x << " " << -(y-500) << endl;
        }
        float newx = x/50.0;
        float newy = (-(y-500))/50.0;
        if (abs((newx - xVertexC))<=threshold && abs((newy - yVertexC))<= threshold) {
            clicked = 1;
            vertexChosen = 5;
        }
        for (int i=0;i<4;i++) {
            if (abs((newx - xVertex3[i])) <= threshold && abs((newy - yVertex3[i]))<= threshold) {
                clicked = 1;
                vertexChosen = i;
            }
        }
        mouseState = LEFT_BUTTON_DOWN;

    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        clicked = 0;
        vertexChosen = NULL;
        mouseState = MOUSE_NONE;
    }
    glutPostRedisplay();
}

void mousemove (int x, int y) {
    cout << x << " " << -(y-500) << endl;
    float newx = x/50.0;
    float newy = (-(y-500))/50.0;
    if (clicked == 1){
        if (vertexChosen == 5) {
            xVertexC = newx;
            yVertexC = newy;
            redraw();
        }
        else if (vertexChosen == 0) {
            xVertex2[vertexChosen+1] = newx;
            yVertex2[vertexChosen+1] = newy;
            xVertex3[vertexChosen] = newx;
            yVertex3[vertexChosen] = newy;
            redraw();
        }
        else if (vertexChosen == 1) {
            xVertex2[vertexChosen+1] = newx;
            yVertex2[vertexChosen+1] = newy;
            xVertex3[vertexChosen] = newx;
            yVertex3[vertexChosen] = newy;
            redraw();
        }
        else if (vertexChosen == 2) {
            xVertex2[vertexChosen+1] = newx;
            yVertex2[vertexChosen+1] = newy;
            xVertex3[vertexChosen] = newx;
            yVertex3[vertexChosen] = newy;
            redraw();
        }
        else if (vertexChosen == 3) {
            xVertex2[vertexChosen-3] = newx;
            yVertex2[vertexChosen-3] = newy;
            xVertex3[vertexChosen] = newx;
            yVertex3[vertexChosen] = newy;
            redraw();
        }
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Triangles");
    glutPositionWindow(10,10);
    glutReshapeWindow(500,500);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,10.0,0.0,10.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(redraw);
    glutMouseFunc(mousebutton);
    glutMotionFunc(mousemove);
    glutMainLoop();
    return 0;
}
