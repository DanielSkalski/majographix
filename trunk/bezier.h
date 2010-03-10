#ifndef BEZIER_H
#define BEZIER_H

#include "figure.h"

class Bezier : public Figure
{
public:
    int x1; int y1;
    int x2; int y2;
    int x3; int y3;
    int x4; int y4;

    Bezier( int x1, int y1, int x4, int y4 );
   // Bezier( QPoint& p1, QPoint& p4 );
    void drawMe(QImage* );
    unsigned int checkPoints( int x, int y );
    void setPoint( int point, int x, int y );

    static void drawBezier( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, QImage * bitmap, bool points = true );
    static void drawBezier( const QPoint& p1, const QPoint& p2, const QPoint& p3, const QPoint& p4, QImage * bitmap, bool points = true );
};

#endif // BEZIER_H
