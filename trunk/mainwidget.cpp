#include "mainwidget.h"
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>

MainWidget::MainWidget()
{
    myBitmap = new MyBitmap;

    LiniaBtn = new QPushButton("Linia", this);
    LiniaAABtn = new QPushButton("Linia AA", this);
    OkragBtn = new QPushButton("Okrag", this);
    KoloBtn = new QPushButton("Kolo", this);
    BezierBtn = new QPushButton( "Bezier", this);
    BsplineBtn = new QPushButton( "B-spline", this);
    TriangleBtn = new QPushButton( "Trójkat", this );
    GradTriBtn = new QPushButton( "Trójkat z gradientem", this );
    HandBtn = new QPushButton( "Lapa", this );

    connect( LiniaBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawLine() ));
    connect( LiniaAABtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawAALine() ));
    connect( OkragBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawCircle() ));
    connect( KoloBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawFullCircle() ));
    connect( BezierBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawBezier() ));
    connect( BsplineBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawBspline() ));
    connect( TriangleBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawTriangle() ));
    connect( GradTriBtn, SIGNAL(clicked()), myBitmap, SLOT( setDrawGradTri() ));
    connect( HandBtn, SIGNAL(clicked()), myBitmap, SLOT( setHand() ));

    QHBoxLayout * przyciski = new QHBoxLayout();
    przyciski->addWidget( LiniaBtn );
    przyciski->addWidget( LiniaAABtn );
    przyciski->addWidget( OkragBtn );
    przyciski->addWidget( KoloBtn );
    przyciski->addWidget( BezierBtn );
    przyciski->addWidget( BsplineBtn );
    przyciski->addWidget( TriangleBtn );
    przyciski->addWidget( GradTriBtn );
    przyciski->addWidget( HandBtn );

    QGridLayout * layout = new QGridLayout();
    layout->addWidget( myBitmap );
    layout->addLayout( przyciski, 1, 0 );

    this->setLayout( layout );
}
