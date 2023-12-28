#include<stdio.h>
#include<conio.h>
#include "CC212SGL.h"
#pragma comment(lib,"CC212SGL.lib")
#include<time.h>
#include<Windows.h>
#define FramesPerSec 30 
CC212SGL graphics;
int terrain;
#define _CRT_SECURE_NO_WARNINGS

int state = 0;

class Guts
{

public:
    int hp;
    float currentframe = 0;
    int Xp, Yp;      //x and y points for the player
    bool framedirection;// direction the char is looking at
    bool alive;
    int* mvF, * DSF;   //mvf stands for movementFrames,dsf stands for down strike frames  
    int* QAF;   //quick attack frames
    int* Hframes; //damage frames
    int speed;
    int w, h;    //the window length and height for resizing images and changing background
    int* idleF;
    Guts() {
        int w = graphics.getWindowWidth();
        int h = graphics.getWindowHeight();
    }

    void updatePlayerLocation(int x, int y) {

    }

    
    void deathanimation() {


        int death = graphics.loadImage("Generalimages\\death");
        graphics.drawImage(death, w - 400, h - 400, RGB(0, 0, 0));
        Sleep(300);

        graphics.resizeImage(death, w, h);
        graphics.setDrawingColor(COLORS::RED);
        graphics.setFontSizeAndBoldness(150, 25);
        graphics.drawText(Xp, Yp + 200, "You have died");
    }

    void checkstate(bool alive) {
        if (alive != true) 
            deathanimation();
        
    }

    void Normalstate() {
        idleF = new int[5];
        idleF[0] = graphics.loadImage("Generalimages\\gutsIdle1");
        idleF[1] = graphics.loadImage("Generalimages\\gutsIdle2");
        idleF[2] = graphics.loadImage("Generalimages\\gutsIdle3");
        idleF[3] = graphics.loadImage("Generalimages\\gutsIdle4");
        idleF[4] = graphics.loadImage("Generalimages\\gutsIdle5");
    }



    void basicRunningSprites() {
        mvF = new int[10];
        mvF[0] = graphics.loadImage("Generalimages\\Running1");
        mvF[1] = graphics.loadImage("Generalimages\\Running2");
        mvF[2] = graphics.loadImage("Generalimages\\Running3");
        mvF[3] = graphics.loadImage("Generalimages\\Running4");
        mvF[4] = graphics.loadImage("Generalimages\\Running5");
        mvF[5] = graphics.loadImage("Generalimages\\Running6");
        mvF[6] = graphics.loadImage("Generalimages\\Running7");
        mvF[7] = graphics.loadImage("Generalimages\\Running8");
        mvF[8] = graphics.loadImage("Generalimages\\Running9");
        mvF[9] = graphics.loadImage("Generalimages\\Running10");
    }
    void QAsprites() {
        QAF = new int[4];
        QAF[0] = graphics.loadImage("Generalimages\\QA1");
        QAF[1] = graphics.loadImage("Generalimages\\QA2");
        QAF[2] = graphics.loadImage("Generalimages\\QA3");
        QAF[3] = graphics.loadImage("Generalimages\\QA4");
    }
    void OnHitsprites() {
        Hframes = new int[4];
        Hframes[0] = graphics.loadImage("Generalimages\\hurt1");
        Hframes[1] = graphics.loadImage("Generalimages\\hurt2");
        Hframes[2] = graphics.loadImage("Generalimages\\hurt3");
        Hframes[3] = graphics.loadImage("Generalimages\\hurt4");
    }
    void DSsprites() {
        DSF = new int[8];
        DSF[0] = graphics.loadImage("Generalimages\\DS1");
        DSF[1] = graphics.loadImage("Generalimages\\DS2");
        DSF[2] = graphics.loadImage("Generalimages\\DS3");
        DSF[3] = graphics.loadImage("Generalimages\\DS4");
        DSF[4] = graphics.loadImage("Generalimages\\DS5");
        DSF[5] = graphics.loadImage("Generalimages\\DS6");
        DSF[6] = graphics.loadImage("Generalimages\\DS7");
        DSF[7] = graphics.loadImage("Generalimages\\DS8");

    }
    void renderRunningF(char* ch) {
        int i;
        if (*ch == 'D') {
            framedirection = 1;
            while (*ch == 'D') {
                for (i = 0;i <= 10;i++) {
                    //this place is reserved for the x coordinate changes every time the character moves
                    graphics.drawImage(mvF[i], 222, 130, COLORS::BLACK);
                    Sleep(50);
                }
                i = 0;
            }
        if (*ch == 'A') {
            framedirection = 0;
                while (*ch == 'A') {
                    for ( i = 0;i <= 10;i++) {
                        //place reserved for x coordinate change but in negative
                      //this is a loop for the images that are reversed  graphics.drawImage();
                        Sleep(50);
                    }
                }
            }
        }
    }
    void renderQA() {
        for (int j = 0;j <= 4;j++) {
            graphics.drawImage(QAF[j],222,130,COLORS::BLACK);
            Sleep(50);
        }

    }


};

class enemies {
public:
    bool alive;
    bool framedirection;
    int Xp, Yp;
    int speed;
    int hp;

    void checkstate() {

    }

};



/*void loadingscreen() {
    int w = graphics.getWindowWidth();
    int l = graphics.getWindowHeight();
    int loadingscreenimg = graphics.loadImage("Generalimages\\guts angry");
    graphics.resizeImage(loadingscreenimg, w / 3, l / 3);
    graphics.drawImage(loadingscreenimg, w - 300, l - 500, RGB(0, 0, 0));
    graphics.setDrawingColor(COLORS::RED);
    graphics.drawText(w / 3, l - 500, "loading");


}*/

void firstlevel() {
    int w = graphics.getWindowWidth();
    int l = graphics.getWindowHeight();
    int bg = graphics.loadImage("Generalimages\\gothiclevel.jpg");
    graphics.resizeImage(bg, w, l);
    int terrainpart = graphics.loadImage("Generalimages\\gothiclevelterrain.png");
    graphics.resizeImage(terrainpart, w / 2, 136);
    int terrainpart2 = graphics.loadImage("Generalimages\\gothiclevelterrain2.png");
    graphics.resizeImage(terrainpart2, w / 2, 136);
    

    while (1) {
        graphics.beginDraw();
        graphics.drawImage(bg, 0, 0, WHITE);
        graphics.drawImage(terrainpart, w / 2, l, WHITE);
        graphics.drawImage(terrainpart2, w / 2, 136, WHITE);
        Sleep(300);
        graphics.endDraw();
    }
}

void Mainmenu() {

    int w = graphics.getWindowWidth();
    int l = graphics.getWindowHeight();
    int mainmenu = graphics.loadImage("Generalimages\\eclipse.jpg");
    graphics.resizeImage(mainmenu, w, l);
    while (1) {
        graphics.beginDraw();
        graphics.drawImage(mainmenu, 0, 0, COLORS::WHITE);
        graphics.setDrawingColor(COLORS::RED);
        graphics.setFontSizeAndBoldness(150, 30);
        graphics.drawText((w / 2) - 500, (l / 2) - 500, "Berserker alpha version");
        graphics.setDrawingColor(COLORS::WHITE);
        graphics.drawText((w / 2) - 700, (l / 2) - 700, "press F to start the game");



        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'F' || ch == 'f');
            break;
        }
        graphics.endDraw();

    }
}

int main() {
    graphics.setup();
    graphics.setFullScreenMode();
    graphics.hideCursor();
    
    Guts player;
    player.Normalstate();
    player.hp = 3;

    Mainmenu();         //loads the first level which has the terrain,special bg,and some randomly generated enemies 
    while (1) {
        graphics.beginDraw();
        firstlevel();
        char ch;

        if (GetAsyncKeyState('A'))
            ch = 'A';
        if (GetAsyncKeyState('D'))
            ch = 'D';
        if (GetAsyncKeyState('W'))
            ch = 'W';

    }




    graphics.endDraw();
    return 0;

}