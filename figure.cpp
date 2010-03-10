#include "figure.h"

Figure::Figure()
{
}

 int Figure::sprX( int x, QImage * bitmap )
 {
    if( x >= bitmap->width() )
        x = bitmap->width()-1;
    if( x < 0 )
        x = 0;
    return x;
 }
 int Figure::sprY( int y, QImage * bitmap )
 {
    if( y >= bitmap->height() )
        y = bitmap->height()-1;
    if( y < 0 )
        y = 0;
    return y;
 }

 void Figure::setPixel( int x, int y, int color, QImage* bitmap )
 {
    x = sprX( x, bitmap );
    y = sprY( y, bitmap );
    bitmap->setPixel( x, y, color );
 }

 void Figure::setPixel( QPoint* point, int color, QImage * bitmap )
 {
    int x = sprX( point->x(), bitmap );
    int y = sprY( point->y(), bitmap );
    bitmap->setPixel( x, y, color );
 }

void Figure::drawPoint( int x, int y, QImage * bitmap )
{
    int x0 = x - 5;
    int x1 = x + 5;
    int y0 = y - 5;
    for( ; y0 <= y + 5; y0++ )
        for( int xi = x0; xi <= x1; xi++ )
            setPixel( xi, y0, qRgb( 255, 0, 0 ), bitmap );
}
