#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "editor.h"
#include "resource.h"
#include <cassert>
#include <fstream>

extern bool bGrid;
extern HWND hwnd;
extern int cx;
extern int cy;
extern int resWidth;
extern int resHeight;
extern int xpos;
extern int ypos;

extern char objectstring[];

extern int gameRound;

TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
OPENFILENAME ofn;

extern BongMapLegacy mapData;

void about()
{
    MessageBox(NULL, TEXT("BONG Map Editor\nWritten by Christopher M. Pugh \n(c) 2006\n"), TEXT("About"), MB_ICONINFORMATION);
}

void help()
{
    static char helpstring[10000];
    FILE* help;
    if (help = fopen("help.txt", "r"))
    {
        fread(&helpstring, sizeof(char), 10000, help);
        fclose(help);
    }

    MessageBox(NULL, helpstring, TEXT("Help"), MB_ICONINFORMATION);
}

void newMap()
{
    switch (MessageBox(NULL, TEXT("Save current map?"), TEXT("Save?"), MB_YESNOCANCEL))
    {
    case IDYES:	save();
    case IDNO:

        mapData = BongMapLegacy();

        SetScrollRange(hwnd, SB_HORZ, 0, mapData.mapBarrier, FALSE);
        SetScrollRange(hwnd, SB_VERT, 0, mapData.mapBarrier, TRUE);

        xpos = 0;
        ypos = 0;

        SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
        SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);

        break;
    case IDCANCEL:
        break;
    }

}

void quit()
{
    extern HDC hDC;
    extern HGLRC hRC;
    if (MessageBox(NULL, TEXT("Save current map before quitting?"), TEXT("Save before quitting?"), MB_YESNO) == IDYES) { save(); }
    wglMakeCurrent(hDC, hRC);
    wglDeleteContext(hRC);
    PostQuitMessage(0);
}

void goTo()
{
    extern HINSTANCE hInstanceG;
    DialogBox(hInstanceG, "goto", hwnd, DlgProcGoTo);
}

void grid()
{
    extern HINSTANCE hInstanceG;
    DialogBox(hInstanceG, "grid", hwnd, DlgProc);
}

// brute force check every possible game object :(
void rightclick()
{
    extern HINSTANCE hInstanceG;

    extern SelectedObjectState selectedObject;

    int clickX = xpos - (resWidth / 2) + cx;
    int clickY = ypos - (resHeight / 2) + cy;
    int i = 0;

    for (i = 0; i < mapData.blocks.size(); i++)
    {
        if (clickX > (mapData.blocks[i].x - mapData.blocks[i].width) && clickX < mapData.blocks[i].x + mapData.blocks[i].width)
        {
            if (clickY > (mapData.blocks[i].y - mapData.blocks[i].height) && clickY < mapData.blocks[i].y + mapData.blocks[i].height)
            {
                if (mapData.blocks[i].round == gameRound || mapData.blocks[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.blocks[i]);

                    sprintf(objectstring, "Block %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    //brick clicked
    for (i = 0; i < mapData.bricks.size(); i++)
    {
        if (clickX > (mapData.bricks[i].x - mapData.bricks[i].width) && clickX < mapData.bricks[i].x + mapData.bricks[i].width)
        {
            if (clickY > (mapData.bricks[i].y - mapData.bricks[i].height) && clickY < mapData.bricks[i].y + mapData.bricks[i].height)
            {
                if (mapData.bricks[i].round == gameRound || mapData.bricks[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.bricks[i]);

                    sprintf(objectstring, "Brick %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.bluePaddles.size(); i++)
    {
        if (clickX > (mapData.bluePaddles[i].x - mapData.bluePaddles[i].width) && clickX < mapData.bluePaddles[i].x + mapData.bluePaddles[i].width)
        {
            if (clickY > (mapData.bluePaddles[i].y - mapData.bluePaddles[i].height) && clickY < mapData.bluePaddles[i].y + mapData.bluePaddles[i].height)
            {
                selectedObject = SelectedObjectState(mapData.bluePaddles[i]);

                sprintf(objectstring, "BLUE PADDLE %i", i);
                DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
            }
        }
    }

    for (i = 0; i < mapData.redPaddles.size(); i++)
    {
        if (clickX > (mapData.redPaddles[i].x - mapData.redPaddles[i].width) && clickX < mapData.redPaddles[i].x + mapData.redPaddles[i].width)
        {
            if (clickY > (mapData.redPaddles[i].y - mapData.redPaddles[i].height) && clickY < mapData.redPaddles[i].y + mapData.redPaddles[i].height)
            {
                selectedObject = SelectedObjectState(mapData.redPaddles[i]);

                sprintf(objectstring, "RED PADDLE %i", i);
                DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
            }
        }
    }

    //red essence clicked
    for (i = 0; i < mapData.redEssences.size(); i++)
    {
        if (clickX > (mapData.redEssences[i].x - mapData.redEssences[i].radius) && clickX < mapData.redEssences[i].x + mapData.redEssences[i].radius)
        {
            if (clickY > (mapData.redEssences[i].y - mapData.redEssences[i].radius) && clickY < mapData.redEssences[i].y + mapData.redEssences[i].radius)
            {
                if (mapData.redEssences[i].round == gameRound || mapData.redEssences[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.redEssences[i]);

                    sprintf(objectstring, "red essence %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.blueEssences.size(); i++)
    {
        if (clickX > (mapData.blueEssences[i].x - mapData.blueEssences[i].radius) && clickX < mapData.blueEssences[i].x + mapData.blueEssences[i].radius)
        {
            if (clickY > (mapData.blueEssences[i].y - mapData.blueEssences[i].radius) && clickY < mapData.blueEssences[i].y + mapData.blueEssences[i].radius)
            {
                if (mapData.blueEssences[i].round == gameRound || mapData.blueEssences[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.blueEssences[i]);

                    sprintf(objectstring, "Blue Essence %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.bouncers.size(); i++)
    {
        if (clickX > (mapData.bouncers[i].x - mapData.bouncers[i].radius) && clickX < mapData.bouncers[i].x + mapData.bouncers[i].radius)
        {
            if (clickY > (mapData.bouncers[i].y - mapData.bouncers[i].radius) && clickY < mapData.bouncers[i].y + mapData.bouncers[i].radius)
            {
                if (mapData.bouncers[i].round == gameRound || mapData.bouncers[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.bouncers[i]);

                    sprintf(objectstring, "bouncer %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.balls.size(); i++)
    {
        if (clickX > (mapData.balls[i].x - mapData.balls[i].radius) && clickX < mapData.balls[i].x + mapData.balls[i].radius)
        {
            if (clickY > (mapData.balls[i].y - mapData.balls[i].radius) && clickY < mapData.balls[i].y + mapData.balls[i].radius)
            {
                if (mapData.balls[i].round == gameRound || mapData.balls[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.balls[i]);
                    sprintf(objectstring, "BALL %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.redGoals.size(); i++)
    {
        if (clickX > (mapData.redGoals[i].x - mapData.redGoals[i].width) && clickX < mapData.redGoals[i].x + mapData.redGoals[i].width)
        {
            if (clickY > (mapData.redGoals[i].y - mapData.redGoals[i].height) && clickY < mapData.redGoals[i].y + mapData.redGoals[i].height)
            {
                if (mapData.redGoals[i].round == gameRound || mapData.redGoals[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.redGoals[i]);

                    sprintf(objectstring, "Red Goal %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < mapData.blueGoals.size(); i++)
    {
        if (clickX > (mapData.blueGoals[i].x - mapData.blueGoals[i].width) && clickX < mapData.blueGoals[i].x + bluegoals[i].width)
        {
            if (clickY > (mapData.blueGoals[i].y - mapData.blueGoals[i].height) && clickY < mapData.blueGoals[i].y + mapData.blueGoals[i].height)
            {
                if (mapData.blueGoals[i].round == gameRound || mapData.blueGoals[i].round == 4)
                {
                    selectedObject = SelectedObjectState(mapData.blueGoals[i]);

                    sprintf(objectstring, "Blue Goal %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }
}

void mapoptions()
{
    extern HINSTANCE hInstanceG;
    DialogBox(hInstanceG, "IDD_MAP", hwnd, DlgProcOpt);
}

void open()
{
    static TCHAR szFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = NULL;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = 0;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = ".txt";
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFileName;
    ofn.lpstrFileTitle = szTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    if (GetOpenFileName(&ofn))
    {
        std::ifstream inFile(szFileName, std::ios::in | std::ios::binary);

        if (inFile.is_open())
        {
            mapData = BongMapLegacy(inFile);
        }

        inFile.close();
    }

    SetScrollRange(hwnd, SB_HORZ, 0, mapData.mapBarrier, FALSE);
    SetScrollRange(hwnd, SB_VERT, 0, mapData.mapBarrier, TRUE);
    xpos = 0;
    ypos = 0;
    SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
    SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
}



void open2()
{
    static TCHAR szFilter[] = TEXT("Bitmaps (*.bmp)\0*.bmp\0");

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = NULL;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = 0;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = ".txt";
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFileName;
    ofn.lpstrFileTitle = szTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    if (GetOpenFileName(&ofn))
    {
        sprintf(mapData.imgString, szTitleName);
    }
}



void save()
{
    static TCHAR szFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");

    mapData.bluePaddle.x = 1000;

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = NULL;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = 0;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = ".txt";
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFileName;
    ofn.lpstrFileTitle = szTitleName;
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn))
    {
        std::ofstream outFile(szFileName, std::ios::out | std::ios::binary);

        if (outFile.is_open())
        {
            mapData.writeToStream(outFile);
        }

        outFile.close();
    }
}

void saveas()
{
    assert(0, "NYI");
}