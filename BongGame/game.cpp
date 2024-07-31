#include <windows.h>
#include "bong.h"
#include <time.h>

char MAPNAME[100];
int modifier = 1;
extern paddle bluepaddlelast;
extern int gameRound;
extern int resWidth;
extern int resHeight;
extern paddle bluepaddle;
extern goal redgoals[3000];
extern goal bluegoals[3000];
extern brick bricks[3000];
extern brick blocks[3000];
extern paddle redpaddle;//eventually add ability to add more paddles
extern bouncer bouncers[3000];
extern essence redessences[3000];
extern essence blueessences[3000];
extern ball PaddleBall;
extern ball PaddleBallRed;
extern ball rPaddleBall[4];
extern ball bPaddleBall[4];
extern paddle redpaddlelast;

extern ball balls[500];
extern ball MainBall;
extern int MAPBARRIER;

double rTime = 0;
extern menuButton gameMenuButtons[20];
int tRedPts, tBluePts;
extern bool gamePaused;

extern bool started;

void gameHelp()
{
    extern bool gHelp;
    gHelp = !gHelp;
    CallMenu();
}

void gameOptions() {

}

void mNewGame()
{
    //glsetup();
    extern int redsWon;
    extern int scores[2];
    extern unsigned char* bitmap;
    extern BITMAPINFOHEADER biHead;
    extern BITMAPINFOHEADER biHeadBck;
    extern char imgString[100];

    openfile();

    modifier = 1;

    bitmap = LoadBMP(imgString);
    if (bitmap != NULL) {
        biHeadBck = biHead;
    }

    glsetup();

    if (bluepaddle.x != NULL)
        CallMenu();

    redsWon = 0;
    scores[RED] = 0;
    scores[BLUE] = 0;
    tRedPts = tBluePts = 0;
}

void makeScore(int x, int y, int color, int value)
{
    int i; extern score scorenums[25];

    for (i = 0; i < 25; i++) {
        if (scorenums[i].active == true) { continue; }
        scorenums[i].vtimecreated = GetTickCount64();
        scorenums[i].color = color;
        scorenums[i].active = true;
        scorenums[i].value = value;
        scorenums[i].x = x;
        scorenums[i].y = y;
        return;
    }


}

void makeParticle(int x, int y)
{
    extern particle particles[25];
    int i, j;

    for (i = 0; i < 25; i++)
    {
        if (particles[i].active == true) { continue; }

        for (j = 0; j < 10; j++) {
            particles[i].parts[j][0] = (x - BLOCKWIDTH) + (rand() % (BLOCKWIDTH * 2));
            particles[i].parts[j][1] = (y - BLOCKHEIGHT) + (rand() % (BLOCKHEIGHT * 2));
        }

        particles[i].active = true;
        particles[i].vtimecreated = GetTickCount64();

        return;
    }
}




void CallMenu() {
    static BOOL cursorz = false;
    gamePaused = !gamePaused;
    gameMenuButtons[NEWGAME].visible = !gameMenuButtons[NEWGAME].visible;
    gameMenuButtons[OPTIONS].visible = !gameMenuButtons[OPTIONS].visible;
    gameMenuButtons[QUIT].visible = !gameMenuButtons[QUIT].visible;
    gameMenuButtons[HELP].visible = !gameMenuButtons[HELP].visible;
    gameMenuButtons[HIGHSCORES].visible = !gameMenuButtons[HIGHSCORES].visible;
    cursorz = !cursorz;
    ShowCursor(cursorz);
}




void setupGame()
{
    extern score scorenums[25];
    extern particle particles[25];
    extern int scores[2];
    extern message gMessage;
    extern int lastBroken;
    extern paddle redpaddle; extern paddle bluepaddle;

    bluepaddle.color = BLUE;

    scores[RED] = 0;
    scores[BLUE] = 0;
    started = false;

    if (!bluepaddle.x) { return; }

    bluepaddle.x = MAPBARRIER / 2;
    bluepaddle.y = 0;
    redpaddle.x = MAPBARRIER / 2;
    redpaddle.y = MAPBARRIER;

    bluepaddle.width = PADDLEWIDTH;
    redpaddle.width = PADDLEWIDTH;

    lastBroken = WHITE;

    gMessage.active = true;
    gMessage.y = resHeight / 2;
    gMessage.x = 0;

    switch (gameRound)
    {
        case 1:sprintf(gMessage.msg, "Welcome to BONG"); break;
        case 2:sprintf(gMessage.msg, "Round 2"); break;
        case 3:sprintf(gMessage.msg, "Round 3"); break;
    }

    MainBall.belongsTo = WHITE;
    MainBall.x = bluepaddle.x;
    MainBall.round = 4;

    MainBall.yVec = 1;
    MainBall.y = bluepaddle.y + bluepaddle.height + (BALLSIZE * 2);

    MainBall.xVec = 0;// MINBALLSPEED;

    MainBall.lx = MainBall.x;
    MainBall.ly = MainBall.y;

    //sticks with ball speed between 20 and 30

    MainBall.radius = BALLSIZE;

    for (int i = 0; i < 500; i++)
    {
        float Angle = (balls[i].angle * (3.14159)) / 180;
        balls[i].xVec = balls[i].speed * cos(Angle);
        balls[i].yVec = balls[i].speed * sin(Angle);
        balls[i].belongsTo = WHITE;
        if ((int)balls[i].xVec == 0) { balls[i].xVec = 1; }
    }


    for (int i = 0; i < 25; i++)
    {
        scorenums[i].active = false;
        particles[i].active = false;

    }
}


void UpdateGame()
{
    extern int redsWon;

    extern int scores[2];
    extern particle particles[25];
    extern score scorenums[25];
    extern message gMessage;

    static int winvtime;


    //extern int cursorX, cursorY;	
    SYSTEMTIME st;
    GetSystemTime(&st);
    double vtime = st.wMilliseconds;

    int i, j;
    i = j = 0;

    extern ball PaddleBall;
    extern float moveamount;

    render();

    if (!bluepaddle.x) { return; }

    bluepaddlelast.x = bluepaddle.x;


    PaddleBall.xVec = (moveamount - bluepaddle.x);

    bluepaddle.x = bluepaddle.x + PaddleBall.xVec * rTime;

    if (bluepaddle.x + bluepaddle.width > MAPBARRIER) { bluepaddle.x = MAPBARRIER - bluepaddle.width; }
    if (bluepaddle.x - bluepaddle.width < 0) { bluepaddle.x = 0 + bluepaddle.width; }


    if (started && !gamePaused) {

        for (i = 0; i < 25; i++) {
            if (particles[i].active == false) { continue; }

            for (j = 0; j < 10; j++) {
                //particles[i].parts[j][0] = (x-BLOCKWIDTH)+(rand()%(BLOCKWIDTH*2));
                particles[i].parts[j][1] += (int)15 * rTime;
            }


            if (GetTickCount64() - particles[i].vtimecreated >= 1000) { particles[i].active = false; }

        }


        for (i = 0; i < 25; i++)
        {
            if (GetTickCount64() - scorenums[i].vtimecreated >= 2000) {
                scorenums[i].active = false;
            }

            scorenums[i].y -= 10 * rTime;

        }


        if (MainBall.round == gameRound || MainBall.round == 4) {



            MainBall.speed = sqrt(pow((double)MainBall.xVec, 2) + pow((double)MainBall.yVec, 2));

            if (MainBall.speed > MAXBALLSPEED) {

                //normalize the vector
                MainBall.xVec = MainBall.xVec / MainBall.speed;
                MainBall.yVec = MainBall.yVec / MainBall.speed;
                //
                MainBall.xVec = MainBall.xVec * MAXBALLSPEED;
                MainBall.yVec = MainBall.yVec * MAXBALLSPEED;

            }

            if (MainBall.speed < MINBALLSPEED) {
                MainBall.xVec = MainBall.xVec / MainBall.speed;
                MainBall.yVec = MainBall.yVec / MainBall.speed;
                //
                MainBall.xVec = MainBall.xVec * MINBALLSPEED;
                MainBall.yVec = MainBall.yVec * MINBALLSPEED;
            }





            MainBall.lx = MainBall.x;
            MainBall.ly = MainBall.y;
            MainBall.x = MainBall.x + (MainBall.xVec * rTime);
            MainBall.y = MainBall.y + (MainBall.yVec * rTime);



            if (MainBall.x < 0) {
                MainBall.x = 0; MainBall.xVec = -MainBall.xVec;
                //PlaySound("boing.wav",NULL,0x0001);
            }
            if (MainBall.x > MAPBARRIER) {
                MainBall.x = MAPBARRIER; MainBall.xVec = -MainBall.xVec;
                //PlaySound("boing.wav",NULL,0x0001);
            }



            if (MainBall.y < 0) {
                MainBall.y = 0;
                if (MainBall.belongsTo == WHITE) {
                    MainBall.yVec = -MainBall.yVec;
                    //PlaySound("boing.wav",NULL,0x0001);
                }
                else {
                    MainBall.round = 0;
                    scores[RED] += 50;
                    PlaySound("boom.wav", NULL, 0x0001);
                    makeScore(MainBall.x, MainBall.y + 50, RED, 50);
                    makeParticle(MainBall.x, MainBall.y);
                    if (MainBall.belongsTo == BLUE) {
                        sprintf(gMessage.msg, "Self Pwnt!");
                        gMessage.x = 0;
                        gMessage.active = true;
                    }

                }
            }
            else {
                if (MainBall.y > MAPBARRIER) {
                    MainBall.y = MAPBARRIER;
                    if (MainBall.belongsTo == WHITE) {
                        MainBall.yVec = -MainBall.yVec;
                        //PlaySound("boing.wav",NULL,0x0001);
                    }
                    else {
                        MainBall.round = 0;
                        scores[BLUE] += 50;
                        PlaySound("boom.wav", NULL, 0x0001);
                        makeParticle(MainBall.x, MainBall.y - 25);
                        makeScore(MainBall.x, MainBall.y, BLUE, 50);
                    }
                }
            }



            if ((int)MainBall.xVec == 0) { MainBall.xVec = 1; }



            MainBall = doCollision(MainBall);//}

        }


        for (i = 0; i < 500; i++)
        {
            if (balls[i].round == 4 || balls[i].round == gameRound)
            {

                if ((int)balls[i].xVec == 0) { balls[i].xVec = 1; }


                if (balls[i].yVec > 0 && balls[i].yVec < MINUPV) { balls[i].yVec = MINUPV; }
                if (balls[i].yVec < 0 && balls[i].yVec > -MINUPV) { balls[i].yVec = -MINUPV; }

                balls[i].speed = sqrt(pow((double)balls[i].xVec, 2) + pow((double)balls[i].yVec, 2));

                if (balls[i].speed > MAXBALLSPEED) {
                    //normalize the vector
                    balls[i].xVec = balls[i].xVec / balls[i].speed;
                    balls[i].yVec = balls[i].yVec / balls[i].speed;
                    //
                    balls[i].xVec = balls[i].xVec * MAXBALLSPEED;
                    balls[i].yVec = balls[i].yVec * MAXBALLSPEED;
                }



                //prevent ridiculously steep angles that slow the fuck outta the gameplay
                if (MainBall.yVec > 0 && MainBall.yVec < MINUPV) { MainBall.yVec = MINUPV; }
                if (MainBall.yVec < 0 && MainBall.yVec > -MINUPV) { MainBall.yVec = -MINUPV; }


                if (balls[i].speed < MINBALLSPEED) {
                    balls[i].xVec = balls[i].xVec / balls[i].speed;
                    balls[i].yVec = balls[i].yVec / balls[i].speed;
                    //
                    balls[i].xVec = balls[i].xVec * MINBALLSPEED;
                    balls[i].yVec = balls[i].yVec * MINBALLSPEED;
                }




                balls[i].lx = balls[i].x;
                balls[i].ly = balls[i].y;
                balls[i].x = balls[i].x + (balls[i].xVec * rTime);
                balls[i].y = balls[i].y + (balls[i].yVec * rTime);
                //if(0<=balls[i].xVec<1){balls[i].xVec = 1;}
                if ((int)balls[i].xVec == 0) { balls[i].xVec = 1; }
                //if(balls[i].xVec == 0){balls[i].xVec = 10;}
                //balls[i].xVec = -.1;





                if (balls[i].x < 0) {
                    balls[i].x = 0; balls[i].xVec = -balls[i].xVec;
                    //PlaySound("boing.wav",NULL,0x0001);
                }
                if (balls[i].x > MAPBARRIER) {
                    balls[i].x = MAPBARRIER; balls[i].xVec = -balls[i].xVec;
                    //PlaySound("boing.wav",NULL,0x0001);
                                //collision = true;
                }


                //if(balls[i].y >= MAPBARRIER || balls[i].y <= 0){balls[i].yVec = -balls[i].yVec;
                //collision = true;
                //}


                //////////////////////////////////////////////
                if (balls[i].y > MAPBARRIER) {
                    balls[i].y = MAPBARRIER;
                    balls[i].yVec = -balls[i].yVec;
                    ////////////////////
                    if (balls[i].belongsTo == WHITE) {
                        //PlaySound("boing.wav",NULL,0x0001);
                    }
                    else {
                        balls[i].round = 0;
                        scores[BLUE] += 50;
                        PlaySound("boom.wav", NULL, 0x0001);
                        makeParticle(balls[i].x, balls[i].y - 25);
                        makeScore(balls[i].x, balls[i].y, BLUE, 50);
                    }
                }
                /////////////////////////////////////////////////////////




                if (balls[i].y < 0) {
                    balls[i].y = 0;
                    if (balls[i].belongsTo == WHITE) {
                        balls[i].yVec = -balls[i].yVec;
                        //PlaySound("boing.wav",NULL,0x0001);
                    }
                    else {
                        balls[i].round = 0;
                        PlaySound("boom.wav", NULL, 0x0001);
                        scores[RED] += 50;
                        makeParticle(balls[i].x, balls[i].y);
                        makeScore(balls[i].x, balls[i].y + 50, RED, 50);
                    }
                }






                balls[i] = doCollision(balls[i]);
            }
        }

        followballs();
    }


    if (gMessage.active && !gamePaused) {
        gMessage.x += 30 * rTime;
        if (gMessage.x > resWidth) { gMessage.active = false; }
    }



    extern int lastBroken;

    if (lastBroken != WHITE) {

        int blocksleft = 0;

        for (i = 0; i < 3000; i++) {
            if (blocks[i].round == 4 || blocks[i].round == gameRound)
            {
                if (blocks[i].broken == false) {
                    blocksleft = blocksleft + 1;
                }
            }
        }


        if (blocksleft == 0 && gameRound <= 3) {
            //if(round < 3){
            char tmpstring[10];

            gMessage.active = true;
            gMessage.x = 0;
            scores[lastBroken] += 100;

            switch (lastBroken) {
            case RED: sprintf(tmpstring, "Red"); break;
            case BLUE:sprintf(tmpstring, "Blue"); break;
            }

            sprintf(gMessage.msg, "%s Cleared the Map!", tmpstring);
            lastBroken = WHITE;

            //readFile();
            //setupGame();

            //round ++;
        //started = false;
        //}
        }


    }

    int ballsleft = 0;
    int coloredballsleft = 0;
    static bool moveon = false;


    if (MainBall.round == gameRound || MainBall.round == 4) {
        ballsleft++;

        if (MainBall.belongsTo != WHITE) { coloredballsleft++; }

    }

    for (i = 0; i < 500; i++) {
        if (balls[i].round == gameRound || balls[i].round == 4) {
            ballsleft++;
            if (balls[i].belongsTo != WHITE) { coloredballsleft++; }

        }
    }





    if (ballsleft == 0) {
        //	if(round < 3){

        if (moveon == false) {

            if (gameRound == 3) {//round =4;
                modifier = 0;
                if (scores[RED] > scores[BLUE]) { redsWon++; }
            }

            moveon = true;
            winvtime = time(0);


            tRedPts += scores[RED];
            tBluePts += scores[BLUE];




            gMessage.active = true;

            if (gameRound < 3) {

                if (scores[RED] > scores[BLUE]) {
                    sprintf(gMessage.msg, "Round Over! You lose!");
                }
                else { sprintf(gMessage.msg, "Round Over! You Win!"); }
            }
            else {
                if (tRedPts > tBluePts) {
                    sprintf(gMessage.msg, "Red Wins the Map with %d Points!", tRedPts);
                }
                else { sprintf(gMessage.msg, "Blue Wins the Map with %d Points!", tBluePts); }

            }


            gMessage.x = 0;


        }



        if (time(0) - winvtime >= 5) {
            //
            if (gameRound < 3)
            {
                if (scores[RED] > scores[BLUE]) { redsWon++; }

                moveon = false;
                gameRound++;

                readFile(MAPNAME);

                setupGame();


                started = false;
            }

            else {
                //bitmap = LoadBmp("TitleScreen.bmp");
                //glSetup();
                bluepaddle.x = NULL;
                gameRound = 0;
                CallMenu();
            }




        }
        //}
    }




    if (coloredballsleft == 0 && ballsleft != 0 && MainBall.round == 0) {
        MainBall.round = gameRound;
        MainBall.x = bluepaddle.x;
        MainBall.y = bluepaddle.y + bluepaddle.height + MainBall.radius;


        MainBall.yVec = 1;
        MainBall.xVec = 0;

        MainBall.belongsTo = WHITE;

        MainBall.lx = MainBall.x;
        MainBall.ly = MainBall.y;

        gMessage.active = true;
        gMessage.x = 0;
        sprintf(gMessage.msg, "Mercy Ball!");
    }


    if (!started) { MainBall.x = bluepaddle.x; }

    GetSystemTime(&st);

    if (st.wMilliseconds < vtime) {
        vtime = (1000 - vtime) + st.wMilliseconds;
    }
    else {
        vtime = st.wMilliseconds - vtime;

    }

    vtime = vtime / 100;
    rTime = (float)vtime;

}
