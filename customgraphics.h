#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void player_names()
{
    settextstyle(8, HORIZ_DIR, 5);
    outtextxy(50, 50, "PLAYER 1");
    outtextxy(1025, 50, "PLAYER 2");
    return;
}

void health_bar1(int a)
{
    a = a/10;
    if (a!=0)
    {
        setcolor(GREEN);
        rectangle(50, 100, 50+(50*a), 150);
        setfillstyle(1, GREEN);
        floodfill(49+(50*a), 101, GREEN);
    }
    if (a < 10)
    {
        setcolor(RED);
        rectangle(50+(50*a), 100, 550, 150);
        setfillstyle(1, RED);
        floodfill(51+(50*a), 101, RED);
    }
    return;
}

void health_bar2(int a)
{
    a = a/10;
    if (a!=0)
    {
        setcolor(GREEN);
        rectangle(730+(50*(10-a)), 100, 1230, 150);
        setfillstyle(1, GREEN);
        floodfill(749+(50*(10-a)), 101, GREEN);
    }
    if (a < 10)
    {
        setcolor(RED);
        rectangle(730, 100, 1230-(50*a), 150);
        setfillstyle(1, RED);
        floodfill(1229-(50*a), 101, RED);
    }
    return;
}

void heal_potion1(int a)
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3);
    char msg[20];
    sprintf(msg, "Heal Potions: %d", a);
    outtextxy(330, 65, msg);
    return;
}

void heal_potion2(int a)
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3);
    char msg[20];
    sprintf(msg, "Heal Potions: %d", a);
    outtextxy(730, 65, msg);
    return;
}

void text_left(char a[1000])
{
    setcolor(RED);
    rectangle(40, 850, 650, 950);
    setfillstyle(1, BLACK);
    floodfill(41, 851, RED);
    setcolor(BLACK);
    rectangle(40, 850, 650, 950);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 5);
    char msg[1000];
    sprintf(msg, "%s", a);
    outtextxy(50, 900, msg);
    return;
}

void text_right(char a[1000])
{
    setcolor(RED);
    rectangle(610, 850, 1280, 950);
    setfillstyle(1, BLACK);
    floodfill(611, 851, RED);
    setcolor(BLACK);
    rectangle(610, 850, 1280, 950);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 5);
    char msg[1000];
    sprintf(msg, "%s", a);
    outtextxy(650, 900, msg);
    return;
}

void esc()
{
    setcolor(RED);
    rectangle(20, 20, 50, 50);
    setfillstyle(1, BLACK);
    floodfill(21, 21, RED);
    setcolor(BLACK);
    rectangle(20, 20, 50, 50);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2);
    outtextxy(20, 20, "Back");
    return;
}

void round (int a)
{
    cleardevice();

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 8);
    char msg[1000];
    sprintf(msg, "Round %d", a);
    outtextxy(455, 450, msg);

    delay(1000);

    cleardevice();

    delay(1000);

    return;
}

void scorebar (int a, int b)
{
    setcolor(RED);
    rectangle(410, 10, 880, 50);
    setfillstyle(1, BLACK);
    floodfill(411, 11, RED);
    setcolor(BLACK);
    rectangle(410, 10, 880, 50);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 5);
    char msg[1000];
    sprintf(msg, "%d | %d", a, b);
    outtextxy(580, 10, msg);

    return;
}

void mainmenu(int a)
{
    if (a == 1)
    {
        setcolor(RED);
        settextstyle(8, HORIZ_DIR, 8);
        outtextxy(410, 250, "New Game");
        setcolor(WHITE);
        outtextxy(350, 450, "High Scores");
        outtextxy(505, 650, "Exit");
    }

    else if (a == 2)
    {
        setcolor(WHITE);
        settextstyle(8, HORIZ_DIR, 8);
        outtextxy(410, 250, "New Game");
        setcolor(RED);
        outtextxy(350, 450, "High Scores");
        setcolor(WHITE);
        outtextxy(505, 650, "Exit");
    }

    else if (a == 3)
    {
        setcolor(WHITE);
        settextstyle(8, HORIZ_DIR, 8);
        outtextxy(410, 250, "New Game");
        outtextxy(350, 450, "High Scores");
        setcolor(RED);
        outtextxy(505, 650, "Exit");
    }
}

void highscores(int a, int b, char c[1000])
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4);
    char msg[1000];
    sprintf(msg, c);
    outtextxy(50 + 250*b, 100 + 40*a, msg);
}

void image(char a[1000])
{
    setcolor(RED);
    rectangle(50, 200, 1230, 800);
    setfillstyle(1, BLACK);
    floodfill(51, 201, RED);
    setcolor(BLACK);
    rectangle(50, 200, 1230, 800);
    readimagefile(a, 50,200, 1230, 800);
}
