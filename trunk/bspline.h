#ifndef BSPLINE_H
#define BSPLINE_H

#include "figure.h"

class Bspline : public Figure
{
    std::vector< QPoint > points;
public:
    Bspline(int, int, int, int);
    void drawMe(QImage* );
    unsigned int checkPoints( int x, int y );
    void setPoint( int point, int x, int y );
    void addPoint( int x, int y );
    void addPoint( const QPoint& p ){
        this->addPoint( p.x(), p.y() );
    }

    static void drawBspline( const std::vector< QPoint >& points , QImage * bitmap );
};

#endif // BSPLINE_H
