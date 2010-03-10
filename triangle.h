#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    QPoint p1;
    QPoint p2;
    QPoint p3;
    bool gradient;
    QColor color1;
    QColor color2;
    QColor color3;

    Triangle(const QPoint& a, const QPoint& b, const QPoint& c, bool = false);

    void drawMe(QImage* );
    unsigned int checkPoints( int x, int y );
    void setPoint( int point, int x, int y );

    static void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, QImage * bitmap, bool gradient = false );
    static void drawTriangle( const QPoint& p1, const QPoint& p2, const QPoint& p3, QImage * bitmap, bool gradient = false );

    static void drawGradientTriangle( QPoint p1, QPoint p2, QPoint p3, QColor c1, QColor c2, QColor c3, QImage * bitmap );

    static void swapColors(QColor &c1, QColor &c2);

    static void fillLine(int p1, QColor c1, int p2, QColor c2, int y, QImage * bitmap);

};

#endif // TRIANGLE_H
