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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "namespace.h"
#include "data.h"
#include "file.h"
#include "viewport.h"
#include "tetrahedralMeshGenerator.h"
#include "translator.h"
#include <cstdio>
#include <string>
#include <vector>

VIRGO_NAMESPACE_BEGIN

using namespace std;

enum Theme {
    Light = 0,
    Dark
};

struct Preferences {
    Preferences(const Language & = Language::English,
        const Theme & = Theme::Light);
    ~Preferences();

    Language language;
    Theme theme;
};

class Application {
public:
    Application();
    ~Application();

    void show();

private:
    size_t option;
    string filename;

    File file;
    Viewport viewport;
    TetrahedralMeshGenerator generator;
    Translator translator;
    Preferences preferences;

    FILE * preferenceFile;
    Geometry * geometry;

    void createTitle();
    void createMenu(const vector<string> &);
    void setTheme(const Theme &);

    bool isUInt(const string &) const;
    bool isFloat(const string &) const;

    void print(const char *);

    void requestOption();
    void requestParameter(float &, bool &);
    
    void clear();
    void separator();

    void removeData();
    void defragmentGeometry();
    bool hasMesh() const;

    void openAction();
    void importAction();
    void informationAction();
    void viewportAction();
    void tetrahedralizeAction();
    void deleteAction();
    void exportAction();
    void saveAction();
    void closeAction();
    void preferencesAction();
    void aboutAction();
    void exitAction();
};

VIRGO_NAMESPACE_END

#endif