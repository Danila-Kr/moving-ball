#pragma once

#include "Vectors.h"

class MovingBall
    {
    public:
        double dt_;
        Vector velocity_;

        int  ballNumber_;
        double x_, y_, r_;

        void InitBall (int i);

        MovingBall ();
    };

//{-MovingBall-----------------------------------------------------------------

    MovingBall::MovingBall ()
       :
        x_ (0),
        y_ (0),
        r_ (0),
        dt_(0),

        ballNumber_(0)
        {}

//}----------------------------------------------------------------------------

//{=Ball===Functions===========================================================
void MovingBall::InitBall   (int i)
    {
        r_  = 15;//+ rand() % 3;

        x_  =  200 + (r_ + 1);//txMouseX() + rand()%25;
        y_  =  900 - (r_ + 1);//txMouseY() + rand()%25;

        velocity_.vx_ =  15;
        velocity_.vy_ =  rand() % 5 + 1;

        velocity_.xFrom_ = x_;
        velocity_.yFrom_ = y_;

        velocity_.xTo_ = x_ + velocity_.vx_;
        velocity_.yTo_ = y_ + velocity_.vy_;



        dt_ = 0.1;

        ballNumber_ = i;

    }
//}============================================================================
