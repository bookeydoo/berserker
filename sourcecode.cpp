#include<stdio.h>
#include<conio.h>
#include "CC212SGL.h"
#pragma comment(lib,"CC212SGL.h")
#include<time.h>
#include<Windows.h>
#define FramesPerSec 30 



class Guts
{

public:
    int hp;
    float currentframe=0;
    int Xp,Yp;      //x and y points for the player
    bool framedirection;
    bool alive;
    int *mvF,*DSF;   //mvf stands for movementFrames,dsf stands for down strike frames  
    int *QAF;   //quick attack frames
    int *Hframes; //damage frames
    int speed; 
    int w,h;    //the window length and height for resizing images and changing background
    
    Guts(){
      int w=graphics.getWindowWidth();
      int h=graphics.getWindowHeight();
    }

void updatePlayerLocation(int x,int y){

}
void deathanimation(){  
  int*death;
  death=new int[1];

  
  death[0]=graphics.loadImage("images\\death");
  graphics.drawImage(death[0],w-400,h-400,RGB(0,0,0));
  Sleep(300);
  
  graphics.resizeImage(death[0],w,h);
  graphics.setDrawingColor(COLORS::RED);
  graphics.setFontSizeAndBoldness(150,25);
  graphics.drawText(Xp,Yp+200,"You have died");
}

void checkstate(bool alive){
  if(alive != true){

  }
  
}
void basicRunningSprites(){
  mvF= new int[10];
  mvF[0]=graphics.loadImage("images\\Running1");
  mvF[1]=graphics.loadImage("images\\Running2");
  mvF[2]=graphics.loadImage("images\\Running3");
  mvF[3]=graphics.loadImage("images\\Running4");
  mvF[4]=graphics.loadImage("images\\Running5");
  mvF[5]=graphics.loadImage("images\\Running6");
  mvF[6]=graphics.loadImage("images\\Running7");
  mvF[7]=graphics.loadImage("images\\Running8");
  mvF[8]=graphics.loadImage("images\\Running9");
  mvF[9]=graphics.loadImage("images\\Running10");
}
void QAsprites(){
QAF= new int[4];
QAF[0]=graphics.loadImage("images\\QA1");
QAF[1]=graphics.loadImage("images\\QA2");
QAF[2]=graphics.loadImage("images\\QA3");
QAF[3]=graphics.loadImage("images\\QA4");
}
void OnHitsprites(){
  Hframes=new int[4];
  Hframes[0]=graphics.loadImage("images\\hurt1");
  Hframes[1]=graphics.loadImage("images\\hurt2");
  Hframes[2]=graphics.loadImage("images\\hurt3");
  Hframes[3]=graphics.loadImage("images\\hurt4");
}
void DSsprites(){
  DSF=new int[8];
  DSF[0]=graphics.loadImage("images\\ds1");
  DSF[1]=graphics.loadImage("images\\ds2");
  DSF[2]=graphics.loadImage("images\\ds3");
  DSF[3]=graphics.loadImage("images\\ds4");
  DSF[4]=graphics.loadImage("images\\ds5");
  DSF[5]=graphics.loadImage("images\\ds6");
  DSF[6]=graphics.loadImage("images\\ds7");
  DSF[7]=graphics.loadImage("images\\ds8");

}

};
CC212SGL graphics;


void Mainmenu(){
  int w=graphics.getWindowWidth();
  int l=graphics.getWindowHeight();
  int mainmenu=graphics.loadImage("images\\eclipse");
  graphics.resizeImage(mainmenu,w,l);
  graphics.drawImage(mainmenu,l,w,RGB(100,0,0));
  graphics.setDrawingColor(COLORS::WHITE);
  graphics.setFontSizeAndBoldness(200,30);
  graphics.drawText((w/2),(l/2),"Berserker alpha version");
  graphics.setDrawingColor(COLORS::RED);
  graphics.drawText((w/3),(l/3),"press F to start the game");
}



int main(){
  graphics.setup();
  graphics.setFullScreenMode();





  
  graphics.endDraw();
  return 0;

}