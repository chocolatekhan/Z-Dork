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
}player1, player2;


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
void playername();
void endgame();


int main()
{
    int gdriver = DETECT, gmode;
    initgraph (&gdriver, &gmode, NULL);
    initwindow(1280, 960);                  //graphics window size
    //readimagefile("Images/Logo.jpg", 0, 80, 1280, 720); //initial logo
    //delay(2000);
    //cleardevice();
    menu();
}

void menu()         //main menu
{
    int pos = 1;    //gives position of selected text (for red coloring)
    cleardevice();
    mainmenu(pos);  //custom graphics function that changes color of text to indicate selection

    int choice;
    for ( ; ; )
    {
        choice = getch();
        if (choice == 0 || choice == 224)       //arrow keys give two values
        {
            choice = getch();

            if (choice == 72)                   //change value of pos based on second value
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
        else if (choice == 13)                  //if enter key is pressed, run function based on current pos value
        {
            if (pos == 1)   playername();
            else if (pos == 2)  display_scores();
            else if (pos == 3)  exit(1);
        }
    }
}

void display_scores()               //high score display screen
{
    int a = 0, j = 0;
    char b;
    cleardevice();
    esc();
    char msg[1000];
    sprintf(msg, "HIGH SCORES");
    highscores(a, 0, msg);
    a++;
    sprintf(msg, "");               //line gap
    highscores(a, 0, msg);

    FILE *scores;

    if ((scores = fopen("userdata", "r")) == NULL)          //if no file exists, display message
    {
        a++;
        sprintf(msg, "No high scores yet!");
        highscores(a, 0, msg);

        while (b != 27) b = getch();                    //until ESC key is pressed, keep getting characters
        menu();
    }

    char temp[1000];
    int i;

    for ( ; ; )
    {
        a++;
        for (j = 0; j < 4; j++)
        {
			for (i = 0; ; i++)                          //store characters one by one until new line or EOF reached
			{
				b = fgetc(scores);
				if (b != EOF)   b = b - 2;              //decryption
				if (b == '\n' || b == EOF)    break;
				else    temp[i] = b;                    //store each character in temporary string
			}
			temp[i] = '\0';
			highscores(a, j, temp);
			//send string to custom graphics function along with integers to display in different positions of screen
			//a indicates y axis position for different lines
			//j indicates x axis position for different parts of same line (like pressing tab key)

			if (b == EOF) break;
        }
        if (b == EOF) break;
        b = fgetc(scores);  //to get line gap between two sets of scores
    }

    fclose(scores);

    while (b != 27) b = getch();    //keep getting characters until ESC key is pressed
    menu();
}

void playername()
{
    cleardevice();
    char player_name[1000];

    int i;
    getname(-1);

    for (i=0; i<1000; i++)
    {
        player_name[i] = getname(i);

        if (player_name[i] == 13)
        {
            if (i == 0)    i--;
            else
            {
                player_name[i] = '\0';
                break;
            }
        }
        else if (player_name[i] == 8)   i -= 2;
        if (i < 0)  i = 0;
    }
    strcpy(player1.name, player_name);

    cleardevice();

    getplayer2name:

    getname(-2);

    for (i=0; i<1000; i++)
    {
        player_name[i] = getname(i);

        if (player_name[i] == 13)
        {
            if (i == 0)    i--;
            else
            {
                player_name[i] = '\0';
                break;
            }
        }
        else if (player_name[i] == 8)   i -= 2;
        if (i < 0)  i = 0;
    }

    if (strcmp(player_name, player1.name) == 0)             //having same name causes errors
    {
        cleardevice();
        highscores(3, 0, "Name already taken by Player 1!");    //using high score function just for position of text
        delay(2000);
        cleardevice();
        goto getplayer2name;
    }

    strcpy(player2.name, player_name);

    player1.score = 0;
    player2.score = 0;
    reset();
}

int reset()                                             //reset all statistics and images
{
    player1.health = 100;
    player1.heal_potion = 5;
    player2.health = 10;
    player2.heal_potion = 5;
    cleardevice();
    round(player1.score+player2.score+1);
    char msg[1000];
    sprintf(msg, "Images/Default Image Left.bmp");
    image_left(msg);
    sprintf(msg, "Images/Default Image Right.bmp");
    image_right(msg);
    scorebar(player1.score, player2.score);
    player_names(player1.name, player2.name);
    health_bar1(100);
    health_bar2(100);
    heal_potion1(5);
    heal_potion2(5);
    if (player1.score + player2.score == 0)         //display instructions on only first round
    {
        text_left("Player 1's instructions");
        delay(2000);
        text_left("");
        text_left("will be displayed here.");
        delay(2000);
        text_left("");
        text_right("Player 2's instructions");
        delay(2000);
        text_right("");
        text_right("will be displayed here.");
        delay(2000);
        text_right("");
    }
    player1_action();
}

void player1_action()
{
    int action = 0;
    char msg[1000];
    while ((action != 1) && (action != 2))                      //keep getting characters until 1 or 2 is pressed
    {
        sprintf(msg, "Player 1's Turn");
        text_left(msg);
        sprintf(msg, "");
        text_right(msg);
        delay(2000);
        sprintf(msg, "Choose an action:");
        text_left(msg);
        delay(2000);
        sprintf(msg, "1. Attack   2. Heal");
        text_left(msg);
        action = getch() - '0';
        if (action == 1)        attack(&player1, &player2);
        else if (action == 2)
        {
            if (heal(&player1) == 0)    player1_action();
        }
        else
        {
            sprintf(msg, "Invalid choice");
            text_left(msg);
            delay(2000);
        }
    }

    if (player2.health <= 0)    win(&player1);              //if at end of action, player 2 is dead, go to win
    else                        player2_action();
}

void player2_action()
{
    int action = 0;
    char msg[1000];
    while ((action != 1) && (action != 2))
    {
        sprintf(msg, "Player 2's Turn");
        text_right(msg);
        sprintf(msg, "");
        text_left(msg);
        delay(2000);
        sprintf(msg, "Choose an action:");
        text_right(msg);
        delay(2000);
        sprintf(msg, "1. Attack   2. Heal");
        text_right(msg);
        action = getch() - '0';
        if (action == 1)        attack(&player2, &player1);
        else if (action == 2)
        {
            if (heal(&player2) == 0)    player2_action();
        }
        else
        {
            sprintf(msg, "Invalid choice");
            text_right(msg);
            delay(2000);
        }
    }

    if (player1.health <= 0)    win(&player2);
    else                        player1_action();
}

void attack (struct stats *character1, struct stats *character2)
{
    int char1_attack, char2_dodge;
    char msg[1000];
    if (strcmp(character1->name, player1.name) == 0)            //get player choices first
    {
        sprintf(msg, "Choose a weapon:");
        text_left(msg);
        delay(2000);
        sprintf(msg, "1. Sword   2. Dagger");
        text_left(msg);
        char1_attack = getch() - '0';
        sprintf(msg, "");
        text_left(msg);
        sprintf(msg, "Player 1 attacked!");
        text_right(msg);
        delay(2000);
        sprintf(msg, "Try to dodge!");
        text_right(msg);
        delay(2000);
        text_right("1. Jump   2. Duck");
        char2_dodge = getch() - '0';

        if (char1_attack == 1)  image_left_attack_high();       //then show images based on choices
        else                    image_left_attack_low();

        if (char2_dodge == 1)   image_right_jump();
        else                    image_right_duck();

        if (char1_attack == char2_dodge)                        //if both go in same direction, damage caused
        {
            damage(character2);
            text_right("You failed to dodge.");
            if (character2->health != 0)    delay(2000);
        }
        else
        {
            text_right("You dodged.");
            delay(2000);
        }
    }
    else                                                        //same code for player 2's side
    {
        text_right("Choose a weapon:");
        delay(2000);
        text_right("1. Sword  2. Dagger");
        char1_attack = getch() - '0';
        text_right("");
        text_left("Player 2 attacked!");
        delay(2000);
        text_left("Try to dodge!");
        delay(2000);
        text_left("1. Jump   2. Duck");
        char2_dodge = getch() - '0';

        if (char1_attack == 1)  image_right_attack_high();
        else                    image_right_attack_low();
        delay(500);
        if (char2_dodge == 1)   image_left_jump();
        else                    image_left_duck();
        delay(500);
        image("Images/Default Image.bmp");

        if (char1_attack == char2_dodge)
        {
            damage(character2);
            //bug made player images disappear when player 1 jumped; short fix
            readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
            readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
            text_left("You failed to dodge.");
            if (character2->health != 0)  delay(2000);
        }
        else
        {
            //bug made player images disappear when player 1 jumped; short fix
            readimagefile("Images/Default Image Left.bmp", 100, 210, 400, 790);
            readimagefile("Images/Default Image Right.bmp", 850, 210, 1150, 790);
            text_left("You dodged.");
            delay(2000);
        }
    }
}

void damage(struct stats *character)                                       //reduces character health and changes health bar
{
    character->health -= 10;
    if (strcmp(character->name, player1.name) == 0)   health_bar1(character->health);
    else                                            health_bar2(character->health);
}

int heal(struct stats *character)                   //checks character health; if low, updates health and changes health bar
{
    if (character->health == 100)
    {
        if (strcmp(character->name, player1.name) == 0)  text_left("Health already full.");
        else                                            text_right("Health already full.");
        delay(2000);
        return 0;
    }
    else if (character->heal_potion == 0)
    {
        if (strcmp(character->name, player1.name) == 0)  text_left("Out of Heal Potions.");
        else                                            text_right("Out of Heal Potions.");
        delay(2000);
        return 0;
    }
    else
    {
        if (character->health > 90)    character->health = 100;
        else                           character->health += 10;
        character->heal_potion--;
        if (strcmp(character->name, player1.name) == 0)
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


int win(struct stats *character)                    //win screen images and text
{
    int error = 0;
    char ans;

    if (strcmp(character->name, player1.name) == 0)
    {

        image_right_dead();
        delay(500);
        image_left_win();
        image_left_win();
        text_right("");
        text_left("Congratulations!");
        delay(2000);
        text_left("You won!");
    }
    else
    {
        image_left_dead();
        delay(500);
        image_right_win();
        image_right_win();
        text_left(" ");
        text_right("Congratulations!");
        delay(2000);
        text_right("You won!");
        delay(2000);
    }

    character->score++;                                 //update score and score bar
    scorebar(player1.score, player2.score);

    next_round:
    if (strcmp(character->name, player1.name) == 0)   text_left("Play again? (Y/N)");
    else                                            text_right("Play again? (Y/N)");
    ans = getch();
    if (ans == 89 || ans == 121)       reset();
    else if (ans == 78 || ans == 110)  endgame();
    else
    {
        if (error == 0)                                 //invalid choice text was printing automatically once; short fix
        {
            error = 1;
            goto next_round;
        }
        if (strcmp(character->name, player1.name) == 0)   text_left("Invalid response.");
        else                                            text_right("Invalid response.");
        delay(2000);
        goto next_round;
    }
}

void endgame()                      //if player goes back to main menu
{
    int i;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char text[1000];
    sprintf(text, "%d %d %d\n%d:%d:%d\n%s: %d\n%s: %d\n\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player1.name, player1.score, player2.name, player2.score);
    //store date, time, player names and scores in string

    FILE *scores;
    scores = fopen("userdata", "a");
    for (i=0; i<strlen(text); i++)  fputc(text[i] + 2, scores);
    //print string to external file, increasing each character by 2 (stays within max ASCII value)
    fclose(scores);

    menu();
}
