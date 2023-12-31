#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include "CC212SGL.h"
#include<stdlib.h>
#pragma comment(lib,"CC212SGL.lib")
#include<time.h>
#include<windows.h>

#include <math.h>
CC212SGL graphics;
int terrain;
#define _CRT_SECURE_NO_WARNINGS

bool hitflag = 0;
//framelimit =70
int FramesPerSec = 30;



int state0 = 0;
int state1 = 0;  //for troubleshooting ask waleed why
int state2 = 0;
int state3 = 0;
int state4 = 0;
int* QApointer = &state0;
int* QA_Rpointer2 = &state1;
int* RUNApointer3 = &state2;
int* DSFpointer4 = &state3;
int* DSF_Rpointer5 = &state4;



class Guts
{

public:
    int enemycount = 4;
    int* RunAF;
    int hp, stagecount;//stagecount is self explantory
    bool winflag;
    float currentframe = 0;
    int Xp, Yp;      //x and y points for the player
    bool framedirection;// direction the char is looking at
    bool alive;
    int* mvF, * DSF, * mvF_R, * DSF_R;   //mvf stands for movementFrames,dsf stands for down strike frames  
    int* QAF;
    int* QAF_R;   //quick attack frames
    int* Hframes, * Hframes_R; //damage frames
    int w, h;    //the window length and height for resizing images and changing background
    int dodge = 0;
    int dodgeR = 0;
    int* idleF;
    int* idleF_R;

    Guts() {
        w = graphics.getWindowWidth();
        h = graphics.getWindowHeight();
        mvF = DSF = mvF_R = DSF_R = QAF = Hframes = Hframes_R = idleF = idleF_R = nullptr;
        QAF_R = DSF_R = nullptr;
        stagecount = 1;
        Xp = 0;
        Yp = h - 480;
        mvF_R = nullptr;
        RunAF = nullptr;
        hitflag = 0;
        hp = 5;
        alive = 1;
    }
    Guts(int xp, int yp) {
        framedirection = 1; //1 is right
        bool winflag = 0;// game not over
        Xp = xp;
        Yp = yp;
    }
    ~Guts() {
        delete[] mvF, DSF, mvF_R, DSF_R, QAF, Hframes, Hframes_R, idleF, idleF_R;
    }
    //loading functions except for goodending and mainmenu
    void goodending() {
        if (winflag) {
            int happyending = graphics.loadImage("Generalimages\\happyending.jpg");
            graphics.resizeImage(happyending, w, h);
            while (1) {
                graphics.beginDraw();
                graphics.drawImage(happyending, 0, 0, 0);
                graphics.setDrawingColor(COLORS::CYAN);
                graphics.setFontSizeAndBoldness(150, 30);
                graphics.drawText((w / 2) - 500, (h / 2) - 500, "You win ,happy ending!");
                graphics.setDrawingColor(COLORS::WHITE);
                graphics.drawText((w / 2) - 700, (h / 2) - 700, "press F to close the game");



                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'F' || ch == 'f');
                    break;
                }
                graphics.endDraw();

            }
        }


    }

    void deathanimation() {


        int death = graphics.loadImage("Generalimages\\death.png");
        graphics.drawImage(death, w - 400, h - 400, RGB(0, 0, 0));
        

        graphics.resizeImage(death, w, h);
        graphics.setDrawingColor(COLORS::RED);
        graphics.setFontSizeAndBoldness(150, 25);
        graphics.drawText(Xp + 600, Yp - 300, "You have died");
    }

    void checkstate() {
        if (alive != true)
            deathanimation();

    }

    void loadidleF() {
        idleF = new int[5];
        idleF[0] = graphics.loadImage("Generalimages\\gutsIdle1.png");
        idleF[1] = graphics.loadImage("Generalimages\\gutsIdle2.png");
        idleF[2] = graphics.loadImage("Generalimages\\gutsIdle3.png");
        idleF[3] = graphics.loadImage("Generalimages\\gutsIdle4.png");
        idleF[4] = graphics.loadImage("Generalimages\\gutsIdle5.png");
    }



    void loadDodgeSprites() {
        dodge = graphics.loadImage("Generalimages\\dodge.png");
        dodgeR = graphics.loadImage("Generalimages\\dodgeR.png");
    }
    void loadbasicRunningSprites() {
        mvF = new int[10];
        mvF[0] = graphics.loadImage("Generalimages\\Running1.png");
        mvF[1] = graphics.loadImage("Generalimages\\Running2.png");
        mvF[2] = graphics.loadImage("Generalimages\\Running3.png");
        mvF[3] = graphics.loadImage("Generalimages\\Running4.png");
        mvF[4] = graphics.loadImage("Generalimages\\Running5.png");
        mvF[5] = graphics.loadImage("Generalimages\\Running6.png");
        mvF[6] = graphics.loadImage("Generalimages\\Running7.png");
        mvF[7] = graphics.loadImage("Generalimages\\Running8.png");
        mvF[8] = graphics.loadImage("Generalimages\\Running9.png");
        mvF[9] = graphics.loadImage("Generalimages\\Running10.png");
    }
    void loadQAsprites() {
        QAF = new int[4];
        QAF[0] = graphics.loadImage("Generalimages\\QA1.png");
        QAF[1] = graphics.loadImage("Generalimages\\QA2.png");
        QAF[2] = graphics.loadImage("Generalimages\\QA3.png");
        QAF[3] = graphics.loadImage("Generalimages\\QA4.png");
    }
    void loadOnHitsprites() {
        Hframes = new int[4];
        Hframes[0] = graphics.loadImage("Generalimages\\hurt1.png");
        Hframes[1] = graphics.loadImage("Generalimages\\hurt2.png");
        Hframes[2] = graphics.loadImage("Generalimages\\hurt3.png");
        Hframes[3] = graphics.loadImage("Generalimages\\hurt4.png");
    }
    void loadDSsprites() {
        DSF = new int[8];
        DSF[0] = graphics.loadImage("Generalimages\\DS1.png");
        DSF[1] = graphics.loadImage("Generalimages\\DS2.png");
        DSF[2] = graphics.loadImage("Generalimages\\DS3.png");
        DSF[3] = graphics.loadImage("Generalimages\\DS4.png");
        DSF[4] = graphics.loadImage("Generalimages\\DS5.png");
        DSF[5] = graphics.loadImage("Generalimages\\DS6.png");
        DSF[6] = graphics.loadImage("Generalimages\\DS7.png");
        DSF[7] = graphics.loadImage("Generalimages\\DS8.png");

    }

    void loadRunA() {
        RunAF = new int[5];
        RunAF[0] = graphics.loadImage("Generalimages\\RunA1.png");
        RunAF[1] = graphics.loadImage("Generalimages\\RunA2.png");
        RunAF[2] = graphics.loadImage("Generalimages\\RunA3.png");
        RunAF[3] = graphics.loadImage("Generalimages\\RunA4.png");
        RunAF[4] = graphics.loadImage("Generalimages\\RunA5.png");



    }



    void loadbasicRunningSpritesR() {       //Reversed
        mvF_R = new int[10];
        mvF_R[0] = graphics.loadImage("Generalimages\\Running1R.png");
        mvF_R[1] = graphics.loadImage("Generalimages\\Running2R.png");
        mvF_R[2] = graphics.loadImage("Generalimages\\Running3R.png");
        mvF_R[3] = graphics.loadImage("Generalimages\\Running4R.png");
        mvF_R[4] = graphics.loadImage("Generalimages\\Running5R.png");
        mvF_R[5] = graphics.loadImage("Generalimages\\Running6R.png");
        mvF_R[6] = graphics.loadImage("Generalimages\\Running7R.png");
        mvF_R[7] = graphics.loadImage("Generalimages\\Running8R.png");
        mvF_R[8] = graphics.loadImage("Generalimages\\Running9R.png");
        mvF_R[9] = graphics.loadImage("Generalimages\\Running10R.png");
    }

    void loadDSspritesR() {
        DSF_R = new int[8];
        DSF_R[0] = graphics.loadImage("Generalimages\\DS1R.png");
        DSF_R[1] = graphics.loadImage("Generalimages\\DS2R.png");
        DSF_R[2] = graphics.loadImage("Generalimages\\DS3R.png");
        DSF_R[3] = graphics.loadImage("Generalimages\\DS4R.png");
        DSF_R[4] = graphics.loadImage("Generalimages\\DS5R.png");
        DSF_R[5] = graphics.loadImage("Generalimages\\DS6R.png");
        DSF_R[6] = graphics.loadImage("Generalimages\\DS7R.png");
        DSF_R[7] = graphics.loadImage("Generalimages\\DS8R.png");


    }

    void loadOnHitspritesR() {
        Hframes_R = new int[4];
        Hframes_R[0] = graphics.loadImage("Generalimages\\hurt1R.png");
        Hframes_R[1] = graphics.loadImage("Generalimages\\hurt2R.png");
        Hframes_R[2] = graphics.loadImage("Generalimages\\hurt3R.png");
        Hframes_R[3] = graphics.loadImage("Generalimages\\hurt4R.png");
    }

    void loadidleFR() {
        idleF_R = new int[5];
        idleF_R[0] = graphics.loadImage("Generalimages\\gutsIdle1R.png");
        idleF_R[1] = graphics.loadImage("Generalimages\\gutsIdle2R.png");
        idleF_R[2] = graphics.loadImage("Generalimages\\gutsIdle3R.png");
        idleF_R[3] = graphics.loadImage("Generalimages\\gutsIdle4R.png");
        idleF_R[4] = graphics.loadImage("Generalimages\\gutsIdle5R.png");
    }

    void loadQAspritesR() {
        QAF_R = new int[4];
        QAF_R[0] = graphics.loadImage("Generalimages\\QA1R.png");
        QAF_R[1] = graphics.loadImage("Generalimages\\QA2R.png");
        QAF_R[2] = graphics.loadImage("Generalimages\\QA3R.png");
        QAF_R[3] = graphics.loadImage("Generalimages\\QA4R.png");

    }


    void movementF() {
        static int k = 0;
        static int R = 0;
        static int i = 0;
        static int z = 0;
        static int A1 = 0;
        static int A2 = 0;
        static int A3 = 0;
        static int A4 = 0;
        static int A5 = 0;



        if (_kbhit() == 1) {
            int input = _getch();
            QApointer = &A1;
            QA_Rpointer2 = &A2;
            RUNApointer3 = &A3;
            DSFpointer4 = &A4;
            DSF_Rpointer5 = &A5;
            switch (input) {
            case 'D':
            case 'd':


                framedirection = 1;
                graphics.drawImage(mvF[k], Xp += 80, Yp + 140, GREEN);
                k++;
                break;

            case 'A':
            case 'a':
                framedirection = 0;
                graphics.drawImage(mvF_R[R], Xp -= 50, Yp + 140, GREEN);
                R++;

                break;

            case 'F':
            case 'f':
                if (framedirection == 1) {
                    if (A1 == 3) {
                        {

                            graphics.drawImage(QAF[3], Xp += 40, Yp + 80, GREEN);

                            A1++;

                        }
                    }
                    else {
                        graphics.drawImage(QAF[A1], Xp += 40, Yp + 140, GREEN);

                        A1++;
                    }
                }
                else if (A2 == 3) {
                    {
                        graphics.drawImage(QAF_R[3], Xp -= 40, Yp + 80, GREEN);
                        A2++;
                    }
                }
                else {

                    graphics.drawImage(QAF_R[A2], Xp -= 40, Yp + 140, GREEN);

                    A2++;

                }break;


            case VK_SPACE:
                if (framedirection == 1) {
                    Xp -= 200;
                    graphics.drawImage(dodge, Xp, Yp + 100, 1);

                }
                else if (framedirection == 0) {
                    Xp += 200;
                    graphics.drawImage(dodgeR, Xp, Yp + 100, WHITE);
                }
                break;

            case 'R':
            case 'r':
                if (framedirection == 1) {
                    graphics.drawImage(RunAF[A3], Xp += 20, Yp + 50, 1);
                    A3++;

                }
                else {

                    graphics.setFontSizeAndBoldness(50, 90);
                    graphics.drawText(Xp, Yp - 100, "you can only use this while running forward");
                    graphics.drawImage(idleF_R[i], Xp, Yp + 140, 1);

                }
            case 'S':
            case 's':
                if (framedirection == 1) {
                    graphics.drawImage(DSF[A4], Xp += 20, Yp + 50, 1);
                    A4++;

                }
                else if (framedirection == 0) {
                    graphics.drawImage(DSF_R[A5], Xp -= 20, Yp + 50, 1);

                }
            }

        }

        else {

            if (framedirection == 1 && hitflag == 0) {
                graphics.drawImage(idleF[i], Xp, Yp + 140, 1);
                i++;
            }
            else if (framedirection == 0 && hitflag == 0) {
                graphics.drawImage(idleF_R[0], Xp, Yp + 140, 1);

            }

        }


        hitflag = 0;
        if (i == 4) {
            i = 0;
        }

        if (k == 9) {
            k = 0;
        }

        if (R == 9) {
            R = 0;
        }
        if (A1 == 4) {
            A1 = 0;
        }

        if (A2 == 4) {
            A2 = 0;
        }
        if (A3 == 5) {
            A3 = 0;
        }
        if (A4 == 8) {
            A4 = 0;
        }
        if (A5 == 8) {
            A5 = 0;

        }
    }
    void  hitlogic() {
        static int z5 = 0;
        if ((hitflag == 1)) {
            graphics.drawImage(Hframes[z5], Xp -= 30, Yp + 140, 1);

        }if (z5 == 4) {
            z5 = 0;
        }
    }




    void back2start() {

        if (Xp >= w) {

            Xp = -265;
            stagecount++;
        }
        if (Xp < -265) {

            Xp = -10;


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

////};
//
//
//class monk {
//public:
//    bool alive;
//    bool framedirection;
//    int Xe, Ye;
//    int speed;
//    int hp;
//    int* monkwmF;// monk walk 
//    int* monkjmF;// jump
//    int* monkkmF;// kick
//    int* monkhmF;// hurt
//    int* monkfkmF;// flyingkick
//    int* monkpmF;// punch
//    void monkmF() {
//        monkwmF = new int[6];
//        monkwmF[0] = graphics.loadImage("enemyImages\\monkwalk1.png");
//        monkwmF[1] = graphics.loadImage("enemyImages\\monkwalk2.png");
//        monkwmF[2] = graphics.loadImage("enemyImages\\monkwalk3.png");
//        monkwmF[3] = graphics.loadImage("enemyImages\\monkwalk4.png");
//        monkwmF[4] = graphics.loadImage("enemyImages\\monkwalk5.png");
//        monkwmF[5] = graphics.loadImage("enemyImages\\monkwalk6.png");
//    }
//
//    void monkpjmF() {
//        monkjmF = new int[2];
//        monkjmF[0] = graphics.loadImage("enemyImages\\jump1.png");
//        monkjmF[1] = graphics.loadImage("enemyImages\\jump2.png");
//
//    }
//
//    void monmF() {
//        monkkmF = new int[6];
//        monkkmF[0] = graphics.loadImage("enemyImages\\monkkick1.png");
//        monkkmF[1] = graphics.loadImage("enemyImages\\kick2.png");
//        monkkmF[2] = graphics.loadImage("enemyImages\\kick3.png");
//        monkkmF[3] = graphics.loadImage("enemyImages\\kick4.png");
//        monkkmF[4] = graphics.loadImage("enemyImages\\kick5.png");
//
//    }
//
//
//    void monktmF() {
//        monkhmF = new int[2];
//        monkhmF[0] = graphics.loadImage("enemyImages\\monkhurt1.png");
//        monkhmF[1] = graphics.loadImage("enemyImages\\monkhurt2.png");
//
//
//    }
//    void monkzkmF() {
//        monkfkmF = new int[2];
//        monkfkmF[0] = graphics.loadImage("enemyImages\\monkflying-kick1.png");
//        monkfkmF[1] = graphics.loadImage("enemyImages\\monkflying-kick2.png");
//
//    }
//
//    void monkfmF() {
//        monkpmF = new int[6];
//        monkpmF[0] = graphics.loadImage("enemyImages\\monkpunch1.png");
//        monkpmF[1] = graphics.loadImage("enemyImages\\monkpunch2.png");
//        monkpmF[2] = graphics.loadImage("enemyImages\\monkpunch3.png");
//        monkpmF[3] = graphics.loadImage("enemyImages\\monkpunch4.png");
//        monkpmF[4] = graphics.loadImage("enemyImages\\monkpunch5.png");
//        monkpmF[5] = graphics.loadImage("enemyImages\\monkpunch6.png");
//    }
//
//
//};
//
//class wizard {
//public:
//    bool alive;
//    bool framedirection;
//    int Xe, Ye;
//    int speed;
//    int hp;
//    int* WizatFe;// attack 
//
//    void wizatck() {
//        WizatFe = new int[11];
//        WizatFe[0] = graphics.loadImage("enemyImages\\wizard-idle-1.png");
//        WizatFe[1] = graphics.loadImage("enemyImages\\wizardfire1.png");
//        WizatFe[2] = graphics.loadImage("enemyImages\\wizardfire2.png");
//        WizatFe[3] = graphics.loadImage("enemyImages\\wizardfire3.png");
//        WizatFe[4] = graphics.loadImage("enemyImages\\wizardfire4.png");
//        WizatFe[5] = graphics.loadImage("enemyImages\\wizardfire5.png");
//        WizatFe[6] = graphics.loadImage("enemyImages\\wizardfire6.png");
//        WizatFe[7] = graphics.loadImage("enemyImages\\wizardfire7.png");
//        WizatFe[8] = graphics.loadImage("enemyImages\\wizardfire8.png");
//        WizatFe[9] = graphics.loadImage("enemyImages\\wizardfire9.png");
//        WizatFe[10] = graphics.loadImage("enemyImages\\wizardfire10.png");
//    }
//
//};

class wolf {
public:
    bool alive=1;
    bool framedirection;
    int Xe=graphics.getWindowWidth()-100, Ye;
    
    int hp=2;
    int* WmvFe=nullptr; // movement frames for enemies
    int* WatFe=nullptr;// attack


    void wolfmove() {

        WmvFe = new int[7];
        WmvFe[0] = graphics.loadImage("enemyImages\\wolfidle1.png");
        WmvFe[1] = graphics.loadImage("enemyImages\\wolfrun1.png");
        WmvFe[2] = graphics.loadImage("enemyImages\\wolfrun2.png");
        WmvFe[3] = graphics.loadImage("enemyImages\\wolfrun3.png");
        WmvFe[4] = graphics.loadImage("enemyImages\\wolfrun4.png");
        WmvFe[5] = graphics.loadImage("enemyImages\\wolfrun5.png");
        WmvFe[6] = graphics.loadImage("enemyImages\\wolfrun6.png");
        WatFe = new int[3];
        WatFe[0] = graphics.loadImage("enemyImages\\wolfattack1.png");
        WatFe[1] = graphics.loadImage("enemyImages\\wolfattack2.png");
        WatFe[2] = graphics.loadImage("enemyImages\\wolfattack3.png");

        

    }
    void wolfatck(Guts& player) {



        static int  movementframe = 0;
        static int attackframe = 0;
        static int damageg = 0;
        if (alive == true && player.Xp + 140 < Xe) {
            framedirection = 0;
            Xe -= 30;
            graphics.drawImage(WmvFe[movementframe], Xe, graphics.getWindowHeight() - 300, 1);
            movementframe++;

        }


        if (alive == true && abs((Xe - player.Xp)) < 150) {
            graphics.drawImage(WatFe[attackframe], Xe, graphics.getWindowHeight() - 400, 1);
            graphics.drawImage(player.Hframes[damageg], player.Xp -= 30, player.Yp + 140, 1);
            player.hp--;
            damageg++;
            attackframe++;
        }

        if (movementframe == 6) {
            movementframe = 0;
        }
        if (damageg == 3) {
            damageg = 0;
        }
        if (attackframe == 2) {
            attackframe = 0;
        }
        if (hp == 0) {
            graphics.drawImage(WmvFe[0], Xe, graphics.getWindowHeight() * 2, 1);
            alive = 0;

        }
    }


    
    

};



class burn {
public:
    bool alive = true;
    bool framedirection = 0;
    int Xe = (graphics.getWindowWidth() - 100), Ye = graphics.getWindowHeight() - 400;
    int hp = 1;

    int h = graphics.getWindowHeight();
    int* mvFeR;//reverse
    int* mvFe = nullptr;// movement frames for enemies
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

        mvFeR = new int[9];
        mvFeR[0] = graphics.loadImage("enemyImages\\burning-ghoul-1R.png");
        mvFeR[1] = graphics.loadImage("enemyImages\\burning-ghoul-2R.png");
        mvFeR[2] = graphics.loadImage("enemyImages\\burning-ghoul-3R.png");
        mvFeR[3] = graphics.loadImage("enemyImages\\burning-ghoul-4R.png");
        mvFeR[4] = graphics.loadImage("enemyImages\\burning-ghoul-5R.png");
        mvFeR[5] = graphics.loadImage("enemyImages\\burning-ghoul-6R.png");
        mvFeR[6] = graphics.loadImage("enemyImages\\burning-ghoul-7R.png");
        mvFeR[7] = graphics.loadImage("enemyImages\\burning-ghoul-8R.png");
        mvFeR[8] = graphics.loadImage("enemyImages\\burning-ghoul-9R.png");

        // image resize

        for (int i = 0; i < 9; i++) {
            graphics.resizeImage(mvFe[i], 200, 200);
            graphics.resizeImage(mvFeR[i], 200, 200);
        }

    }

    void burnatk(Guts& player) {
        static int  FRAMES = 0;
        static int damageg = 0;
        if (alive == true && player.Xp + 140 < Xe) {
            framedirection = 0;
            Xe -= 30;
            graphics.drawImage(mvFe[FRAMES], Xe, graphics.getWindowHeight() - 400, 1);
            FRAMES++;

        }
        else if (alive == true && player.Xp + 140 > Xe) {
            framedirection = 0;
            Xe += 30;
            graphics.drawImage(mvFeR[FRAMES], Xe, graphics.getWindowHeight() - 400, 1);
            FRAMES++;
        }
        if (alive == true && abs((Xe - player.Xp)) < 150) {
            graphics.drawImage(player.Hframes[damageg], player.Xp -= 30, player.Yp + 140, 1);
            player.hp--;
            damageg++;
        }

        if (FRAMES == 8) {
            FRAMES = 0;
        }
        if (damageg == 3) {
            damageg = 0;
        }
        if (hp == 0) {
            Ye = 2 * h;
            alive = 0;
        }
    }
    void checkstate() {
        if (!alive) {
            graphics.drawImage(mvFe[0], Xe, graphics.getWindowHeight() * 2, 1);
        }
        return;
    }


};
//
//class Zodd {
//public:
//    bool alive;
//    bool framedirection;
//    int Xe = 0, Ye = 0;
//    int speed;
//    int hp;
//    int* zoddmvFe; // movement frames for enemies
//    int* zoddatFe; // Attack frames for enemies
//    void Zoddmove() {
//
//        zoddmvFe = new int[4];
//        zoddmvFe[0] = graphics.loadImage("enemyImages\\zoddlanding.png");
//        zoddmvFe[1] = graphics.loadImage("enemyImages\\zoddintro1.png");
//        zoddmvFe[2] = graphics.loadImage("enemyImages\\zoddintro2.png");
//        zoddmvFe[3] = graphics.loadImage("enemyImages\\zodintro3.png");
//
//    }
//    void ZoddAtck() {
//        zoddatFe = new int[1];
//        zoddatFe[0] = graphics.loadImage("enemyImages\\zoddattack.png");
//    }
//};







void firstlevel(Guts& player) {
    int w = graphics.getWindowWidth();
    int l = graphics.getWindowHeight();
    int bg1 = graphics.loadImage("Generalimages\\gothiclevelbg.png");
    graphics.resizeImage(bg1, 1700, 700);
    int terrainpart = graphics.loadImage("Generalimages\\gothiclevelterrain.png");
    graphics.resizeImage(terrainpart, w / 2, 200);
    int terrainpart2 = graphics.loadImage("Generalimages\\gothiclevelterrain2.png");
    graphics.resizeImage(terrainpart2, w / 2, 200);
    int bg2 = graphics.loadImage("Generalimages\\evilforest.jpg");
    graphics.resizeImage(bg2, 1700, 700);
    int bg3 = graphics.loadImage("Generalimages\\medieveltown.png");
    graphics.resizeImage(bg3, 1700, 700);



    if (player.stagecount == 1) {
        graphics.setFontSizeAndBoldness(90, 50);
        graphics.drawText(w / 2, l / 2 - 300, "first stage");
        graphics.drawImage(bg1, 0, 0, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart, w / 2, l - 200, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart2, 0, l - 200, graphics.generateFromRGB(0, 0, 0));


    }
    else if (player.stagecount == 2) {
        graphics.drawImage(bg2, 0, 0, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart, w / 2, l - 200, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart2, 0, l - 200, graphics.generateFromRGB(0, 0, 0));

    }
    else if (player.stagecount == 3) {
        graphics.drawImage(bg3, 0, 0, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart, w / 2, l - 200, graphics.generateFromRGB(0, 0, 0));
        graphics.drawImage(terrainpart2, 0, l - 200, graphics.generateFromRGB(0, 0, 0));
        
    }
    else {
        if (player.stagecount > 3) {
            player.goodending();
        }
    }

    Sleep(70);


}


void waitForTime(int start)
{
    while (1)
    {
        float t = (clock() / (float)CLOCKS_PER_SEC * 1000.0f) - (start / (float)CLOCKS_PER_SEC * 1000.0f);
        if (t > 1.0f / (30 * 1000.0f)) {
            break;
        }
    }
}
void hitlogic(Guts& player, burn& fireEnemy, int* frame) {
    if ((abs((fireEnemy.Xe - player.Xp)) < 260) && *QApointer == 3) {
        fireEnemy.hp--;
        fireEnemy.checkstate();
    }
    else if ((*RUNApointer3 == 1 || *RUNApointer3 == 2) && (abs((fireEnemy.Xe - player.Xp)) < 260)) {
        fireEnemy.hp--;
        fireEnemy.checkstate();
    }
    else if ((*DSFpointer4 == 5 || *DSFpointer4 == 6) && (abs((fireEnemy.Xe - player.Xp)) < 250)) {
        fireEnemy.hp--;
        fireEnemy.checkstate();
    }
    else


        return;

}


void Mainmenu() {

    int w = graphics.getWindowWidth();
    int h = graphics.getWindowHeight();
    int mainmenu = graphics.loadImage("Generalimages\\eclipse.jpg");
    graphics.resizeImage(mainmenu, w, h);
    while (1) {
        graphics.beginDraw();
        graphics.drawImage(mainmenu, 0, 0, COLORS::BLACK);
        graphics.setDrawingColor(COLORS::RED);
        graphics.setFontSizeAndBoldness(150, 30);
        graphics.drawText((double(w) / 2.5) - 500, (double(h) / 2) - 500, "Berserker alpha version");
        graphics.setDrawingColor(COLORS::RED);
        graphics.setFontSizeAndBoldness(40, 90);
        graphics.drawText((double(w) / 2.6) - h, (double(h) / 1.3) - h, "press F to start the game");



        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'F' || ch == 'f')
                break;
        }
        graphics.endDraw();

    }
}

int main() {
    graphics.setup();
    graphics.setFullScreenMode();
    graphics.hideCursor();
    burn fireEnemy;
    Guts player;
    wolf grandma;

    player.hp = 3;
    bool hitflag = 0;
    Mainmenu();

    player.loadidleF();
    player.loadbasicRunningSprites();
    player.loadbasicRunningSpritesR();
    player.loadDSsprites();
    player.loadQAsprites();
    player.loadDSspritesR();
    player.loadidleFR();
    player.loadOnHitspritesR();
    player.loadOnHitsprites();
    player.deathanimation();
    player.loadQAsprites();
    player.loadDodgeSprites();
    player.loadQAspritesR();
    player.loadRunA();
    fireEnemy.BurnWalk();
    char* ch = (char*)malloc(sizeof(char)); // Allocate memory for char


    if (ch == NULL) {
        printf("Memory allocation failed\n");
        return 1;  // Return an error code
    }

    while (1) {

        graphics.beginDraw();
        firstlevel(player);
        player.back2start();



        player.movementF();
        if (player.stagecount == 1 ) {
            fireEnemy.burnatk(player);

        }
        if (player.stagecount == 2) {
            grandma.wolfmove();
            grandma.wolfatck(player);
        }
        
        
        hitlogic(player, fireEnemy, QApointer);
        fireEnemy.checkstate();
        if (player.hp <= 0) {
            graphics.fillScreen(BLACK);
            graphics.setFontSizeAndBoldness(100, 50);
            graphics.drawText(player.Xp, player.Yp - 200, "YOU HAVE DIED !");
            graphics.drawText(graphics.getWindowWidth() / 2 - 500, graphics.getWindowHeight() / 2 - 200, "press f to close the game");
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'F' || ch == 'f')
                    break;
            }

        }
        graphics.endDraw();
        waitForTime(30);
    }

    free(ch);  // Free the allocated memory
    return 0;
}