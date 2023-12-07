#include<stdio.h>
#include<conio.h>
#include "CC212SGL.h"
#pragma comment(lib,"CC212SGL.h")
#include<time.h>
class Guts
{

public:
    int hp=100;
    float currentframe=0;
    int x,y;
    bool framedirection;
    bool alive;
    Guts(){}

};
CC212SGL graphics;


void Mainmenu(){
  int w=graphics.getWindowWidth();
   int l=graphics.getWindowHeight();
   int intro=graphics.loadImage("images\\mainmenu.jpeg") ;
   graphics.resizeImage(intro,w,l);

    

    }