#ifndef FIGURE_H
#define FIGURE_H

#include <QtGui/QWidget>
#include <QtGui/QImage>

class Figure : public QWidget
{
    Q_OBJECT

public:
    Figure();
    virtual void drawMe( QImage *) = 0;
    static int sprX( int x, QImage* bitmap );
    static int sprY( int y, QImage* bitmap );

    static void setPixel( int x, int y, int color, QImage * bitmap );
    static void setPixel( QPoint* point, int color, QImage * bitmap );
    static void drawPoint( int x, int y, QImage * bitmap );

    virtual unsigned int checkPoints( int x, int y ){
        return 0;
    }
    virtual void setPoint( int point, int x, int y ){}
    virtual void addPoint( int x, int y ){}
    virtual void addPoint( const QPoint& p ){
        this->addPoint( p.x(), p.y() );
    }
};

#endif // FIGURE_H
