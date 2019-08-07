#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <modern_glwidget_copy.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWindow(GLFWwindow* _window);
    ModernGLWidget* widget;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
