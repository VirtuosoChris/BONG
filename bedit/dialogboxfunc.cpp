#include <windows.h>
#include "editor.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "resource.h"

extern HWND hwnd;
extern bool gridtoggle;
extern int gridwidth;
extern int gridheight;
extern bool gridshowcoords;
extern bool gridplacecenter;
extern int gridoffsetX;
extern int gridoffsetY;
extern int xpos;
extern int ypos;
extern HWND hwndCh;
extern HGLRC hRCh;
extern HGLRC hRC;
extern HDC hDC;
extern int resWidth;
extern int resHeight;
extern HDC hdCh;

extern char objectstring[];

extern BongMapLegacy mapData;
extern SelectedObjectState selectedObject;

// object properties dialog
INT_PTR  CALLBACK DlgProcObject(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL transsuc = FALSE;

    switch (message)
    {
        case WM_INITDIALOG:
        {
            SetDlgItemText(hDlg, IDC_EDIT9, objectstring);

            if (selectedObject.selectedbrick)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedObject.selectedbrick->x, TRUE); //x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedObject.selectedbrick->y, TRUE); //y
                SetDlgItemInt(hDlg, IDC_EDIT3, selectedObject.selectedbrick->width, TRUE); //width
                SetDlgItemInt(hDlg, IDC_EDIT4, selectedObject.selectedbrick->height, TRUE); //height
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedObject.selectedbrick->round, TRUE); //round #
            }

            if (selectedObject.selectedball)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedObject.selectedball->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedObject.selectedball->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT10, selectedObject.selectedball->speed, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT11, selectedObject.selectedball->angle, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedObject.selectedball->round, TRUE);//round #
                SetDlgItemInt(hDlg, IDC_EDIT8, selectedObject.selectedball->radius, TRUE);//round #
            }

            if (selectedObject.selectedbouncer)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedObject.selectedbouncer->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedObject.selectedbouncer->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedObject.selectedbouncer->round, TRUE);//round #
                SetDlgItemInt(hDlg, IDC_EDIT6, selectedObject.selectedbouncer->multiplier, TRUE);//reflection vector
                SetDlgItemInt(hDlg, IDC_EDIT8, selectedObject.selectedbouncer->radius, TRUE);//radius
            }

            if (selectedObject.selectedessence)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedObject.selectedessence->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedObject.selectedessence->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedObject.selectedessence->round, TRUE);//round #
                SetDlgItemInt(hDlg, IDC_EDIT8, selectedObject.selectedessence->radius, TRUE);//radius
            }

            if (selectedObject.selectedgoal)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedObject.selectedgoal->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedObject.selectedgoal->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT3, selectedObject.selectedgoal->width, TRUE);//width
                SetDlgItemInt(hDlg, IDC_EDIT4, selectedObject.selectedgoal->height, TRUE);//height
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedObject.selectedgoal->round, TRUE);//round #
            }

            return TRUE;
        }
        case WM_MOVE:
        {
            render();
            return TRUE;
        }
        case WM_COMMAND:
        {
            switch (wParam)
            {
                case IDC_BUTTON1://default

                    if (selectedObject.selectedball) {
                        SetDlgItemInt(hDlg, IDC_EDIT8, BALLSIZE, TRUE);//round #
                    }

                    if (selectedObject.selectedbrick) {
                        SetDlgItemInt(hDlg, IDC_EDIT3, BLOCKWIDTH, TRUE);//width
                        SetDlgItemInt(hDlg, IDC_EDIT4, BLOCKHEIGHT, TRUE);//height}
                    }

                    if (selectedObject.selectedgoal) {
                        SetDlgItemInt(hDlg, IDC_EDIT3, GOALWIDTH, TRUE);
                        SetDlgItemInt(hDlg, IDC_EDIT4, GOALHEIGHT, TRUE);//height}
                    }

                    if (selectedObject.selectedbouncer) {
                        SetDlgItemInt(hDlg, IDC_EDIT8, BOUNCERRADIUS, TRUE);
                        SetDlgItemInt(hDlg, IDC_EDIT6, BOUNCEVECTOR, TRUE);
                    }

                    if (selectedObject.selectedessence) {
                        SetDlgItemInt(hDlg, IDC_EDIT8, BOUNCERRADIUS, TRUE);
                        SetDlgItemInt(hDlg, IDC_EDIT6, BOUNCEVECTOR, TRUE);
                    }

                    break;
                case IDC_BUTTON3: //delete
                    if (selectedObject.selectedbrick)
                    {
                        selectedObject.selectedbrick->round = NULL;
                        selectedObject.selectedbrick = NULL;
                    }
                    if (selectedObject.selectedbouncer)
                    {
                        selectedObject.selectedbouncer->round = NULL;
                        selectedObject.selectedbouncer = NULL;
                    }
                    if (selectedObject.selectedessence)
                    {
                        selectedObject.selectedessence->round = NULL;
                        selectedObject.selectedessence = NULL;
                    }
                    if (selectedObject.selectedgoal)
                    {
                        selectedObject.selectedgoal->round = NULL;
                        selectedObject.selectedgoal = NULL;
                    }
                    EndDialog(hDlg, 0);
                    if (selectedObject.selectedball) {
                        selectedObject.selectedball->round = 0;
                        selectedObject.selectedball = 0;
                    }
                    if (selectedObject.selectedpaddle) {
                        selectedObject.selectedpaddle->x = NULL;
                        selectedObject.selectedpaddle = NULL;
                    }
                    break;
                case IDOK:
                    if (selectedObject.selectedbrick)
                    {
                        selectedObject.selectedbrick->x = GetDlgItemInt(hDlg, IDC_EDIT1, &transsuc, TRUE);
                        selectedObject.selectedbrick->y = GetDlgItemInt(hDlg, IDC_EDIT2, &transsuc, TRUE);
                        selectedObject.selectedbrick->width = GetDlgItemInt(hDlg, IDC_EDIT3, &transsuc, TRUE);
                        selectedObject.selectedbrick->height = GetDlgItemInt(hDlg, IDC_EDIT4, &transsuc, TRUE);
                        selectedObject.selectedbrick->round = GetDlgItemInt(hDlg, IDC_EDIT5, &transsuc, TRUE);
                        if (selectedObject.selectedbrick->round < 1 || selectedbrick->round > 4) { selectedbrick->round = 1; }
                        if (selectedObject.selectedbrick->width < 1) { selectedbrick->width = 1; }
                        if (selectedObject.selectedbrick->height < 1) { selectedbrick->height = 1; }
                        selectedObject.selectedbrick = NULL;
                    }

                    if (selectedObject.selectedball)
                    {
                        selectedObject.selectedball->x = GetDlgItemInt(hDlg, IDC_EDIT1, &transsuc, TRUE);
                        selectedObject.selectedball->y = GetDlgItemInt(hDlg, IDC_EDIT2, &transsuc, TRUE);
                        selectedObject.selectedball->round = GetDlgItemInt(hDlg, IDC_EDIT5, &transsuc, TRUE);
                        selectedObject.selectedball->speed = GetDlgItemInt(hDlg, IDC_EDIT10, &transsuc, TRUE);
                        selectedObject.selectedball->angle = GetDlgItemInt(hDlg, IDC_EDIT11, &transsuc, TRUE);
                        selectedObject.selectedball->radius = GetDlgItemInt(hDlg, IDC_EDIT8, &transsuc, TRUE);

                        if (selectedObject.selectedball->round < 1 || selectedObject.selectedball->round > 4) { selectedObject.selectedball->round = 1; }
                        if (selectedObject.selectedball->radius < 1) { selectedObject.selectedball->radius = 2; }
                    }

                    if (selectedObject.selectedessence)
                    {
                        //selectedessence->color = iColor;
                        selectedObject.selectedessence->radius = GetDlgItemInt(hDlg, IDC_EDIT8, &transsuc, TRUE);
                        selectedObject.selectedessence->round = GetDlgItemInt(hDlg, IDC_EDIT5, &transsuc, TRUE);
                        selectedObject.selectedessence->x = GetDlgItemInt(hDlg, IDC_EDIT1, &transsuc, TRUE);
                        selectedObject.selectedessence->y = GetDlgItemInt(hDlg, IDC_EDIT2, &transsuc, TRUE);

                        if (selectedObject.selectedessence->radius < 1) { selectedObject.selectedessence->radius = 1; }
                        if (selectedObject.selectedessence->round < 1 || selectedObject.selectedessence->round > 4) { selectedObject.selectedessence->round = 1; }

                        selectedObject.selectedessence = NULL;
                    }

                    if (selectedObject.selectedgoal)
                    {
                        selectedObject.selectedgoal->x = GetDlgItemInt(hDlg, IDC_EDIT1, &transsuc, TRUE);
                        selectedObject.selectedgoal->y = GetDlgItemInt(hDlg, IDC_EDIT2, &transsuc, TRUE);
                        //selectedgoal->color=iColor;
                        selectedObject.selectedgoal->height = GetDlgItemInt(hDlg, IDC_EDIT4, &transsuc, TRUE);
                        selectedObject.selectedgoal->round = GetDlgItemInt(hDlg, IDC_EDIT5, &transsuc, TRUE);
                        selectedObject.selectedgoal->width = GetDlgItemInt(hDlg, IDC_EDIT3, &transsuc, TRUE);
                        if (selectedObject.selectedgoal->round < 1 || selectedObject.selectedgoal->round > 4) { selectedObject.selectedgoal->round = 1; }
                        if (selectedObject.selectedgoal->width < 1) { selectedObject.selectedgoal->width = 1; }
                        if (selectedObject.selectedgoal->height < 1) { selectedObject.selectedgoal->height = 1; }
                        selectedObject.selectedgoal = NULL;

                    }

                    if (selectedObject.selectedbouncer)
                    {
                        selectedObject.selectedbouncer->multiplier = GetDlgItemInt(hDlg, IDC_EDIT6, &transsuc, TRUE);
                        selectedObject.selectedbouncer->radius = GetDlgItemInt(hDlg, IDC_EDIT8, &transsuc, TRUE);
                        selectedObject.selectedbouncer->round = GetDlgItemInt(hDlg, IDC_EDIT5, &transsuc, TRUE);
                        selectedObject.selectedbouncer->x = GetDlgItemInt(hDlg, IDC_EDIT1, &transsuc, TRUE);
                        selectedObject.selectedbouncer->y = GetDlgItemInt(hDlg, IDC_EDIT2, &transsuc, TRUE);
                        if (selectedObject.selectedbouncer->round < 1 || selectedObject.selectedbouncer->round > 4) { selectedObject.selectedbouncer->round = 1; }
                        if (selectedObject.selectedbouncer->radius < 1) { selectedObject.selectedbouncer->radius = 1; }

                        selectedObject.selectedbouncer = NULL;
                    }


                    EndDialog(hDlg, 0);
                    break;

                case IDCANCEL:EndDialog(hDlg, 0);
                    break;
                default: break;
            }
        }
        default: break;
}


return FALSE;
}


// map options dialog
INT_PTR  CALLBACK DlgProcOpt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL transsuc = FALSE;

    OPENFILENAME lofn;
    TCHAR lszFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");
    TCHAR lszFileName[MAX_PATH], lszTitleName[MAX_PATH];

    switch(message)
    {
        case WM_INITDIALOG: 
                SetDlgItemInt(hDlg, IDC_EDIT1,mapData.mapBarrier, TRUE);
                return TRUE;
        case WM_MOVE:
            render(); 
            return TRUE;
        case WM_COMMAND:
            switch(wParam)
            {
                /////////////////////////////////////////////////////
                ////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////
                case IDC_BUTTON1:
                    open2();
                    
                    break;
                ////////////////////////////////////////////////////
                ///////////////////////////////////////////////////
                ///////////////////////////////////////////////////

                case IDOK:  mapData.mapBarrier = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                            if(xpos > mapData.mapBarrier){xpos = mapData.mapBarrier;roundcoordinate();}
                            if(xpos < 0){xpos = 0;roundcoordinate();}
                            if(ypos > mapData.mapBarrier){ypos = mapData.mapBarrier;roundcoordinate();}
                            if(ypos < 0){ypos = 0;roundcoordinate();}
                            SetScrollRange(hwnd,SB_HORZ,0, mapData.mapBarrier,FALSE);
                            SetScrollRange(hwnd,SB_VERT,0, mapData.mapBarrier,TRUE);
                            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
                            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
                            EndDialog(hDlg, 0);
                            break;
                            
                case IDCANCEL:EndDialog(hDlg, 0);
                                break;
                default: break;
            }
        default: break;
}

return FALSE;
}


// unneeded so left un hooked up.  goes to map position.  really shouldn't need this.
INT_PTR CALLBACK DlgProcGoTo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL transsuc = FALSE;

    switch(message)
    {
        case WM_INITDIALOG: 
                SetDlgItemInt(hDlg, IDC_EDIT1,xpos,TRUE);
                SetDlgItemInt(hDlg, IDC_EDIT2,ypos,TRUE);
                return TRUE;
        case WM_MOVE:
            render(); 
            return TRUE;
        case WM_COMMAND:
            switch(wParam)
            {
                case IDOK:  xpos = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                            ypos = GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                            if(xpos >mapData.mapBarrier)
                            {
                                xpos = mapData.mapBarrier;
                                roundcoordinate();
                            }
                            if(xpos < 0)
                            {
                                xpos = 0;
                                roundcoordinate();
                            }
                            if(ypos > mapData.mapBarrier)
                            {
                                ypos = mapData.mapBarrier;
                                roundcoordinate();
                            }
                            if(ypos < 0)
                            {
                                ypos = 0;roundcoordinate();
                            }

                            SetScrollPos(hwnd, SB_VERT, ypos, TRUE);
                            SetScrollPos(hwnd, SB_HORZ, xpos, TRUE);
                            EndDialog(hDlg, 0);
                            break;
                            
                case IDCANCEL:EndDialog(hDlg, 0);
                                break;
                default: break;
            }
        default: break;
    }

    return FALSE;
}



INT_PTR  CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    static bool bGridToggle = gridtoggle;
    static int	iGridWidth = gridwidth;
    static int	iGridHeight = gridheight;
    static bool bGridShowCoords = gridshowcoords;
    static bool bGridPlaceCenter = gridplacecenter;
    
    BOOL transsuc = FALSE;
    
    switch(message)
    {
        case WM_INITDIALOG:
            SetDlgItemInt(hDlg, IDC_EDIT4,gridwidth,TRUE);//width
            SetDlgItemInt(hDlg, IDC_EDIT1,gridheight,TRUE);//height
            SetDlgItemInt(hDlg, IDC_EDIT2,gridoffsetX,TRUE);//x
            SetDlgItemInt(hDlg, IDC_EDIT3,gridoffsetY,TRUE);//y
            
            if(gridtoggle == true)
            {
                CheckDlgButton(hDlg, IDC_CHECK4, 1);
            }

            if(gridshowcoords == true)
            {
                CheckDlgButton(hDlg, IDC_CHECK3, 1);
            }

            if(gridplacecenter == true)
            {
                CheckDlgButton(hDlg, IDC_CHECK5, 1);
            }

            return TRUE;

        case WM_MOVE:
            render(); 
            return TRUE;
        case WM_COMMAND:
            switch(wParam){
                case IDC_CHECK3:
                    bGridShowCoords= !bGridShowCoords;
                        break;
                case IDC_CHECK4: 
        
                    //CheckDlgButton(hDlg, IDC_CHECK4, !IsDlgButtonChecked(hDlg, IDC_CHECK4));
                    bGridToggle = !bGridToggle;	
                    break;
                case IDC_CHECK5:
                    bGridPlaceCenter = !bGridPlaceCenter;
                    break;
                    //return FALSE;
                case IDC_BUTTON1://brick
                    iGridWidth = BLOCKWIDTH*2;
                    iGridHeight = BLOCKHEIGHT*2;
                    SetDlgItemInt(hDlg, IDC_EDIT4,iGridWidth,TRUE);//width
                    SetDlgItemInt(hDlg, IDC_EDIT1,iGridHeight,TRUE);//height
                    break;
                case IDC_BUTTON2://essence
                    iGridWidth = ESSENCERADIUS*2;
                    iGridHeight = ESSENCERADIUS*2;
                    SetDlgItemInt(hDlg, IDC_EDIT4,iGridWidth,TRUE);//width
                    SetDlgItemInt(hDlg, IDC_EDIT1,iGridHeight,TRUE);//height
                    break;
            
                case IDC_BUTTON4://goal
                    iGridWidth = GOALWIDTH*2;
                    iGridHeight = GOALHEIGHT*2;
                    SetDlgItemInt(hDlg, IDC_EDIT4,iGridWidth,TRUE);//width
                    SetDlgItemInt(hDlg, IDC_EDIT1,iGridHeight,TRUE);//height
                    
                    
                            break;
                case IDOK:  gridtoggle = bGridToggle;
                            gridheight = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);//iGridWidth;
                            gridwidth  = GetDlgItemInt(hDlg, IDC_EDIT4,&transsuc,TRUE);//iGridHeight;
                            
                            gridoffsetX = GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);//x
                            gridoffsetY = GetDlgItemInt(hDlg, IDC_EDIT3,&transsuc,TRUE);//y
                            gridshowcoords = bGridShowCoords;
                            gridplacecenter = bGridPlaceCenter;
                            EndDialog(hDlg, 0);
                            break;
                            

                case IDCANCEL:
                            //gridtoggle = bGridToggle;
                            EndDialog(hDlg, 0);
                            break;

                default: //gridtoggle = bGridToggle;
                            //EndDialog(hDlg, 0);
                            break;
            
                
            return TRUE;
            }
    
    return FALSE;

    }
    return FALSE;
}






LRESULT CALLBACK MiniMapProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    //int i;
        
    

    switch(message)
    {
        case WM_CREATE:
            extern PIXELFORMATDESCRIPTOR pfd;
            return 0;
        case WM_QUIT: 
            return 0;

        case WM_MOVE: render();
            return 0;
        
        //////////////////////////////////////
        /////////////////////////////////////
    
        case WM_MOUSEMOVE:
                return 0;
            
        case WM_LBUTTONDOWN://glsetup();
                return 0;
        /////////////////////////////////////
        /////////////////////////////////////
        
        case WM_DESTROY:
                wglMakeCurrent(hdCh, hRCh);
                wglDeleteContext(hRCh);
            return 0;
        default:
            break;
                        
    }
    
    return DefWindowProc(hwnd, message, wParam, lParam);
}

