#include "line.h"
#include <cmath>

Line::Line()
{
    x1 = y1 = 0;
    x2 = y2 = 1;
    aa = false;
}

Line::Line( int x1, int y1, int x2, int y2, bool aa )
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->aa = aa;
}

void Line::drawMe( QImage * bitmap )
{
    if( this->aa )
        drawAALine( x1, y1, x2, y2, bitmap );
    else
        drawLine( x1, y1, x2, y2, bitmap );
}

void Line::drawLine(int x1, int y1, int x2, int y2, QImage * bitmap )
 {
     int d, dx, dy, ai, bi, xi, yi;
     int x = x1, y = y1;
     int color = qRgb( 255, 255, 255 );

     if (x1 < x2){
         xi = 1;
         dx = x2 - x1;
     }
     else{
         xi = -1;
         dx = x1 - x2;
     }

     if (y1 < y2){
         yi = 1;
         dy = y2 - y1;
     }
     else{
         yi = -1;
         dy = y1 - y2;
     }
     // pierwszy piksel
     setPixel( x, y, color, bitmap );
     // os wiodaca OX
     if (dx > dy){
         ai = (dy - dx) * 2;
         bi = dy * 2;
         d = bi - dx;
         while (x != x2){
             if (d >= 0){
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else{
                 d += bi;
                 x += xi;
             }
            setPixel( x, y, color, bitmap );
         }
     }
     // os wiodaca OY
     else{
         ai = ( dx - dy ) * 2;
         bi = dx * 2;
         d = bi - dy;
         while (y != y2){
             if (d >= 0){
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else{
                 d += bi;
                 y += yi;
             }
             setPixel( x, y, color, bitmap );
         }
     }
 }

int Line::ipart( double x ){
    return (int)floor( x );
}

int Line::round( double x){
    return (int)floor(x + 0.5);
}

double Line::fpart( double x){
    return x - floor( x );
}
double Line::rfpart( double x){
    return 1 - fpart(x);
}


void Line::drawAALine( int x1, int y1, int x2, int y2, QImage * bitmap )
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if( abs(dx) > abs(dy) ){
        //handle "horizontal" lines
        if (x2 < x1){
               std::swap(x1, x2);
               std::swap(y1, y2);
             //  dx = (x2-x1);
             //  dy = (y2-y1);
        }
        double gradient = dy / (double)dx;

        // handle first endpoint
        int xend = x1;
        double yend = y1 + gradient * (xend - x1);
        double xgap = rfpart(x1 + 0.5);
        int xpxl1 = xend;  // this will be used in the main loop
        int ypxl1 = ipart(yend);
        int color = qRgb( 255*(rfpart(yend)*xgap), 255*(rfpart(yend)*xgap), 255*(rfpart(yend)*xgap) );
        setPixel(xpxl1, ypxl1, color, bitmap);
        color = qRgb( 255*(fpart(yend)*xgap), 255*(fpart(yend)*xgap), 255*(fpart(yend)*xgap) );
        setPixel(xpxl1, ypxl1 + 1, color, bitmap);
        double intery = yend + gradient; // first y-intersection for the main loop

        // handle second endpoint
        xend = x2;
        yend = y2 + gradient * (xend - x2);
        xgap = fpart(x2 + 0.5);
        int xpxl2 = xend;  // this will be used in the main loop
        int ypxl2 = ipart(yend);
        color = qRgb( 255*(rfpart(yend)*xgap), 255*(rfpart(yend)*xgap), 255*(rfpart(yend)*xgap) );
        setPixel(xpxl2, ypxl2, color, bitmap);
        color = qRgb( 255*(fpart(yend)*xgap), 255*(fpart(yend)*xgap), 255*(fpart(yend)*xgap) );
        setPixel(xpxl2, ypxl2 + 1, color, bitmap);

        // main loop
        for(int x = xpxl1 + 1; x < xpxl2; x++){
            color = qRgb( 255*(rfpart(intery)), 255*(rfpart(intery)), 255*(rfpart(intery)) );
            setPixel(x, ipart(intery), color, bitmap);
            color = qRgb( 255*(fpart(intery)), 255*(fpart(intery)), 255*(fpart(intery)) );
            setPixel(x, ipart(intery) + 1, color, bitmap);
            intery += gradient;
        }
    }
    else{
        //handle "vertical" lines
        if (y2 < y1){
               std::swap(x1, x2);
               std::swap(y1, y2);
             //  dx = (x2-x1);
             //  dy = (y2-y1);
        }
        double gradient = dx / (double)dy;

        // handle first endpoint
        int yend = round(y1);
        double xend = x1 + gradient * (yend - y1);
        double ygap = rfpart(y1 + 0.5);
        int ypxl1 = yend;  // this will be used in the main loop
        int xpxl1 = ipart(xend);
        int color = qRgb( 255*(rfpart(xend)*ygap), 255*(rfpart(xend)*ygap), 255*(rfpart(xend)*ygap) );
        setPixel(xpxl1, ypxl1, color, bitmap);
        color = qRgb( 255*(fpart(xend)*ygap), 255*(fpart(xend)*ygap), 255*(fpart(xend)*ygap) );
        setPixel(xpxl1 + 1, ypxl1, color, bitmap);
        double intery = xend + gradient; // first y-intersection for the main loop

        // handle second endpoint
        yend = round(x2);
        xend = x2 + gradient * (yend - y2);
        ygap = fpart(y2 + 0.5);
        int ypxl2 = yend;  // this will be used in the main loop
        int xpxl2 = ipart(xend);
        color = qRgb( 255*(rfpart(xend)*ygap), 255*(rfpart(xend)*ygap), 255*(rfpart(xend)*ygap) );
        setPixel(xpxl2, ypxl2, color, bitmap);
        color = qRgb( 255*(fpart(xend)*ygap), 255*(fpart(xend)*ygap), 255*(fpart(xend)*ygap) );
        setPixel(xpxl2 + 1, ypxl2, color, bitmap);

        // main loop
        for(int y = ypxl1 + 1; y < ypxl2; y++){
            color = qRgb( 255*(rfpart(intery)), 255*(rfpart(intery)), 255*(rfpart(intery)) );
            setPixel(ipart(intery), y, color, bitmap);
            color = qRgb( 255*(fpart(intery)), 255*(fpart(intery)), 255*(fpart(intery)) );
            setPixel(ipart(intery) + 1, y, color, bitmap);
            intery += gradient;
        }
    }
}
void Line::drawGradientLine( QPoint p1, QPoint p2, QColor color1, QColor color2, QImage * bitmap , bool axisX )
{
    int X = p1.x(), Y = p1.y();
    if( axisX ){
        int deltax = abs( p1.x() - p2.x() );

        int r, g, b;
        int color;
        r = qMin( (color1.red() ), 255);
        g = qMin( (color1.green() ), 255);
        b = qMin( (color1.blue() ), 255);
        color = qRgb( r, g, b );

        if( deltax == 0 ){
            setPixel( X, Y, color, bitmap );
            return;
        }
        int xstep = (p2.x() > p1.x())?1:-1;
        int redDiff = (color2.red() - color1.red())/deltax;
        int greenDiff = (color2.green() - color1.green())/deltax;
        int blueDiff = (color2.blue() - color1.blue())/deltax;

        setPixel( X, Y, color, bitmap );
        X += xstep;
        while( X != p2.x() )
        {
            r = qMin( ( r + redDiff ), 255 );
            g = qMin( ( g + greenDiff ), 255 );
            b = qMin( ( b + blueDiff ), 255 );

            color = qRgb( r, g, b );
            setPixel( X, Y, color, bitmap );
            X += xstep;
        }
        r = qMin( ( r + redDiff ), 255 );
        g = qMin( ( g + greenDiff ), 255 );
        b = qMin( ( b + blueDiff ), 255 );
        color = qRgb( r, g, b );
        setPixel( X, Y, color, bitmap );
    }else{
        int deltay = abs( p1.y() - p2.y() );

        int r, g, b;
        int color;
        r = qMin( (color1.red() ), 255);
        g = qMin( (color1.green() ), 255);
        b = qMin( (color1.blue() ), 255);
        color = qRgb( r, g, b );

        if( deltay == 0 ){
            setPixel( X, Y, color, bitmap );
            return;
        }
        int ystep = (p2.y() > p1.y())?1:-1;
        int redDiff = (color2.red() - color1.red())/deltay;
        int greenDiff = (color2.green() - color1.green())/deltay;
        int blueDiff = (color2.blue() - color1.blue())/deltay;

        setPixel( X, Y, color, bitmap );
        Y += ystep;
        while( Y != p2.y() )
        {
            r = qMin( ( r + redDiff ), 255 );
            g = qMin( ( g + greenDiff ), 255 );
            b = qMin( ( b + blueDiff ), 255 );

            color = qRgb( r, g, b );
            setPixel( X, Y, color, bitmap );
            Y += ystep;
        }
        r = qMin( ( r + redDiff ), 255 );
        g = qMin( ( g + greenDiff ), 255 );
        b = qMin( ( b + blueDiff ), 255 );
        color = qRgb( r, g, b );
        setPixel( X, Y, color, bitmap );
    }
}


