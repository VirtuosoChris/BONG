#include <windows.h>
#include "editor.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

#include "resource.h"
extern PIXELFORMATDESCRIPTOR pfd;
extern int gameRound;
extern int resWidth;
extern int resHeight;
extern int ypos;
extern int xpos;
extern int cx;
extern int cy;
extern bool gridshowcoords;
extern bouncer bouncers[3000];
extern int gridoffsetX;
extern int gridoffsetY;
extern int gridwidth;
extern int gridheight;
extern bool gridtoggle;
extern HGLRC hRC;
extern HDC hDC;
extern HGLRC hRCh;
extern HDC hdCh;
extern HWND hwndCh;
extern HWND hwnd;

extern BongMapLegacy mapData;

void glsetup()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xpos - (.5 * resWidth), (xpos + (.5 * resWidth)) - 25, (ypos + (.5 * resHeight)) - 63, (ypos - (.5 * resHeight)));
    glDisable(GL_DITHER);
    glClearColor(0, 0, 0, 0);
    glLineWidth(2);
}

void render()
{
    extern HDC hDC;
    int i;
    char strBuffer[200];

    wglMakeCurrent(hdCh, hRCh);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    gluOrtho2D(0, mapData.mapBarrier, mapData.mapBarrier, 0);

    drawGameObjects();

    glColor3f(1, 0, 0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(xpos, ypos);
    glEnd();
    glPopMatrix();

    SwapBuffers(hdCh);
    wglMakeCurrent(hDC, hRC);

    //wglMakeCurrent(hDC, hRC);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(xpos - (.5 * resWidth), (xpos + (.5 * resWidth)), (ypos + (.5 * resHeight)), (ypos - (.5 * resHeight)));

    drawGameObjects();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int cWidth;
    int cHeight;
    extern int object;
    switch (object) {
    case ID_PADDLE_RED:
    case ID_PADDLE_BLUE:
    case ID_PADDLE_BLUEEXTRA:
    case ID_PADDLE_REDEXTRA:
        cWidth = PADDLEWIDTH;
        cHeight = PADDLEHEIGHT;
        break;
    case ID_OBJECT_BLOCK:
    case ID_OBJECT_BRICK:
        cWidth = BLOCKWIDTH;
        cHeight = BLOCKHEIGHT;
        break;
    case ID_OBJECT_BALL142:
        cWidth = BALLSIZE;
        cHeight = cWidth;
        break;
    case ID_ESSENCE_BLUE:
    case ID_ESSENCE_RED:
        cWidth = ESSENCERADIUS;
        cHeight = ESSENCERADIUS;
        break;
    case ID_OBJECT_BOUNCER:
        cWidth = BOUNCERRADIUS;
        cHeight = cWidth;
        break;
    case ID_GOAL_RED:
    case ID_GOAL_BLUE:
        cWidth = GOALWIDTH;
        cHeight = GOALHEIGHT;
        break;
    }


    //draw grid
    /////////////////////////////////////////////////////////////
    if (gridtoggle == true)
    {
        glColor3f(.3, .3, .3);
        glLineWidth(1);
        glBegin(GL_LINES);
        for (i = (0); i < (mapData.mapBarrier + gridwidth); i = (i + gridwidth)) {
            glVertex2i(i + gridoffsetX, 0);
            glVertex2i(i + gridoffsetX, mapData.mapBarrier);
        }

        for (i = (0); i < (mapData.mapBarrier + gridheight); i = (i + gridheight)) {
            glVertex2i(0, i + gridoffsetY);
            glVertex2i(mapData.mapBarrier, i + gridoffsetY);
        }
        glEnd();
    }
    //////////////////////////////////////////////////
    //mapbarrier outline
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(mapData.mapBarrier, 0);
    glVertex2i(mapData.mapBarrier, 0);
    glVertex2i(mapData.mapBarrier, mapData.mapBarrier);
    glVertex2i(mapData.mapBarrier, mapData.mapBarrier);
    glVertex2i(0, mapData.mapBarrier);
    glVertex2i(0, mapData.mapBarrier);
    glVertex2i(0, 0);
    glEnd();

    //crusorsquare
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0, 1, 0);
    drawObject(xpos - (resWidth / 2) + cx, ypos - (resHeight / 2) + cy, cWidth, cHeight);

    //text
    if (gridshowcoords == true) {

        //if cursor is outside box print coords in red
        if (xpos - (resWidth / 2) + cx <= 0 || xpos - (resWidth / 2) + cx >= mapData.mapBarrier || ypos - (resHeight / 2) + cy <= 0 || ypos - (resHeight / 2) + cy >= mapData.mapBarrier) {
            glColor3f(1, 0, 0);
        }
        else {
            glColor3f(1, 1, 1);
        }



        glRasterPos2i(-370 + xpos, -270 + ypos);
        //glRasterPos2i (xpos,ypos);
        sprintf(strBuffer, "\t  %i,%i\n", xpos - (resWidth / 2) + cx, ypos - (resHeight / 2) + cy);

        ShowText(strBuffer);
    }

    glPopMatrix();


    SwapBuffers(hDC);




}

//

void ShowText(char* string)
{
    extern unsigned int base;
    wglUseFontBitmaps(hDC, 32, 96, base);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);
    glPopAttrib();
}

void drawObject(int x, int y, int width, int height)
{
    glBegin(GL_QUADS);
    glVertex2i(x - width, y - height);
    glVertex2i(x + width, y - height);
    glVertex2i(x + width, y + height);
    glVertex2i(x - width, y + height);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(x, y - height);
    glVertex2i(x, y + height);
    glVertex2i(x - width, y);
    glVertex2i(x + width, y);
    glEnd();
}

void drawGameObjects()
{
    if (redpaddle.x)
    {
        glColor3f(1, 0, 0);
        drawObject(redpaddle.x, redpaddle.y, PADDLEWIDTH, PADDLEHEIGHT);
    }

    if (bluepaddle.x)
    {
        glColor3f(0, 0, 1);
        drawObject(bluepaddle.x, bluepaddle.y, PADDLEWIDTH, PADDLEHEIGHT);
    }

    for (int i = 0; i < mapData.redPaddles.size(); i++)
    {
        glColor3f(1, 0, 0);

        if (mapData.redPaddles[i].x)
        {
            drawObject(mapData.redPaddles[i].x, mapData.redPaddles[i].y, PADDLEWIDTH, PADDLEHEIGHT);
        }
    }


    for (int i = 0; i < mapData.bluePaddles.size(); i++)
    {
        glColor3f(0, 0, 1);

        if (mapData.bluePaddles[i].x)
        {
            drawObject(mapData.bluePaddles[i].x, mapData.bluePaddles[i].y, PADDLEWIDTH, PADDLEHEIGHT);
        }
    }

    for (int i = 0; i < mapData.bricks.size(); i++)
    {
        glColor3f(.5, .5, .5);

        if (mapData.bricks[i].round == gameRound || mapData.bricks[i].round == 4)
        {
            drawObject(mapData.bricks[i].x, mapData.bricks[i].y, mapData.bricks[i].width, mapData.bricks[i].height);
        }
    }

    for (int i = 0; i < mapData.blocks.size(); i++)
    {
        glColor3f(1, 1, 1);

        if (mapData.blocks[i].round)
        {
            if (mapData.blocks[i].round == gameRound || mapData.blocks[i].round == 4)
            {
                drawObject(mapData.blocks[i].x, mapData.blocks[i].y, mapData.blocks[i].width, mapData.blocks[i].height);
            }
        }
    }

    for (int i = 0; i < mapData.blueGoals.size(); i++)
    {
        glColor3f(0, 0, 1);
        if (mapData.blueGoals[i].round)
        {
            if (mapData.blueGoals[i].round == gameRound || mapData.blueGoals[i].round == 4)
            {
                drawObject(mapData.blueGoals[i].x, mapData.blueGoals[i].y, mapData.blueGoals[i].width, mapData.blueGoals[i].height);
            }
        }
    }

    for (int i = 0; i < mapData.redGoals.size(); i++)
    {
        glColor3f(1, 0, 0);
        if (mapData.redGoals[i].round)
        {
            if (mapData.redGoals[i].round == gameRound || mapData.redGoals[i].round == 4)
            {
                drawObject(mapData.redGoals[i].x, mapData.redGoals[i].y, mapData.redGoals[i].width, mapData.redGoals[i].height);
            }
        }
    }

    float ANG = THIRTYDEGREES;

    glColor3f(1, 1, 1);

    for (int i = 0; i < mapData.balls.size(); i++)
    {
        if (mapData.balls[i].round == gameRound || mapData.balls[i].round == 4)
        {
            glPushMatrix();
            glTranslatef(mapData.balls[i].x, mapData.balls[i].y, 0);
            glBegin(GL_POLYGON);

                for (int j = 0; j < 12; j++)
                {
                    glVertex2i(mapData.balls[i].radius * cos(ANG), mapData.balls[i].radius * sin(ANG));
                    ANG = ANG + THIRTYDEGREES;
                }

            glEnd();
            glPopMatrix();
        }
    }

    glColor3f(1, 0, 0);
    for (int i = 0; i < mapData.redEssences.size(); i++)
    {
        if (mapData.redEssences[i].round) {
            if (mapData.redEssences[i].round == gameRound || mapData.redEssences[i].round == 4)
            {
                glPushMatrix();
                glTranslatef(mapData.redEssences[i].x, mapData.redEssences[i].y, 0);
                glBegin(GL_POLYGON);
                for (int j = 0; j < 12; j++) {
                    glVertex2i(mapData.redEssences[i].radius * cos(ANG), mapData.redEssences[i].radius * sin(ANG));
                    ANG = ANG + THIRTYDEGREES;
                }
                glEnd();
                glPopMatrix();
            }
        }
    }

    glColor3f(0, 0, 1);
    for (int i = 0; i < mapData.blueEssences.size(); i++)
    {
        if (mapData.blueEssences[i].round) {
            if (mapData.blueEssences[i].round == gameRound || mapData.blueEssences[i].round == 4)
            {
                glPushMatrix();
                glTranslatef(mapData.blueEssences[i].x, mapData.blueEssences[i].y, 0);
                glBegin(GL_POLYGON);
                for (int j = 0; j < 12; j++) {
                    glVertex2i(mapData.blueEssences[i].radius * cos(ANG), mapData.blueEssences[i].radius * sin(ANG));
                    ANG = ANG + THIRTYDEGREES;
                }
                glEnd();
                glPopMatrix();
            }
        }
    }

    glColor3f(.5, .5, .5);

    for (int i = 0; i < mapData.bouncers.size(); i++)
    {
        if (mapData.bouncers[i].round)
        {
            if (mapData.bouncers[i].round == gameRound || mapData.bouncers[i].round == 4)
            {
                glPushMatrix();
                glTranslatef(mapData.bouncers[i].x, mapData.bouncers[i].y, 0);
                glBegin(GL_POLYGON);

                for (int j = 0; j < 12; j++)
                {
                    glVertex2i(mapData.bouncers[i].radius * cos(ANG), mapData.bouncers[i].radius * sin(ANG));
                    ANG = ANG + THIRTYDEGREES;
                }
                glEnd();
                glPopMatrix();
            }
        }
    }
}