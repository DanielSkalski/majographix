#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
    static void circlePoints( int x0, int y0, int x, int y, QImage * bitmap );
    static void fullCirclePoints( int x0, int y0, int x, int y, QImage * bitmap );
public:
    int x;
    int y;
    int r;
    bool full;

    Circle();
    Circle( int x, int y, int r, bool full = false );
    void drawMe(QImage* );

    static void drawCircle( int x0, int y0, int r, QImage * bitmap, bool full = false);
};

#endif // CIRCLE_H
