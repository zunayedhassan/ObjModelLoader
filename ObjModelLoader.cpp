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

#include "ObjModelLoader.h"

ObjModelLoader::ObjModelLoader(string filename)
{
    this->filename = filename;

    // Open the *.obj file
    fstream *objFile = new fstream;
    objFile->open(filename, ios_base::in);

    // If can't open the file
    if (!objFile->is_open())
    {
        cout << "[!] ERROR: Unable to open the file" << endl;

        // Terminate the program
        exit(EXIT_FAILURE);
    }

    /*
        Sample *.obj file example

        # Blender v2.73 (sub 0) OBJ File: ''
        # www.blender.org
        mtllib cube.mtl
        o Cube
        v 1.000000 -1.000000 -1.000000
        v 1.000000 -1.000000 1.000000
        v -1.000000 -1.000000 1.000000
        v -1.000000 -1.000000 -1.000000
        v 1.000000 1.000000 -0.999999
        v 0.999999 1.000000 1.000001
        v -1.000000 1.000000 1.000000
        v -1.000000 1.000000 -1.000000
        usemtl Material
        s off
        f 2 3 4
        f 8 7 6
        f 5 6 2
        f 6 7 3
        f 3 7 8
        f 1 4 8
        f 1 2 4
        f 5 8 6
        f 1 5 2
        f 2 6 3
        f 4 3 8
        f 5 1 8
     */

    string currentLine;

    // Read every line
    while (!objFile->eof())
    {
        getline(*objFile, currentLine);

        // Split every line according to space
        vector<string> *parameters = this->GetSplittedStrings(currentLine, ' ');

        // If current line has information about vertices
        if (parameters->at(0) == "v")
        {
            // Remove 'v' and keep the rest of the numbers
            parameters->erase(parameters->begin());

            vector<float> *currentPoint = new vector<float>;

            for (int index = 0; index < parameters->size(); index++)
            {
                // Convert each x, y, z coordinate (as string) to float value
                currentPoint->push_back(this->GetFloatFromString(parameters->at(index)));
            }

            // Save that point on "vertices"
            vertices->push_back(currentPoint);
        }
        // If current line has information about faces
        else if (parameters->at(0) == "f")
        {
            // Remove 'f' and keep the rest of the numbers
            parameters->erase(parameters->begin());

            vector<int> *vertexIndexes = new vector<int>;

            for (int index = 0; index < parameters->size(); index++)
            {
                // Convert each face index (as string) to integer
                int faceIndex = this->GetFloatFromString(parameters->at(index));

                // Our obj file uses indexing from 1. So, we are decrementing 1 to make it start from 0
                vertexIndexes->push_back(--faceIndex);
            }

            // And finally saving faces information
            faces->push_back(vertexIndexes);
        }

        // Freeing unnecessary memory
        delete parameters;
    }

    // Closing the *.obj file
    objFile->close();
}

ObjModelLoader::~ObjModelLoader()
{
    // Freeing unnecessary memory
    delete this->faces;
    delete this->vertices;
}

void ObjModelLoader::Draw()
{
    // We will draw faces as triangles
    glBegin(GL_TRIANGLES);

    // For every faces
    for (int i = 0; i < faces->size(); i++)
    {
        // There will be a normal for lighting
        float *normal = NULL;

        // Since this is triangle, so every face must have 3 vertices
        float coord1[3],
              coord2[3],
              coord3[3];

        // For every vertex/point
        for (int j = 0; j < (faces->at(i))->size(); j++)
        {
            int index = (faces->at(i))->at(j);

            switch(j)
            {
                // If 1st vertex, then save it to coord1
                case 0:
                    coord1[0] = (vertices->at(index))->at(0);
                    coord1[1] = (vertices->at(index))->at(1);
                    coord1[2] = (vertices->at(index))->at(2);
                    break;

                // If 2nd vertex, then save it to coord2
                case 1:
                    coord2[0] = (vertices->at(index))->at(0);
                    coord2[1] = (vertices->at(index))->at(1);
                    coord2[2] = (vertices->at(index))->at(2);
                    break;

                // If 3rd vertex, then save it to coord3
                case 2:
                    coord3[0] = (vertices->at(index))->at(0);
                    coord3[1] = (vertices->at(index))->at(1);
                    coord3[2] = (vertices->at(index))->at(2);
                    break;
            }

            // When we got all the 3 point/vertices, then calculate normal and draw the triangle
            if (j == 2)
            {
                // Calculating normal
                normal = this->GetNormal(coord1, coord2, coord3);

                // Setting normal for these vertices
                glNormal3f(normal[0], normal[2], normal[2]);

                // Drawing the triangle as a face
                glVertex3f(coord1[0], coord1[1], coord1[2]);
                glVertex3f(coord2[0], coord2[1], coord2[2]);
                glVertex3f(coord3[0], coord3[1], coord3[2]);
            }
        }
    }

    glEnd();
}

vector<string>* ObjModelLoader::GetSplittedStrings(string text, char delimeter)
{
    text += delimeter;

    string word = "";
    vector<string> *words = new vector<string>;

    for (int character = 0; character < text.length(); character++)
    {
        if (text[character] != delimeter)
        {
            word += text[character];
        }
        else
        {
            words->push_back(word);
            word = "";
        }
    }

    return words;
}

float ObjModelLoader::GetFloatFromString(string text)
{
    float value = 0.0f;

    istringstream buffer(text);
    buffer >> value;

    return value;
}

float* ObjModelLoader::GetNormal(float *coord1, float *coord2, float *coord3)
{
    // calculate Vector1 and Vector2
    float va[3], vb[3], vr[3];

    va[0] = coord1[0] - coord2[0];
    va[1] = coord1[1] - coord2[1];
    va[2] = coord1[2] - coord2[2];

    vb[0] = coord1[0] - coord3[0];
    vb[1] = coord1[1] - coord3[1];
    vb[2] = coord1[2] - coord3[2];

    // cross product
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    // normalization factor
    float val = sqrt(pow(vr[0], 2) + pow(vr[1], 2) + pow(vr[2], 2));

    float norm[3];

    norm[0] = vr[0] / val;
    norm[1] = vr[1] / val;
    norm[2] = vr[2] / val;

    return norm;
}
