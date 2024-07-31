#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "editor.h"
#include "resource.h"

extern bool bGrid;
extern int MAPBARRIER;
extern HWND hwnd;
extern int cx;
extern int cy;
extern int resWidth;
extern int resHeight;
extern int xpos;
extern int ypos;

extern char objectstring[];

extern paddle rpaddles[4];
extern paddle bpaddles[4];
extern ball balls[500];
extern int gameRound;
extern char imgString[100];
extern char musString[100];

extern goal redgoals[3000];
extern goal bluegoals[3000];
extern brick bricks[3000];
extern brick blocks[3000];
extern paddle redpaddle;//eventually add ability to add more paddles
extern paddle bluepaddle;
extern bouncer bouncers[3000];
extern essence redessences[3000];
extern essence blueessences[3000];

TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
OPENFILENAME ofn;

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
        MAPBARRIER = DEFAULT;
        SetScrollRange(hwnd, SB_HORZ, 0, MAPBARRIER, FALSE);
        SetScrollRange(hwnd, SB_VERT, 0, MAPBARRIER, TRUE);
        xpos = 0;
        ypos = 0;
        SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
        SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);

        for (int i = 0; i < 9; i++) {
            balls[i].round = NULL;
        }

        for (int i = 0; i < 4; i++) {
            rpaddles[i].x = 0;
            bpaddles[i].x = 0;

        }

        for (int i = 0; i < 3000; i++) {
            redgoals[i].round = 0;
            bluegoals[i].round = 0;
            bricks[i].round = 0;
            blocks[i].round = 0;
            //paddle redpaddle;//eventually add ability to add more paddles
            //paddle bluepaddle;
            bouncers[i].round = 0;
            redessences[i].round = 0;
            blueessences[i].round = 0;
        }

        redpaddle.x = NULL;
        bluepaddle.x = NULL;

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

void rightclick() {
    extern HINSTANCE hInstanceG;
    extern goal* selectedgoal;
    extern brick* selectedbrick;
    extern paddle* selectedpaddle;
    extern bouncer* selectedbouncer;
    extern essence* selectedessence;
    extern ball* selectedball;

    int clickX = xpos - (resWidth / 2) + cx;
    int clickY = ypos - (resHeight / 2) + cy;
    int i = 0;
    //block clicked
    for (i = 0; i < 3000; i++)
    {
        if (clickX > (blocks[i].x - blocks[i].width) && clickX < blocks[i].x + blocks[i].width) {
            if (clickY > (blocks[i].y - blocks[i].height) && clickY < blocks[i].y + blocks[i].height) {
                if (blocks[i].round == gameRound || blocks[i].round == 4) {

                    selectedbrick = &blocks[i];
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedessence = NULL;
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "Block %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    //brick clicked
    for (i = 0; i < 3000; i++)
    {
        if (clickX > (bricks[i].x - bricks[i].width) && clickX < bricks[i].x + bricks[i].width)
        {
            if (clickY > (bricks[i].y - bricks[i].height) && clickY < bricks[i].y + bricks[i].height)
            {
                if (bricks[i].round == gameRound || bricks[i].round == 4) {
                    selectedbrick = &bricks[i];
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedessence = NULL;
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "Brick %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (clickX > (bpaddles[i].x - bpaddles[i].width) && clickX < bpaddles[i].x + bpaddles[i].width)
        {
            if (clickY > (bpaddles[i].y - bpaddles[i].height) && clickY < bpaddles[i].y + bpaddles[i].height)
            {
                //	  if(bricks[i].round == round || bricks[i].round == 4){
                selectedbrick = NULL;
                selectedgoal = NULL;
                selectedpaddle = NULL;
                selectedbouncer = NULL;
                selectedessence = NULL;
                selectedpaddle = &bpaddles[i];
                selectedball = NULL;
                sprintf(objectstring, "BLUE PADDLE %i", i);
                DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
            }
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (clickX > (rpaddles[i].x - rpaddles[i].width) && clickX < rpaddles[i].x + rpaddles[i].width)
        {
            if (clickY > (rpaddles[i].y - rpaddles[i].height) && clickY < rpaddles[i].y + rpaddles[i].height)
            {
                selectedbrick = NULL;
                selectedgoal = NULL;
                selectedpaddle = NULL;
                selectedbouncer = NULL;
                selectedessence = NULL;
                selectedpaddle = &rpaddles[i];
                selectedball = NULL;
                sprintf(objectstring, "RED PADDLE %i", i);
                DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
            }
        }
    }

    //red essence clicked
    for (i = 0; i < 3000; i++)
    {
        if (clickX > (redessences[i].x - redessences[i].radius) && clickX < redessences[i].x + redessences[i].radius)
        {
            if (clickY > (redessences[i].y - redessences[i].radius) && clickY < redessences[i].y + redessences[i].radius)
            {
                if (redessences[i].round == gameRound || redessences[i].round == 4) {
                    selectedbrick = NULL;
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedessence = &redessences[i];
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "red essence %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < 3000; i++)
    {
        if (clickX > (bouncers[i].x - bouncers[i].radius) && clickX < bouncers[i].x + bouncers[i].radius)
        {
            if (clickY > (bouncers[i].y - bouncers[i].radius) && clickY < bouncers[i].y + bouncers[i].radius)
            {
                if (bouncers[i].round == gameRound || bouncers[i].round == 4)
                {
                    selectedbrick = NULL;
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = &bouncers[i];
                    selectedessence = NULL;
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "bouncer %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }


    for (i = 0; i < 3000; i++)
    {
        if (clickX > (blueessences[i].x - blueessences[i].radius) && clickX < blueessences[i].x + blueessences[i].radius)
        {
            if (clickY > (blueessences[i].y - blueessences[i].radius) && clickY < blueessences[i].y + blueessences[i].radius)
            {
                if (blueessences[i].round == gameRound || blueessences[i].round == 4)
                {
                    selectedbrick = NULL;
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedessence = &blueessences[i];
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "Blue Essence %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < 500; i++)
    {
        if (clickX > (balls[i].x - balls[i].radius) && clickX < balls[i].x + balls[i].radius)
        {
            if (clickY > (balls[i].y - balls[i].radius) && clickY < balls[i].y + balls[i].radius)
            {
                if (balls[i].round == gameRound || balls[i].round == 4) {
                    selectedbrick = NULL;
                    selectedgoal = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedessence = NULL;
                    selectedball = &balls[i];
                    selectedpaddle = NULL;
                    sprintf(objectstring, "BALL %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < 3000; i++)
    {
        if (clickX > (redgoals[i].x - redgoals[i].width) && clickX < redgoals[i].x + redgoals[i].width)
        {
            if (clickY > (redgoals[i].y - redgoals[i].height) && clickY < redgoals[i].y + redgoals[i].height)
            {
                if (redgoals[i].round == gameRound || redgoals[i].round == 4)
                {
                    selectedbrick = NULL;
                    selectedessence = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedgoal = &redgoals[i];
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "Red Goal %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }

    for (i = 0; i < 3000; i++)
    {
        if (clickX > (bluegoals[i].x - bluegoals[i].width) && clickX < bluegoals[i].x + bluegoals[i].width)
        {
            if (clickY > (bluegoals[i].y - bluegoals[i].height) && clickY < bluegoals[i].y + bluegoals[i].height)
            {
                if (bluegoals[i].round == gameRound || bluegoals[i].round == 4) {
                    selectedbrick = NULL;
                    selectedessence = NULL;
                    selectedpaddle = NULL;
                    selectedbouncer = NULL;
                    selectedgoal = &bluegoals[i];
                    selectedpaddle = NULL;
                    selectedball = NULL;
                    sprintf(objectstring, "Blue Goal %i", i);
                    DialogBox(hInstanceG, "object", hwnd, DlgProcObject);
                }
            }
        }
    }
}







void mapoptions() {
    extern HINSTANCE hInstanceG;
    DialogBox(hInstanceG, "IDD_MAP", hwnd, DlgProcOpt);
}


void open() {

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

    if (GetOpenFileName(&ofn)) {
        FILE* fp;
        fp = fopen(szFileName, "rb");
        fread(&MAPBARRIER, sizeof(int), 1, fp);
        fread(&bluepaddle, sizeof(paddle), 1, fp);
        fread(&redpaddle, sizeof(paddle), 1, fp);
        fread(&redgoals, sizeof(goal), 3000, fp);
        fread(&bluegoals, sizeof(goal), 3000, fp);
        fread(&bricks, sizeof(brick), 3000, fp);
        fread(&blocks, sizeof(brick), 3000, fp);
        fread(&bouncers, sizeof(bouncer), 3000, fp);
        fread(&redessences, sizeof(essence), 3000, fp);
        fread(&blueessences, sizeof(essence), 3000, fp);
        fread(&rpaddles, sizeof(paddle), 4, fp);
        fread(&bpaddles, sizeof(paddle), 4, fp);
        fread(&balls, sizeof(ball), 500, fp);
        fread(&imgString, sizeof(char), 100, fp);
        fread(&musString, sizeof(char), 100, fp);
        fclose(fp);
    }


    SetScrollRange(hwnd, SB_HORZ, 0, MAPBARRIER, FALSE);
    SetScrollRange(hwnd, SB_VERT, 0, MAPBARRIER, TRUE);
    xpos = 0;
    ypos = 0;
    SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
    SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);

}



void open2() {

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

    if (GetOpenFileName(&ofn)) {

        //MessageBox(hwnd,szTitleName,szFileName,MB_OK);
        sprintf(imgString, szTitleName);
        //MessageBox(hwnd,imgString,szFileName,MB_OK);


    }
}



void save()
{
    static TCHAR szFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");

    bluepaddle.x = 1000;

    //	if(bluepaddle.x == NULL){needspaddle();return;}
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
        FILE* fp;
        fp = fopen(szFileName, "wb");
        fwrite(&MAPBARRIER, sizeof(int), 1, fp);
        fwrite(&bluepaddle, sizeof(paddle), 1, fp);
        fwrite(&redpaddle, sizeof(paddle), 1, fp);
        fwrite(&redgoals, sizeof(goal), 3000, fp);
        fwrite(&bluegoals, sizeof(goal), 3000, fp);
        fwrite(&bricks, sizeof(brick), 3000, fp);
        fwrite(&blocks, sizeof(brick), 3000, fp);
        fwrite(&bouncers, sizeof(bouncer), 3000, fp);
        fwrite(&redessences, sizeof(essence), 3000, fp);
        fwrite(&blueessences, sizeof(essence), 3000, fp);
        fwrite(&rpaddles, sizeof(paddle), 4, fp);
        fwrite(&bpaddles, sizeof(paddle), 4, fp);
        fwrite(&balls, sizeof(ball), 500, fp);
        fwrite(&imgString, sizeof(char), 100, fp);
        fwrite(&musString, sizeof(char), 100, fp);


        fclose(fp);
    }

}

void saveas()
{
}