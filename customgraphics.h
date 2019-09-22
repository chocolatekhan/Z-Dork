#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void player_names()
{
    settextstyle(8, HORIZ_DIR, 5);
    outtextxy(50, 50, "PLAYER 1");
    outtextxy(1025, 50, "PLAYER 2");
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
