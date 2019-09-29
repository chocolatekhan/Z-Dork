#include<stdio.h>
#include<stdlib.h>
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
int intro();
void player1_action();
void player2_action();
int heal (struct stats *character);
void attack (struct stats *character1, struct stats *character2);
void damage (struct stats *character);
int win(struct stats *character);
int reset(struct stats *character1, struct stats *character2);
void endgame();


int main()
{
    printf("Welcome to Z-Dork.\n\n");
    int gdriver = DETECT, gmode;
    initgraph (&gdriver, &gmode, NULL);
    initwindow(1280, 960);                  //graphics window size
    //readimagefile("Logo.jpg", 0,80, 1280, 720);
    //delay(2000);
    //cleardevice();
    player_names();
    health_bar1(100);
    //heal_potion1(5);
    health_bar2(100);
    intro();
}


int intro()
{
    printf("\n\nPlayer 1 Heal Potions:%d\n\nPlayer 2 Heal Potions: %d\n\n", player1.heal_potion, player2.heal_potion);
    //line above temporary
    player1_action();
}

void player1_action()
{
    int action = 0;
    while ((action != 1) && (action != 2))
    {
        text_left("Player 1's Turn");
        text_right(" ");
        printf("Choose an action:\n\t1. Attack\n\t2. Heal\nAction: ");
        scanf("%d", &action);
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

        printf("Choose an action:\n\t1. Attack\n\t2. Heal\nAction: ");
        scanf("%d", &action);
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
    else                        intro();
}

void attack (struct stats *character1, struct stats *character2)
{
    int char1_attack, char2_dodge;
    printf("\n\nChoose an attack:\n1. Attack high\n2. Attack low\nChoice: ");
    scanf("%d", &char1_attack);
    printf("\n\n%s has attacked! Choose a dodge:\n1. Dodge high\n2. Dodge low\nChoice: ", character1->name);
    scanf("%d", &char2_dodge);
    if (char1_attack == char2_dodge)
    {
        damage(character2);
        printf("\n%s failed to dodge the attack. Damage 10.\n", character2->name);
    }
    else    printf("%s has dodge the attack.\n", character2->name);

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
        printf("Your health is already full.\n\n");
        return 0;
    }
    else if (character->heal_potion == 0)
    {
        printf("You are out of heal potions.\n\n");
        return 0;
    }
    else
    {
        if (character->health > 90)    character->health = 100;
        else                           character->health += 10;
        character->heal_potion--;
        printf("You restored your health to: %d.\n\n",  character->health);
        if (strcmp(character->name, "Player 1") == 0)   health_bar1(character->health);
        else                                            health_bar2(character->health);
    }
}


int win(struct stats *character)
{
    char ans;
    character->score++;
    printf("\n\nCongratulations. %s has won.\n\n", character->name);

    next_round:
    printf("Play another round? (Y/N)\n\n");
    scanf("%c", &ans);
    if (ans == 'Y' || ans == 'y')
    {
        reset(&player1, &player2);
        intro();
    }
    else if (ans == 'N' || ans == 'n')  endgame();
    else
    {
        printf("Invalid response.\n\n");
        goto next_round;
    }
}

int reset(struct stats *character1, struct stats *character2)
{
    character1->health = 100;
    character1->heal_potion = 5;
    character2->health = 100;
    character2->heal_potion = 5;
    health_bar1(100);
    health_bar2(100);
}

void endgame()
{

}
