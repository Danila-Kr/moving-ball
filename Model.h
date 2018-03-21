#pragma once

#include "Vectors.h"

class Model
    {
    private:
        VectorFunctions func;
        unsigned long ballArray_ [10000];
        void Physics  (double pistonY, int i, MovingBall ball);

    public:

        void FillUp     (                    int numBalls);
        void InitBalls  (MovingBall balls[], int numBalls);

        void MoveBall   (double pistonY, int i, MovingBall ball);

        void MoveAllBalls   (MovingBall balls[], int numBalls, double pistonY);
        void FindDoBump     (MovingBall balls[], int numBalls);
        void Bump           (MovingBall balls[], int i, int j);

        void AddBall      (MovingBall balls[], int numBalls);
        void DeleteBall   (                    int numBalls);

        double DtForMoment  (MovingBall balls[], int i, int j, double L, int depth);
        double BallPlace    (MovingBall balls[], int numBalls, double x1, double y1, double x2, double y2);

        double Density      (int numBalls);
        double Pressure     (int numBalls);
        double Temperature  (int numBalls);

        double pistonY_;
        double Piston       ();

        Model ();
    };

//{-Model----------------------------------------------------------------------

    Model::Model ()
    :
    pistonY_    (0)

    {}

//}----------------------------------------------------------------------------

//{=Functions==================================================================

//{=ChangeBallsNum=============================================================

void   Model::AddBall       (MovingBall balls[], int numBalls)
    {
    if (BallPlace(balls, numBalls, 260, 900, 200, 840) == 0)
        {
        balls[numBalls].InitBall (numBalls + 1);
        ballArray_[numBalls] = numBalls;
        numBalls++;
        Sleep (5);
        }
    }

//-----------------------------------------------------------------------------

void   Model::DeleteBall    (int numBalls)
    {
    if (numBalls >= 0) numBalls--;
    }

//}============================================================================

//{=Values=====================================================================

double Model::Density       (int numBalls)
    {
    double height  = 900 - Piston ();
    double density = ((3.34 * 15) * numBalls / (1200 * height * 148877 * 1000) )* pow (10, 13);// 15 = r_

    return density;
    }

//-----------------------------------------------------------------------------

double Model::Pressure      (int numBalls)
    {
    double pressure = 0;
    if (averageV > 0)
        {
        pressure = ((Density (numBalls) / pow (10, 4)) * pow (averageV, 2)) / 3;
        }
    return pressure;
    }

//-----------------------------------------------------------------------------

double Model::Temperature   (int numBalls)
    {
    double height  = 900 - Piston ();
    double t = 0;

    t = ((Pressure (numBalls) / pow (10, 9)) * 1200 * height * 14887) / (1.38 * numBalls);

    return t;
    }

//}============================================================================

//{=ball's=Moving==============================================================
void Model::MoveAllBalls    (MovingBall balls[], int numBalls, double pistonY)
    {
    double velocitySumm = 0;
    FindDoBump (balls, numBalls);

    for (int i = 0; i < numBalls; i++)
        {
        MoveBall (pistonY, i, balls[i]);

        //ballArray_[i] = ballArray_[i] + balls[i].bounceNum_ * numBalls_;
        //balls[i].bounceNum_ = 0;

        velocitySumm += balls[i].velocity_.length();
        //printf  ("\n hello %f", velocitySumm);
        //printf  ("\n iks   %f", balls[i].x_);
        //printf  ("\n igrek %f", balls[i].y_);

        }
    averageV = velocitySumm / numBalls;
    }

void Model::MoveBall        (double pistonY, int i, MovingBall ball)
    {
    Physics (pistonY, i, ball);

    ball.x_ = ball.x_ + ball.velocity_.vx_ * ball.dt_;
    ball.y_ = ball.y_ + ball.velocity_.vy_ * ball.dt_;
    }

void Model::Physics         (double pistonY, int i, MovingBall ball)
    {

    double x = ball.x_;
    double y = ball.y_;
    double r = ball.r_;

    double vx = ball.velocity_.vx_;
    double vy = ball.velocity_.vy_;

    if (x >= 1200 - r)
        {
        vx  = -vx;
        x   = 1200 - r;
        vx -=  vx / 4;
        }

    if (x <=  200 + r)
        {
        vx  = -vx;
        x   =  200 + r;
        vx -=  vx / 4;
        }

    if (y <=  pistonY + r)
        {
        vy  = -vy;
        y   =  pistonY + r;
        vy -=  vy / 8;
        }

    if (y >=  900 - r)
        {
        vy  = -vy;
        y   =  900 - r;
        vy -=  vy / 4;
        }

    if (x <= 350 + r/4 && (y >=  750 - r && y <=  750 + r ))
        {
        vy  = -vy;
        if (y <   750 - r)  y  =  750 + r;
        if (y >   750 + r)  y  =  750 - r;
        vy -=  vy / 4;
        }

    ball.x_ = x;
    ball.y_ = y;
    ball.velocity_.vx_ = vx;
    ball.velocity_.vy_ = vy;

//{----------------------------------------------------------------------------
/*
    if (velocity_.vy_ >=  50)
        {
        velocity_.vy_ =   50;
        }

    if (velocity_.vy_ <= -50)
        {
        velocity_.vy_ =  -50;
        }

    if (velocity_.vx_ >=  50)
        {
        velocity_.vx_ =   50;
        }

    if (velocity_.vx_ <= -50)
        {
        velocity_.vx_ =  -50;
        }
 */
//}----------------------------------------------------------------------------
    }

//}============================================================================

double Model::Piston        ()
    {
    if (pistonY_ >= 750)
        {
        pistonY_ = 750;
        }
    return pistonY_;
    }

void   Model::FillUp        (int numBalls)
    {

    for (int i = 0; i < numBalls; i += 1)
        {
        ballArray_ [i] = i;
        }
    }

void   Model::InitBalls     (MovingBall balls[], int numBalls)
    {
    int i;
    for (i = 0; i < numBalls; i += 1)
        {
        balls[i].InitBall (i);
        }

    }

void   Model::FindDoBump    (MovingBall balls[], int numBalls)
    {
    bool bump = false;
    for (int i = 0; i < numBalls - 1 && bump == false; i++)
        {
        for (int j = i + 1; j < numBalls && bump == false; j++)
            {
            double L = (balls[i].x_ - balls[j].x_)*(balls[i].x_ - balls[j].x_) +
                       (balls[i].y_ - balls[j].y_)*(balls[i].y_ - balls[j].y_);

            if ((balls[i].r_ + balls[j].r_)*(balls[i].r_ + balls[j].r_) >=
               ((balls[i].x_ - balls[j].x_)*(balls[i].x_ - balls[j].x_) +
                (balls[i].y_ - balls[j].y_)*(balls[i].y_ - balls[j].y_)))
                {
                double tempDtI = balls[i].dt_;
                double tempDtJ = balls[j].dt_;

                balls[i].dt_ = - DtForMoment (balls, i, j, L, 0);
                balls[j].dt_ =   balls[i].dt_;

                //getch ();
                MoveBall (Piston (), i, balls[i]);
                MoveBall (Piston (), j, balls[j]);
                //DrawAllBalls (/*ballImage*/);
                //txSleep (5);

                //getch ();

                Bump (balls, i, j);
                bump = true;
                balls[i].dt_ = tempDtI;
                balls[j].dt_ = tempDtJ;
                }
            }

        //printf(" I \n");
        }
    //printf("FDB \n");

    }

double Model::DtForMoment   (MovingBall balls[], int i, int j, double L, int depth)
    {
    //return 0.01;
    double TwoR = (balls[i].r_ + balls[j].r_) * (balls[i].r_ + balls[j].r_);

    if  (TwoR == L || depth >= 200)
        {
        return balls[i].dt_;
        }
    else
        {
        if  (TwoR > L)
            {
            balls[i].dt_ = balls[i].dt_ * 1.5;
            L =
            (balls[i].x_ - balls[j].x_ - (balls[i].velocity_.vx_ - balls[j].velocity_.vx_) * balls[i].dt_) *
            (balls[i].x_ - balls[j].x_ - (balls[i].velocity_.vx_ - balls[j].velocity_.vx_) * balls[i].dt_) +
            (balls[i].y_ - balls[j].y_ - (balls[i].velocity_.vy_ - balls[j].velocity_.vy_) * balls[i].dt_) *
            (balls[i].y_ - balls[j].y_ - (balls[i].velocity_.vy_ - balls[j].velocity_.vy_) * balls[i].dt_);
            return DtForMoment (balls, i, j, L, depth + 1);
            }
        else
            {
            balls[i].dt_ = balls[i].dt_ * 0.5;
            L =
            (balls[i].x_ - balls[j].x_ - (balls[i].velocity_.vx_ - balls[j].velocity_.vx_) * balls[i].dt_) *
            (balls[i].x_ - balls[j].x_ - (balls[i].velocity_.vx_ - balls[j].velocity_.vx_) * balls[i].dt_) +
            (balls[i].y_ - balls[j].y_ - (balls[i].velocity_.vy_ - balls[j].velocity_.vy_) * balls[i].dt_) *
            (balls[i].y_ - balls[j].y_ - (balls[i].velocity_.vy_ - balls[j].velocity_.vy_) * balls[i].dt_);
            return DtForMoment (balls, i, j, L, depth + 1);
            }
        }
    }

double Model::BallPlace     (MovingBall balls[], int numBalls, double x1, double y1, double x2, double y2)
    {

    double n = 0;
    for (int i = 0; i < numBalls; i++)
        {
        //double r = balls[i].x_;

        if (((balls[i].x_ /*- r*/ < x1  && balls[i].x_ /*+ r*/ > x2) || (balls[i].x_ /*+ r*/ > x1  && balls[i].x_ /*- r*/ < x2)) &&
            ((balls[i].y_ /*+ r*/ < y1  && balls[i].y_ /*- r*/ > y2) || (balls[i].y_ /*- r*/ > y1  && balls[i].y_ /*+ r*/ < y2)))
                {
                n++;
                }
        }
    //printf ("\n %f", n);
    return n;//1;
    }

void   Model::Bump          (MovingBall balls[], int i, int j)
    {
    //assert(balls[0].velocity_.vx_ < 0 || balls[0].velocity_.vx_ > 0 );
    //assert(balls[1].velocity_.vy_ < 0 || balls[1].velocity_.vy_ > 0 );
    // printf("bump \n");
    Vector n =
        func.nVector    (balls[i].x_, balls[i].y_, balls[j].x_, balls[j].y_);
        n.xFrom_ = balls[i].x_ + (balls[j].x_ - balls[i].x_) * balls[i].r_ / (balls[i].r_ + balls[j].r_);
        n.yFrom_ = balls[i].y_ + (balls[j].y_ - balls[i].y_) * balls[i].r_ / (balls[i].r_ + balls[j].r_);

    n.vx_ = n.xTo_ - n.xFrom_ ;
    n.vy_ = n.yTo_ - n.yFrom_ ;
    //assert(n.vx_ < 0 || n.vx_ > 0 );
    //assert(n.vy_ < 0 || n.vy_ > 0 );

        n = func.VectorP (n, 1. / n.length());
        func.DrawVector  (n, 255,   0, 255);

    n.vx_ = n.xTo_ - n.xFrom_ ;
    n.vy_ = n.yTo_ - n.yFrom_ ;
    //getch ();

    //assert(n.vx_ < 0 || n.vx_ > 0 );
    //assert(n.vy_ < 0 || n.vy_ > 0 );

     func.DrawVector (func.NormalVector
    (func.nVector    (balls[i].x_, balls[i].y_, balls[j].x_, balls[j].y_)),   0, 255, 255);
    //getch ();

    POINT scalarP = func.Swap (
                         func.scalarProduct
                        (func.DrawVector (func.VectorP (balls[i].velocity_, pow(balls[i].r_, 2)), 255, 255,   0), n),
                         func.scalarProduct
                        (func.DrawVector (func.VectorP (balls[j].velocity_, pow(balls[j].r_, 2)),   0,   0, 255), n));
    //getch ();


    Vector Pn1 = func.DrawVector (func.VectorP (n,  scalarP.x), 255,   0,   0);
    Vector Pn2 = func.DrawVector (func.VectorP (n, -scalarP.y), 100, 200,   0);


    //getch ();

    Vector Pt1 = func.DrawVector (func.VectorDiff (func.VectorP (balls[i].velocity_, pow(balls[i].r_, 2)), Pn2), 200, 200, 200);
    Vector Pt2 = func.DrawVector (func.VectorDiff (func.VectorP (balls[j].velocity_, pow(balls[i].r_, 2)), Pn1), 100, 100, 100);
    //getch ();

    //assert(balls[0].velocity_.vx_ < 0 || balls[0].velocity_.vx_ > 0 );
    //assert(balls[1].velocity_.vy_ < 0 || balls[1].velocity_.vy_ > 0 );

    balls[i].velocity_ = func.DrawVector (func.VectorP (func.VectorSumm (Pt1, Pn1), 0.9 / pow(balls[i].r_, 2)),   0, 200, 150);
    balls[j].velocity_ = func.DrawVector (func.VectorP (func.VectorSumm (Pt2, Pn2), 0.9 / pow(balls[i].r_, 2)), 150, 200,   0);
    //getch ();

    balls[i].velocity_.vx_ = balls[i].velocity_.xTo_ - balls[i].velocity_.xFrom_ ;
    balls[i].velocity_.vy_ = balls[i].velocity_.yTo_ - balls[i].velocity_.yFrom_ ;

    balls[j].velocity_.vx_ = balls[j].velocity_.xTo_ - balls[j].velocity_.xFrom_ ;
    balls[j].velocity_.vy_ = balls[j].velocity_.yTo_ - balls[j].velocity_.yFrom_ ;

    //assert(balls[0].velocity_.vx_ < 0 || balls[0].velocity_.vx_ > 0 );
    //assert(balls[1].velocity_.vy_ < 0 || balls[1].velocity_.vy_ > 0 );

balls[i].velocity_.vx_ -= balls[i].velocity_.vx_ / 10;
balls[i].velocity_.vy_ -= balls[i].velocity_.vy_ / 10;

balls[j].velocity_.vx_ -= balls[j].velocity_.vx_ / 10;
balls[j].velocity_.vy_ -= balls[j].velocity_.vy_ / 10;


    //func.DrawVector (balls[j].velocity_ ,   0, 200, 150);
    //func.DrawVector (balls[i].velocity_ , 150, 200,   0);

    //getch ();
        //движение?
    //balls[i].dt_ = 100;
    //balls[j].dt_ = 100;
    MoveBall (Piston (), i, balls[i]);
    MoveBall (Piston (), j, balls[j]);

    }

//}============================================================================

