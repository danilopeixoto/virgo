// Copyright (c) 2016, Danilo Peixoto and Gabriel Gustavo. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "viewport.h"
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>

VIRGO_NAMESPACE_BEGIN

Viewport * Viewport::instance = nullptr;

Viewport::Viewport() {
    window = -1;
    object = -1;

    windowWidth = 800;
    windowHeight = 500;

    enableGrid = true;
    enableWireframe = true;
    enableShade = true;

    sensitivity = 0.25;

    mouseInfo.leftButton = false;
    mouseInfo.middleButton = false;
    mouseInfo.rightButton = false;

    instance = this;
}

Viewport::~Viewport() {}

void Viewport::show() {
    int x, y, argc;

    argc = 0;
    glutInit(&argc, nullptr);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    x = (glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2;
    y = (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight - glutGet(GLUT_WINDOW_HEADER_HEIGHT)) / 2;

    glutInitWindowPosition(x, y);
    glutInitWindowSize(windowWidth, windowHeight);

    window = glutCreateWindow("Viewport");

    initialize();

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardEventCallback);
    glutMouseFunc(mouseEventCallback);
    glutMotionFunc(mouseMoveEventCallback);
    glutMouseWheelFunc(mouseWheelEventCallback);
    glutCloseFunc(closeEventCallback);

    loadObject();

    glutMainLoop();
}

void Viewport::close() {
    if (object != -1)
        glDeleteLists(object, 1);
    
    if (window != -1)
        glutLeaveMainLoop();
}

void Viewport::loadGeometry(const Geometry * geometry) {
    this->geometry = (Geometry *)geometry;

    setDefaultViewport();
}

void Viewport::initialize() {
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glEnable(GL_DEPTH_TEST);
    glEnable(GLUT_MULTISAMPLE);
    glShadeModel(GL_FLAT);

    glClearColor(0.35, 0.35, 0.35, 1.0);
}

void Viewport::loadObject() {
    if (geometry == nullptr)
        return;

    if (object != -1)
        glDeleteLists(object, 1);

    object = glGenLists(1);

    glNewList(object, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    Mesh * mesh = nullptr;
    Vector * points[3] = { nullptr };

    Vector normal;

    for (size_t i = 0; i < geometry->getMeshCount(); i++) {
        mesh = geometry->getMeshByIndex(i);

        for (size_t j = 0; j < mesh->triangles.size(); j++) {
            points[0] = geometry->points[mesh->triangles[j]->v1 - 1];
            points[1] = geometry->points[mesh->triangles[j]->v2 - 1];
            points[2] = geometry->points[mesh->triangles[j]->v3 - 1];

            normal = (*points[1] - *points[0]).cross(*points[2] - *points[0]).normalize();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(points[0]->x, points[0]->y, points[0]->z);
            glVertex3f(points[1]->x, points[1]->y, points[1]->z);
            glVertex3f(points[2]->x, points[2]->y, points[2]->z);
        }
    }

    glEnd();
    glEndList();
    glFlush();
}

void Viewport::drawObject() {
    if (enableShade) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1.0, 1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glCallList(object);
    }

    if (enableWireframe) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor4f(0, 0, 0.35, 1.0);
        glLineWidth(1.0);

        glCallList(object);
    }
}

void Viewport::drawGrid(int size) {
    if (enableGrid) {
        if (size < 0)
            return;

        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor4f(0.25, 0.25, 0.25, 1.0);

        for (int i = -size; i <= size; i++) {
            if (i != 0)
                glLineWidth(1.0);
            else
                glLineWidth(2.0);

            glBegin(GL_LINES);

            glVertex3f((float)i, 0, -(float)size);
            glVertex3f((float)i, 0, (float)size);

            glVertex3f(-(float)size, 0, (float)i);
            glVertex3f((float)size, 0, (float)i);

            glEnd();
            glFlush();
        }

        drawGrid(size - 10);
    }
}

void Viewport::setDefaultViewport() {
    mouseMotion = Vector(0, 0, 0);
    mouseRotation = Vector(0, 0, 0);
}

void Viewport::display() {
    Vector axis;
    float viewMatrix[16];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(mouseMotion.x, mouseMotion.y, mouseMotion.z);
    glRotatef(mouseRotation.x, 0, 1.0, 0);

    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
    axis = Vector(-viewMatrix[2], -viewMatrix[6], -viewMatrix[10]).cross(Vector(0, 1.0, 0));

    glRotatef(mouseRotation.y, axis.x, axis.y, axis.z);

    drawGrid(10);
    drawObject();

    glutSwapBuffers();
}

void Viewport::reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, width, height);

    glLoadIdentity();
    gluPerspective(45.0, width / (float)height, 0.001, 1000.0);

    glutPostRedisplay();
}

void Viewport::keyboardEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
        case 'D':
            setDefaultViewport();
            break;
        case 'g':
        case 'G':
            enableGrid = (enableGrid == GLUT_DOWN);
            break;
        case 'w':
        case 'W':
            enableWireframe = (enableWireframe == GLUT_DOWN);
            break;
        case 's':
        case 'S':
            enableShade = (enableShade == GLUT_DOWN);
            break;
        case ESC:
            close();
            break;
    }

    glutPostRedisplay();
}

void Viewport::mouseEvent(int button, int state, int x, int y) {
    mouseInfo.position = Point(x, y);

    mouseInfo.leftButton = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
    mouseInfo.middleButton = (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN);
    mouseInfo.rightButton = (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN);

    glutPostRedisplay();
}

void Viewport::mouseMoveEvent(int x, int y) {
    x = (x > 0) ? x : 0;
    y = (y > 0) ? y : 0;

    if (mouseInfo.leftButton) {
        mouseRotation.x += (x - (float)mouseInfo.position.x) * sensitivity;
        mouseRotation.y += (y - (float)mouseInfo.position.y) * sensitivity;
    }

    if (mouseInfo.middleButton) {
        mouseMotion.x += (x - (float)mouseInfo.position.x) * sensitivity * 0.5;
        mouseMotion.y -= (y - (float)mouseInfo.position.y) * sensitivity * 0.5;
    }

    if (mouseInfo.rightButton) {
        mouseMotion.z += (x - (float)mouseInfo.position.x) * sensitivity;
        mouseMotion.z += (y - (float)mouseInfo.position.y) * sensitivity;
    }

    mouseInfo.position = Point(x, y);

    glutPostRedisplay();
}

void Viewport::mouseWheelEvent(int wheel, int direction, int x, int y) {
    mouseMotion.z += direction * sensitivity * 1.5;

    glutPostRedisplay();
}

void Viewport::displayCallback() {
    instance->display();
}

void Viewport::reshapeCallback(int width, int height) {
    instance->reshape(width, height);
}

void Viewport::keyboardEventCallback(unsigned char key, int x, int y) {
    instance->keyboardEvent(key, x, y);
}

void Viewport::mouseEventCallback(int button, int state, int x, int y) {
    instance->mouseEvent(button, state, x, y);
}

void Viewport::mouseMoveEventCallback(int x, int y) {
    instance->mouseMoveEvent(x, y);
}

void Viewport::mouseWheelEventCallback(int wheel, int direction, int x, int y) {
    instance->mouseWheelEvent(wheel, direction, x, y);
}

void Viewport::closeEventCallback() {
    instance->close();
}

VIRGO_NAMESPACE_END