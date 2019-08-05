#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modern_glwidget_copy.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ModernGLWidget* widget = new ModernGLWidget(this);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
