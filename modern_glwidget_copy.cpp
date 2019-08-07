#include "modern_glwidget_copy.h"
#include <QDebug>
#include <QTimer>

ModernGLWidget::ModernGLWidget(QWidget *parent)
    //:QOpenGLWidget (parent)
{
//    setAttribute(Qt::WA_OpaquePaintEvent);
//         setAttribute(Qt::WA_StaticContents);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(paintGL()));
    timer->start(60);
    color = QColor(Qt::red);
    wireframe = false;
    tr_x=tr_y=tr_z=0.0f;

    //QString objpath = "/home/kostas/Documents/Qt-projects/Blender2/lib/tinyrenderer/obj";
    file_obj  = "/home/kostas/Documents/Qt-projects/Blender2/lib/tinyrenderer/obj/diablo3_pose/diablo3_pose.obj";
    file_nm   = "/home/kostas/Documents/Qt-projects/Blender2/lib/tinyrenderer/obj/diablo3_pose/diablo3_pose_nm_tangent.tga";
    file_diff = "/home/kostas/Documents/Qt-projects/Blender2/lib/tinyrenderer/obj/diablo3_pose/diablo3_pose_diffuse.tga";
    file_spec = "/home/kostas/Documents/Qt-projects/Blender2/lib/tinyrenderer/obj/diablo3_pose/diablo3_pose_spec.tga";
    


    float vertices1[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     std::cerr << "Failed to initialize OpenGL context" << std::endl;
    //     return -1;
    // }
//    QGLFormat format;
//    format.setVersion(3,3);
////    QGLContext ctx(format);
//QGLContext context(format);
//if(!context.isValid())
//{
//    std::cout << "Cannot create GL context" << std::endl;

//}

//context.makeCurrent();




    //GLuint prog_hdlr = set_shaders("/home/kostas/Documents/Qt-projects/Blender2/vertex.glsl", "/home/kostas/Documents/Qt-projects/Blender2/fragment.glsl");

    GLuint prog_hdlr = set_shaders("/home/kostas/Documents/Qt-projects/Blender2/vert.glsl", "/home/kostas/Documents/Qt-projects/Blender2/frag.glsl");


    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object


   glUseProgram(prog_hdlr); // specify the shaders to use

//    auto start = std::chrono::steady_clock::now();

    m_width = width();
    m_height = height();
    img =new QImage(m_width,m_height, QImage::Format_RGB888);
    img1 = QImage(m_width, m_height, QImage::Format_RGB888);
    qDebug()<<m_width<<" "<<m_height;
    initializeGL();
    oldWidth = 0;
    oldHeight = 0;
    tga.pic = new GLubyte[m_width*m_height*3];
    resizing = false;
    tga.rpic = new GLubyte[m_width*m_height*10];
    tga.gpic = new GLubyte[m_width*m_height*10];
    tga.bpic = new GLubyte[m_width*m_height*10];
}

void ModernGLWidget::initializeGL(){
    //glClearColor(0,0,0,1);
    //glEnable(GL_DEPTH_TEST);
   
}

void ModernGLWidget::paintGL(){
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //qDebug()<<"PAINTING";
    int unchangable_w = m_width;
    int unchangable_h = m_height;
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
            //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            // Create framebuffer
          unsigned int canvasFrameBuffer;
          glGenFramebuffers(1, &canvasFrameBuffer);
          glBindFramebuffer(GL_RENDERBUFFER, canvasFrameBuffer);

          // Attach renderbuffer
          unsigned int canvasRenderBuffer;
          glGenRenderbuffers(1, &canvasRenderBuffer);
          glBindRenderbuffer(GL_RENDERBUFFER, canvasRenderBuffer);
          glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, 800, 800);
          glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, canvasRenderBuffer);

            /* Prepare the targa header */
            memcpy(tga.head, tgahead, 12);

            tga.dx = unchangable_w;
            tga.dy = unchangable_h;
            tga.head2 = 0x2018;



            if(unchangable_w != oldWidth){

                oldWidth = unchangable_w;
                oldHeight= unchangable_h;
                qDebug()<<"Resizing ARRAY";
//                delete tga.rpic;
//                delete tga.gpic;
//                delete tga.bpic;
//                tga.rpic = nullptr;
//                tga.gpic = nullptr;
//                tga.bpic = nullptr;
                int v=1;
                tga.rpic = new GLubyte[unchangable_w*unchangable_h*v];
                tga.gpic = new GLubyte[unchangable_w*unchangable_h*v];
                tga.bpic = new GLubyte[unchangable_w*unchangable_h*v];
           }
            int screenWidth,screenHeight;
            glfwGetFramebufferSize(window, &screenWidth, &screenHeight); /* Get size, store into specified variables  */


            glPixelStorei(GL_PACK_ALIGNMENT,1);
            glPixelStorei(GL_PACK_ROW_LENGTH,  0);
            glPixelStorei(GL_PACK_SKIP_ROWS,   0);
            glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
             glFlush();
            glReadBuffer( GL_BACK );
            glReadPixels(0,0,unchangable_w, unchangable_h, GL_RED, GL_UNSIGNED_BYTE, tga.rpic);
            glReadPixels(0,0,unchangable_w, unchangable_h, GL_GREEN, GL_UNSIGNED_BYTE, tga.gpic);
            glReadPixels(0,0,unchangable_w, unchangable_h, GL_BLUE, GL_UNSIGNED_BYTE, tga.bpic);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//*img = (img->scaled(width(),height(),Qt::KeepAspectRatio));
//           img1 = img1.scaled(width(),height());
            img1.fill(Qt::green);
            unsigned int pixelSize = 3;

//            GLubyte *rpixels=new GLubyte[unchangable_w*10];
//            GLubyte *gpixels=new GLubyte[unchangable_w*10];
//            GLubyte *bpixels=new GLubyte[unchangable_w*10];


            for (unsigned int y = 0; y < unchangable_h; y++){
//                glReadPixels(0,y,unchangable_w*10,1,GL_RED,GL_UNSIGNED_BYTE,rpixels);
//                glReadPixels(0,y,unchangable_w*10,1,GL_GREEN,GL_UNSIGNED_BYTE, gpixels);
//                glReadPixels(0,y,unchangable_w*10,1,GL_BLUE,GL_UNSIGNED_BYTE, bpixels);

                for (unsigned int x = 0; x < unchangable_w; x++){

                    GLubyte valr = tga.rpic[y * unchangable_w + x];
                    GLubyte valg = tga.gpic[y * unchangable_w + x];
                    GLubyte valb = tga.bpic[y * unchangable_w + x];

                    QColor value(valr, valg, valb);
//                    value.setRed((value.red() + 11)%255);
//                    value.setRed((value.green() + 11)%255);
//                    value.setRed((value.blue() + 11)%255);
                    img1.setPixelColor(x, y, value);
                }
            }

            img1 = img1.mirrored(false,true);
            glDeleteFramebuffers(1,&canvasFrameBuffer);
            glDeleteRenderbuffers(1,&canvasRenderBuffer);
    glfwSwapBuffers(window);
    update();
}

void ModernGLWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

//    if(resizing==false)

//    if(img)

//    img->fill(Qt::green);

        painter.drawImage(0,0,img1);
        painter.setBrush(QBrush(Qt::blue));
painter.drawRect(QRectF(img1.width()-100,0,100,100));
}
/*
void ModernGLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //update();
    //updateGL();
    qDebug()<<"resizing "<<w<<h;
}*/

void ModernGLWidget::resizeEvent(QResizeEvent *e){
    qDebug()<<"Resizeing";
    m_width = e->size().width();
    m_height = e->size().height();
    qDebug()<<m_width<<" " <<m_height;

//    QImage *newimg = new QImage(m_width, m_height, QImage::Format_RGB888);
//    newimg->fill(Qt::black);
//    delete img;
//    img=nullptr;
//    img = newimg;
    qDebug()<<e->size().width();
//    delete img;
    img1 = QImage(m_width,m_height, QImage::Format_RGB888);
//    img1 = img1.scaled(m_width, m_height,Qt::KeepAspectRatio);
    img1.fill(Qt::green);
//    img = new QImage(e->size(),QImage::Format_RGB888);
//    update();
    glfwSetWindowSize(window,m_width,m_height);
    //*img = img->scaled(m_width, m_height, Qt::KeepAspectRatio);
    glViewport(0,0,m_width,m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    oldWidth = e->oldSize().width();
    oldHeight= e->oldSize().height();

//    img = new QImage(e->size().width(), e->size().height(), QImage::Format_RGB888);
//    img->fill(Qt::black);

//    oldWidth = e->size().width();
//    oldHeight = e->size().height();


}

void ModernGLWidget::read_n_compile_shader(const std::string filename, GLuint &hdlr, GLenum shaderType) {
    std::cerr << "Loading shader file " << filename << "... ";
    std::ifstream is(filename, std::ios::in|std::ios::binary|std::ios::ate);
    if (!is.is_open()) {
        std::cerr << "failed" << std::endl;
        return;
    }
    std::cerr << "ok" << std::endl;

    long size = is.tellg();
    char *buffer = new char[size+1];
    is.seekg(0, std::ios::beg);
    is.read(buffer, size);
    is.close();
    buffer[size] = 0;

    std::cerr << "Compiling the shader " << filename << "... ";
    hdlr = glCreateShader(shaderType);
    glShaderSource(hdlr, 1, (const GLchar**)&buffer, NULL);
    glCompileShader(hdlr);
    GLint success;
    glGetShaderiv(hdlr, GL_COMPILE_STATUS, &success);
    std::cerr << (success ? "ok" : "failed") << std::endl;

    GLint log_length;
    glGetShaderiv(hdlr, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length>0) {
        std::vector<char> v(log_length, 0);
        glGetShaderInfoLog(hdlr, log_length, NULL, v.data());
        if (strlen(v.data())>0) {
            std::cerr << v.data() << std::endl;
        }
    }

    delete [] buffer;
}



void ModernGLWidget::checkCompileErrors(GLuint shader, std::string type)
{
GLint success;
GLchar infoLog[1024];
if(type != "PROGRAM")
{
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}
else
{
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}
}

void ModernGLWidget::load_shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if(geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
        std::cerr<<"Ok";
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if(geometryPath != nullptr)
    {
        const char * gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr)
        glAttachShader(ID, geometry);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr)
        glDeleteShader(geometry);

}


GLuint ModernGLWidget::set_shaders(const std::string vsfile, const std::string fsfile) {
    GLuint vert_hdlr, frag_hdlr;
    load_shader(vsfile.c_str(), fsfile.c_str());//vert_hdlr, GL_VERTEX_SHADER);

    std::cerr << "Linking shaders... ";

    return ID;
}
