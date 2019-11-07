//dibuat oleh Chrystian 18/430257/PA/18770
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

extern int verticesSize;
extern int facesSize;
extern int faceLength;

extern float* vertices;
extern int* faces;

extern float t2,t1;

void getObjData(std::string objFile);