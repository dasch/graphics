#ifndef PARSER_H
#define PARSER_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>

#include "solution/math_types.h"
#include "solution/triangle.h"

using std::cout; using std::cerr; using std::endl; using std::flush;
using std::ifstream; using std::setw;

typedef struct patch {
    int number;

    // Indices into the vertex list.
    int vertices[16];

    // The next patch in the list.
    struct patch *next;
} patch_t;

typedef struct {
    patch_t *head;
    patch_t *tail;
} patch_list_t;

typedef struct {
    unsigned int num_vertices;
    vertex_t *vertices;
    patch_list_t *patches;
} object_t;

object_t *
object_init()
{
    object_t *object = (object_t*)malloc(sizeof(object_t));

    object->num_vertices = 0;
    object->vertices = NULL;
    object->patches = (patch_list_t*)malloc(sizeof(patch_list_t));

    object->patches->head = NULL;
    object->patches->tail = NULL;

    return object;
}

patch_t *
patch_list_append(patch_list_t *list, int number)
{
    if (list == NULL)
        throw new std::runtime_error("list was NULL");

    patch_t *patch = (patch_t*)malloc(sizeof(patch_t));

    if (patch == NULL)
        throw new std::runtime_error("could not allocate memory");

    patch->number = number;
    patch->next = NULL;

    if (list->head == NULL)
        list->head = patch;

    if (list->tail != NULL)
        list->tail->next = patch;

    list->tail = patch;

    return patch;
}

int
parse_data_file(const char *filename, object_t *object)
{
    const int NVERTEX        = 0;
    const int READ_VERTICES  = 1;
    const int PATCHNAME      = 2;
    const int SEARCH_PATCHES = 3;
    const int READ_PATCHES   = 4;

    char ch;
    const int MAX_BUFFER = 256;
    char  InputBuffer[MAX_BUFFER];

    int    NumberOfVertices;
    int    VertexNumber;
    double x;
    double y;
    double z;

    char   PatchName[MAX_BUFFER];
    int    PatchNumber;
    int    index_11, index_12, index_13, index_14;
    int    index_21, index_22, index_23, index_24;
    int    index_31, index_32, index_33, index_34;
    int    index_41, index_42, index_43, index_44;

    patch_t *patch;

    ifstream data_file(filename);
    if (!data_file) {
        cerr << "Cannot open data file: " << filename << endl << flush;
        return -1;
    }

    int state = NVERTEX;
    while (data_file.get(InputBuffer, MAX_BUFFER, '\n')) {
        if (data_file.get(ch) && ch != '\n') {
            data_file.close();
            cerr << "Eof on data file: " << filename << endl << flush;
            return -1;
        }

        // Now one line of data is in InputBuffer
        // Use sscanf to extract the numeric values

        // Build a data structure which represents the different
        // vertices and patches
        //
        // There are several possibilities for the input lines:
        //
        // 1: a comment line, i.e. InputBuffer[0] == '#'
        // 2: a 'number of vertices line', i.e. just one number
        //    sscanf(InputBuffer, "%d", &NumberOfVertices)
        // 3: a 'vertex line', i.e. 4 numbers
        //    sscanf(InputBuffer, "%d%lf%lf%lf", &VertexNumber, &x, &y, &z)
        // 4: a 'patch line', i.e. 17 numbers
        //    sscanf(InputBuffer,
        //           "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        //           &PatchNumber,
        //           &index_11, &index_12, &index_13, &index_14,
        //           &index_21, &index_22, &index_23, &index_24,
        //           &index_31, &index_32, &index_33, &index_34,
        //           &index_41, &index_42, &index_43, &index_44)

        switch (state) {
          case NVERTEX:
              if (InputBuffer[0] != '#') {
                  if (sscanf(InputBuffer, "%d", &NumberOfVertices) != 1) {
                      cerr << "number of vertices not found in data file: "
                       << filename << endl << flush;
                      return -1;
                  }

                  object->num_vertices = NumberOfVertices;
                  object->vertices = (vertex_t*)malloc(sizeof(vertex_t) * (NumberOfVertices + 1));

                  cout << "Number of Vertices = " << NumberOfVertices
                       << endl << endl;

                  state = READ_VERTICES;
              }
              break;
          case READ_VERTICES:
            if (InputBuffer[0] != '#') {
                if (sscanf(InputBuffer, "%d%lf%lf%lf", &VertexNumber, &x, &y, &z) != 4) {
                    cerr << "vertex not found in data file: " << filename << endl << flush;
                    return -1;
                } else {
                    object->vertices[VertexNumber] = vertex_t(x, y, z);

                    if (VertexNumber == NumberOfVertices)
                        state = PATCHNAME;
                }
            }
            break;
        case PATCHNAME:
            if (InputBuffer[0] == '#') {
                if (strlen(InputBuffer) > 2) {
                    // read the name of the patch
                    if (sscanf(InputBuffer, "# %s", PatchName) != 1) {
                        cerr << "patch name not found" << endl << flush;
                        return -1;
                    }
                    state = SEARCH_PATCHES;
                }
            }
            break;
        case SEARCH_PATCHES:
        case READ_PATCHES:
            if (InputBuffer[0] == '#') {
                if (state == READ_PATCHES) {
                    state = PATCHNAME;
                }
            } else {
                state = READ_PATCHES;
                if (sscanf(InputBuffer,
                       "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                       &PatchNumber,
                       &index_11, &index_12, &index_13, &index_14,
                       &index_21, &index_22, &index_23, &index_24,
                       &index_31, &index_32, &index_33, &index_34,
                       &index_41, &index_42, &index_43, &index_44) != 17) {
                    cerr << "No patch found in data file: " << filename
                     << endl << flush;
                    return -1;
                } else {
                    patch = patch_list_append(object->patches, PatchNumber);
                    patch->vertices[ 0] = index_11;
                    patch->vertices[ 1] = index_12;
                    patch->vertices[ 2] = index_13;
                    patch->vertices[ 3] = index_14;
                    patch->vertices[ 4] = index_21;
                    patch->vertices[ 5] = index_22;
                    patch->vertices[ 6] = index_23;
                    patch->vertices[ 7] = index_24;
                    patch->vertices[ 8] = index_31;
                    patch->vertices[ 9] = index_32;
                    patch->vertices[10] = index_33;
                    patch->vertices[11] = index_34;
                    patch->vertices[12] = index_41;
                    patch->vertices[13] = index_42;
                    patch->vertices[14] = index_43;
                    patch->vertices[15] = index_44;
                }
            }
            break;
        }
    }
    if (!data_file.eof()) {
        cerr << "Something strange happend on data file: " << filename << endl;
        return -1;
    }
    data_file.close();

    return 0;
}

#endif
