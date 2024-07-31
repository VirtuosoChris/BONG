#include <windows.h>
#include "editor.h"
#include "resource.h"


void toomany(){
MessageBox(NULL, TEXT("You have placed too many of this object. Remove some to continue"), TEXT("Error"), MB_ICONERROR);
}



void roundcoordinate(){
MessageBox(NULL,"Coordinate component outside map boundaries\nIt has been rounded", TEXT("Error"), MB_ICONERROR);
}