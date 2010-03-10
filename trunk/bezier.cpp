#include "bezier.h"
#include "line.h"

Bezier::Bezier( int x1, int y1, int x4, int y4 ){
    this->x1 = x1;
    this->y1 = y1;
    this->x4 = x4;
    this->y4 = y4;
    int dx = ( x4 - x1 );
    int dy = ( y4 - y1 );
    x2 = (int)(x1 + dx/3 );
    y2 = (int)(y1 + dy/3 );
    x3 = (int)(x4 - dx/3 );
    y3 = (int)(y4 - dy/3 );
}

void Bezier::drawMe( QImage * bitmap ){
    drawBezier(x1, y1, x2, y2, x3, y3, x4, y4, bitmap );
}

void Bezier::setPoint( int point, int x, int y ){
    if( point == 1 ){
        x1 = x; y1 = y;
    }
    else if( point == 2 ){
        x2 = x; y2 = y;
    }
    else if( point == 3 ){
        x3 = x; y3 = y;
    }
    else if( point == 4 ){
        x4 = x; y4 = y;
    }
}

unsigned int Bezier::checkPoints( int x, int y ){
    if( ((x > x1 - 5) && (x < x1 + 5)) && ((y > y1 - 5) && (y < y1 + 5)) )
        return 1;
    if( ((x > x2 - 5) && (x < x2 + 5)) && ((y > y2 - 5) && (y < y2 + 5)) )
        return 2;
    if( ((x > x3 - 5) && (x < x3 + 5)) && ((y > y3 - 5) && (y < y3 + 5)) )
        return 3;
    if( ((x > x4 - 5) && (x < x4 + 5)) && ((y > y4 - 5) && (y < y4 + 5)) )
        return 4;
    return 0;
}

void Bezier::drawBezier( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, QImage * bitmap, bool points )
{
    int cx = 3*(x2 - x1);
    int bx = 3*(x3 - x2) - cx;
    int ax = x4 - x1 - cx - bx;

    int cy = 3*(y2 - y1);
    int by = 3*(y3 - y2) - cy;
    int ay = y4 - y1 - cy - by;

    double at = 0.01;
    int popX = x1;
    int popY = y1;
    for( double t = at; t <= 1; t += at )
    {
        int x = ax*( t*t*t ) + bx*( t*t ) + cx*t + x1;
        int y = ay*( t*t*t ) + by*( t*t ) + cy*t + y1;
        if( x != popX || y != popY ){
            Line::drawLine( popX, popY, x, y, bitmap );
            popX = x;
            popY = y;
        }
    }
    if( points ){
        drawPoint( x1, y1, bitmap );
        drawPoint( x2, y2, bitmap );
        drawPoint( x3, y3, bitmap );
        drawPoint( x4, y4, bitmap );
    }
}

void Bezier::drawBezier( const QPoint& p1, const QPoint& p2, const QPoint& p3, const QPoint& p4, QImage * bitmap, bool points )
{
    drawBezier( p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), p4.x(), p4.y(), bitmap, points );
}
