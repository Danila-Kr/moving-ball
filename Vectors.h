#pragma once

#include <cmath>

//{=structures=================================================================
    struct TWO
        {
            int i, j;
        };

    class Vector
        {
        public:
            double xFrom_, yFrom_;
            double xTo_  , yTo_;
            double vx_ = xTo_ - xFrom_;
            double vy_ = yTo_ - yFrom_;

            double length ()
                {
                return sqrt(pow(xTo_ - xFrom_, 2) + pow(yTo_ - yFrom_, 2));
                }

            double angle  ()
                {
                if (xTo_ == xFrom_)
                    {
                    //printf ("%f", sin(3.1415926/2));
                    //getch();
                    if (vy_ < 0)
                        {
                        return 3.1415926/2*3;
                        }
                    else
                        {
                        return 3.1415926/2;
                        }
                    }
                else
                    {
                    return atan((   yTo_-  yFrom_)    /    (xTo_ - xFrom_));  //деление на ноль
                    }
                }

            Vector ();
        };

//-----------------------------------------------------------------------------
    class VectorFunctions
        {
        public:
            POINT  Swap             (double P1, double P2);                   //Vector v1, Vector v2
            Vector DrawVector       (Vector v_, int red, int green, int blue);//Draw - otladka
            Vector nVector          (double xi, double yi, double xj, double yj);
            Vector NormalVector     (Vector vector);
            Vector VectorP          (Vector v, double n);

            Vector VectorDiff       (Vector v1, Vector v2);
            Vector VectorSumm       (Vector v1, Vector v2);

            double scalarProduct    (Vector v1, Vector v2);
            double r1_, r2_;

            VectorFunctions ();

        };

//}============================================================================

//{=Constructors===============================================================

//{-Vector-Functions-----------------------------------------------------------

    VectorFunctions::VectorFunctions()
    :
        r1_(0),
        r2_(0)
        {}

//}----------------------------------------------------------------------------

//{-Vector---------------------------------------------------------------------

Vector::Vector()
    :
        xFrom_(0),
        yFrom_(0),
        xTo_  (0),
        yTo_  (0)
        {}

//}----------------------------------------------------------------------------

//}============================================================================

//{=Vector=Functions===========================================================

POINT  VectorFunctions::Swap             (double P1, double P2) //Vector v1, Vector v2
    {
    double twoR = r1_ + r2_;

    /*Vector temp;
    temp.xFrom_ = v1.xFrom_ + twoR;
    temp.xTo_   = v1.xFrom_ + twoR;

    v1.xFrom_  = v2.xFrom_ - twoR;
    v1.xTo_    = v2.xTo_   - twoR;

    v2.xFrom_  = temp.xFrom_;
    v2.xTo_    = temp.xTo_;
    */
    double temp = P1;
           P1   = P2;
           P2   = temp;

    return POINT {P1, P2};
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::DrawVector      (Vector v, int red, int green, int blue)
    {
    //txSetColor (RGB(red, green, blue), 4);
    //txLine (v.xFrom_, v.yFrom_, v.xTo_, v.yTo_);

    return v;
    }

//-----------------------------------------------------------------------------

double VectorFunctions::scalarProduct   (Vector v1, Vector v2)
    {
    return v1.length() * v2.length() * fabs(cos(v1.angle() - v2.angle()));
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::nVector         (double xi, double yi, double xj, double yj)
    {
    Vector nVector;
    nVector.xFrom_ = xi;
    nVector.yFrom_ = yi;

    nVector.xTo_   = xj;
    nVector.yTo_   = yj;

    double angle = nVector.angle ();//atan((nVector.yTo_ -  nVector.yFrom_)/(nVector.xTo_ - nVector.xFrom_))

    nVector.xTo_   = cos(angle) + nVector.xFrom_;
    nVector.yTo_   = sin(angle) + nVector.yFrom_;

    return nVector;
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::NormalVector    (Vector vector)
    {
    Vector NormalVector;


    NormalVector.xFrom_ = vector.xFrom_;
    NormalVector.yFrom_ = vector.yFrom_;

    NormalVector.xTo_   = vector.xFrom_ - vector.yTo_ + vector.yFrom_;
    NormalVector.yTo_   = vector.yFrom_ + vector.xTo_ - vector.xFrom_;

    return NormalVector;
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::VectorP         (Vector v, double n)
    {
    Vector pulse;
    pulse.xFrom_ = v.xFrom_;
    pulse.yFrom_ = v.yFrom_;

    pulse.xTo_ = (v.xTo_ - v.xFrom_) * n + v.xFrom_;
    pulse.yTo_ = (v.yTo_ - v.yFrom_) * n + v.yFrom_;

    return pulse;
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::VectorSumm      (Vector v1, Vector v2)
    {
    Vector Summ;
    Summ.xFrom_ = (v1.xFrom_ + v2.xFrom_) / 2;
    Summ.yFrom_ = (v1.xFrom_ + v2.xFrom_) / 2;

    Summ.xTo_ = v1.xTo_ + v2.xTo_ - (v1.xFrom_ + v2.xFrom_) / 2;
    Summ.yTo_ = v1.yTo_ + v2.yTo_ - (v1.xFrom_ + v2.xFrom_) / 2;

    return Summ;
    }

//-----------------------------------------------------------------------------

Vector VectorFunctions::VectorDiff      (Vector v1, Vector v2)
    {
    Vector difference;
    difference.xFrom_ = v1.xFrom_;
    difference.yFrom_ = v1.yFrom_;

    difference.xTo_ = v1.xTo_ - v2.xTo_ + v2.xFrom_;
    difference.yTo_ = v1.yTo_ - v2.yTo_ + v2.yFrom_;

    return difference;
    }

//}=============================================================================
