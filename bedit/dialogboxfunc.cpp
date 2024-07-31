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
extern int MAPBARRIER;
extern HWND hwndCh;
extern HGLRC hRCh;
extern HGLRC hRC;
extern HDC hDC;
extern int resWidth;
extern int resHeight;
extern HDC hdCh;

extern char objectstring[];

extern goal      *selectedgoal;
extern brick     *selectedbrick;
extern paddle    *selectedpaddle;
extern bouncer   *selectedbouncer;
extern essence   *selectedessence;
extern ball *selectedball;


INT_PTR  CALLBACK DlgProcObject(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL transsuc = FALSE;

    switch(message)
    {
        case WM_INITDIALOG:
            SetDlgItemText(hDlg,IDC_EDIT9, objectstring);
            
            if(selectedbrick)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedbrick->x, TRUE); //x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedbrick->y, TRUE); //y
                SetDlgItemInt(hDlg, IDC_EDIT3, selectedbrick->width, TRUE); //width
                SetDlgItemInt(hDlg, IDC_EDIT4, selectedbrick->height, TRUE); //height
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedbrick->round, TRUE); //round #
            }

            if(selectedball)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedball->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedball->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT10, selectedball->speed, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT11, selectedball->angle, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedball->round, TRUE);//round #
                SetDlgItemInt(hDlg, IDC_EDIT8, selectedball->radius, TRUE);//round #
            }

            if(selectedbouncer)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedbouncer->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedbouncer->y, TRUE);//y

                SetDlgItemInt(hDlg, IDC_EDIT5, selectedbouncer->round, TRUE);//round #

                SetDlgItemInt(hDlg, IDC_EDIT6, selectedbouncer->multiplier, TRUE);//reflection vector

                SetDlgItemInt(hDlg, IDC_EDIT8, selectedbouncer->radius, TRUE);//radius
            }

            if(selectedessence)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedessence->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedessence->y, TRUE);//y

                SetDlgItemInt(hDlg, IDC_EDIT5, selectedessence->round, TRUE);//round #

                SetDlgItemInt(hDlg, IDC_EDIT8, selectedessence->radius, TRUE);//radius
            }

            if(selectedgoal)
            {
                SetDlgItemInt(hDlg, IDC_EDIT1, selectedgoal->x, TRUE);//x
                SetDlgItemInt(hDlg, IDC_EDIT2, selectedgoal->y, TRUE);//y
                SetDlgItemInt(hDlg, IDC_EDIT3, selectedgoal->width, TRUE);//width
                SetDlgItemInt(hDlg, IDC_EDIT4, selectedgoal->height, TRUE);//height
                SetDlgItemInt(hDlg, IDC_EDIT5, selectedgoal->round, TRUE);//round #
            }
                
                return TRUE;
        case WM_MOVE:
            render(); 
            return TRUE;
        case WM_COMMAND:
            switch(wParam){
                
                //case IDC_RADIO1: iColor = RED;break;
                //case IDC_RADIO2: iColor = BLUE;break;
                case IDC_BUTTON1://default


                if(selectedball){
                    SetDlgItemInt(hDlg, IDC_EDIT8, BALLSIZE, TRUE);//round #
                }

                    if(selectedbrick){
                    SetDlgItemInt(hDlg, IDC_EDIT3, BLOCKWIDTH, TRUE);//width
                    SetDlgItemInt(hDlg, IDC_EDIT4, BLOCKHEIGHT, TRUE);//height}
                    }

                    if(selectedgoal){
                    SetDlgItemInt(hDlg, IDC_EDIT3, GOALWIDTH, TRUE);
                    SetDlgItemInt(hDlg, IDC_EDIT4, GOALHEIGHT, TRUE);//height}
                    }

                    if(selectedbouncer){
                        SetDlgItemInt(hDlg, IDC_EDIT8, BOUNCERRADIUS, TRUE);
                        SetDlgItemInt(hDlg, IDC_EDIT6, BOUNCEVECTOR, TRUE);
                    }

                    if(selectedessence){
                        SetDlgItemInt(hDlg, IDC_EDIT8, BOUNCERRADIUS, TRUE);
                        SetDlgItemInt(hDlg, IDC_EDIT6, BOUNCEVECTOR, TRUE);
                    }

                    break;
                case IDC_BUTTON3: //delete
                    if(selectedbrick)
                    {selectedbrick->round = NULL;
                    selectedbrick = NULL;}
                    if(selectedbouncer)
                    {selectedbouncer->round = NULL;
                    selectedbouncer = NULL;}
                    if(selectedessence)
                    {selectedessence->round = NULL;
                    selectedessence = NULL;}
                    if(selectedgoal)
                    {selectedgoal->round = NULL;
                    selectedgoal = NULL;}
                    EndDialog(hDlg, 0);
                    if(selectedball){
                    selectedball->round = 0;
                    selectedball = 0;
                    }
                    if(selectedpaddle){
                        selectedpaddle->x = NULL;
                        selectedpaddle = NULL;
                    }
                    break;
                case IDOK:  
                    if(selectedbrick){
                        selectedbrick->x = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                        selectedbrick->y = GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                        selectedbrick->width = GetDlgItemInt(hDlg, IDC_EDIT3,&transsuc,TRUE);
                        selectedbrick->height = GetDlgItemInt(hDlg, IDC_EDIT4,&transsuc,TRUE);
                        selectedbrick->round  = GetDlgItemInt(hDlg, IDC_EDIT5,&transsuc,TRUE);
                        if(selectedbrick->round <1 || selectedbrick->round > 4){selectedbrick->round = 1;}
                        if(selectedbrick->width <1){selectedbrick->width = 1;}
                        if(selectedbrick->height<1){selectedbrick->height = 1;}
                        selectedbrick = NULL;
                    }

                    if(selectedball)
                    {
                        selectedball->x = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                        selectedball->y = GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                        selectedball->round = GetDlgItemInt(hDlg, IDC_EDIT5,&transsuc,TRUE);
                        selectedball->speed = GetDlgItemInt(hDlg, IDC_EDIT10,&transsuc,TRUE);
                        selectedball->angle = GetDlgItemInt(hDlg, IDC_EDIT11,&transsuc,TRUE);
                        selectedball->radius = GetDlgItemInt(hDlg, IDC_EDIT8,&transsuc,TRUE);
                    
                        if(selectedball->round <1 || selectedball->round > 4){selectedball->round = 1;}
                        if(selectedball->radius <1){selectedball->radius = 2;}

                        //if(selectedball->
                    }

                    if(selectedessence)
                    {
                        //selectedessence->color = iColor;
                        selectedessence->radius = GetDlgItemInt(hDlg, IDC_EDIT8,&transsuc,TRUE);
                        selectedessence->round = GetDlgItemInt(hDlg, IDC_EDIT5,&transsuc,TRUE);
                        selectedessence->x = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                        selectedessence->y = GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                        
                        if(selectedessence->radius < 1){selectedessence->radius = 1;}
                        if(selectedessence->round <1 || selectedessence->round > 4){selectedessence->round = 1;}

                        selectedessence = NULL;
                    }
                    
                    if(selectedgoal)
                    {
                        selectedgoal->x=GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                        selectedgoal->y=GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                        //selectedgoal->color=iColor;
                        selectedgoal->height=GetDlgItemInt(hDlg, IDC_EDIT4,&transsuc,TRUE);
                        selectedgoal->round=GetDlgItemInt(hDlg, IDC_EDIT5,&transsuc,TRUE);
                        selectedgoal->width=GetDlgItemInt(hDlg, IDC_EDIT3,&transsuc,TRUE);
                        if(selectedgoal->round <1 || selectedgoal->round > 4){selectedgoal->round = 1;}
                        if(selectedgoal->width <1){selectedgoal->width = 1;}
                        if(selectedgoal->height<1){selectedgoal->height = 1;}
                        selectedgoal = NULL;
                        
                    }

                    if(selectedbouncer)
                    {
                        selectedbouncer->multiplier = GetDlgItemInt(hDlg, IDC_EDIT6,&transsuc,TRUE);
                        selectedbouncer->radius = GetDlgItemInt(hDlg, IDC_EDIT8,&transsuc,TRUE);
                        selectedbouncer->round = GetDlgItemInt(hDlg, IDC_EDIT5,&transsuc,TRUE);
                        selectedbouncer->x =GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                        selectedbouncer->y =GetDlgItemInt(hDlg, IDC_EDIT2,&transsuc,TRUE);
                        if(selectedbouncer->round <1 || selectedbouncer->round > 4){selectedbouncer->round = 1;}
                        if(selectedbouncer->radius <1){selectedbouncer->radius = 1;}
                        
                        selectedbouncer = NULL;
                    }


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

INT_PTR  CALLBACK DlgProcOpt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    BOOL transsuc = FALSE;

OPENFILENAME lofn;
TCHAR lszFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");
TCHAR lszFileName[MAX_PATH], lszTitleName[MAX_PATH];

    switch(message)
    {
        case WM_INITDIALOG: 
                SetDlgItemInt(hDlg, IDC_EDIT1,MAPBARRIER,TRUE);
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




                case IDOK:  MAPBARRIER = GetDlgItemInt(hDlg, IDC_EDIT1,&transsuc,TRUE);
                            if(xpos >MAPBARRIER){xpos = MAPBARRIER;roundcoordinate();}
                            if(xpos < 0){xpos = 0;roundcoordinate();}
                            if(ypos > MAPBARRIER){ypos = MAPBARRIER;roundcoordinate();}
                            if(ypos < 0){ypos = 0;roundcoordinate();}
                            SetScrollRange(hwnd,SB_HORZ,0,MAPBARRIER,FALSE);
                            SetScrollRange(hwnd,SB_VERT,0,MAPBARRIER,TRUE);
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
                            if(xpos >MAPBARRIER){xpos = MAPBARRIER;roundcoordinate();}
                            if(xpos < 0){xpos = 0;roundcoordinate();}
                            if(ypos > MAPBARRIER){ypos = MAPBARRIER;roundcoordinate();}
                            if(ypos < 0){ypos = 0;roundcoordinate();}
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

