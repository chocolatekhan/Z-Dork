#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void player_names(char player1[1000], char player2[1000])       //gets entered names and displays them on top
{
    settextstyle(8, HORIZ_DIR, 5);
    char msg[20];
    sprintf(msg, player1);
    outtextxy(50, 50, msg);
    sprintf(msg, player2);
    outtextxy(1025, 50, msg);
    return;
}

char getname(int i)                                             //runs function getting characters entered
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4);
    char b[2], msg[2];
    if (i == -1)        outtextxy(50, 200, "Enter Player 1 Name:");
    else if (i == -2)   outtextxy(50, 200, "Enter Player 2 Name:");
    else
    {
        b[0] = getch();
        while (((b[0] < 65) && (b[0] != 13) && (b[0] !=8))|| (b[0] > 122) || ((b[0] < 97) && (b[0] > 90))) b[0] = getch();
        //accept entered character as long as lower or upper case alphabet or enter or backspace key
        if (b[0] == 8)  //remove previous character if backspace is pressed
        {
            sprintf(msg, " ");
            outtextxy(500 + 20*(i-1), 200, msg);

        }
        else if (b[0] != 13)    outtextxy(500 + 20*i, 200, b);  //print character unless enter is pressed
    }
    return b[0];
}

void health_bar1(int a)         //display left health bar from integer value of health
{
    a = a/10;
    if (a!=0)                   //make area upto a from left green
    {
        setcolor(GREEN);
        rectangle(50, 100, 50+(50*a), 150);
        setfillstyle(1, GREEN);
        floodfill(49+(50*a), 101, GREEN);
    }
    if (a < 10)                 //make rest red
    {
        setcolor(RED);
        rectangle(50+(50*a), 100, 550, 150);
        setfillstyle(1, RED);
        floodfill(51+(50*a), 101, RED);
    }
    return;
}

void health_bar2(int a)         //display right health bar from integer value of health
{
    a = a/10;
    if (a!=0)                   //make area from right upto a green
    {
        setcolor(GREEN);
        rectangle(730+(50*(10-a)), 100, 1230, 150);
        setfillstyle(1, GREEN);
        floodfill(749+(50*(10-a)), 101, GREEN);
    }
    if (a < 10)                 //make rest red
    {
        setcolor(RED);
        rectangle(730, 100, 1230-(50*a), 150);
        setfillstyle(1, RED);
        floodfill(1229-(50*a), 101, RED);
    }
    return;
}

void heal_potion1(int a)        //display heal potions left
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3);
    char msg[20];
    sprintf(msg, "Heal Potions: %d", a);
    outtextxy(330, 65, msg);
    return;
}

void heal_potion2(int a)        //display heal potions right
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3);
    char msg[20];
    sprintf(msg, "Heal Potions: %d", a);
    outtextxy(730, 65, msg);
    return;
}

void text_left(char a[1000])    //get string and display string on bottom left
{
    setcolor(RED);              //make a red rectangle around text, fill it black, and replace rectangle with black one
    rectangle(40, 850, 650, 950);
    setfillstyle(1, BLACK);
    floodfill(41, 851, RED);
    setcolor(BLACK);
    rectangle(40, 850, 650, 950);

    setcolor(WHITE);            //print text inside rectangle
    settextstyle(8, HORIZ_DIR, 5);
    char msg[1000];
    sprintf(msg, "%s", a);
    outtextxy(50, 900, msg);
    return;
}

void text_right(char a[1000])       //display string on bottom right
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

void esc()                      //display ESC on top left on high scores screen
{
    setcolor(RED);
    rectangle(20, 20, 50, 50);
    setfillstyle(1, BLACK);
    floodfill(21, 21, RED);
    setcolor(BLACK);
    rectangle(20, 20, 50, 50);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2);
    char msg[1000];
    sprintf(msg, "Esc");
    outtextxy(20, 20, msg);
    return;
}

void round (int a)                  //display round number at beginning of each round
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

void scorebar (int a, int b)            //display score bar on top center
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

void mainmenu(int a)                //main menu
{
    char msg[1000];
    if (a == 1)                     //by default make line 1 red
    {
        setcolor(RED);
        settextstyle(8, HORIZ_DIR, 8);
        sprintf(msg, "New Game");
        outtextxy(410, 250, msg);
        setcolor(WHITE);
        sprintf(msg, "High Scores");
        outtextxy(350, 450, msg);
        sprintf(msg, "Exit");
        outtextxy(505, 650, msg);
    }

    else if (a == 2)                //if arrow keys pressed, value of changes making color change accordingly
    {
        setcolor(WHITE);
        settextstyle(8, HORIZ_DIR, 8);
        sprintf(msg, "New Game");
        outtextxy(410, 250, msg);
        setcolor(RED);
        sprintf(msg, "High Scores");
        outtextxy(350, 450, msg);
        setcolor(WHITE);
        sprintf(msg, "Exit");
        outtextxy(505, 650, msg);
    }

    else if (a == 3)
    {
        setcolor(WHITE);
        settextstyle(8, HORIZ_DIR, 8);
        sprintf(msg, "New Game");
        outtextxy(410, 250, msg);
        sprintf(msg, "High Scores");
        outtextxy(350, 450, msg);
        setcolor(RED);
        sprintf(msg, "Exit");
        outtextxy(505, 650, msg);
    }
}

void highscores(int a, int b, char c[1000])         //display string given at position based on a and b values
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4);
    char msg[1000];
    sprintf(msg, c);
    outtextxy(50 + 250*b, 100 + 40*a, msg);
}

void image(char a[1000])                            //display logo
{
    setcolor(RED);
    rectangle(50, 200, 1230, 800);
    setfillstyle(1, BLACK);
    floodfill(51, 201, RED);
    setcolor(BLACK);
    rectangle(50, 200, 1230, 800);
    readimagefile(a, 50,200, 1230, 800);
}

void clear_left_image()                             //clear left character space
{
    setcolor(RED);
    rectangle(100, 200, 650, 800);
    setfillstyle(1, BLACK);
    floodfill(101, 201, RED);
    setcolor(BLACK);
    rectangle(100, 200, 650, 800);
}

void clear_right_image()                            //clear right character space
{
    setcolor(RED);
    rectangle(650, 200, 1210, 800);
    setfillstyle(1, BLACK);
    floodfill(791, 201, RED);
    setcolor(BLACK);
    rectangle(650, 200, 1210, 800);
}

void image_left(char a[1000])                       //default left character
{
    clear_left_image();
    readimagefile(a, 100, 210, 400, 790);
}

void image_right(char a[1000])                      //default right character
{
    clear_right_image();
    readimagefile(a, 850, 210, 1150, 790);
}

void image_left_attack_high()                       //left sword attack animation
{
    int a = 100;    //delay time
    int dim1 = 100, dim2= 200, dim3 = 650, dim4 = 790;  //dimensions of image
    clear_left_image();
    readimagefile("Images/Left Attack High 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 7.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 8.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 9.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack High 10.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
}

void image_right_attack_high()              //right sword attack animation
{
    int a = 100;
    int dim1 = 700, dim2= 200, dim3 = 1250, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Attack High 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 7.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 8.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 9.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack High 10.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
}

void image_right_attack_low()                //left dagger attack animation
{
    int a = 100;
    int dim1 = 870, dim2= 300, dim3 = 1200, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Attack Low (1).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (2).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (3).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (4).bmp", 700, dim2, dim3, dim4);     //dimensions manually adjusted for wider images
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);         //left image redrawn due to overlap
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (5).bmp", 620, dim2, dim3, dim4);
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (6).bmp", 540, dim2, dim3, dim4);
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (7).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (8).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (9).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Attack Low (10).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
}

void image_left_attack_low()               //right dagger attack animation
{
    int a = 100;    //delay time
    int dim1 = 100, dim2= 300, dim3 = 480, dim4 = 790;  //dimensions of image
    clear_left_image();
    readimagefile("Images/Left Attack Low (1).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (2).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (3).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (4).bmp", dim1, dim2, 650, dim4);     //dimensions manually adjusted for wider images
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);       //right image redrawn due to overlap
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (5).bmp", dim1, dim2, 730, dim4);
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (6).bmp", dim1, dim2, 810, dim4);
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (7).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (8).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (9).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Attack Low (10).bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
}

void image_left_jump()                      //left jump animation
{
    int a = 100;
    int dim1 = 100, dim2 = 210, dim3 = 500, dim4 = 790;
    clear_left_image();
    readimagefile("Images/Left Jump 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Jump 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
}

void image_right_jump()                 //right jump animation
{
    int a = 100;
    int dim1 = 750, dim2 = 210, dim3 = 1150, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Jump 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Jump 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
}

void image_left_dead()                  //left death animation
{
    int a = 100;
    int dim1 = 100, dim2 = 210, dim3 = 600, dim4 = 790;
    clear_left_image();
    image_right("Images/Default Image Right.bmp");
    readimagefile("Images/Left Dead 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Dead 7.bmp", dim1, dim2, dim3, dim4);
}

void image_right_dead()                     //right death animation
{
    int a = 100;
    int dim1 = 700, dim2 = 210, dim3 = 1200, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Dead 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Dead 7.bmp", dim1, dim2, dim3, dim4);
}

void image_left_duck()                      //left duck animation
{
    int dim1 = 150, dim2 = 310, dim3 = 600, dim4 = 790;
    clear_left_image();
    readimagefile("Images/Left Duck.bmp", dim1, dim2, dim3, dim4);
    delay(1000);
    clear_left_image();
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
}

void image_right_duck()                     //right duck animation
{
    int dim1 = 750, dim2 = 310, dim3 = 1200, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Duck.bmp", dim1, dim2, dim3, dim4);
    delay(1000);
    clear_right_image();
    readimagefile("Images/Default Image Right.bmp", 850, 201, 1150, 790);
}

void image_left_win()                       //left win dance animation
{
    int a = 100;
    int dim1 = 100, dim2= 200, dim3 = 450, dim4 = 790;
    clear_left_image();
    readimagefile("Images/Left Win 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 7.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 8.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 9.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Left Win 10.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_left_image();
    readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
}

void image_right_win()                          //right win dance animation
{
    int a = 100;
    int dim1 = 800, dim2= 200, dim3 = 1200, dim4 = 790;
    clear_right_image();
    readimagefile("Images/Right Win 1.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 2.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 3.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 4.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 5.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 6.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 7.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 8.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 9.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Right Win 10.bmp", dim1, dim2, dim3, dim4);
    delay(a);
    clear_right_image();
    readimagefile("Images/Default Image Right.bmp", 850, 210, 1200, 790);
}
