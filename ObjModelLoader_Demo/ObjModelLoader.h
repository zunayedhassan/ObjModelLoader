/**
 *  Class Name:     ObjModelLoader
 *
 *  Version:        1.0
 *  Date:           March 28, 2015
 *
 *  Author:         Mohammad Zunayed Hassan
 *  Email:          ZunayedHassanBD@gmail.com
 *
 *  Last Updated:
 *
 *  Changes History:
 */

#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#ifdef __APPLE__
    #include <GLUT/gl.h>
#else
    #include <GL/gl.h>
#endif

using namespace std;

/**
 *  Loads model from Wavefront Obj file (*.obj). Using triangles and normals
 *  as static object. No texture mapping.
 *
 *  Warning: OBJ files must be triangulated. Non triangulated objects wont
 *           work! You can use Blender to triangulate.
 *
 *  Exporting as Obj File on Blender:
 *           (a) Open Blender program. Create your model.
 *           (b) File -> Export -> Wavefront (.obj)
 *           (c) Now at the left side panel on "Export Obj" section check on
 *               "Triangulate Faces".
 *           (d) Click on "Export OBJ" button. It produce two files. For
 *               example: cube.obj and cube.mtl. We will only need the *.obj
 *               file only.
 *
 *  Sample Usage:
 *          ObjModelLoader *mesh = NULL;
 *          mesh = new ObjModelLoader("C:\\data\\filename.obj");
 *
 *          mesh->Draw();
 *
 */
class ObjModelLoader
{
    public:
        /**
         *  Constructor
         *  @param string filename
         *         File name of the *.obj file with path.
         *         Example: "C:\\data\\cube.obj"
         */
        ObjModelLoader(string filename);

        /**
         *  Destructor
         */
        ~ObjModelLoader();

        /**
         *  Draws model from *.obj file.
         */
        void Draw();

    private:
        string filename = "";

        vector<vector<float>*> *vertices = new vector<vector<float>*>;
        vector<vector<int>*>   *faces    = new vector<vector<int>*>;

        /**
         *  Split string to individual strings according to given option
         *
         *  @param  string text
         *          Text to be splitted
         *
         *          char delimeter
         *          Separator for the string
         *
         *  @return vector<string>*
         *          vector of strings
         *
         *  @example
         *          If text = "Hello World", delimeter = ' '
         *          Then { "Hello", "World" }
         */
        vector<string>* GetSplittedStrings(string text, char delimeter);

        /**
         *  Converts string to float value
         *
         *  @param  string text
         *          Text to be converted
         *
         *  @return float
         *          Converter value
         *
         *  @example
         *          If text = "1.5"
         *          Then 1.5f
         */
        float GetFloatFromString(string text);

        /**
         *  Calculates normal from given points
         *
         *  @param  float *coord1, float *coord2, float *coord3
         *          3 points of the triangle plane to be calculated
         *          for normal
         *
         *  @return float*
         *          Array of float where normal points are located
         *          x, y, z coordinate.
         */
        float* GetNormal(float *coord1, float *coord2, float *coord3);
};

#endif // OBJMODELLOADER_H
