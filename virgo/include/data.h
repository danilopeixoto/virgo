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

#ifndef DATA_H
#define DATA_H

#include "namespace.h"
#include <vector>
#include <string>
#include <OpenEXR\ImathVec.h>
#include <OpenEXR\ImathMatrix.h>

VIRGO_NAMESPACE_BEGIN

using namespace std;
using namespace Imath;

typedef Vec2<size_t> Point;
typedef Vec3<float> Vector;
typedef Matrix44<float> Matrix;

struct Triangle {
    Triangle(size_t = 0, size_t = 0, size_t = 0);
    ~Triangle();

    size_t v1, v2, v3;
};

struct Mesh {
    Mesh();
    ~Mesh();

    string name;
    vector<Triangle *> triangles;
};

struct Geometry {
    Geometry();
    ~Geometry();

    vector<Vector *> points;
    vector<Mesh *> meshes;

    Mesh * getMeshByIndex(size_t) const;
    Mesh * getMeshByName(const char *) const;

    void getMeshDataByIndex(size_t,
        vector<Vector *> &, vector<Triangle *> &) const;
    void getMeshDataByName(const char *,
        vector<Vector *> &, vector<Triangle *> &) const;

    size_t getVertexCount() const;
    size_t getPolygonCount() const;
    size_t getMeshCount() const;
};

VIRGO_NAMESPACE_END

#endif