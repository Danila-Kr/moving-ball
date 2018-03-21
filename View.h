#pragma once



class View
    {
    public:
        void DrawBall       (int ballI,  VectorFunctions func_, MovingBall ball);
        void DrawAllBalls   (                                   MovingBall balls[], int numBalls);

        void DrawPiston     (double PistonY);

        void PrintValues    (double density, double pressure, double temperature);
    };

//{=Functions==================================================================

void View::PrintValues  (double density, double pressure, double temperature)
    {
    $b;
    printf ("\n D.= %f * 10^13", density);
    printf ("\n P.= %f * 10^9 ", pressure);
    printf ("\n t°= %f K°",      temperature);
    }

void View::DrawPiston   (double PistonY)
    {
    txSetColor      (RGB (255,   0, 255));
    txSetFillColor  (RGB (  0,   0,   0));
    double y = PistonY;
    if (y < 750)
        {
        txRectangle (200, y, 1200, y - 50);
        }
    else
        {
        txRectangle (200, 750, 1200, 700);
        }

    }

void View::DrawBall     (int ballI, VectorFunctions func_, MovingBall ball)
    {
    char text [10] = {};

    double x = ball.x_;
    double y = ball.y_;
    double r = ball.r_;

    txSetFillColor (RGB (  0, 150,   0));
    txSetColor     (RGB (  0, 127,   0));
    txCircle       (x, y, r);

    txSetFillColor (RGB (  0, 200,   0));
    txCircle       (x - r/6, y - r/6, r/1.5);

    txSetFillColor (RGB (   255, 255, 255));
    txCircle       (x - r/4, y - r/4, r/4);
    //txTransparentBlt  (txDC (), x_, y_, 0, 0, /*ballImage*/);
    //txSetColor     (RGB (  0,   0,   0), 2);
    //txSetColor     (RGB (255, 255, 255));
    sprintf        (text, "\%d", ballI);
    txTextOut      (x - 10, y + 20, text);
    }

void View::DrawAllBalls (MovingBall balls[], int numBalls)
    {
    for (int i = 0; i < numBalls; i++)
        {
        VectorFunctions func_;
        DrawBall (i,  func_, balls[i]);
        }
    }

//}============================================================================

