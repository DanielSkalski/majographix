#include "triangle.h"
#include "line.h"
#include "rgb.h"

Triangle::Triangle( const QPoint& a, const QPoint& b, const QPoint& c, bool grad )
{
    p1 = a;
    p2 = b;
    p3 = c;
    gradient = grad;
}

void Triangle::drawMe( QImage * bitmap )
{
    drawTriangle( p1, p2, p3, bitmap, gradient );
}

unsigned int Triangle::checkPoints( int x, int y )
{
    if( (x > p1.x()-5)&&(x < p1.x()+5) && (y > p1.y()-5)&&(y < p1.y()+5) )
        return 1;
    if( (x > p2.x()-5)&&(x < p2.x()+5) && (y > p2.y()-5)&&(y < p2.y()+5) )
        return 2;
    if( (x > p3.x()-5)&&(x < p3.x()+5) && (y > p3.y()-5)&&(y < p3.y()+5) )
        return 3;
    return 0;
}

void Triangle::setPoint( int point, int x, int y )
{
    if( point == 1 ){
        p1.setX( x );
        p1.setY( y );
    }
    else if( point == 2 ){
        p2.setX( x );
        p2.setY( y );
    }
    else if( point == 3 ){
        p3.setX( x );
        p3.setY( y );
    }
}

void Triangle::drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, QImage * bitmap, bool gradient )
{
    Triangle::drawTriangle( QPoint(x1, y1), QPoint(x2, y2), QPoint(x3, y3), bitmap, gradient );
}

void Triangle::drawTriangle( const QPoint& p1, const QPoint& p2, const QPoint& p3, QImage * bitmap, bool gradient )
{
    if( gradient ){
        QColor c1 = QColor(255,0,0);
        QColor c2 = QColor(0,255,0);
        QColor c3 = QColor(0,0,255);
        Triangle::drawGradientTriangle( p1, p2, p3, c1, c2, c3, bitmap );
    }
    else{
        QColor c1 = QColor(255,255,255);
        QColor c2 = QColor(255,255,255);
        QColor c3 = QColor(255,255,255);
        Triangle::drawGradientTriangle( p1, p2, p3, c1, c2, c3, bitmap );
    }
}
/*
void Triangle::drawTriangle( const QPoint& p1, const QPoint& p2, const QPoint& p3, QImage * bitmap, bool gradient )
{
    // znajdz najdluzszy bok i os po której bedziesz szedl
    QPoint top;
    QPoint bottom;
    QPoint middle;

    if( p1.y() < p2.y() ){
        if( p1.y() < p3.y() ){
            top = p1;
            // bottom = P2 lub P3
            if( p2.y() < p3.y() ){
                // middle = P2, bottom = P3
                bottom = p3;
                middle = p2;
            }else{
                bottom = p2;
                middle = p3;
            }
        }else{
            top = p3;
            //bottom = P2 middle = P1
            bottom = p2;
            middle = p1;
        }
    }else{
        if( p2.y() < p3.y() ){
            top = p2;
            // bottom = P1 lub P3
            if( p1.y() < p3.y() ){
                // middle = P1, bottom = P3
                bottom = p3;
                middle = p1;
            }else{
                bottom = p1;
                middle = p3;
            }
        }else{
            top = p3;
            // bottom = P1 middle = P2
            bottom = p1;
            middle = p2;
        }
    }

    int tri_dy = bottom.y() - top.y();

        //idziemy po osi Y w dól od top do bottom
        //idziemy w petli od top do bottom
        int top_bottom_x = top.x();
        int curr_y = top.y();
        int top_bottom_dx = abs(top.x()-bottom.x());
        int top_bottom_dy = tri_dy;
        int top_bottom_err = (top_bottom_dx>top_bottom_dy)?top_bottom_dx:top_bottom_dy;
        top_bottom_err /= 2;
        int top_bottom_xstep = (top.x()<bottom.x())?1:-1;
        // rysowana druga linia - curr_line = top-middle
        int curr_line_x = top.x();
        int curr_line_dx = abs(top.x()-middle.x());
        int curr_line_dy = abs(top.y()-middle.y());
        int curr_line_err = (curr_line_dx>curr_line_dy)?curr_line_dx:curr_line_dy;
        curr_line_err /= 2;
        int curr_line_xstep = (top.x()<middle.x())?1:-1;

        double i = 0;
        double j = 0;
        bool secondHalf = false;
        while( curr_y <= bottom.y() )
        {

            //narysowanie linni od top_bottom do curr_line
            if( gradient )
            {
                // color1 = róznica odleglosc od top i od bottom
                QColor color1;
                if( top_bottom_dy != 0 ){
                    int r, g;
                    r = (int)(( i/top_bottom_dy )*255);
                    if( r > 255 ) r = 255;
                    g = (int)(( i/top_bottom_dy )*255);
                    if( g > 255 ) g = 255;
                    color1.setRed( 255 - r );
                    color1.setGreen( g );
                    color1.setBlue( 0 );
                }else{
                    color1.setRed( 255 );
                    color1.setGreen( 0 );
                    color1.setBlue( 0 );
                }
                QColor color2;
                if( curr_line_dy != 0 ){
                    if( secondHalf ){
                        int g,b;
                        g = (int)(( j/curr_line_dy )*255);
                        if( g > 255 ) g = 255;
                        b = (int)(( j/curr_line_dy )*255);
                        if( b > 255 ) b = 255;

                        color2.setRed( 0 );
                        color2.setGreen( g );
                        color2.setBlue( 255 - b );

                    }
                    else{
                        int r, b;
                        r = (int)(( j/curr_line_dy )*255);
                       // r = (int)(( i/top_bottom_dy )*255);
                        if( r > 255 ) r = 255;
                        b = (int)(( j/curr_line_dy )*255);
                        if( b > 255 ) b = 255;

                        if( j == curr_line_dy ){
                            r = 255;
                            b = 255;
                            j = 0;
                        }
                        color2.setRed( 255 - r );
                        color2.setGreen( 0 );
                        color2.setBlue( b );
                    }

                }
                else{
                    color2.setRed( 0 );
                    color2.setGreen(0);
                    color2.setBlue( 255 );
                }
                Line::drawGradientLine( QPoint(top_bottom_x, curr_y), QPoint(curr_line_x, curr_y), color1, color2, bitmap, true );
                i++;
                j++;
            }else{
                Line::drawLine( top_bottom_x, curr_y, curr_line_x, curr_y, bitmap );
            }


            // obliczenie nowych wartosci x i zwiekszenie y
            if( curr_y == middle.y() ){
                // zmiana ryswoanej lini - curr_line = middle-bottom
                curr_line_dx = abs(middle.x()-bottom.x());
                curr_line_dy = abs(middle.y()-bottom.y());
                curr_line_err = (curr_line_dx>curr_line_dy)?curr_line_dx:curr_line_dy;
                curr_line_err /= 2;
                curr_line_xstep = (bottom.x()<middle.x())?-1:1;
                secondHalf = true;
            }

            curr_y++;

            // nowe x dla top_bottom
            if( top_bottom_dy > top_bottom_dx ){
                top_bottom_err -= top_bottom_dx;
                if( top_bottom_err < 0 ){
                    top_bottom_x += top_bottom_xstep;
                    top_bottom_err += top_bottom_dy;
                }
            }else{
                while( top_bottom_err > 0 ){
                    top_bottom_x += top_bottom_xstep;
                    if( top_bottom_dy == 0 )
                        break;
                    top_bottom_err -= top_bottom_dy;
                }
                top_bottom_err += top_bottom_dx;
            }

            // nowe x dla curr_line
            if( curr_line_dy > curr_line_dx ){
                curr_line_err -= curr_line_dx;
                if( curr_line_err < 0 ){
                    curr_line_x += curr_line_xstep;
                    curr_line_err += curr_line_dy;
                }
            }else{
                while( curr_line_err >= 0 ){
                    curr_line_x += curr_line_xstep;
                    if( curr_line_dy == 0 )
                        break;
                    curr_line_err -= curr_line_dy;
                }
                curr_line_err += curr_line_dx;
            }
        }
}
*/
void Triangle::drawGradientTriangle( QPoint p1, QPoint p2, QPoint p3, QColor c1, QColor c2, QColor c3, QImage * bitmap )
{

    if( p1.y() > p2.y() ) {
        QPoint tmp = p1;
        p1 = p2;
        p2 = tmp;
        swapColors(c1,c2);
    }

    if(p2.y() > p3.y()) {
        QPoint tmp = p2;
        p2 = p3;
        p3 = tmp;
        swapColors(c2,c3);
        if(p1.y() > p2.y()) {
             QPoint tmp = p1;
             p1 = p2;
             p2 = tmp;
             swapColors(c1,c2);
        }
    }

    double delta_xl;
    double delta_xr;
    double xl;
    double xr;

    if ( p1.y() == p2.y() )
    {
        xl = p3.x();
        xr = p3.x();

        delta_xl = (double)(p2.x() - p3.x()) / (double)(p2.y() - p3.y());
        delta_xr = (double)(p1.x() - p3.x()) / (double)(p1.y() - p3.y());

        Rgb colorDeltaL = (Rgb(c3) - Rgb(c2)) / ( p3.y() - p2.y() );

        Rgb colorDeltaR = (Rgb(c3) - Rgb(c1)) / ( p3.y() - p1.y() );

        Rgb colorL(c3);
        Rgb colorR(c3);
        fillLine(p1.x(), c1, p2.x(), c2, p2.y(), bitmap);
        for(int i = p3.y(); i > p2.y(); i--)
        {
            fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i, bitmap);
            colorL = colorL - colorDeltaL;
            colorR = colorR - colorDeltaR;

            xl -= delta_xl;
            xr -= delta_xr;
        }

    }
    else
    {
        delta_xl = (double)(p2.x() - p1.x()) / (double)(p2.y() - p1.y());
        delta_xr = (double)(p3.x() - p1.x()) / (double)(p3.y() - p1.y());
        xl = p1.x();
        xr = p1.x();

        Rgb colorDeltaL = (Rgb(c1) - Rgb(c2)) / ( p1.y() - p2.y() );
        Rgb colorDeltaR = (Rgb(c1) - Rgb(c3)) / ( p1.y() - p3.y() );

        Rgb colorL(c1);
        Rgb colorR(c1);

        for(int i = p1.y(); i < p2.y(); i++)
        {
            fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i, bitmap);

            colorL = colorL + colorDeltaL;
            colorR = colorR + colorDeltaR;

            xl += delta_xl;
            xr += delta_xr;
        }

        if (p3.y() == p2.y())
        {
            fillLine(p3.x(), c3, p2.x(), c2, p3.y(), bitmap);
        }
        else
        {
            delta_xl = (double)(p3.x() - p2.x()) / (double)(p3.y() - p2.y());

            colorDeltaL = (Rgb(c3) - Rgb(c2)) / abs(( p3.y() - p2.y() ));
            for(int i = p2.y() ; i < p3.y(); i++)
            {
                fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i, bitmap);
                colorL = colorL + colorDeltaL;
                colorR = colorR + colorDeltaR;

                xl += delta_xl;
                xr += delta_xr;
            }
        }

    }
}

void Triangle::fillLine(int p1, QColor c1, int p2, QColor c2, int y, QImage * bitmap)
{
    if(p2 < p1)
    {
        int tmp = p1;
        p1 = p2;
        p2 = tmp;
        swapColors(c1, c2);
    }
    Rgb delta = (Rgb(c2) - Rgb(c1)) / (p2 - p1);
    Rgb start(c1);

    for(int i = p1; i < p2; i++)
    {
        setPixel(i, y, start.toQColor().rgb(), bitmap);
        start = start + delta;
    }
}
void Triangle::swapColors(QColor &c1, QColor &c2)
{
      QColor tmpC(c1.rgb());
      c1 = QColor(c2.rgb());
      c2 = QColor(tmpC.rgb());
}
