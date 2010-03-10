#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new MainWidget();
    this->setCentralWidget( mainWidget );

    setWindowTitle("majoGraphix");
    setMinimumSize(220, 240);
    resize(960, 700);
}

MainWindow::~MainWindow()
{
}
