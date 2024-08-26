#include <windows.h>
#include "bong.h"
#include <commdlg.h>



extern int resWidth;
extern int resHeight;
extern HWND hwnd;
extern int MAPBARRIER;

extern unsigned char *bitmap;
extern BITMAPINFOHEADER biHead;
extern paddle bluepaddle;

void openfile()
{
    // Save the current working directory
    TCHAR originalDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, originalDir);

    extern char MAPNAME[100];

    extern int gameRound;


    static TCHAR szFilter[] = TEXT("BONG MAPS(*.bng)\0*.bng\0");
    static TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
    HINSTANCE hInstance = NULL;

    static OPENFILENAME ofn;
    ofn.lStructSize = sizeof(OPENFILENAME);
    
    ofn.hwndOwner =hwnd;
    
    ofn.hInstance = hInstance;
    
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
    
    ofn.lpstrDefExt = ".bng";
    
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    
    ofn.hwndOwner = hwnd;
    
    ofn.lpstrFile = szFileName;
    ofn.lpstrFileTitle = szTitleName;
    ofn.Flags = OFN_HIDEREADONLY|OFN_CREATEPROMPT;

    if(GetOpenFileName(&ofn))
    {
        sprintf(MAPNAME,szTitleName);
        //sprintf(&szFileName[0], "balls.bng");
        readFile(szFileName);
        setupGame();
        gameRound = 1;
        //MessageBox(hwnd,imgString,imgString,MB_OK);

        float tx = bluepaddle.x;
        SetCursorPos(((float)bluepaddle.x/(float)MAPBARRIER)*(float)resWidth,bluepaddle.y);
        bluepaddle.x = tx;

        SetCurrentDirectory(originalDir);

        setupGame();
    }

}


void readFile(char *szFileName){

    FILE *fp;

extern goal redgoals[3000];
extern goal bluegoals[3000];
extern brick bricks[3000];
extern brick blocks[3000];
//extern 
paddle rpaddles[4];
//extern 
paddle bpaddles[4];
extern paddle redpaddle;//eventually add ability to add more paddles
extern bouncer bouncers[3000];
extern essence redessences[3000];
extern essence blueessences[3000];
extern ball balls[500];

extern char imgString[100];
extern char musString[100];


    fp = fopen(szFileName,"rb");
    fread(&MAPBARRIER, sizeof(int),1, fp);
    fread(&bluepaddle, sizeof(paddle),1, fp);
    fread(&redpaddle, sizeof(paddle),1, fp);
    fread(&redgoals, sizeof(goal),3000, fp);
    fread(&bluegoals, sizeof(goal),3000, fp);
    fread(&bricks, sizeof(brick),3000, fp);
    fread(&blocks, sizeof(brick),3000, fp);
    fread(&bouncers, sizeof(bouncer),3000, fp);
    fread(&redessences, sizeof(essence),3000, fp);
    fread(&blueessences, sizeof(essence),3000, fp);
    fread(&rpaddles, sizeof(paddle),4, fp);
    fread(&bpaddles, sizeof(paddle),4, fp);
    fread(&balls, sizeof(ball),500, fp);
    fread(&imgString, sizeof(char),100, fp);
    fread(&musString, sizeof(char),100, fp);
    fclose(fp);
}




unsigned char *LoadBMP(char *filestring){
    unsigned char* BITMAP;
    extern unsigned char* dftBmp;
    extern BITMAPINFOHEADER dftHead;
    BITMAPFILEHEADER bfHead;
    
    int i = 0;

    FILE *fp;
    
        fp = fopen(filestring,"r");

        if(fp == NULL){
                biHead = dftHead;
                BITMAP = dftBmp;
                //fclose(fp);
                return dftBmp;
        
        }
            fread(&bfHead,sizeof(BITMAPFILEHEADER),1,fp);
                if(bfHead.bfType != 0x4D42){printf("not a valid file!\n");fclose(fp);}
                fread(&biHead,sizeof(BITMAPINFOHEADER),1,fp);
            fseek(fp, bfHead.bfOffBits,SEEK_SET);
            BITMAP = (unsigned char*)malloc(biHead.biSizeImage);
            
            
            if(!BITMAP){
                biHead = dftHead;
                BITMAP = dftBmp;
                //fclose(fp);
                return BITMAP;
            }

            fread(BITMAP,1,biHead.biSizeImage,fp);
            if(BITMAP == NULL){
                biHead = dftHead;
                BITMAP = dftBmp;
                //fclose(fp);
                return BITMAP;
            }

    fclose(fp);

    unsigned char Temp;

    for(i = 0; i <biHead.biSizeImage; i= i+ 3){
        Temp = BITMAP[i];
        BITMAP[i] = BITMAP[i+2];
        BITMAP[i+2] = Temp;
    }

 return BITMAP;
}

