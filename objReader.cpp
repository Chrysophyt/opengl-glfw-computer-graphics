#include "include/objReader.h"
//dibuat Chrystian 18/430257/PA/18770

int verticesSize;
int facesSize;
int faceLength;

float* vertices;
int* faces;

float t2,t1;


void getObjFaces(std::string objFile, int *faces){
    std::ifstream infile;
    infile.open(objFile);

    std::string line;
    int v = 0;
    int f = 0;
    int index = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string temp;
        iss >> temp;
        if(temp.compare("f")==0){
            //for (int i = 0; i < 3; i++){
                while(iss>>temp){
                    std::replace(temp.begin(), temp.end(), '/', ' ');
                    std::stringstream ss(temp);

                    std::string vertexIndex;
                    ss >> vertexIndex;

                    faces[index++] = ::atoi(vertexIndex.c_str());
                }
            //}
        }
    }
}

void getObjVertices(std::string objFile, float *vertices){
    std::ifstream infile;
    infile.open(objFile);

    std::string line;
    int v = 0;
    int f = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string temp;
        iss >> temp;
        if(temp.compare("v")==0){
            for(int i = 0; i<3; i++){
                iss >> temp;
                vertices[v] = ::atof(temp.c_str());
                v++;
            }
        }
    }
}

void getObjVertexFaceSize(std::string objFile){ //size * 3
    std::ifstream infile;
    infile.open(objFile);

    std::string line;
    int v = 0;
    int f = 0;
    int m = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string a;
        iss >> a;
        if(a.compare("v")==0){
            v++;
        } else if (a.compare("f")==0){
            m++;
            while(iss>>a){
                f++;
            }
        }
    }
    infile.close();
    std::cout<<"Vertices in data : "<<v <<" Faces : "<<m<<" Face Length : "<<(int) f/m<<"\n";
    verticesSize = v * 3; // for x y z
    facesSize = f;
    faceLength = (int) f/m;
}

void getObjData(std::string objFile){
    getObjVertexFaceSize(objFile);
    std::cout<<"Obj File Found with VerticesSize : " <<verticesSize<<", FacesSize : "<<facesSize<<"\n";

    vertices = new float[verticesSize];
    faces = new int[facesSize];

    getObjVertices(objFile, vertices);
    getObjFaces(objFile, faces);
}