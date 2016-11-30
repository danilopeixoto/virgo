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

#include "application.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cstring>

VIRGO_NAMESPACE_BEGIN

Preferences::Preferences(const Language & language,
    const Theme & theme) : language(language), theme(theme) {}

Preferences::~Preferences() {}

Application::Application() {
    geometry = nullptr;
    
    preferenceFile = fopen("preferences", "rb+");
    
    if (preferenceFile != nullptr) {
        fread(&preferences, sizeof(Preferences), 1, preferenceFile);
    }
    else {
        preferenceFile = fopen("preferences", "wb+");

        if (preferenceFile != nullptr)
            fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);
    }

    fclose(preferenceFile);

    translator.setLanguage(preferences.language);
    setTheme(preferences.theme);

    clear();
}

Application::~Application() {
    if (preferenceFile != nullptr)
        fclose(preferenceFile);
    
    removeData();
}

void Application::show() {
    clear();

    createTitle();
    separator();

    vector<string> menu;
    menu.push_back(translator.OPEN);
    menu.push_back(translator.IMPORT);
    menu.push_back(translator.INFORMATION);
    menu.push_back(translator.VIEWPORT);
    menu.push_back(translator.TETRAHEDRALIZE);
    menu.push_back(translator.DELETE);
    menu.push_back(translator.EXPORT);
    menu.push_back(translator.SAVE);
    menu.push_back(translator.CLOSE);
    menu.push_back(translator.PREFERENCES);
    menu.push_back(translator.ABOUT);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            openAction();
            break;
        case 2:
            if (geometry != nullptr)
                importAction();
            else
                show();
            break;
        case 3:
            if (geometry != nullptr)
                informationAction();
            else
                show();
            break;
        case 4:
            if (geometry != nullptr)
                viewportAction();
            else
                show();
            break;
        case 5:
            if (hasMesh())
                tetrahedralizeAction();
            else
                show();
            break;
        case 6:
            if (hasMesh())
                deleteAction();
            else
                show();
            break;
        case 7:
            if (hasMesh())
                exportAction();
            else
                show();
            break;
        case 8:
            if (geometry != nullptr)
                saveAction();
            else
                show();
            break;
        case 9:
            if (geometry != nullptr)
                closeAction();
            else
                show();
            break;
        case 10:
            preferencesAction();
            break;
        case 11:
            aboutAction();
            break;
        case 12:
            exitAction();
            break;
        default:
            show();
    }
}

void Application::createTitle() {
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    print("*                                    VIRGO                                    *");
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");

    separator();

    if (geometry != nullptr) {
        string name;

        for (size_t i = filename.size(); i > 0; i--) {
            if (filename[i - 1] == '\\')
                break;

            name = filename.substr(i - 1);
        }

        printf(translator.CURRENT_FILE, name.c_str());
    }
    else {
        print(translator.NO_FILE);
    }
}

void Application::createMenu(const vector<string> & menuList) {
    for (size_t i = 0; i < menuList.size(); i++)
        printf("%zu. %s\n", i + 1, menuList[i].c_str());
}

void Application::setTheme(const Theme & theme) {
    switch (theme) {
        case Theme::Dark:
            system("color 0F");
            break;
        default:
            system("color F0");
    }
}

bool Application::isUInt(const string & str) const {
    size_t temp;
    
    istringstream stream(str);
    stream >> noskipws >> temp;

    return stream && stream.eof();
}

bool Application::isFloat(const string & str) const {
    float temp;
    
    istringstream stream(str);
    stream >> noskipws >> temp;

    return stream && stream.eof();
}

void Application::print(const char * str) {
    cout << str << endl;
}

void Application::requestOption() {
    string optionString;

    cin >> optionString;

    if (optionString.size() > 5)
        optionString = optionString.substr(0, 5);

    if (!isUInt(optionString)) {
        option = 0;
        return;
    }

    option = stoi(optionString);
}

void Application::requestParameter(float & parameter, bool & status) {
    string parameterString;

    cin >> parameterString;

    if (parameterString.size() > 10)
        parameterString = parameterString.substr(0, 10);

    if (!isFloat(parameterString)) {
        status = false;
        return;
    }

    status = true;
    parameter = stof(parameterString);
}

void Application::clear() {
    system("cls");
}

void Application::separator() {
    cout << endl;
}

void Application::removeData() {
    file.close();

    if (geometry != nullptr)
        delete geometry;

    geometry = nullptr;
}

void Application::defragmentGeometry() {
    if (geometry != nullptr)
        geometry->meshes.erase(remove(geometry->meshes.begin(), geometry->meshes.end(), nullptr),
            geometry->meshes.end());
}

bool Application::hasMesh() const {
    if (geometry != nullptr) {
        if (geometry->getMeshCount() != 0)
            return true;
    }

    return false;
}

void Application::openAction() {
    clear();

    createTitle();
    separator();

    print(translator.OPEN);
    separator();

    print(translator.OPEN_FILE);
    separator();

    string newFilename;

    cin >> newFilename;
    separator();
    
    vector<string> menu;
    menu.push_back(translator.OPEN);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            file.open(newFilename.c_str(), FileMode::Read);

            if (file.isOpen()) {
                separator();
                print(translator.OPENING);

                if (geometry != nullptr)
                    delete geometry;

                geometry = new Geometry;

                file.read(geometry);
                file.close();

                viewport.loadGeometry(geometry);

                filename = newFilename;

                show();
            }
            else {
                openAction();
            }
            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            openAction();
    }
}

void Application::importAction() {
    clear();

    createTitle();
    separator();

    print(translator.IMPORT);
    separator();

    print(translator.IMPORT_FILE);
    separator();

    string newFilename;

    cin >> newFilename;
    separator();

    vector<string> menu;
    menu.push_back(translator.IMPORT);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            file.open(newFilename.c_str(), FileMode::Read);

            if (file.isOpen()) {
                separator();
                print(translator.IMPORTING);

                Geometry * newGeometry = new Geometry;
                size_t offset = geometry->getVertexCount();

                file.read(newGeometry);
                file.close();

                for (size_t i = 0; i < newGeometry->getVertexCount(); i++)
                    geometry->points.push_back(newGeometry->points[i]);

                Mesh * mesh = nullptr;
                Triangle * triangle = nullptr;

                for (size_t i = 0; i < newGeometry->getMeshCount(); i++) {
                    mesh = newGeometry->getMeshByIndex(i);

                    for (size_t j = 0; j < mesh->triangles.size(); j++) {
                        triangle = mesh->triangles[j];

                        triangle->v1 += offset;
                        triangle->v2 += offset;
                        triangle->v3 += offset;
                    }

                    geometry->meshes.push_back(mesh);
                }

                show();
            }
            else {
                importAction();
            }

            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            importAction();
    }
}

void Application::informationAction() {
    clear();

    createTitle();
    separator();

    print(translator.INFORMATION);
    separator();

    size_t meshCount = geometry->getMeshCount();

    printf(translator.VERTEX_COUNT, geometry->getVertexCount());
    printf(translator.POLYGON_COUNT, geometry->getPolygonCount());
    printf(translator.MESH_COUNT, meshCount);
    separator();

    print(translator.MESHES);

    if (meshCount != 0) {
        for (size_t i = 0; i < meshCount; i++)
            print(geometry->getMeshByIndex(i)->name.c_str());
    }
    else {
        print(translator.NONE);
    }
    
    separator();

    vector<string> menu;
    menu.push_back(translator.OK);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            show();
            break;
        case 2:
            exitAction();
            break;
        default:
            informationAction();
    }
}

void Application::viewportAction() {
    viewport.show();

    show();
}

void Application::tetrahedralizeAction() {
    clear();

    createTitle();
    separator();

    print(translator.TETRAHEDRALIZE);
    separator();

    size_t meshCount = geometry->getMeshCount();
    vector<string> meshNameList;

    float radiusEdgeRatio = 0;
    size_t index = 0;

    if (meshCount != 1) {
        print(translator.TETRAHEDRALIZE_MESH);
        separator();

        for (size_t i = 0; i < meshCount; i++)
            meshNameList.push_back(geometry->getMeshByIndex(i)->name);

        createMenu(meshNameList);
        separator();

        requestOption();
        separator();

        if (option < 1 || option > meshCount)
            tetrahedralizeAction();

        index = option - 1;
    }

    bool status;
    print(translator.EDGE_RATIO_PARAMETER);
    separator();

    requestParameter(radiusEdgeRatio, status);
    separator();

    vector<string> menu;
    menu.push_back(translator.TETRAHEDRALIZE);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            if (status && radiusEdgeRatio > 1.0) {
                separator();
                print(translator.TETRAHEDRALIZING);

                generator.tetrahedralizeMesh(geometry, index, radiusEdgeRatio);

                show();
            }
            else {
                tetrahedralizeAction();
            }
            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            tetrahedralizeAction();
    }
}

void Application::deleteAction() {
    clear();

    createTitle();
    separator();

    print(translator.DELETE);
    separator();

    size_t meshCount = geometry->getMeshCount();
    vector<string> meshNameList;

    size_t index = 0;

    if (meshCount != 1) {
        print(translator.DELETE_MESH);
        separator();

        for (size_t i = 0; i < meshCount; i++)
            meshNameList.push_back(geometry->getMeshByIndex(i)->name);

        createMenu(meshNameList);
        separator();

        requestOption();
        separator();

        if (option < 1 || option > meshCount)
            deleteAction();

        index = option - 1;
    }

    vector<string> menu;
    menu.push_back(translator.DELETE);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            separator();
            print(translator.DELETING);

            if (meshCount == 1) {
                for (size_t i = 0; i < geometry->getVertexCount(); i++) {
                    if (geometry->points[i] != nullptr)
                        delete geometry->points[i];
                }

                geometry->points.clear();
            }
        
            delete geometry->getMeshByIndex(index);
            geometry->meshes[index] = nullptr;
        
            defragmentGeometry();
            show();

            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            deleteAction();
    }
}

void Application::exportAction() {
    clear();

    createTitle();
    separator();

    print(translator.EXPORT);
    separator();

    size_t meshCount = geometry->getMeshCount();
    vector<string> meshNameList;
    string newFilename;

    size_t index = 0;

    if (meshCount != 1) {
        print(translator.EXPORT_MESH);
        separator();

        for (size_t i = 0; i < meshCount; i++)
            meshNameList.push_back(geometry->getMeshByIndex(i)->name);

        createMenu(meshNameList);
        separator();

        requestOption();
        separator();

        if (option < 1 || option > meshCount)
            exportAction();

        index = option - 1;
    }

    print(translator.EXPORT_FILE);
    separator();

    cin >> newFilename;
    separator();

    vector<string> menu;
    menu.push_back(translator.EXPORT);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            file.open(newFilename.c_str(), FileMode::Write);

            if (file.isOpen()) {
                separator();
                print(translator.EXPORTING);

                Geometry * newGeometry = new Geometry;

                vector<Vector *> points;
                vector<Triangle *> triangles;

                geometry->getMeshDataByIndex(index, points, triangles);

                newGeometry->meshes.push_back(new Mesh);

                newGeometry->meshes[0]->name = geometry->getMeshByIndex(index)->name;
                newGeometry->meshes[0]->triangles = triangles;
                newGeometry->points = points;

                file.write(newGeometry);
                file.close();

                delete newGeometry;

                show();
            }
            else {
                exportAction();
            }

            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            exportAction();
    }
}

void Application::saveAction() {
    clear();

    createTitle();
    separator();

    print(translator.SAVE);
    separator();

    print(translator.OVERWRITE_FILE);
    separator();

    vector<string> menu;
    string newFilename;

    bool overwrite = false;

    menu.push_back(translator.NO);
    menu.push_back(translator.YES);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option < 1 || option > menu.size())
        return saveAction();

    if (option == 1) {
        print(translator.SAVE_FILE);
        separator();

        cin >> newFilename;
        separator();
    }
    else {
        overwrite = true;
    }

    menu.clear();
    menu.push_back(translator.SAVE);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            if (overwrite)
                file.open(filename.c_str(), FileMode::Write);
            else
                file.open(newFilename.c_str(), FileMode::Write);

            if (file.isOpen()) {
                separator();
                print(translator.SAVING);

                file.write(geometry);
                file.close();

                if (!overwrite)
                    filename = newFilename;

                show();
            }
            else {
                saveAction();
            }

            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            saveAction();
    }
}

void Application::closeAction() {
    removeData();
    show();
}

void Application::preferencesAction() {
    clear();

    createTitle();
    separator();

    print(translator.PREFERENCES);
    separator();

    print(translator.DEFAULT_LANGUAGE);
    separator();
    
    vector<string> menu;
    menu.push_back(translator.ENGLISH);
    menu.push_back(translator.PORTUGUESE);
    menu.push_back(translator.SPANISH);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option < 1 || option > menu.size())
        preferencesAction();

    preferences.language = (Language)(option - 1);

    print(translator.DEFAULT_THEME);
    separator();

    menu.clear();
    menu.push_back(translator.LIGHT);
    menu.push_back(translator.DARK);

    createMenu(menu);
    separator();

    requestOption();
    separator();

    if (option < 1 || option > menu.size())
        preferencesAction();

    preferences.theme = (Theme)(option - 1);

    menu.clear();
    menu.push_back(translator.SAVE);
    menu.push_back(translator.CANCEL);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            preferenceFile = fopen("preferences", "wb+");

            if (preferenceFile != nullptr)
                fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);
        
            fclose(preferenceFile);
        
            translator.setLanguage(preferences.language);
            setTheme(preferences.theme);

            show();

            break;
        case 2:
            show();
            break;
        case 3:
            exitAction();
            break;
        default:
            preferencesAction();
    }
}

void Application::aboutAction() {
    clear();

    createTitle();
    separator();

    print(translator.ABOUT);
    separator();

    print(translator.ABOUT_VIRGO);
    separator();

    print("Copyright (c) 2016, Danilo Peixoto and Gabriel Gustavo. All rights reserved.");
    print("Software developed under the BSD-3-Clause license.");
    separator();

    print(translator.DEPENDENCIES);
    separator();

    print("Imath");
    print("Copyright (c) 2002, Industrial Light & Magic, a division of Lucas Digital Ltd.");
    print("All rights reserved.");
    print("Software developed under the BSD license.");
    separator();

    print("FreeGLUT");
    print("Software developed under the X-Consortium license.");
    separator();

    print("TetGen");
    print("Software developed under the GNU Affero General Public License.");
    separator();

    vector<string> menu;
    menu.push_back(translator.OK);
    menu.push_back(translator.EXIT);

    createMenu(menu);
    separator();

    requestOption();

    switch (option) {
        case 1:
            show();
            break;
        case 2:
            exitAction();
            break;
        default:
            aboutAction();
    }
}

void Application::exitAction() {
    exit(0);
}

VIRGO_NAMESPACE_END