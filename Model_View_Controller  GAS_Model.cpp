#include <cmath>
#include "TXLib.h"

double averageV = 0;

#include "MovingBall.h"
#include "Controller.h"


//{=Functions=Declaration======================================================
POINT NewAxis           (Vector NewX, double x, double y);
//}============================================================================

int main ()
    {
    txCreateWindow  (1200, 900);
    txTextCursor    (false);

    int     numBalls_ = 1;
    MovingBall balls_  [10000];

    Controller controll;
    controll.Menu     (balls_, numBalls_);

    txDisableAutoPause  ();
    return 0;
    }

//{=Functions==================================================================
POINT NewAxis (Vector NewX, double x, double y)
    {

    double angle = NewX.angle ();
    double x_ = x*cos(angle) + y*sin(angle);
    double y_ = y*cos(angle) - x*sin(angle);

    return POINT {x_, y_};
    }
//}============================================================================

