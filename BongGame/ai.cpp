#include <windows.h>
#include "bong.h"

#define FAST 1.5
#define SLOW 1
#define AISPD 8

extern ball MainBall;
extern ball balls[500];
extern double rTime;
extern int gameRound;
extern ball PaddleBallRed;
extern ball rPaddleBall[4];
extern paddle redpaddlelast;
extern paddle rpaddleslast[4];

extern BongMapLegacy mapData;

void followballs()
{
    if(mapData.redPaddle.x)
    {
        redpaddlelast = mapData.redPaddle;

        PaddleBallRed.radius = 1;
        PaddleBallRed.xVec= mapData.redPaddle.x - redpaddlelast.x;
        PaddleBallRed.yVec= mapData.redPaddle.y - redpaddlelast.y;
        mapData.redPaddle = doai(mapData.redPaddle);
    }
}

paddle doai(paddle tPaddle)
{
    float distClose = 0;
    float distQuery = 0;
    float dist = 0;
    float padrate = FAST;

    //by default follow the mainball, follow another if its closer on the y axis
    ball cBall = MainBall;
    distClose = cBall.y;
    if(MainBall.round == 0){distClose = -1;}

    for(int i = 0; i <mapData.balls.size(); i++)
    {
        if(mapData.balls[i].round == gameRound || mapData.balls[i].round == 4)
        {
            if(mapData.balls[i].y > distClose)
            {
                cBall = mapData.balls[i];
                distClose = cBall.y;
            }
        }
    }

    if(cBall.yVec>=0)
    {
        padrate = FAST;
    }
    else
    {
        padrate = SLOW;
    }

    int AIMOVEAMT = -20;
    float aipadmove;

    if(tPaddle.x)
    {
        if(cBall.x > tPaddle.x)
        {
            tPaddle.x += AISPD;
        }

        if(cBall.x < tPaddle.x)
        {
            tPaddle.x -= AISPD;
        }

        if(tPaddle.x <= 0)
        {
            tPaddle.x = 1;
        }
    }

    return tPaddle;
}

