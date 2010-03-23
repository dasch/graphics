#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

/*******************************************************************\
*                                                                   *
*         R e a d D a t a F i l e ( c o n s t   c h a r * )         *
*                                                                   *
* The file contains the specification of a number of Bezier patches *
*                                                                   *
* This function `ReadDataFile(const char* filename)' which can read *
* the specific file `patches.data' are provided by knud henriksen   *
*                                                                   *
* The function is by no means general! It can only read the         *
* data file `patches.data', and that is also the intension!         *
*                                                                   *
* The purpose of the this function is to make it easy for the       *
* students to get the control points of the specific                *
* Bezier surfaces, which are obligatory in the report.              *
*                                                                   *
\*******************************************************************/

using std::cout; using std::cerr; using std::endl; using std::flush;
using std::ifstream; using std::setw;

int ReadDataFile(const char* filename)
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

		  cout << "Number of Vertices = " << NumberOfVertices
		       << endl << endl;

		  state = READ_VERTICES;
	      }
	      break;
          case READ_VERTICES:
            if (InputBuffer[0] != '#') {
                if (sscanf(InputBuffer, "%d%lf%lf%lf",
                           &VertexNumber, &x, &y, &z) != 4) {
                    cerr << "vertex not found in data file: " 
			 << filename << endl << flush;
                    return -1;
                }
                else {
                    // insert the vertex in a data structure
		    
		    cout << "Vertex " << setw(3) << VertexNumber << ": ";

		    cout.precision(4);
		    cout << "(x, y, z) = (" 
			 << setw(6) << x << ", " 
			 << setw(6) << y << ", " 
			 << setw(6) << z 
			 << ')' << endl;

                    if (VertexNumber == NumberOfVertices) {
                        state = PATCHNAME;
                    }

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
		    cout << "patch name: " << PatchName << endl << flush;
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
	    }
	    else {
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
		}
		else {
		    // insert patch in a data structure
		    
		    cout << "patch number: " 
			 << setw(2) << PatchNumber << endl << flush;
		    cout << "patch indices: " << endl << '\t'
			 << setw(6) << index_11 << ", " 
			 << setw(6) << index_12 << ", " 
			 << setw(6) << index_13 << ", " 
			 << setw(6) << index_14 << endl;
		    
		    cout << '\t'
			 << setw(6) << index_21 << ", " 
			 << setw(6) << index_22 << ", "
			 << setw(6) << index_23 << ", " 
			 << setw(6) << index_24 << endl;
		    
		    cout << '\t'
			 << setw(6) << index_31 << ", " 
			 << setw(6) << index_32 << ", "
			 << setw(6) << index_33 << ", " 
			 << setw(6) << index_34 << endl;
		    
		    cout << '\t'
			 << setw(6) << index_41 << ", " 
			 << setw(6) << index_42 << ", "
			 << setw(6) << index_43 << ", " 
			 << setw(6) << index_44 << endl;
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

int main()
{
    int result = ReadDataFile("patches.data");

    cout << "Reading data file: patches.data - ";
    if (result == 0)
	cout << "succeded";
    else {
	cout << "failed";
    }
    cout << endl;

    return result;
}
