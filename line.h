#ifndef LINE_H
#define LINE_H

#include "figure.h"

class Line : public Figure
{
    public:
    static int ipart( double x );
    static int round( double x);
    static double fpart( double x);
    static double rfpart( double x);

public:
    int x1;
    int y1;
    int x2;
    int y2;
    bool aa;

    Line();
    Line( int, int, int, int, bool = false );
    void drawMe(QImage* );

    static void drawAALine( int x1, int y1, int x2, int y2, QImage * bitmap );
    static void drawLine(int x1, int y1, int x2, int y2, QImage * bitmap );
    static void drawGradientLine( QPoint p1, QPoint p2, QColor color1, QColor color2, QImage * bitmap, bool axisX = true );
};

#endif // LINE_H
