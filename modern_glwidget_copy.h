#ifndef __MODERNGLWIDGET_H__
#define __MODERNGLWIDGET_H__

#include <QMouseEvent>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
//#include <GL/gl.h>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>




#include <QOpenGLWidget>
#include <QTimer>
#include <QPainter>
#include <unistd.h>
class ModernGLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModernGLWidget(QWidget *parent=0);
    float tr_x=0.0f,tr_y=0.0f,tr_z=0.0f;//translate x,y,z(camera)
    float r_x,r_y,r_z;                  //rotate x,y,z(camera)

    //Render to image to display content
    QImage *img;


    std::string file_obj ;
    std::string file_nm  ;
    std::string file_diff;
    std::string file_spec;
 unsigned int VAO;


    // Get handles to our uniforms
    GLuint LightID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint Texture0ID;
    GLuint Texture1ID;
    GLuint Texture2ID;

    std::vector<GLfloat>    vertices;
    std::vector<GLfloat>     normals;
    std::vector<GLfloat>    tangents;
    std::vector<GLfloat>  bitangents;
    std::vector<GLfloat>      uvs;

    unsigned int ID;
    bool wireframe;
    QPointF pos;//mouse pos
    QColor color;//selected object color
    void read_n_compile_shader(const std::string filename, GLuint &hdlr, GLenum shaderType);
    GLuint set_shaders(const std::string vsfile, const std::string fsfile);
    void load_shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    void checkCompileErrors(GLuint shader, std::string type);


    QTimer *timer;
    typedef struct
    {
        u_char head[12];
        u_short dx /* Width */, dy /* Height */, head2;
//        u_char pic[768 * 1024 * 10][3];
        GLubyte *pic;
        GLubyte *rpic;
        GLubyte *gpic;
        GLubyte *bpic;
    } typetga;
    typetga tga;

    int oldWidth;//keep old width for resizing array tga.pic
    int oldHeight;

    char captureName[256];
    u_long captureNo;
    u_char tgahead[12] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    bool resizing=false;
    int m_width,m_height;

protected:
    void initializeGL() ;
    void paintEvent(QPaintEvent *event);
private slots:
    void paintGL() ;
    //virtual void resizeGL(int w, int h) override;
    virtual void resizeEvent(QResizeEvent *) override;
};


#endif //__MODERNGLWIDGET_H__
