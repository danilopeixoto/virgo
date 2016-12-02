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

#include "namespace.h"
#include "file.h"
#include <iostream>
#include <string>

VIRGO_NAMESPACE_BEGIN

File::File() {
    file = new fstream;
}

File::~File() {
    close();
    delete file;
}

void File::open(const char * filename, const FileMode & mode) {
    int filemode;

    switch (mode) {
        case FileMode::Read:
            filemode = fstream::in;
            break;
        case FileMode::Write:
            filemode = fstream::out;
            break;
        default:
            filemode = fstream::in | fstream::out | fstream::app;
    }

    file->open(filename, (fstream::openmode)filemode);
}

void File::close() {
    if (isOpen()) file->close();
}

bool File::isOpen() const {
    return file->is_open();
}

void File::read(Geometry * geometry) const {
    if (!isOpen()) return;

    string line, name;
    size_t i = 0;

    Mesh * mesh = nullptr;

    Vector * point = nullptr;
    Triangle * triangle = nullptr;

    while (getline(*file, line)) {
        if (line.substr(0, 2) == "v ") {
            point = new Vector;

            sscanf(line.c_str(), "%*s %f %f %f", &point->x, &point->y, &point->z);

            geometry->points.push_back(point);
        }
        else if (line.substr(0, 2) == "g ") {
            geometry->meshes.push_back(new Mesh);
            mesh = geometry->getMeshByIndex(i);

            mesh->name = line.substr(2);

            i++;
        }
        else if (line.substr(0, 2) == "f ") {
            triangle = new Triangle;

            sscanf(line.c_str(), "%*s %zu %zu %zu", &triangle->v1, &triangle->v2, &triangle->v3);

            mesh->triangles.push_back(triangle);
        }
        else {
            continue;
        }
    }
}

void File::write(const Geometry * geometry) {
    if (!isOpen()) return;

    const Mesh * mesh = nullptr;

    Vector * point;
    Triangle * triangle;

    for (size_t i = 0; i < geometry->getVertexCount(); i++) {
        point = geometry->points[i];
        *file << "v " << point->x << " " << point->y << " " << point->z << endl;
    }

    for (size_t i = 0; i < geometry->getMeshCount(); i++) {
        mesh = geometry->getMeshByIndex(i);

        *file << "g " << mesh->name << endl;

        for (size_t j = 0; j < mesh->triangles.size(); j++) {
            triangle = mesh->triangles[j];
            *file << "f " << triangle->v1 << " " << triangle->v2 << " " << triangle->v3 << endl;
        }
    }
}

VIRGO_NAMESPACE_END
