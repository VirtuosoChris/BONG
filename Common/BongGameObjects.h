#pragma once

struct goal
{
    int color;
    int width;
    int height;
    int x;
    int round=0;
    int y;
};

struct brick
{
    bool breakable;
    bool broken;
    int x;
    int y;
    int width;
    int round=0;
    int height;
};

struct bouncer
{
    int x;
    int y;
    int radius;
    int round=0;
    int multiplier;
};

struct essence
{
    int x;
    int y;
    int color;
    int radius;
    int round=0;
};

struct paddle
{
    int x = 0;
    int y = 0;
    int color;
    int width;
    int height;
};

struct ball
{
    float x = 0;
    float y = 0;
    float lx;
    float ly;
    float yVec;
    float xVec;
    int belongsTo;
    int mountedColor;
    int round = 0;
    int radius;
    int angle;
    int speed;
};

