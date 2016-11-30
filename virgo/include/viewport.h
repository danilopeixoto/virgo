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

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "namespace.h"
#include "data.h"

#define ESC 27

VIRGO_NAMESPACE_BEGIN

class Viewport {
public:
    Viewport();
    ~Viewport();

    void show();
    void loadGeometry(const Geometry *);

private:
    int window, object;

    Geometry * geometry;

    int windowWidth;
    int windowHeight;

    bool enableGrid, enableWireframe, enableShade;

    float sensitivity;

    struct MouseInfo {
        bool leftButton;
        bool middleButton;
        bool rightButton;

        Point position;
    } mouseInfo;

    Vector mouseMotion, mouseRotation;

    void initialize();
    void loadObject();
    void drawObject();
    void drawGrid(int);
    void setDefaultViewport();
    void close();

    void display();
    void reshape(int, int);
    void keyboardEvent(unsigned char, int, int);
    void mouseEvent(int, int, int, int);
    void mouseMoveEvent(int, int);
    void mouseWheelEvent(int, int, int, int);

    static void displayCallback();
    static void reshapeCallback(int, int);
    static void keyboardEventCallback(unsigned char, int, int);
    static void mouseEventCallback(int, int, int, int);
    static void mouseMoveEventCallback(int, int);
    static void mouseWheelEventCallback(int, int, int, int);
    static void closeEventCallback();

protected:
    static Viewport * instance;
};

VIRGO_NAMESPACE_END

#endif