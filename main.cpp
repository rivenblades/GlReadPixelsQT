#include "mainwindow.h"
#include <QApplication>
#include "glew.h"
#include "glfw3.h"
#include "GL/glut.h"
#include <iostream>
#include <thread>
int main(int argc, char **argv)
{
    /*GLFWWidget *window = new GLFWWidget;
    window->init();*/
glfwInit();
    glutInit(&argc,argv);

//       glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
        if (!window)
        {
               std::cerr<< "GLFW Window creating failed";
        }
            glfwMakeContextCurrent(window);


   glewExperimental = GL_TRUE;
   GLenum res = glewInit();
   std::cout<<"Glew initialization:"<<res;
   if (res != GLEW_OK){
       std::cout<< glewGetErrorString(res);
       exit(1);
   }
   glfwHideWindow(window);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    return 1;
}

