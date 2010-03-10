#ifndef MYBITMAP_H
#define MYBITMAP_H

#include <QtGui/QWidget>
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include "figure.h"
#include "line.h"
#include "circle.h"
#include "bezier.h"
#include "bspline.h"
#include "triangle.h"

class MyBitmap : public QWidget
{
    Q_OBJECT

public:
    QImage * bitmap;
    QImage * tempBitmap;
    MyBitmap();
    void drawGradient();

protected:
    QPoint firstPoint;
    bool draw;
    bool drawMeLine;
    bool drawMeAALine;
    bool drawMeCircle;
    bool drawMeFullCircle;
    bool drawMeBezier;
    bool drawMeBspline;
    bool drawMeTriangle;
    bool drawMeGradTri;
    bool hand;
    bool grabbed;
    unsigned int grabbedFigure;
    unsigned int grabbedPoint;

    std::vector< Figure* > obiekty;

    void paintEvent( QPaintEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent * event );

    void false2all();

public slots:
    void setDrawLine();
    void setDrawAALine();
    void setDrawCircle();
    void setDrawFullCircle();
    void setDrawBezier();
    void setDrawBspline();
    void setDrawTriangle();
    void setDrawGradTri();
    void setHand();
};

#endif // MYBITMAP_H
