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

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "namespace.h"

VIRGO_NAMESPACE_BEGIN

enum Language {
    English = 0,
    Portuguese,
    Spanish
};

class Translator {
public:
    Translator();
    ~Translator();

    void setLanguage(const Language &);

    char * OPEN, *IMPORT, *INFORMATION, *VIEWPORT, *TETRAHEDRALIZE,
        *DELETE, *EXPORT, *SAVE, *CLOSE, *PREFERENCES, *ABOUT, *EXIT,
        *CURRENT_FILE, *NO_FILE, *OPEN_FILE, *IMPORT_FILE, *MESHES, *NONE,
        *VERTEX_COUNT, *POLYGON_COUNT, *MESH_COUNT, *TETRAHEDRALIZE_MESH,
        *EDGE_RATIO_PARAMETER, *DELETE_MESH, *EXPORT_MESH, *EXPORT_FILE,
        *OVERWRITE_FILE, *SAVE_FILE, *DEFAULT_LANGUAGE, *ENGLISH, *PORTUGUESE,
        *SPANISH, *DEFAULT_THEME, *LIGHT, *DARK, *ABOUT_VIRGO, *DEPENDENCIES,
        *OPENING, *IMPORTING, *TETRAHEDRALIZING, *DELETING, *EXPORTING,
        *SAVING, *YES, *NO, *OK, *CANCEL;

private:
    void setEnglishLanguage();
    void setPortugueseLanguage();
    void setSpanishLanguage();
};

VIRGO_NAMESPACE_END

#endif