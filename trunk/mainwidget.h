#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include "mybitmap.h"

class MainWidget : public QWidget
{
        Q_OBJECT
public:
    QPushButton * LiniaBtn;
    QPushButton * LiniaAABtn;
    QPushButton * OkragBtn;
    QPushButton * KoloBtn;
    QPushButton * BezierBtn;
    QPushButton * BsplineBtn;
    QPushButton * TriangleBtn;
    QPushButton * GradTriBtn;
    QPushButton * HandBtn;
    MyBitmap * myBitmap;
    MainWidget();
};

#endif // MAINWIDGET_H
