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

#include "tetrahedralMeshGenerator.h"
#include <vector>
#include <tetgen.h>

VIRGO_NAMESPACE_BEGIN

using namespace std;

TetrahedralMeshGenerator::TetrahedralMeshGenerator() {}
TetrahedralMeshGenerator::~TetrahedralMeshGenerator() {}

void TetrahedralMeshGenerator::tetrahedralizeMesh(Geometry * geometry, size_t index,
    float radiusEdgeRatio) const {
    Mesh * mesh = geometry->getMeshByIndex(index);

    if (mesh == nullptr)
        return;

    vector<Vector *> points;
    vector<Triangle *> triangles;

    geometry->getMeshDataByIndex(index, points, triangles);

    size_t offset = geometry->getVertexCount();

    tetgenio * input = new tetgenio;
    tetgenio * output = new tetgenio;

    input->firstnumber = 1;
    output->firstnumber = 1;

    tetgenio::facet * facet = nullptr;
    tetgenio::polygon * polygon = nullptr;

    tetgenbehavior behavior;
    behavior.plc = 1;
    behavior.quality = 1;
    behavior.order = 0;
    behavior.facesout = 1;
    behavior.quiet = 1;
    behavior.minratio = radiusEdgeRatio;

    input->numberofpoints = (int)points.size();
    input->pointlist = new double[input->numberofpoints * 3];

    for (int i = 0; i < input->numberofpoints; i++) {
        input->pointlist[i * 3] = points[i]->x;
        input->pointlist[i * 3 + 1] = points[i]->y;
        input->pointlist[i * 3 + 2] = points[i]->z;
    }

    input->numberoffacets = (int)triangles.size();
    input->facetlist = new tetgenio::facet[input->numberoffacets];

    for (int i = 0; i < input->numberoffacets; i++) {
        facet = &input->facetlist[i];
        facet->numberofpolygons = 1;
        facet->polygonlist = new tetgenio::polygon[facet->numberofpolygons];
        facet->numberofholes = 0;
        facet->holelist = nullptr;

        polygon = &facet->polygonlist[0];
        polygon->numberofvertices = 3;
        polygon->vertexlist = new int[polygon->numberofvertices];
        polygon->vertexlist[0] = (int)triangles[i]->v1;
        polygon->vertexlist[1] = (int)triangles[i]->v2;
        polygon->vertexlist[2] = (int)triangles[i]->v3;
    }

    for (size_t i = 0; i < points.size(); i++) {
        if (points[i] != nullptr)
            delete points[i];
    }

    for (size_t i = 0; i < triangles.size(); i++) {
        if (triangles[i] != nullptr)
            delete triangles[i];
    }

    points.clear();
    triangles.clear();

    for (size_t i = 0; i < mesh->triangles.size(); i++) {
        if (mesh->triangles[i] != nullptr)
            delete mesh->triangles[i];
    }

    mesh->triangles.clear();
    
    tetrahedralize(&behavior, input, output);

    Vector * point = nullptr;
    Triangle * triangle = nullptr;

    for (int i = 0; i < output->numberofpoints; i++) {
        point = new Vector;

        point->x = output->pointlist[i * 3];
        point->y = output->pointlist[i * 3 + 1];
        point->z = output->pointlist[i * 3 + 2];

        geometry->points.push_back(point);
    }

    for (int i = 0; i < output->numberoftrifaces; i++) {
        triangle = new Triangle;

        triangle->v1 = (size_t)output->trifacelist[i * 3 + 2] + offset;
        triangle->v2 = (size_t)output->trifacelist[i * 3 + 1] + offset;
        triangle->v3 = (size_t)output->trifacelist[i * 3] + offset;

        mesh->triangles.push_back(triangle);
    }

    delete input;
    delete output;
}

VIRGO_NAMESPACE_END