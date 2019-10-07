#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"customgraphics.h"

//statistics about characters
struct stats
{
    int health;
    int heal_potion;
    char name[100];
    int score;
};

struct stats player1 = {100, 5, "Player 1", 0};
struct stats player2 = {100, 5, "Player 2", 0};


//declaration of all user-defined functions
void player1_action();
void player2_action();
int heal (struct stats *character);
void attack (struct stats *character1, struct stats *character2);
void damage (struct stats *character);
int win(struct stats *character);
void menu();
void display_scores();
int reset();
void endgame();


int main()
{
    int gdriver = DETECT, gmode;
    initgraph (&gdriver, &gmode, NULL);
    initwindow(1280, 960);                  //graphics window size
    readimagefile("Images/Logo.jpg", 0,80, 1280, 720);
    delay(2000);
    cleardevice();
    menu();
}

void menu()
{
    int pos = 1;
    cleardevice();
    mainmenu(pos);

    int choice;
    for ( ; ; )
    {
        choice = getch();
        if (choice == 0 || choice == 224)
        {
            choice = getch();

            if (choice == 72)
            {
                pos--;
                if (pos == 0)   pos = 1;
                mainmenu(pos);
            }
            else if (choice == 80)
            {
                pos++;
                if (pos == 4)   pos = 3;
                mainmenu(pos);
            }
        }
        else if (choice == 13)
        {
            if (pos == 1)   reset();
            else if (pos == 2)  display_scores();
            else if (pos == 3)  exit(1);
        }
    }
}

void display_scores()
{
    int a = 0, j = 0;
    cleardevice();
    esc();
    highscores(a, 0, "HIGH SCORES");
    a++;
    highscores(a, 0, "");

    FILE *scores;

    if ((scores = fopen("userdata", "r")) == NULL)
    {
        a++;
        highscores(a, 1, "No high scores yet!");

        getch();
        while (getch() != 27)
        {
            getch();
            if (getch() == 27)  menu();
        }
        if (getch() == 27)  menu();
    }

    char temp[1000];
    char b;
    int i;

    for ( ; ; )
    {
        a++;
        for (j=0; j<4; j++)
        {
        for (i=0; ; i++)
        {
            b = fgetc(scores);
            if (b != EOF)   b = b - 30;
            if (b == '\n' || b == EOF)    break;
            else    temp[i] = b;
        }
        temp[i] = '\0';
        highscores(a, j, temp);
        if (b == EOF) break;
        }
        if (b == EOF) break;
        b = fgetc(scores);
    }

    fclose(scores);

    getch();
    while (getch() != 27)
    {
        getch();
        if (getch() == 27)  menu();
    }
    if (getch() == 27)  menu();
}

int reset()
{
    player1.health = 100;
    player1.heal_potion = 5;
    player2.health = 100;
    player2.heal_potion = 5;
    cleardevice();
    round(player1.score+player2.score+1);
    image("Images/Default Image.bmp");
    scorebar(player1.score, player2.score);
    player_names();
    health_bar1(100);
    health_bar2(100);
    heal_potion1(5);
    heal_potion2(5);
    player1_action();
}

void player1_action()
{
    int action = 0;
    while ((action != 1) && (action != 2))
    {
        text_left("Player 1's Turn");
        text_right(" ");
        delay(1000);
        text_left("Choose an action:");
        delay(1000);
        text_left("1. Attack   2. Heal");
        action = getch() - '0';
        if (action == 1)        attack(&player1, &player2);
        else if (action == 2)
        {
            if (heal(&player1) == 0)    player1_action();
        }
        else
        {
            text_left("Invalid choice.\n");
            delay(1000);
        }
    }

    if (player2.health <= 0)    win(&player1);
    else                        player2_action();
}

void player2_action()
{
    int action = 0;
    while ((action != 1) && (action != 2))
    {
        text_right("Player 2's Turn");
        text_left(" ");
        delay(1000);
        text_right("Choose an action:");
        delay(1000);
        text_right("1. Attack   2. Heal");
        action = getch() - '0';
        if (action == 1)        attack(&player2, &player1);
        else if (action == 2)
        {
            if (heal(&player2) == 0)    player2_action();
        }
        else
        {
            text_right("Invalid choice.\n");
            delay(1000);
        }
    }

    if (player1.health <= 0)    win(&player2);
    else                        player1_action();
}

void attack (struct stats *character1, struct stats *character2)
{
    int char1_attack, char2_dodge;
    if (strcmp(character1->name, "Player 1") == 0)
    {
        text_left("Choose an attack:");
        delay(1000);
        text_left("1. Punch   2. Kick");
        char1_attack = getch() - '0';
        text_left(" ");
        text_right("Player 1 attacked!");
        delay(1000);
        text_right("Try to dodge!");
        delay(1000);
        text_right("1. Jump   2. Duck");
        char2_dodge = getch() - '0';

        if (char1_attack == 1)  image("Images/Player 1 Attack High.bmp");
        else                    image("Images/Player 1 Attack Low.bmp");
        delay(500);
        if (char2_dodge == 1)   image("Images/Player 2 Jump.bmp");
        else                    image("Images/Player 2 Duck.bmp");
        delay(500);
        image("Images/Default Image.bmp");

        if (char1_attack == char2_dodge)
        {
            damage(character2);
            text_right("You failed to dodge.");
            delay(1000);
        }
        else
        {
            text_right("You dodged.");
            delay(1000);
        }
    }
    else
    {
        text_right("Choose an attack:");
        delay(1000);
        text_right("1. Punch   2. Kick");
        char1_attack = getch() - '0';
        text_right(" ");
        text_left("Player 2 attacked!");
        delay(1000);
        text_left("Try to dodge!");
        delay(1000);
        text_left("1. Jump   2. Duck");
        char2_dodge = getch() - '0';

        if (char1_attack == 1)  image("Images/Player 2 Attack High.bmp");
        else                    image("Images/Player 2 Attack Low.bmp");
        delay(500);
        if (char2_dodge == 1)   image("Images/Player 1 Jump.bmp");
        else                    image("Images/Player 1 Duck.bmp");
        delay(500);
        image("Images/Default Image.bmp");

        if (char1_attack == char2_dodge)
        {
            damage(character2);
            text_left("You failed to dodge.");
            delay(1000);
        }
        else
        {
            text_left("You dodged.");
            delay(1000);
        }
    }
}

void damage(struct stats *character)
{
    character->health -= 10;
    if (strcmp(character->name, "Player 1") == 0)   health_bar1(character->health);
    else                                            health_bar2(character->health);
}

int heal(struct stats *character)
{
    if (character->health == 100)
    {
        if (strcmp(character->name, "Player 1") == 0)  text_left("Health already full.");
        else                                            text_right("Health already full.");
        delay(1000);
        return 0;
    }
    else if (character->heal_potion == 0)
    {
        if (strcmp(character->name, "Player 1") == 0)  text_left("Out of Heal Potions.");
        else                                            text_right("Out of Heal Potions.");
        delay(1000);
        return 0;
    }
    else
    {
        if (character->health > 90)    character->health = 100;
        else                           character->health += 10;
        character->heal_potion--;
        if (strcmp(character->name, "Player 1") == 0)
        {
            health_bar1(character->health);
            heal_potion1(character->heal_potion);
        }
        else
        {
            health_bar2(character->health);
            heal_potion2(character->heal_potion);
        }
    }
}


int win(struct stats *character)
{
    int error = 0;
    char ans;
    character->score++;
    scorebar(player1.score, player2.score);
    image("Images/Win.bmp");

    if (strcmp(character->name, "Player 1") == 0)
    {

        text_right(" ");
        text_left("Congratulations!");
        delay(1000);
        text_left("You won!");
    }
    else
    {
        text_left(" ");
        text_right("Congratulations!");
        delay(1000);
        text_right("You won!");
        delay(1000);
    }

    next_round:
    if (strcmp(character->name, "Player 1") == 0)   text_left("Play again? (Y/N)");
    else                                            text_right("Play again? (Y/N)");
    ans = getch();
    if (ans == 89 || ans == 121)       reset();
    else if (ans == 78 || ans == 110)  endgame();
    else
    {
        if (error == 0)
        {
            error = 1;
            goto next_round;
        }
        if (strcmp(character->name, "Player 1") == 0)   text_left("Invalid response.");
        else                                            text_right("Invalid response.");
        delay(1000);
        goto next_round;
    }
}

void endgame()
{
    int i;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char text[1000];
    sprintf(text, "%d %d %d\n%d:%d:%d\nPlayer 1: %d\nPlayer 2: %d\n\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player1.score, player2.score);

    FILE *scores;
    scores = fopen("userdata", "a");
    for (i=0; i<strlen(text); i++)  fputc(text[i] + 30, scores);
    fclose(scores);

    player1.score = 0;
    player2.score = 0;
    menu();
}
