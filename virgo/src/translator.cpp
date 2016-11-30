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

#include "translator.h"
#include <locale>

VIRGO_NAMESPACE_BEGIN

Translator::Translator() {
    setlocale(LC_ALL, "english");
    setEnglishLanguage();
}

Translator::~Translator() {}

void Translator::setLanguage(const Language & language) {
    switch (language) {
        case Language::Portuguese:
            setlocale(LC_CTYPE, "portuguese");
            setPortugueseLanguage();

            break;
        case Language::Spanish:
            setlocale(LC_CTYPE, "spanish");
            setSpanishLanguage();

            break;
        default:
            setlocale(LC_ALL, "english");
            setEnglishLanguage();
    }
}

void Translator::setEnglishLanguage() {
    OPEN = "Open";
    IMPORT = "Import";
    INFORMATION = "Information";
    VIEWPORT = "Viewport";
    TETRAHEDRALIZE = "Tetrahedralize";
    DELETE = "Delete";
    EXPORT = "Export";
    SAVE = "Save";
    CLOSE = "Close";
    PREFERENCES = "Preferences";
    ABOUT = "About";
    EXIT = "Exit";
    CURRENT_FILE = "File: %s\n";
    NO_FILE = "File: No file selected";
    OPEN_FILE = "Enter an object file to open:";
    IMPORT_FILE = "Enter an object file to import:";
    MESHES = "Meshes:";
    NONE = "None";
    VERTEX_COUNT = "Vertex count: %zu\n";
    POLYGON_COUNT = "Polygon count: %zu\n";
    MESH_COUNT = "Mesh count: %zu\n";
    TETRAHEDRALIZE_MESH = "Select a mesh to tetrahedralize:";
    EDGE_RATIO_PARAMETER = "Enter the radius-edge ratio parameter:";
    DELETE_MESH = "Select a mesh to delete:";
    EXPORT_MESH = "Select a mesh to export:";
    EXPORT_FILE = "Enter a filename to save mesh:";
    OVERWRITE_FILE = "Are you sure you want to overwrite it?";
    SAVE_FILE = "Enter a filename to save:";
    DEFAULT_LANGUAGE = "Select a default language for application:";
    ENGLISH = "English";
    PORTUGUESE = "Portuguese";
    SPANISH = "Spanish";
    DEFAULT_THEME = "Select a default theme for application:";
    LIGHT = "White";
    DARK = "Dark";
    ABOUT_VIRGO = "Virgo offers an interative feature set for 3D computer visualization.";
    DEPENDENCIES = "Dependencies";
    OPENING = "Opening...";
    IMPORTING = "Importing...";
    TETRAHEDRALIZING = "Tetrahedralizing...";
    DELETING = "Deleting...";
    EXPORTING = "Exporting...";
    SAVING = "Saving...";
    YES = "YES";
    NO = "NO";
    OK = "OK";
    CANCEL = "Cancel";
}

void Translator::setPortugueseLanguage() {
    OPEN = "Abrir";
    IMPORT = "Importar";
    INFORMATION = "Informação";
    VIEWPORT = "Visualizar";
    TETRAHEDRALIZE = "Tetraedralizar";
    DELETE = "Deletar";
    EXPORT = "Exportar";
    SAVE = "Salvar";
    CLOSE = "Fechar";
    PREFERENCES = "Preferências";
    ABOUT = "Sobre";
    EXIT = "Sair";
    CURRENT_FILE = "Arquivo: %s\n";
    NO_FILE = "Arquivo: Nenhum arquivo selecionado";
    OPEN_FILE = "Entre com o arquivo de objeto para abrir:";
    IMPORT_FILE = "Entre com o arquivo de objeto para importar:";
    MESHES = "Geometrias:";
    NONE = "Nenhum";
    VERTEX_COUNT = "Contagem de vértices: %zu\n";
    POLYGON_COUNT = "Contagem de polígonos: %zu\n";
    MESH_COUNT = "Contagem de geometrias: %zu\n";
    TETRAHEDRALIZE_MESH = "Selecione a geometria para tetraedralizar:";
    EDGE_RATIO_PARAMETER = "Entre com o parâmetro de razão raio aresta:";
    DELETE_MESH = "Selecione a geometria para deletar:";
    EXPORT_MESH = "Selecione a geometria para exportar:";
    EXPORT_FILE = "Entre com o nome de arquivo para salvar a geometria:";
    OVERWRITE_FILE = "Tem certeza que você deseja sobrescrever o arquivo?";
    SAVE_FILE = "Entre com o nome de arquivo para salvar:";
    DEFAULT_LANGUAGE = "Selecione o idioma padrão da aplicação:";
    ENGLISH = "Inglês";
    PORTUGUESE = "Português";
    SPANISH = "Espanhol";
    DEFAULT_THEME = "Selecione o tema padrão da aplicação:";
    LIGHT = "Claro";
    DARK = "Escuro";
    ABOUT_VIRGO = "Virgo oferece um conjunto de recursos interativos para visualização 3D.";
    DEPENDENCIES = "Dependências";
    OPENING = "Abrindo...";
    IMPORTING = "Importando...";
    TETRAHEDRALIZING = "Tetraedralizando...";
    DELETING = "Deletando...";
    EXPORTING = "Exportando...";
    SAVING = "Salvando...";
    YES = "SIM";
    NO = "NÃO";
    OK = "OK";
    CANCEL = "Cancelar";
}

void Translator::setSpanishLanguage() {
    OPEN = "Abrir";
    IMPORT = "Importar";
    INFORMATION = "Información";
    VIEWPORT = "Visualizar";
    TETRAHEDRALIZE = "Tetraedralizar";
    DELETE = "Eliminar";
    EXPORT = "Exportar";
    SAVE = "Guardar";
    CLOSE = "Cerrar";
    PREFERENCES = "Preferencias";
    ABOUT = "Acerca de";
    EXIT = "Salida";
    CURRENT_FILE = "Archivo: %s\n";
    NO_FILE = "Archivo: Ningún archivo seleccionado";
    OPEN_FILE = "Introduzca el archivo de objeto para abrir:";
    IMPORT_FILE = "Introduzca el archivo de objeto para importar:";
    MESHES = "Geometrías:";
    NONE = "Ninguno";
    VERTEX_COUNT = "Recuento de vértices: %zu\n";
    POLYGON_COUNT = "Recuento de polígonos: %zu\n";
    MESH_COUNT = "Recuento de geometrías: %zu\n";
    TETRAHEDRALIZE_MESH = "Seleccione la geometría para tetraedralizar:";
    EDGE_RATIO_PARAMETER = "Introduzca el parámetro de relación radio arista:";
    DELETE_MESH = "Seleccione la geometría para eliminar:";
    EXPORT_MESH = "Seleccione la geometría para exportar:";
    EXPORT_FILE = "Introduzca el nombre de archivo para guardar la geometría:";
    OVERWRITE_FILE = "¿Está seguro de que desea sobrescribir el archivo?";
    SAVE_FILE = "Introduzca el nombre de archivo para guardar:";
    DEFAULT_LANGUAGE = "Seleccione el idioma por defecto de la aplicación:";
    ENGLISH = "Inglés";
    PORTUGUESE = "Portugués";
    SPANISH = "Español";
    DEFAULT_THEME = "Seleccione el tema por defecto de la aplicación:";
    LIGHT = "Claro";
    DARK = "Oscuro";
    ABOUT_VIRGO = "Virgo proporciona un conjunto de características interactivas para la visualización en 3D.";
    DEPENDENCIES = "Dependencias";
    OPENING = "Abriendo...";
    IMPORTING = "Importando...";
    TETRAHEDRALIZING = "Tetraedralizando...";
    DELETING = "Eliminando...";
    EXPORTING = "Exportando...";
    SAVING = "Guardando...";
    YES = "SÍ";
    NO = "NO";
    OK = "OK";
    CANCEL = "Cancelar";
}

VIRGO_NAMESPACE_END