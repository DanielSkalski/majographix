#include "mybitmap.h"
#include <cmath>
#include <iostream>

#include <QtGui/QPainter>

MyBitmap::MyBitmap() : QWidget()
{
    bitmap = new QImage(800, 600, QImage::Format_RGB32);
    tempBitmap = new QImage(800, 600, QImage::Format_RGB32 );

    drawMeAALine = false;
    drawMeLine = false;
    drawMeCircle = false;
    drawMeFullCircle = false;
    drawMeBezier = false;
    drawMeBspline = false;
    drawMeTriangle = false;
    drawMeGradTri = false;
    hand = false;
    draw = false;
    grabbed = false;

 //   Triangle::drawTriangle( 100, 100, 150, 200, 190, 150, tempBitmap, true);
}

 void MyBitmap::paintEvent(QPaintEvent *event)
 {
    QPainter paint( this );

    paint.drawImage( QPoint(0,0), *tempBitmap );
 }

 void MyBitmap::mousePressEvent( QMouseEvent * event )
 {
    if ( drawMeLine || drawMeAALine || drawMeCircle || drawMeFullCircle
         || drawMeBezier || drawMeBspline || drawMeTriangle || drawMeGradTri ){
        firstPoint = event->pos();
        draw = true;
    }
    else if( hand && grabbed && event->button() == Qt::RightButton ){
        obiekty.at( grabbedFigure )->addPoint( event->pos() );
        bitmap->fill( qRgb( 0, 0, 0) );
        for(unsigned int j = 0; j < obiekty.size(); j++ ){
            obiekty.at( j )->drawMe( bitmap );
        }
        *tempBitmap = bitmap->copy();
        update();
    }
    else if( hand ){
        unsigned int i = 0;
        int point = 0;
        for( ; i < obiekty.size(); i++ ){
            point = obiekty.at(i)->checkPoints( event->pos().x(), event->pos().y() );
            if( point != 0 ){
                grabbedFigure = i;
                grabbedPoint = point;
                grabbed = true;
                break;
            }
        }
        if( grabbed ){
        // stworzenie nowej bitmapy
            bitmap->fill( qRgb( 0, 0, 0) );
            for(unsigned int j = 0; j < obiekty.size(); j++)
            {
                if( j != grabbedFigure )
                    obiekty.at( j )->drawMe( bitmap );
            }
            update();
        }
    }
 }

 void MyBitmap::mouseMoveEvent ( QMouseEvent * event )
 {
     if( draw ){
        QPoint secondPoint = event->pos();
        *tempBitmap = bitmap->copy();
        if( drawMeLine ){
            Line::drawLine(firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y(), this->tempBitmap );
        }
        else if( drawMeAALine ){
            Line::drawAALine(firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y(), this->tempBitmap );
        }
        else if( drawMeCircle ){
            int r = Line::ipart(sqrt( pow( secondPoint.x() - firstPoint.x(), 2 ) + pow( secondPoint.y() - firstPoint.y(), 2 ) ));
            Circle::drawCircle(firstPoint.x(), firstPoint.y(), r, this->tempBitmap );
        }
        else if( drawMeFullCircle ){
            int r = Line::ipart(sqrt( pow( secondPoint.x() - firstPoint.x(), 2 ) + pow( secondPoint.y() - firstPoint.y(), 2 ) ));
            Circle::drawCircle(firstPoint.x(), firstPoint.y(), r, this->tempBitmap, true );
        }
        else if( drawMeBezier ){
            Line::drawLine( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y(), this->tempBitmap );
        }
        else if( drawMeBspline ){
            Line::drawLine( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y(), this->tempBitmap );
        }
        else if( drawMeTriangle || drawMeGradTri ){
            if( firstPoint.x() != secondPoint.x() && firstPoint.y() != secondPoint.y() ){
                int dx = secondPoint.x() - firstPoint.x();
                int dy = secondPoint.y() - firstPoint.y();
                QPoint thirdPoint(firstPoint.x() - dx, secondPoint.y() );
                Triangle::drawTriangle( firstPoint, secondPoint, thirdPoint, this->tempBitmap, drawMeGradTri );

            }
        }
        update();
    }else if( hand && grabbed && grabbedPoint != 0 ){
        QPoint secondPoint = event->pos();
        *tempBitmap = bitmap->copy();
        obiekty.at( grabbedFigure )->setPoint( grabbedPoint, secondPoint.x(), secondPoint.y() );
        obiekty.at( grabbedFigure )->drawMe( this->tempBitmap );
        update();
    }
 }

 void MyBitmap::mouseReleaseEvent( QMouseEvent * event )
 {
    if( draw ){
        QPoint secondPoint = event->pos();
        if( drawMeLine ){
            obiekty.push_back( new Line( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y()) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeAALine ){
            obiekty.push_back( new Line( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y(), true) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeCircle ){
            int r = Line::ipart(sqrt( pow( secondPoint.x() - firstPoint.x(), 2 ) + pow( secondPoint.y() - firstPoint.y(), 2 ) ));
            obiekty.push_back( new Circle( firstPoint.x(), firstPoint.y(), r ) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeFullCircle ){
            int r = Line::ipart(sqrt( pow( secondPoint.x() - firstPoint.x(), 2 ) + pow( secondPoint.y() - firstPoint.y(), 2 ) ));
            obiekty.push_back( new Circle( firstPoint.x(), firstPoint.y(), r, true ) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeBezier ){
            obiekty.push_back( new Bezier( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y() ) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeBspline ){
            obiekty.push_back( new Bspline( firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y() ) );
            obiekty.back()->drawMe( bitmap );
        }
        else if( drawMeTriangle || drawMeGradTri ){
            if( firstPoint.x() != secondPoint.x() && firstPoint.y() != secondPoint.y() ){
                int dx = secondPoint.x() - firstPoint.x();
                int dy = secondPoint.y() - firstPoint.y();
                QPoint thirdPoint(firstPoint.x() - dx, secondPoint.y() );
                obiekty.push_back( new Triangle( firstPoint, secondPoint, thirdPoint, drawMeGradTri ) );
                obiekty.back()->drawMe( bitmap );
            }
        }
        *tempBitmap = bitmap->copy();
        draw = false;
        update();
    }
    else if( hand && grabbed ){
        grabbedPoint = 0;
        *bitmap = tempBitmap->copy();
    }
 }

 void MyBitmap::setDrawLine(){
    false2all();
    drawMeLine = true;
 }
 void MyBitmap::setDrawAALine(){
    false2all();
    drawMeAALine = true;
 }
 void MyBitmap::setDrawCircle(){
   false2all();
   drawMeCircle = true;
 }
 void MyBitmap::setDrawFullCircle(){
    false2all();
    drawMeFullCircle = true;
 }
 void MyBitmap::setDrawBezier(){
    false2all();
    drawMeBezier = true;
 }
 void MyBitmap::setDrawBspline(){
    false2all();
    drawMeBspline = true;
 }
 void MyBitmap::setDrawTriangle(){
    false2all();
    drawMeTriangle = true;
 }
 void MyBitmap::setDrawGradTri(){
    false2all();
    drawMeGradTri = true;
 }
 void MyBitmap::setHand(){
    false2all();
    grabbed = false;
    hand = true;
 }

 void MyBitmap::false2all()
 {
    drawMeLine = drawMeAALine = drawMeCircle = drawMeFullCircle = drawMeBezier = drawMeBspline = drawMeTriangle = drawMeGradTri = false;
    hand = false;
    draw = false;
 }

 void MyBitmap::drawGradient()
 {
    int a, b, c, d, e, f;
    a = b = c = 0;
    d = e = f = 255;
    for(int i = 0; i < 100; i++ )
    {
        int r, g, b;
        r = (i * ( d - a )/100)%255;
        g = (i * ( e - b )/100)%255;
        b = (i * ( f - c )/100)%255;

        int color = qRgb( r, g, b );

        for( int j=0; j < 100; j++)
        {
            bitmap->setPixel( i,j, color );
        }
    }
 }
