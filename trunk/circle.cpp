#include "circle.h"

Circle::Circle()
{
    x = 0;
    y = 0;
    r = 0;
    full = false;
}

Circle::Circle( int x, int y, int r, bool full )
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->full = full;
}

void Circle::drawMe( QImage * bitmap )
{
    Circle::drawCircle( x, y, r, bitmap, full );
}

 void Circle::circlePoints( int x0, int y0, int x, int y, QImage * bitmap )
 {
     int color = qRgb( 255, 255, 255 );

    setPixel(x0-x, y0-y, color, bitmap);
    setPixel(x0-x, y0+y, color, bitmap);
    setPixel(x0+x, y0-y, color, bitmap);
    setPixel(x0+x, y0+y, color, bitmap);
    setPixel(x0-y, y0-x, color, bitmap);
    setPixel(x0-y, y0+x, color, bitmap);
    setPixel(x0+y, y0-x, color, bitmap);
    setPixel(x0+y, y0+x, color, bitmap);
 }

 void Circle::fullCirclePoints( int x0, int y0, int x, int y, QImage * bitmap )
 {
    int color = qRgb( 255, 255, 255 );
    for( int xi = (x0-x); xi <=(x0+x); xi++ ){
        setPixel(xi, y0-y, color, bitmap);
        setPixel(xi, y0+y, color, bitmap);
    }
    for( int xi = (x0-y); xi <= (x0+y); xi++ ){
        setPixel(xi, y0-x, color, bitmap);
        setPixel(xi, y0+x, color, bitmap);
    }
 }

 void Circle::drawCircle( int x0, int y0, int r, QImage * bitmap, bool full )
 {
    double d = 5 - 4 * r;
    int x = 0;
    int y = r;

    double deltaA = (-2 * r + 5) * 4;
    double deltaB = 3 * 4;
    while (x <= y){
        if ( full )
            fullCirclePoints( x0, y0, x, y, bitmap );
        else
            circlePoints( x0, y0, x, y, bitmap );
        if (d > 0){
            d += deltaA;
            y -= 1;
            x += 1;
            deltaA += 4 * 4;
            deltaB += 2 * 4;
        }
        else{
            d += deltaB;
            x += 1;
            deltaA += 2 * 4;
            deltaB += 2 * 4;
        }
    }
 }
