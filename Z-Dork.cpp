#include<stdio.h>
#include<stdlib.h>
#include"customgraphics.h"

//parts will need to be rearranged based on when things are used.

struct stats             //statistics about characters
{
    int health;
    int heal_potion;
    char name[100];
};

struct stats player1 = {100, 5, "Player 1"};
struct stats player2 = {100, 5, "Player 2"};

int heal(struct stats *character)                      //heal function
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

void attack(struct stats *character1, struct stats *character2)              //attack function
{
    if (rand()%2 == 0)
    {
        int initial_health = character2->health;
        character2->health -= 10;
        printf("\n\nYou caused %d damage.\n\n", initial_health-character2->health);
        if (strcmp(character2->name, "Player 1") == 0)  health_bar1(character2->health);
        else                                            health_bar2(character2->health);
    }
    else
    {
        printf("\n\nYour attack failed.\n\n");
        return;
    }

}

int intro();
int win(struct stats *character);
void player2_action();

void player1_action()
{
    int action = 0;
    while ((action != 1) && (action != 2))
    {
        printf("Player 1's Turn.\n\nChoose an action:\n\t1. Attack\n\t2. Heal\nAction: ");
        scanf("%d", &action);
        if (action == 1)        attack(&player1, &player2);
        else if (action == 2)
        {
            if (heal(&player1) == 0)    player1_action();
        }
        else                    printf("Invalid choice.\n");
    }

    if (player2.health <= 0) win(&player1);
    else                    player2_action();
}

void player2_action()
{
    int action = 0;
    while ((action != 1) && (action != 2))
    {
        printf("Player 2's Turn.\n\nChoose an action:\n\t1. Attack\n\t2. Heal\nAction: ");
        scanf("%d", &action);
        if (action == 1)        attack(&player2, &player1);
        else if (action == 2)
        {
            if (heal(&player2) == 0)    player2_action();
        }
        else                    printf("Invalid choice.\n");
    }

    if (player1.health <= 0) win(&player2);
    else                    intro();
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


int win(struct stats *character)
{
    char ans;
    printf("\nCongratulations. %s has won.\n\n", character->name);

    next_round:
    printf("Play another round? (Y/N)\n\n");
    scanf("%c", &ans);
    if (ans == 'Y' || ans == 'y')
    {
        reset(&player1, &player2);
        intro();
    }
    else if (ans == 'N' || ans == 'n')  exit(1);
    else
    {
        printf("Invalid response.\n\n");
        goto next_round;
    }
}

int intro()
{
    printf("\n\nPlayer 1 Statistics:\nHealth: %d\nHeal Potions:%d\n\nPlayer 2 Statistics:\nHealth: %d\nHeal Potions: %d\n\n", player1.health, player1.heal_potion, player2.health, player2.heal_potion);
    //line above temporary
    player1_action();
}

int main()
{
    printf("Welcome to Z-Dork.\n\n");
    int gdriver = DETECT, gmode;
    initgraph (&gdriver, &gmode, NULL);
    initwindow(1280, 960);                  //graphics window size
    player_names();
    health_bar1(100);
    health_bar2(100);
    intro();
}
