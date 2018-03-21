#pragma once

#include "Model.h"
#include "View.h"

class Controller
    {
    public:
        void Menu           (MovingBall balls[], int numBalls);
        void RunGame        (MovingBall balls[], int numBalls);
        void BallControls   (MovingBall balls[], int numBalls);
        double PistonY      ();
    };

//{=Functions=================================================================

void Controller::BallControls   (MovingBall balls[], int numBalls)
    {
    for (int i = 0; i < numBalls; i++)
        {
        if (GetAsyncKeyState (VK_LEFT))  balls[i].velocity_.vx_ -= 1;
        if (GetAsyncKeyState (VK_RIGHT)) balls[i].velocity_.vx_ += 1;

        if (GetAsyncKeyState (VK_UP))    balls[i].velocity_.vy_ -= 1;
        if (GetAsyncKeyState (VK_DOWN))  balls[i].velocity_.vy_ += 1;

        if (GetAsyncKeyState ('0'))
            {
            balls[i].velocity_.vx_ = 0;
            balls[i].velocity_.vy_ = 0;
            }

        balls[i].x_ += balls[i].velocity_.vx_ * balls[i].dt_;

        balls[i].y_ += balls[i].velocity_.vy_ * balls[i].dt_;
        }
    }

//-----------------------------------------------------------------------------

void Controller::Menu           (MovingBall balls[], int numBalls)
    {
    int run = false;
    HDC menu  = txLoadImage ("Menu.bmp");
    HDC Exit  = txLoadImage ("Exit_Button.bmp");
    HDC Start = txLoadImage ("Start_button.bmp");
    txBitBlt (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), menu);

    while (run != true)
        {
        if (txMouseX () > 370 && txMouseX () < 840 && txMouseY () > 330 && txMouseY () < 560)
            {
            txBitBlt (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), Start);

            if (txMouseButtons () & 1)
                {
                RunGame  (balls, numBalls);
                run = true;
                }
            Sleep (50);
            txBitBlt   (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), menu);
            Sleep (10);
            }

        if (txMouseX () > 435 && txMouseX () < 765 && txMouseY () > 670 && txMouseY () < 780)
            {

            txBitBlt (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), Exit);

            if (txMouseButtons () & 1)
                {
                Sleep (300);
                break;
                }
            Sleep (50);
            txBitBlt (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), menu);
            Sleep (10);
            }
        }
    txDeleteDC (Start);
    txDeleteDC (menu);
    txDeleteDC (Exit);
    }

//-----------------------------------------------------------------------------

void Controller::RunGame        (MovingBall balls[], int numBalls)
    {

    /*HDC /*ballImage  = txLoadImage ("cursor.bmp");*/
    HDC background = txLoadImage ("backgroud.bmp");

    Model model;
    View  view;

    model.InitBalls    (balls, numBalls);
    model.FillUp       (numBalls);

    //view.DrawAllBalls (/*ballImage,*/ model);

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txClear ();
        txClearConsole ();

        txBitBlt (txDC (), 0, 0, txGetExtentX (), txGetExtentY (), background);
        txLine  (200,   0, 200, 900);
        txLine  (200, 750, 350, 750);
        model. pistonY_ =       PistonY ();
        double pistonY  = model.Piston  ();
        view.DrawPiston (pistonY);


        txBegin ();

            view.DrawAllBalls   (balls, numBalls);
            view.PrintValues    (model.Density      (numBalls),
                                 model.Pressure     (numBalls),
                                 model.Temperature  (numBalls));

        txEnd ();

        model.MoveAllBalls  (balls, numBalls, pistonY);
        BallControls        (balls, numBalls);

        if (GetAsyncKeyState ('W')) model.AddBall    (balls, numBalls);
        if (GetAsyncKeyState ('S')) model.DeleteBall (numBalls);

        Sleep (5);

        txSetFillColor (RGB (0, 0, 0));
        }

    //txClearConsole ();
    Menu (balls, numBalls);
    }

//-----------------------------------------------------------------------------

double Controller::PistonY      ()
    {
    double y = txMouseY ();
    return y;
    }

//}============================================================================
