#include "bspline.h"
#include "bezier.h"

Bspline::Bspline( int x1, int y1, int x2, int y2 )
{
    this->points.push_back( QPoint( x1, y1 ) );
    // srodkowe punkty
    int dx = ( x2 - x1 );
    int dy = ( y2 - y1 );
    int xd2 = (int)(x1 + dx/3 );
    int yd2 = (int)(y1 + dy/3 );
    int xd3 = (int)(x2 - dx/3 );
    int yd3 = (int)(y2 - dy/3 );
    this->points.push_back( QPoint( xd2, yd2 ) );
    this->points.push_back( QPoint( xd3, yd3 ) );
    this->points.push_back( QPoint( x2, y2 ) );
   // addPoint( 100, 200 );
}

void Bspline::drawMe(QImage* bitmap)
{
    drawBspline( this->points, bitmap );
}

unsigned int Bspline::checkPoints( int x, int y )
{
    for( int i = 0; i < points.size(); i++ )
    {
        int xa = points[i].x();
        int ya = points[i].y();
        if( (x < xa + 5 && x > xa - 5) && (y < ya + 5 && y > ya - 5) )
            return i + 1;
    }
    return 0;
}

void Bspline::setPoint( int point, int x, int y )
{
    point--;
    points[point].setX( x );
    points[point].setY( y );
}

void Bspline::addPoint( int x, int y )
{
    QPoint temp = points[ points.size() - 1 ];
    points[ points.size() - 2 ] = temp;

    int dx = ( x - temp.x() );
    int dy = ( y - temp.y() );
    int x3 = ( x - dx/3 );
    int y3 = ( y - dy/3 );

    points[ points.size() - 1 ] = QPoint( x3, y3 );
    points.push_back( QPoint( x, y ) );
    return;
}

void Bspline::drawBspline( const std::vector< QPoint >& points , QImage * bitmap )
{
    if( points.size() == 4 )
    {
        // zwykla pojedyncza krzywa bezier
        Bezier::drawBezier( points[0], points[1], points[2], points[3], bitmap, false );
    }
    else
    {
        // zaczynaja sie schodki ;]
        QPoint e, f, g, e1, f1;
        // narysowanie pierwszej krzywej
        e = points[0];
        f = points[1];
        g = (points[1] + points[2]) / 2;
        f1 = (2 * points[2] / 3) + (points[3] / 3);
        e1 = (g + f1) / 2;
        Bezier::drawBezier( e, f, g, e1, bitmap, false );
        // rysowanie srodkowych krzywych
        for( int i = 1; i < points.size() - 4; i++ )
        {
            e = e1;
            f = f1;
            g = (points[i+1] / 3) + (2 * points[i+2] / 3);
            f1 = (2 * points[i+2] / 3) + (points[i+3] / 3);
            e1 = (g + f1) / 2;
            Bezier::drawBezier( e, f, g, e1, bitmap, false );
        }
        // narysowanie ostatniej krzywej
        e = e1;
        f = f1;
        g = points[ points.size() - 2 ];
        e1 = points[ points.size() - 1 ];
        Bezier::drawBezier( e, f, g, e1, bitmap, false );
    }
    for( int i = 0; i < points.size(); i++ )
    {
        drawPoint( points[i].x(), points[i].y(), bitmap );
    }
}
