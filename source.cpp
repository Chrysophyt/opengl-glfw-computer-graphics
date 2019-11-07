#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/objReader.h"

#include <cstdio>

//untuk input
bool toggleWireFrame;

//untuk buffer & color buffer
GLfloat *buff;
GLfloat *cbuff;

void controls(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if(key == GLFW_KEY_SPACE){
            if(!toggleWireFrame){
                toggleWireFrame = !toggleWireFrame;
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                std::cout<< "Changing Fill\n";
                return;
            }else{
                toggleWireFrame = !toggleWireFrame;
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                std::cout<< "Changing WireFrame\n";
            }
        }       
    }
}

GLFWwindow* initWindow(const int resX, const int resY, std::string title){
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, title.c_str(), NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

void generateObject(){
    
    static float alpha = 0;
    
    //rotate object
    glRotatef(alpha, 0, 1, 0);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, buff);
    glColorPointer(3, GL_FLOAT, 0, cbuff);


    /* Send data : number of vertices */
    if(faceLength==3){
        glDrawArrays(GL_TRIANGLES, 0, facesSize);
    }else{
        glDrawArrays(GL_QUADS, 0, facesSize);
    }
    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    t1 = glfwGetTime();
    alpha += 1 *(60)*(t1-t2);
    t2 = t1;

}

void display( GLFWwindow* window ){
    while(!glfwWindowShouldClose(window))
    {
        // Setting up View
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);
        
        //Setting up Attribute
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,0,-5);

        glPushMatrix();
        generateObject();
        glPopMatrix();

        
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

void generateBuffer(){
    int totalBufferSize = facesSize*3;
    buff = new GLfloat[totalBufferSize];
    cbuff = new GLfloat[totalBufferSize];

    //for each vertex in faces
    for(int i = 0; i < facesSize; i++){
        int faceIndex = faces[i]; 
        for(int j = 0; j < 3; j++){
            buff[i*3+j] = vertices[(faceIndex-1)*3+j];
            cbuff[i*3+j] = 1;
        }
    }
}

int main(int argc, char** argv){
    //get data name from user
    std::string FileName;
    std::cout << "Masukan nama *.obj di dalam folder \"3D_Model\" : \nCnth: 3D_Model/triangle.obj masukan triangle :\n";
    std::cin >> FileName;

    //get data from .obj file
    getObjData("3D_Model/"+FileName+".obj");
    generateBuffer();

    GLFWwindow* window = initWindow(1024, 620, "Chrystian|18770 - press Spacebar To Toggle WireFrame and Fill");

    //awal setting Polygon Mode Wireframe
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    if( NULL != window )
    {
        display(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}