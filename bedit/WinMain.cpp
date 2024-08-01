#include <windows.h>
#include "editor.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "resource.h"
#include <cassert>

char objectstring[100];

HWND hwndCh;
HGLRC hRCh;
HDC hdCh;

bool gridtoggle = true;
bool gridplacecenter = true;
bool gridshowcoords = true;

int gridoffsetX = 0;
int gridoffsetY = 0;
int gridwidth = BLOCKWIDTH * 2;
int gridheight = BLOCKHEIGHT * 2;

PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1, //version
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,
    32,//colormode
    0,0,0,0,0,0,//colorbits
    0,//alpha buffer
    0,//shift bit
    0,//accum buffer
    0,0,0,0,//accum bits
    16,//zbuffer size
    0,//stencil
    0,//aux
    PFD_MAIN_PLANE,//main drawing plane
    0,//reserved
    0,0,0//layer masks
};


//char objectstring* = "12345678901234567890123456789012345678901234567890";
int gameRound = 1; //round being edited/displayed
int object = ID_OBJECT_BRICK;//ID_OBJECT_BRICK; //object selected
bool bGrid = false; //show grid
HGLRC hRC;
HDC hDC;

unsigned int base;
HFONT font;

int resWidth = 1024;
int resHeight = 768;
int xpos = 0;//resWidth/2;
int ypos = 0;//resHeight/2;
int cx = 0;
int cy = 0;

char imgString[100];
char musString[100];

HINSTANCE hInstanceG;

SelectedObjectState selectedObject;

BongMapLegacy mapData;

HWND hwnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i;

    switch (message)
    {
    case WM_CREATE:

        mapData.bluePaddle.x = 500;

        SetScrollRange(hwnd, SB_VERT, 0, mapData.mapBarrier, FALSE);
        SetScrollRange(hwnd, SB_HORZ, 0, mapData.mapBarrier, FALSE);
        SetScrollPos(hwnd, SB_HORZ, xpos, FALSE);
        SetScrollPos(hwnd, SB_VERT, ypos, TRUE);

        hDC = GetDC(hwnd);
        SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);

        glsetup();

        base = glGenLists(96);
        font = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Courier");
        SelectObject(hDC, font);
        wglUseFontBitmaps(hDC, 32, 96, base);

        return 0;

    case WM_MOUSEMOVE:
        cx = (int)LOWORD(lParam);
        cy = (int)HIWORD(lParam);
        render();
        return 0;

    case WM_SIZE:
        resHeight = HIWORD(lParam);
        resWidth = LOWORD(lParam);
        glViewport(0, 0, resWidth, resHeight);
        return 0;

    case WM_LBUTTONDOWN:

        placeObject(mapData, object, LOWORD(lParam), HIWORD(lParam));

        return 0;
    case WM_RBUTTONDOWN:
        rightclick();
        return 0;
        /////////////////////////////////////
        /////////////////////////////////////

    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_THUMBTRACK:

        case SB_THUMBPOSITION:
            ypos = HIWORD(wParam);
            SetScrollPos(hwnd, SB_VERT, HIWORD(wParam), TRUE);
            render();
            return 0;

        case SB_LINEUP:
            if (ypos <= 0) { return 0; }
            ypos = ypos - 10;
            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
            render();
            return 0;

        case SB_PAGEUP:
            if (ypos <= 0) { return 0; }
            ypos = ypos - 50;
            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
            render();
            return 0;
        case SB_LINEDOWN:
            if (ypos >= mapData.mapBarrier) { return 0; }
            ypos = ypos + 10;
            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
            render();
            return 0;
        case SB_PAGEDOWN:
            if (ypos >= mapData.mapBarrier) { return 0; }
            ypos = ypos + 50;
            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
            render();
            return 0;
        }

        return 0;

    case WM_HSCROLL:
        switch (LOWORD(wParam)) {

        case SB_LINELEFT:
            if (xpos <= 0) { return 0; }
            xpos = xpos - 10;
            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
            render();
            return 0;
        case SB_PAGELEFT:
            if (xpos <= 0) { return 0; }
            xpos = xpos - 50;
            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
            render();
            return 0;
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION:
            xpos = HIWORD(wParam);
            SetScrollPos(hwnd, SB_HORZ, HIWORD(wParam), TRUE);
            render();
            return 0;
        case SB_LINERIGHT:
            if (xpos >= mapData.mapBarrier) { return 0; }
            xpos = xpos + 10;
            render();
            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
            return 0;
        case SB_PAGERIGHT:
            if (xpos >= mapData.mapBarrier) { return 0; }
            xpos = xpos + 50;
            render();
            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
            return 0;
        }

        return 0;
    case WM_QUIT:


    case WM_DESTROY:
        quit();
        return 0;

    case WM_COMMAND:
        HMENU hMenu = GetMenu(hwnd);
        {
            switch LOWORD(wParam)
            {
            case ID_HELP_ABOUT: about(); return 0;
            case ID_HELP_MAXIMUMS:help(); return 0;


            case ID_FILE_OPTIONS:  newMap();  return 0;
            case ID_FILE_OPEN103: open();  return 0;
            case ID_FILE_SAVE104: save(); return 0;
            case ID_FILE_SAVEAS: saveas(); return 0;
            case ID_FILE_EXIT: quit(); return 0;

            case ID_ROUND_1:
                gameRound = 1;
                for (int i = 111; i < 114; i++) {
                    CheckMenuItem(hMenu, i, MF_UNCHECKED);
                    CheckMenuItem(hMenu, 141, MF_UNCHECKED);
                }CheckMenuItem(hMenu, wParam, MF_CHECKED); return 0;
            case ID_ROUND_2:
                gameRound = 2;
                for (int i = 111; i < 114; i++) {
                    CheckMenuItem(hMenu, i, MF_UNCHECKED);
                    CheckMenuItem(hMenu, 141, MF_UNCHECKED);
                }CheckMenuItem(hMenu, wParam, MF_CHECKED); return 0;
            case ID_ROUND_3:
                gameRound = 3;
                for (int i = 111; i < 114; i++) {
                    CheckMenuItem(hMenu, i, MF_UNCHECKED);
                    CheckMenuItem(hMenu, 141, MF_UNCHECKED);
                }CheckMenuItem(hMenu, wParam, MF_CHECKED); return 0;
            case ID_ROUND_OMNIPRESENT:
                gameRound = 4;
                for (int i = 111; i < 114; i++) {
                    CheckMenuItem(hMenu, i, MF_UNCHECKED);

                }CheckMenuItem(hMenu, wParam, MF_CHECKED); return 0;

            case ID_OPTIONS_GRID: grid(); return 0;
            case ID_OPTIONS_GOTO: goTo(); return 0;
            case ID_OPTIONS_MAP: mapoptions(); return 0;
            case ID_OPTIONS_MINIMAP:minimap(); return 0;


            case ID_OBJECT_BLUEPADDLE:
            case ID_OBJECT_BALL:
            case ID_OBJECT_BRICK:
            case ID_OBJECT_BLOCK:
            case ID_ESSENCE_RED:
            case ID_ESSENCE_BLUE:
            case ID_OBJECT_BOUNCER:
            case ID_OBJECT_GOAL:
            case ID_GOAL_RED:
            case ID_GOAL_BLUE:
            case ID_PADDLE_RED:
            case ID_PADDLE_BLUE:
            case ID_OBJECT_BALL142:
            case ID_PADDLE_REDEXTRA:
            case ID_PADDLE_BLUEEXTRA:
                for (i = 116; i < 127; i++)
                {
                    CheckMenuItem(hMenu, i, MF_UNCHECKED);
                    CheckMenuItem(hMenu, 137, MF_UNCHECKED);
                    CheckMenuItem(hMenu, 138, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_OBJECT_BALL142, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_PADDLE_REDEXTRA, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_PADDLE_BLUEEXTRA, MF_UNCHECKED);

                }

                CheckMenuItem(hMenu, wParam, MF_CHECKED);
                object = (int)wParam;
            }
        }
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    MSG msg;
    WNDCLASS wndclass1;

    wndclass1.style = CS_HREDRAW | CS_VREDRAW;
    wndclass1.lpfnWndProc = WndProc;
    wndclass1.cbClsExtra = 0;
    wndclass1.cbWndExtra = 0;
    wndclass1.hInstance = hInstance;
    wndclass1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wndclass1.hCursor = LoadCursor(NULL, IDC_ARROW);

    wndclass1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass1.lpszMenuName = "BongEditor";
    wndclass1.lpszClassName = "BongEditor";

    RegisterClass(&wndclass1);

    wndclass1.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass1.hIcon = NULL;
    wndclass1.lpszClassName = "MiniMap";
    wndclass1.lpfnWndProc = MiniMapProc;
    wndclass1.cbWndExtra = 0;
    wndclass1.lpszMenuName = NULL;

    RegisterClass(&wndclass1);
    hInstanceG = hInstance;


    hwnd = CreateWindow("BongEditor", //window class name
        "Bong Editor",//caption
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        0, //x position
        0, //y position
        resWidth, //x size
        resHeight, //y size
        NULL, //parent handle
        NULL, //menu handle
        hInstance, //instance
        NULL); //creation paramaters

    minimap();

    hdCh = GetDC(hwndCh);
    SetPixelFormat(hdCh, ChoosePixelFormat(hdCh, &pfd), &pfd);
    hRCh = wglCreateContext(hdCh);

    hDC = GetDC(hwnd);
    SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
    hRC = wglCreateContext(hDC);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        render();
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void minimap()
{
    //SendMessage(hwndCh, WM_DESTROY, 1, 1);
    DestroyWindow(hwndCh);
    hwndCh = CreateWindow("MiniMap", //window class name
        "MiniMap",//caption
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, //x position
        100, //y position
        200, //x size
        200, //y size
        hwnd, //parent handle
        NULL, //menu handle
        hInstanceG, //instance
        NULL); //creation paramaters

    hdCh = GetDC(hwndCh);
    SetPixelFormat(hdCh, ChoosePixelFormat(hdCh, &pfd), &pfd);
    hRCh = wglCreateContext(hdCh);
}

