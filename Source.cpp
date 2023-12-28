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
int w = graphics.getWindowWidth();
int h = graphics.getWindowHeight();

class Guts
{

public:
    int hp;
    float currentframe = 0;
    int Xp, Yp;      //x and y points for the player
    bool framedirection;// direction the char is looking at
    bool alive;
    int* mvF, * DSF , *mvF_R , *DSF_R;   //mvf stands for movementFrames,dsf stands for down strike frames  
    int* QAF, QAF_R;   //quick attack frames
    int* Hframes, *Hframes_R; //damage frames
    int speed;
    int w, h;    //the window length and height for resizing images and changing background
    int* idleF ;
    int* idleF_R;
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

    void basicRunningSpritesR() {       //Reversed
        mvF_R = new int[10];
        mvF_R[0] = graphics.loadImage("Generalimages\\Running1R");
        mvF_R[1] = graphics.loadImage("Generalimages\\Running2R");
        mvF_R[2] = graphics.loadImage("Generalimages\\Running3R");
        mvF_R[3] = graphics.loadImage("Generalimages\\Running4R");
        mvF_R[4] = graphics.loadImage("Generalimages\\Running5R");
        mvF_R[5] = graphics.loadImage("Generalimages\\Running6R");
        mvF_R[6] = graphics.loadImage("Generalimages\\Running7R");
        mvF_R[7] = graphics.loadImage("Generalimages\\Running8R");
        mvF_R[8] = graphics.loadImage("Generalimages\\Running9R");
        mvF_R[9] = graphics.loadImage("Generalimages\\Running10R");
    }

    void DSspritesR() {
        DSF_R = new int[8];
        DSF_R[0] = graphics.loadImage("Generalimages\\DS1R");
        DSF_R[1] = graphics.loadImage("Generalimages\\DS2R");
        DSF_R[2] = graphics.loadImage("Generalimages\\DS3R");
        DSF_R[3] = graphics.loadImage("Generalimages\\DS4R");
        DSF_R[4] = graphics.loadImage("Generalimages\\DS5R");
        DSF_R[5] = graphics.loadImage("Generalimages\\DS6R");
        DSF_R[6] = graphics.loadImage("Generalimages\\DS7R");
        DSF_R[7] = graphics.loadImage("Generalimages\\DS8R");

    }

    void OnHitspritesR() {
        Hframes_R = new int[4];
        Hframes_R[0] = graphics.loadImage("Generalimages\\hurt1R");
        Hframes_R[1] = graphics.loadImage("Generalimages\\hurt2R");
        Hframes_R[2] = graphics.loadImage("Generalimages\\hurt3R");
        Hframes_R[3] = graphics.loadImage("Generalimages\\hurt4R");
    }

    void idleFR() {
        idleF_R = new int[5];
        idleF_R[0] = graphics.loadImage("Generalimages\\gutsIdle1R");
        idleF_R[1] = graphics.loadImage("Generalimages\\gutsIdle2R");
        idleF_R[2] = graphics.loadImage("Generalimages\\gutsIdle3R");
        idleF_R[3] = graphics.loadImage("Generalimages\\gutsIdle4R");
        idleF_R[4] = graphics.loadImage("Generalimages\\gutsIdle5R");
    }

    void renderRunningF(char* ch) {
        int i;
        if (*ch == 'D') {
            framedirection = 1;
            while (*ch == 'D') {
                for (i = 0;i < 10;i++) {
                    //this place is reserved for the x coordinate changes every time the character moves
                    graphics.drawImage(mvF[i], 5, 130, 0);
                    Sleep(50);
                }
                i = 0;
            }
            if (*ch == 'A') {
                framedirection = 0;
                while (*ch == 'A') {
                    for (i = 0;i <= 10;i++) {
                        //place reserved for x coordinate change but in negative
                        graphics.drawImage(mvF_R[i], 5, 130, 0);
                        Sleep(50);
                    }
                }
            }
        }
    }
    void renderQA() {
        if (framedirection == 0) {
            for (int j = 0;j <= 4;j++) {
                graphics.drawImage(QAF[j], w - 222, h-130, 0);
                Sleep(50);
            }
        }
        else
        {
            for (int j = 0;j <= 4;j++) {
                graphics.drawImage(QAF_R,w-222,h-130,0);
                Sleep(50);
            }
        }

    }


};

//class enemies {
//public:
  //  bool alive;
    //bool framedirection;
    //int Xp, Yp;
    //int speed;
    //int hp;

    //void checkstate() {

    //}

//};


class monk {
public:
    bool alive;
    bool framedirection;
    int Xe, Ye;
    int speed;
    int hp;
    int* monkwmF;// monk walk 
    int* monkjmF;// jump
    int* monkkmF;// kick
    int* monkhmF;// hurt
    int* monkfkmF;// flyingkick
    int* monkpmF;// punch
    void monkmF() {
        monkwmF = new int[6];
        monkwmF[0] = graphics.loadImage("enemyImages\\monkwalk1.png");
        monkwmF[1] = graphics.loadImage("enemyImages\\monkwalk2.png");
        monkwmF[2] = graphics.loadImage("enemyImages\\monkwalk3.png");
        monkwmF[3] = graphics.loadImage("enemyImages\\monkwalk4.png");
        monkwmF[4] = graphics.loadImage("enemyImages\\monkwalk5.png");
        monkwmF[5] = graphics.loadImage("enemyImages\\monkwalk6.png");
    }

    void monkpjmF() {
        monkjmF = new int[2];
        monkjmF[0] = graphics.loadImage("enemyImages\\jump1.png");
        monkjmF[1] = graphics.loadImage("enemyImages\\jump2.png");

    }

    void monmF() {
        monkkmF = new int[6];
        monkkmF[0] = graphics.loadImage("enemyImages\\monkkick1.png");
        monkkmF[1] = graphics.loadImage("enemyImages\\kick2.png");
        monkkmF[2] = graphics.loadImage("enemyImages\\kick3.png");
        monkkmF[3] = graphics.loadImage("enemyImages\\kick4.png");
        monkkmF[4] = graphics.loadImage("enemyImages\\kick5.png");

    }


    void monktmF() {
        monkhmF = new int[2];
        monkhmF[0] = graphics.loadImage("enemyImages\\monkhurt1.png");
        monkhmF[1] = graphics.loadImage("enemyImages\\monkhurt2.png");


    }
    void monkzkmF() {
        monkfkmF = new int[2];
        monkfkmF[0] = graphics.loadImage("enemyImages\\monkflying-kick1.png");
        monkfkmF[1] = graphics.loadImage("enemyImages\\monkflying-kick2.png");

    }

    void monkfmF() {
        monkpmF = new int[6];
        monkpmF[0] = graphics.loadImage("enemyImages\\monkpunch1.png");
        monkpmF[1] = graphics.loadImage("enemyImages\\monkpunch2.png");
        monkpmF[2] = graphics.loadImage("enemyImages\\monkpunch3.png");
        monkpmF[3] = graphics.loadImage("enemyImages\\monkpunch4.png");
        monkpmF[4] = graphics.loadImage("enemyImages\\monkpunch5.png");
        monkpmF[5] = graphics.loadImage("enemyImages\\monkpunch6.png");
    }


};

class wizard {
public:
    bool alive;
    bool framedirection;
    int Xe, Ye;
    int speed;
    int hp;
    int* WizatFe;// attack 

    void wizatck() {
        WizatFe = new int[11];
        WizatFe[0] = graphics.loadImage("enemyImages\\wizard-idle-1.png");
        WizatFe[1] = graphics.loadImage("enemyImages\\wizardfire1.png");
        WizatFe[2] = graphics.loadImage("enemyImages\\wizardfire2.png");
        WizatFe[3] = graphics.loadImage("enemyImages\\wizardfire3.png");
        WizatFe[4] = graphics.loadImage("enemyImages\\wizardfire4.png");
        WizatFe[5] = graphics.loadImage("enemyImages\\wizardfire5.png");
        WizatFe[6] = graphics.loadImage("enemyImages\\wizardfire6.png");
        WizatFe[7] = graphics.loadImage("enemyImages\\wizardfire7.png");
        WizatFe[8] = graphics.loadImage("enemyImages\\wizardfire8.png");
        WizatFe[9] = graphics.loadImage("enemyImages\\wizardfire9.png");
        WizatFe[10] = graphics.loadImage("enemyImages\\wizardfire10.png");
    }

};

class wolf {
public:
    bool alive;
    bool framedirection;
    int Xe, Ye;
    int speed;
    int hp;
    int* WmvFe;// movement frames for enemies
    int* WatFe;// attack 
    void wolfmove() {

        WmvFe = new int[6];
        WmvFe[0] = graphics.loadImage("enemyImages\\wolfidle1.png");
        WmvFe[1] = graphics.loadImage("enemyImages\\wolfrun1.png");
        WmvFe[2] = graphics.loadImage("enemyImages\\wolfrun2.png");
        WmvFe[3] = graphics.loadImage("enemyImages\\wolfrun3.png");
        WmvFe[4] = graphics.loadImage("enemyImages\\wolfrun4.png");
        WmvFe[5] = graphics.loadImage("enemyImages\\wolfrun5.png");
        WmvFe[6] = graphics.loadImage("enemyImages\\wolfrun6.png");



    }
    void wolfatck() {
        WatFe = new int[3];
        WatFe[0] = graphics.loadImage("enemyImages\\wolfattack1.png");
        WatFe[1] = graphics.loadImage("enemyImages\\wolfattack2.png");
        WatFe[2] = graphics.loadImage("enemyImages\\wolfattack3.png");



    }

};



class burn {
public:
    bool alive;
    bool framedirection;
    int Xe, Ye;
    int speed;
    int hp;
    int* mvFe; // movement frames for enemies
    void BurnWalk() {

        mvFe = new int[9];
        mvFe[0] = graphics.loadImage("enemyImages\\burning-ghoul-1.png");
        mvFe[1] = graphics.loadImage("enemyImages\\burning-ghoul-2.png");
        mvFe[2] = graphics.loadImage("enemyImages\\burning-ghoul-3.png");
        mvFe[3] = graphics.loadImage("enemyImages\\burning-ghoul-4.png");
        mvFe[4] = graphics.loadImage("enemyImages\\burning-ghoul-5.png");
        mvFe[5] = graphics.loadImage("enemyImages\\burning-ghoul-6.png");
        mvFe[6] = graphics.loadImage("enemyImages\\burning-ghoul-7.png");
        mvFe[7] = graphics.loadImage("enemyImages\\burning-ghoul-8.png");
        mvFe[8] = graphics.loadImage("enemyImages\\burning-ghoul-9.png");


    }


};


class Zodd {
public:
    bool alive;
    bool framedirection;
    int Xe, Ye;
    int speed;
    int hp;
    int* zoddmvFe; // movement frames for enemies
    int* zoddatFe; // Attack frames for enemies
    void Zoddmove() {

        zoddmvFe = new int[4];
        zoddmvFe[0] = graphics.loadImage("enemyImages\\zoddlanding.png");
        zoddmvFe[1] = graphics.loadImage("enemyImages\\zoddintro1.png");
        zoddmvFe[2] = graphics.loadImage("enemyImages\\zoddintro2.png");
        zoddmvFe[3] = graphics.loadImage("enemyImages\\zodintro3.png");

    }
    void ZoddAtck() {
        zoddatFe = new int[1];
        zoddatFe[0] = graphics.loadImage("enemyImages\\zoddattack.png");
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
    int bg = graphics.loadImage("Generalimages\\gothiclevelbg.png");
    graphics.resizeImage(bg, 1700, 700);
    int terrainpart = graphics.loadImage("Generalimages\\gothiclevelterrain.png");
    graphics.resizeImage(terrainpart, w/2 , 200);
    int terrainpart2 = graphics.loadImage("Generalimages\\gothiclevelterrain2.png");
    graphics.resizeImage(terrainpart2, w / 2, 200);


    while (1) {
        graphics.beginDraw();
        graphics.drawImage(bg, 0, 0, graphics.generateFromRGB(0,0,0));
       graphics.drawImage(terrainpart, w/2 , l-200, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart2, 0 , l-200, graphics.generateFromRGB(0, 0, 0));
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
