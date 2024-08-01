#include <BongGameObjects.h>
#include <BongMapLegacy.h>
#include "resource.h"

void placeObject(BongMapLegacy& mapData, int object, int xClick, int yClick)
{
    switch (object)
    {
        case ID_PADDLE_RED:
        {
            if (xpos - (resWidth / 2) + xClick > mapData.mapBarrier ||
                xpos - (resWidth / 2) + xClick < 0 ||
                ypos - (resHeight / 2) + yClick > mapData.mapBarrier ||
                ypos - (resHeight / 2) + yClick < 0)
            {
                break;
            }

            redpaddle.color = RED;
            redpaddle.height = PADDLEHEIGHT;
            redpaddle.width = PADDLEWIDTH;
            redpaddle.x = xpos - (resWidth / 2) + xClick;
            redpaddle.y = ypos - (resHeight / 2) + yClick;

            break;
        }
        case ID_PADDLE_BLUE:
        {
            if (xpos - (resWidth / 2) + xClick > mapData.mapBarrier ||
                xpos - (resWidth / 2) + xClick < 0 ||
                ypos - (resHeight / 2) + yClick > mapData.mapBarrier ||
                ypos - (resHeight / 2) + yClick < 0)
            {
                break;
            }
            bluepaddle.color = BLUE;
            bluepaddle.height = PADDLEHEIGHT;
            bluepaddle.width = PADDLEWIDTH;
            bluepaddle.x = xpos - (resWidth / 2) + xClick;
            bluepaddle.y = ypos - (resHeight / 2) + yClick;

            break;
        }
        case ID_OBJECT_BRICK:
        {
            auto& bricks = mapData.bricks;

            for (int i = 0; i < bricks.size(); i++)
            {
                if (bricks[i].round) { continue; }

                bricks[i].breakable = FALSE;
                bricks[i].round = gameRound;
                bricks[i].height = BLOCKHEIGHT;
                bricks[i].width = BLOCKWIDTH;
                bricks[i].x = xpos - (resWidth / 2) + xClick;
                bricks[i].y = ypos - (resHeight / 2) + yClick;

                if (gridplacecenter == true)
                {
                    if (bricks[i].y > 0 && bricks[i].y < mapData.mapBarrier)
                    {
                        if (bricks[i].x < mapData.mapBarrier && bricks[i].x > 0)
                        {
                            bricks[i].x = bricks[i].x - gridoffsetX;
                            bricks[i].y = bricks[i].y - gridoffsetY;
                            bricks[i].x = (bricks[i].x / gridwidth) * gridwidth + (.5 * gridwidth) + gridoffsetX;
                            bricks[i].y = (bricks[i].y / gridheight) * gridheight + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (bricks[i].x > mapData.mapBarrier || bricks[i].x < 0 || bricks[i].y > mapData.mapBarrier || bricks[i].y < 0)
                {
                    bricks[i].round = NULL;
                }

                return 0;
            }

            toomany();
            return 0;
        }
        case ID_OBJECT_BLOCK:
        {
            auto& blocks = mapData.blocks;

            for (int i = 0; i < blocks.size(); i++)
            {
                if (blocks[i].round) { continue; }

                blocks[i].breakable = TRUE;
                blocks[i].height = BLOCKHEIGHT;
                blocks[i].width = BLOCKWIDTH;
                blocks[i].round = gameRound;
                blocks[i].x = xpos - (resWidth / 2) + xClick;
                blocks[i].y = ypos - (resHeight / 2) + yClick;

                if (gridplacecenter == true)
                {
                    if (blocks[i].y > 0 && blocks[i].y < mapData.mapBarrier)
                    {
                        if (blocks[i].x < mapData.mapBarrier && blocks[i].x > 0)
                        {
                            blocks[i].x = (((blocks[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            blocks[i].y = (((blocks[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (blocks[i].x > mapData.mapBarrier || blocks[i].x < 0 || blocks[i].y > mapData.mapBarrier || blocks[i].y < 0)
                {
                    blocks[i].round = NULL;
                }

                return 0;
            }

            toomany();
            return 0;
        }
        case ID_OBJECT_BALL142:
        {
            auto& balls = mapData.balls;

            for (int i = 0; i < balls.size(); i++)
            {
                if (balls[i].round) { continue; }
                balls[i].round = gameRound;
                balls[i].x = xpos - (resWidth / 2) + xClick;
                balls[i].y = ypos - (resHeight / 2) + yClick;
                balls[i].radius = BALLSIZE;

                if (balls[i].x > mapData.mapBarrier || balls[i].x < 0 || balls[i].y > mapData.mapBarrier || balls[i].y < 0)
                {
                    balls[i].round = NULL;
                }

                return 0;
            }
            toomany();
            return 0;
        }
        case ID_ESSENCE_RED:
        {
            auto& redessences = mapData.redEssences;

            for (int i = 0; i < redessences.size(); i++)
            {
                if (redessences[i].round) { continue; }
                redessences[i].radius = ESSENCERADIUS;
                redessences[i].round = gameRound;
                redessences[i].x = xpos - (resWidth / 2) + xClick;
                redessences[i].y = ypos - (resHeight / 2) + yClick;

                if (gridplacecenter == true)
                {
                    if (redessences[i].y > 0 && redessences[i].y < mapData.mapBarrier)
                    {
                        if (redessences[i].x < mapData.mapBarrier && redessences[i].x > 0)
                        {
                            redessences[i].x = (((redessences[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            redessences[i].y = (((redessences[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (redessences[i].x > mapData.mapBarrier || redessences[i].x < 0 || redessences[i].y > mapData.mapBarrier || redessences[i].y < 0)
                {
                    redessences[i].round = NULL;
                }

                return 0;

            }

            toomany();
            return 0;
        }
        case ID_ESSENCE_BLUE:
        {
            auto& blueessences = mapData.blueEssences;

            for (int i = 0; i < blueessences.size(); i++)
            {
                if (blueessences[i].round) { continue; }
                blueessences[i].radius = ESSENCERADIUS;
                blueessences[i].round = gameRound;
                blueessences[i].x = xpos - (resWidth / 2) + xClick;
                blueessences[i].y = ypos - (resHeight / 2) + yClick;
                if (gridplacecenter == true)
                {
                    if (blueessences[i].y > 0 && blueessences[i].y < mapData.mapBarrier)
                    {
                        if (blueessences[i].x < mapData.mapBarrier && blueessences[i].x > 0)
                        {
                            blueessences[i].x = (((blueessences[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            blueessences[i].y = (((blueessences[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (blueessences[i].x > mapData.mapBarrier || blueessences[i].x < 0 || blueessences[i].y > mapData.mapBarrier || blueessences[i].y < 0)
                {
                    blueessences[i].round = NULL;
                }

                return 0;
            }

            toomany();
            return 0;
        }
        case ID_OBJECT_BOUNCER:
        {
            auto& bouncers = mapData.bouncers;
            for (int i = 0; i < bouncers.size(); i++)
            {
                if (bouncers[i].round) { continue; }

                bouncers[i].radius = ESSENCERADIUS;
                bouncers[i].round = gameRound;
                bouncers[i].x = xpos - (resWidth / 2) + xClick;
                bouncers[i].y = ypos - (resHeight / 2) + yClick;
                bouncers[i].multiplier = 1;

                if (gridplacecenter == true)
                {
                    if (bouncers[i].y > 0 && bouncers[i].y < mapData.mapBarrier)
                    {
                        if (bouncers[i].x < mapData.mapBarrier && bouncers[i].x > 0)
                        {
                            bouncers[i].x = (((bouncers[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            bouncers[i].y = (((bouncers[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (bouncers[i].x > mapData.mapBarrier || bouncers[i].x < 0 || bouncers[i].y > mapData.mapBarrier || bouncers[i].y < 0)
                {
                    bouncers[i].round = NULL;
                }

                return 0;
            }
            toomany();
            return 0;
        }
        case ID_GOAL_RED:
        {
            auto& redgoals = mapData.redGoals;

            for (int i = 0; i < redgoals.size(); i++)
            {
                if (redgoals[i].round) { continue; }

                redgoals[i].width = GOALWIDTH;
                redgoals[i].color = RED;
                redgoals[i].height = GOALHEIGHT;
                redgoals[i].round = gameRound;
                redgoals[i].x = xpos - (resWidth / 2) + xClick;
                redgoals[i].y = ypos - (resHeight / 2) + yClick;

                if (gridplacecenter == true)
                {
                    if (redgoals[i].y > 0 && redgoals[i].y < mapData.mapBarrier)
                    {
                        if (redgoals[i].x < mapData.mapBarrier && redgoals[i].x > 0)
                        {
                            redgoals[i].x = (((redgoals[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            redgoals[i].y = (((redgoals[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (redgoals[i].x > mapData.mapBarrier || redgoals[i].x < 0 || redgoals[i].y > mapData.mapBarrier || redgoals[i].y < 0)
                {
                    redgoals[i].round = NULL;
                }

                return 0;
            }

            toomany();
            return 0;
        }
        case ID_GOAL_BLUE:
        {
            auto& bluegoals = mapData.bluegoals;

            for (int i = 0; i < bluegoals.size(); i++)
            {
                if (bluegoals[i].round) { continue; }

                bluegoals[i].width = GOALWIDTH;
                bluegoals[i].color = BLUE;
                bluegoals[i].height = GOALHEIGHT;
                bluegoals[i].round = gameRound;
                bluegoals[i].x = xpos - (resWidth / 2) + xClick;
                bluegoals[i].y = ypos - (resHeight / 2) + yClick;

                if (gridplacecenter == true)
                {
                    if (bluegoals[i].y > 0 && bluegoals[i].y < mapData.mapBarrier)
                    {
                        if (bluegoals[i].x < mapData.mapBarrier && bluegoals[i].x > 0)
                        {
                            bluegoals[i].x = (((bluegoals[i].x - gridoffsetX) / gridwidth) * gridwidth) + (.5 * gridwidth) + gridoffsetX;
                            bluegoals[i].y = (((bluegoals[i].y - gridoffsetY) / gridheight) * gridheight) + (.5 * gridheight) + gridoffsetY;
                        }
                    }
                }

                if (bluegoals[i].x > mapData.mapBarrier || bluegoals[i].x < 0 || bluegoals[i].y > mapData.mapBarrier || bluegoals[i].y < 0) {
                    bluegoals[i].round = NULL;
                }

                return 0;
            }

            toomany();
            return 0;
        }
        default: {assert(0 && "unknown object type"); }
    }
}
