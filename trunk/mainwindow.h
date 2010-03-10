#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "mybitmap.h"
#include "mainwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget * mainWidget;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
