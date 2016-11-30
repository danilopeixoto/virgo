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

#include "data.h"

VIRGO_NAMESPACE_BEGIN

Triangle::Triangle(size_t v1, size_t v2, size_t v3)
    : v1(v1), v2(v2), v3(v3) {}

Triangle::~Triangle() {}

Mesh::Mesh() {}

Mesh::~Mesh() {
    for (size_t i = 0; i < triangles.size(); i++) {
        if (triangles[i] != nullptr)
            delete triangles[i];
    }

    triangles.clear();
}

Geometry::Geometry() {}

Geometry::~Geometry() {
    for (size_t i = 0; i < getMeshCount(); i++) {
        if (getMeshByIndex(i) != nullptr)
            delete getMeshByIndex(i);
    }

    for (size_t i = 0; i < getVertexCount(); i++) {
        if (points[i] != nullptr)
            delete points[i];
    }

    meshes.clear();
    points.clear();
}

Mesh * Geometry::getMeshByIndex(size_t index) const {
    if (meshes[index] != nullptr)
        return meshes[index];

    return nullptr;
}

Mesh * Geometry::getMeshByName(const char * meshName) const {
    for (size_t i = 0; i < getMeshCount(); i++) {
        if (getMeshByIndex(i) != nullptr) {
            if (getMeshByIndex(i)->name == meshName)
                return getMeshByIndex(i);
        }
    }

    return nullptr;
}

void Geometry::getMeshDataByIndex(size_t index,
    vector<Vector *> & points, vector<Triangle *> & triangles) const {
    Mesh * mesh = getMeshByIndex(index);

    if (mesh == nullptr)
        return;

    Vector * point = nullptr;
    Triangle * triangle = nullptr;

    for (size_t i = 0; i < mesh->triangles.size(); i++) {
        triangle = mesh->triangles[i];

        point = new Vector;
        *point = *this->points[triangle->v1 - 1];
        points.push_back(point);

        point = new Vector;
        *point = *this->points[triangle->v2 - 1];
        points.push_back(point);

        point = new Vector;
        *point = *this->points[triangle->v3 - 1];
        points.push_back(point);

        triangle = new Triangle;

        triangle->v1 = i * 3 + 1;
        triangle->v2 = i * 3 + 2;
        triangle->v3 = i * 3 + 3;

        triangles.push_back(triangle);
    }
}

void Geometry::getMeshDataByName(const char * meshName,
    vector<Vector *> & points, vector<Triangle *> & triangles) const {
    for (size_t i = 0; i < getMeshCount(); i++) {
        if (getMeshByIndex(i)->name == meshName) {
            getMeshDataByIndex(i, points, triangles);;
            break;
        }
    }
}

size_t Geometry::getVertexCount() const {
    return points.size();
}

size_t Geometry::getPolygonCount() const {
    size_t polygonCount = 0;

    for (size_t i = 0; i < getMeshCount(); i++) {
        if (getMeshByIndex(i) != nullptr)
            polygonCount += getMeshByIndex(i)->triangles.size();
    }

    return polygonCount;
}

size_t Geometry::getMeshCount() const {
    return meshes.size();
}

VIRGO_NAMESPACE_END