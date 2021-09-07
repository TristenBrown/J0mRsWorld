#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct _Character
{
  // Stats
  int strength;
  int intelligence;
  int health;

  // Race
  char race[64];
  
  // Class 
  char Class[64];

  // Save Info
  char charname[256];
  char playername[256];
} Character;

// Functions
void chooseRace(Character * char1);

void chooseClass(Character * char1);

void setStats(Character * char1, int strength, int intelligence, int health);

void firstScenario();

int dungeon1(Character * char1);

int dragonFight(Character * char1);
void dragonTurn(int *);

int dungeon2(Character * char1);

int poisonFight(Character * char1);
void poisonTurn(int *);

int dungeon3(Character * char1);

int mimicFight(Character * char1);
void mimicTurn(int *);

void dungeon4();

int necromancerFight(Character * char1);
void necromancerTurn(int *);

void dungeon5();

int charTurn(int *, Character * char1);
void heavyAttack(int *);
void lightAttack(int *);

void input(int *);
void stringInput(char *);
void blue();
void green();
void reset();

char *decrypt(char in[], char *passphrase);

//global variable for weapon upgrade
int damageBoost = 0;

int main(void) 
{
  Character character = {0, 0, 0, "", "", "", ""};
  //printf("\033[1m");
 // printf("***** Disclaimer: Throughout the course of this adventure, please do NOT TYPE SPACES!!!!! If you do, you deserve everything coming to you!!! *****\n\n");
  //reset();
  puts("Welcome adventurer! Please tell us a little about yourself.");
  printf("What is your name? \n");
  //printf("\033[1m");
  //printf("(Please do not use spaces!)\n");
 // reset();
  stringInput(character.charname);
  chooseRace(&character);
  chooseClass(&character);
  printf("\nWelcome %s! You are a %s %s\n", character.charname, character.race, character.Class);
  printf("As a %s, your stats are\n\tStrength: %d\n\tIntelligence: %d\n\tHealth: %d\n", character.Class, character.strength, character.intelligence, character.health);
  firstScenario();
  if(dungeon1(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has died. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  srand(time(NULL));
  if(dragonFight(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s was slain by the dragon. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  if(dungeon2(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has died. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  if(poisonFight(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has perished to the posion and the mysterious figure. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  if(dungeon3(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has died to the mimic's bite. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  if(mimicFight(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has died, with their body being eaten by the mimic. They lived a wonderful life. Feel free to play again!", character.charname); 
    return 0;
  }
  dungeon4();
  if(necromancerFight(&character) == 0)
  {
    printf("\033[7;31m");
    printf("Oh no! It seems like %s has died, overrun by skeletons. Maybe one day their body will decompose, and join the ranks of the skeletons. They lived a wonderful life. Feel free to play again!", character.charname);
    return 0;
  }
  dungeon5();
}

void chooseRace(Character *char1)
{
  char * choices[4] = {"Human", "Dwarf", "Elf", "Goblin"};

  MENU:printf("Please choose a race from the following list:\n");
  printf("\t1. Human\n\t2. Dwarf\n\t3. Elf\n\t4. Goblin\n");

  char choiceString[20] = "";
  int choice = -1;
  input(&choice);

  if (choice > 4 || choice < 1)
  {
    printf("Bad Input! Please try again!\n");
    goto MENU;
  }
  else
  {
    switch(choice)
    {
      case 1:
      {
        //strcpy copies the value into the char array
        strcpy(choiceString, "Human");
        puts("Humans are well-rounded and versatile. Is this what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 2:
      {
        strcpy(choiceString, "Dwarf");
        puts("Dwarfs are short and stout, and tend to be rather stubborn. Is this what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 3:
      {
        strcpy(choiceString, "Elf");
        puts("Elves are very graceful and lithe, and tend to enjoy nature. Is this what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 4:
      {
        strcpy(choiceString, "Goblin");
        puts("Goblins are small green creatures, who enjoy causing mischief. Is this what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
    }
    int confirm;
    input(&confirm);
    while(confirm < 1 || confirm > 2)
    {
      puts("Bad Input! Please enter 1 for yes, or 2 for no.");
      input(&confirm);
    }
    if(confirm == 2)
    {
      goto MENU;
    }  
    strcpy(char1->race, choiceString);
  }

  return;
}

void chooseClass(Character *char1)
{
  char * choices[4] = {"Wizard", "Fighter", "Healer", "Ranger"};

  MENU:printf("Please choose a class from the following list:\n");
  printf("\t1. Wizard\n\t2. Fighter\n\t3. Healer\n\t4. Ranger\n");

  char choiceString[20] = "";
  int choice;
  input(&choice);
  choice--;

  if (choice > 3 || choice < 0)
  {
    printf("Bad Input! Please try again!\n");
    goto MENU;
  }
  else
  {
    switch(choice)
    {
      case 0:
      {
        //strcpy copies the value into the char array
        strcpy(choiceString, "Wizard");
        setStats(char1, 5, 10, 20);
        puts("Wizards are capable of using magic to accomplish their goals. They are armed with a quarterstaff and robes, and can use their magic to create a damaging fireball, or a magic barrier to protect themselves. Is that what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 1:
      {
        strcpy(choiceString, "Fighter");
        setStats(char1, 9, 4, 30);
        puts("Fighters are very strong. They are armed with a sword, shield, and chainmail. They can attack with their sword, bash with their shield, and also use their shield to protect themselves. Is that what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 2:
      {
        strcpy(choiceString, "Healer");
        setStats(char1, 5, 8, 25);
        puts("Healers focus on restoring their own health. They are armed with a holy staff and robes. They can attack with their staff, or use their holy magic to smite the enemy or heal themselves. Is that what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
      case 3:
      {
        strcpy(choiceString, "Ranger");
        setStats(char1, 7, 6, 25);
        puts("Rangers prefer to stay at a distance while fighting. They are armed with a bow and arrows, leather armor, and a dagger. They can shoot, dodge away from attacks, or stab with their dagger. Is that what you want to be? (Enter 1 for yes, or 2 for no)");
        break;
      }
    }
    int confirm;
    input(&confirm);
    while(confirm < 1 || confirm > 2)
    {
      puts("Bad Input! Please enter 1 for yes, or 2 for no.");
      input(&confirm);
    }
    if(confirm == 2)
    {
      goto MENU;
    }  
    strcpy(char1->Class, choiceString);
  }
  return;
}

void input(int *Ptr)
{
  printf("\033[0;31m");
  char hold[256];
  scanf(" %[^\n]s",hold);
  int holdint = atoi(hold);
  if(holdint)
  {
    *Ptr = holdint;
  }
  else
  {
    *Ptr = -1;
  }
  printf("\033[0m");
}

void stringInput(char *Ptr)
{ 
  printf("\033[0;31m");
  //printf("we are here\n");
  //fseek(stdin, -2, SEEK_END );
  //fgets(Ptr, 255, stdin);
  scanf(" %[^\n]s", Ptr);
  //printf("Ptr is %s", Ptr);
  //int i;
  //for(i = 0; Ptr[i] != '\0'; i++);
  //Ptr[i - 1] = '\0';
  printf("\033[0m");
  //printf("we get to the end of stringInput\n");
}

void blue()
{
  printf("\033[0;36m");
}

void green()
{
  printf("\033[0;32m");
}

void reset()
{
  printf("\033[0m");
}

void setStats(Character * char1, int strength, int intelligence, int health)
{
  char1->strength = strength;
  char1->intelligence = intelligence;
  char1->health = health;
}

void firstScenario()
{
  printf("Enter 1 to start the game.\n");
  int choice;
  input(&choice);
  while(choice != 1)
  {
    printf("Bad input! Please try again!\n");
    input(&choice);
  }
  char secret1[256] = {"Vvsqzowg vl okmk/ {v{ pwzz jq ~nhtl rw moqf l|lfltfg vl gghzk. hrrpn }lvo zkg juoqy ui ivxh. {nh evrrt vl ykvrhpjk dpk }kgyk wjlxh kz srtl4"};
  char secretanswer[256] = {"Opposite of life, you must go where you find evidence of death, along with the color of gore, the color of violence and where there is more."};
  int response;
  printf("\nYou're staring at the quest postings in the adventurer's guild. You see one that doesn't quite look like the others; where there would normally be a description of the mission, instead there's a riddle:\n");
  blue();
  printf("I give plants their vibrancy, animals their breath, and your eyes something to behold, what am I?\n");
  reset();
  printf("You also notice some strange unreadable symbols that seem to be decipherable. Do you try to read them?\n\t1. Yes\n\t2. No\n");
  input(&response);
  while(response > 2 || response < 1)
  {
    printf("Bad Input! Please try again!\n");
    input(&response);
  }
  {
    if(response == 1)
    {
      printf("You get a headache but are able to discern that the symbols spell out: ");
      blue();
      printf("%s\n", secret1);
      reset();
      int tries = 0;
      char answer[4];

     while(tries < 3)
     {
       if(tries == 0)
       {
          printf("You get the feeling that this secret message requires some sort of password to be deciphered, likely the answer to the riddle. What could it be? (Hint: the password is 4 letters)\n");
       }
       stringInput(answer);
       if(strcmp(answer,"life") == 0 || strcmp(answer,"LIFE") == 0)
       {
         strcpy(answer,"Life");
       }
       
       if(strcmp(decrypt(secret1,answer),secretanswer) == 0)
       {
         break;
       }
       else if(tries < 3)
       {
         printf("That doesn't seem to be the right password. What else would it be?\n");
       }
       else
       {
         printf("You were never very good at riddles, and decide to give up and move on.\n");
         break;
       }
       strcpy(secret1,"Vvsqzowg vl okmk/ {v{ pwzz jq ~nhtl rw moqf l|lfltfg vl gghzk. hrrpn }lvo zkg juoqy ui ivxh. {nh evrrt vl ykvrhpjk dpk }kgyk wjlxh kz srtl4");
       tries++;
     }
     
    }
    else
    {
      printf("You decide not to bother with the weird symbols.\n");
    }
    printf("You take the paper down and notice some writing on the back. It tells you the location of a cave. Being the strong warrior you are, you can't resist a good adventure.\n\t1. Head out on the adventure\n");
    input(&choice);
    while(choice != 1)
    {
     printf("Bad input! Please try again!\n");
     input(&choice);
    }
  }
}

int dungeon1(Character * char1)
{
  printf("You arrive at the cave the paper talked about, realizing it actually appears to be a dungeon. Confident in yourself, you walk into the dungeon. The second you make it all the way inside, an iron gate crashes down behind you, locking you in. Do you try and escape, or continue forward into the dungeon?\n\t1. Try to escape\n\t2. Continue into the dungeon\n");
  int choice;
  input(&choice);
  while(choice < 1 || choice > 2)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  if(choice == 1)
  {
    printf("You run towards the gate, trying to lift it back up, but it's no good. With your strength of %d, even you can't get the gate back open. You have no choice but to venture further into the dungeon.\n\t1. Venture further\n", char1->strength);
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
     input(&choice);
    }
  }
  printf("You look into the dark, and see a staircase leading downwards. With no other choice, you begin to descend. As you go down the stairs, magical torches light up on either side of you. Once you reach the bottom, you find yourself in a small room with three doors.\n\t1. Examine the doors\n");
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  printf("**Door 1 is covered in blood, and the ground in front of it is littered with bones.\n**Door 2 shines with a beautiful golden light.\n**Door 3 is so dark you can hardly make it out next to the dark walls.\n\nYou feel like you have some sort of hint for which door you should pick. Which door will you go through?\n\t1. Door 1\n\t2. Door 2\n\t3. Door 3\n");
 input(&choice);
 while(choice < 1 || choice > 3)
 {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  if(choice == 3)
  {
    printf("You walk up to door 3, and manage to find the knob in the darkness. You open the door to reveal a dark, shadowy place. As you step forward, you realize that there isn't any ground, only a dark abyss.\n\t1. Uh-oh\n");
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(!(strcmp(char1->Class,"Ranger")))
    {
      printf("You use your abilities as a ranger to jump backwards, back into the main room. You breathe a sigh of relief, having avoided almost certain death. You turn back to the other doors, knowing you have to choose one. Which door do you pick now?\n\t1. Door 1\n\t2. Door 2\n");
      input(&choice);
      while(choice < 1 || choice > 2)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
      if(choice == 1)
        goto DOOR1;
      else
        goto DOOR2;
    }
    else
    {
      printf("You try to jump backwards, but you've already lost your footing on the ground behind you. You start to fall into the abyss. You try to turn and grab the edge of the floor behind you, but you just barely miss. Nothing can save you now, as you fall to your death.\n");
      return 0;
    }
  }
  DOOR2: if(choice==2)
  {
    printf("You walk up to door 2, still shining a bright gold. You open the door, and are blinded by how bright it is inside. You immediately notice that it's hot, so hot.\n\t1. This can't be good\n");
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(char1->intelligence > 7){
      printf("With your high intelligence, you realize that somehow, this door led to something as hot as the sun, maybe even the sun itself.");
    }
    else
    {
      printf("Your intelligence isn't high enough to understand what's happening. ");
    }
    printf("Not even a second later, you find yourself vaporized by the heat, now only a pile of ash in front of the door.\n");
    return 0;
  }
  DOOR1: if(choice == 1)
  {
    printf("You walk up to door 1, trying not to step on too many of the bones on the ground. You open the door to find another room up ahead. Stepping forward into the room, you see a skeletal dragon staring right at you. You know that you have no choice but to fight it.\n\t1. Let's go!\n");
    input(&choice);
    while(choice != 1)
    {
       printf("Bad Input! Please try again.\n");
       input(&choice);
    }
    return 1;
  }
  return 1;
}

int dragonFight(Character * char1)
{
  int dragonHealth = 30;
  while(char1->health > 0 && dragonHealth > 0)
  {
    int defendCheck;
    defendCheck = charTurn(&dragonHealth, char1);
    if(dragonHealth > 0)
    {
      if(defendCheck == 1)
      {
        green();
        printf("The dragon tries to attack, but you don't take any damage!\n");
        reset();
      }
      else
      {
        dragonTurn(&char1->health);
      }
    }
  }
  if(char1->health <= 0)
    return 0;
  else
  {
    int choice;
    printf("With that final blow, the dragon lets out a roar and collapses into a pile of bones. He's been defeated!\n\t1. Hooray!\n");
    input(&choice);
    while(choice != 1)
    {
      printf("Bad input! Please try again!\n");
      input(&choice);
    }
    printf("You look around the room, and see a health potion laying in the corner. Do you go drink it?\n\t1. Yes\n\t2. No\n");
    input(&choice);
    while(choice < 1 || choice > 2)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice==1)
    {
      char1->health += 8;
      printf("Tired after your battle, you go and drink the potion, restoring 8 health points. You now have %d health.\n", char1->health);
    }
    else
    {
      printf("Despite being tired and injured, you decide not to drink the health potion. ");
    }
    printf("You take some time to catch your breath, but you know you need to get going soon\n\t1. Continue onward\n");
    input(&choice);
    while(choice != 1)
    {
      printf("Bad input! Please try again!");
      input(&choice);
    }
    return 1;
  }
}

void dragonTurn(int * charHealth)
{
  int move = rand() % 3;
  int damage;
  if(move == 0)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The dragon roars and bites at you with his skeletal teeth, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 1)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The dragon spins around and swings his tail at you, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 2)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The dragon flies up in the air, then tries to slam down on top of you, dealing %d damage.\n", damage);
    reset();
  }
}

int dungeon2(Character * char1)
{
  printf("Looking around the room, you don't see any other doors or passageways. Confused, you go back to the room you were in before, the one with 3 doors. You notice that the 3rd door, which used to be dark and shadowy, now appears to be just a normal door. Do you enter?\n\t1. Yes\n\t2. No\n");
  int choice;
  input(&choice);
    while(choice < 1 || choice > 2)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
  if(choice == 2)
  {
    printf("You don't want to enter the door. Exploring the areas you've been to though, you don't see any other options except for the second door, which glowed with golden light. You must pick one of these two doors if you want to have a hope of escaping. Which door do you choose?\n\t1. The golden door\n\t2. The normal looking door\n");
    input(&choice);
    while(choice < 1 || choice > 2)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      printf("You walk up to door 2, still shining a bright gold. You open the door, and are blinded by how bright it is inside. You immediately notice that it's hot, so hot.\n\t1. This can't be good\n");
      input(&choice);
      while(choice != 1)
      {
       printf("Bad Input! Please try again.\n");
       input(&choice);
      }
      if(char1->intelligence > 7)
      {
        printf("With your high intelligence, you realize that somehow, this door led to something as hot as the sun, maybe even the sun itself. ");
      }
      else
      {
        printf("Your intelligence isn't high enough to understand what's happening. ");
      }
     printf("Not even a second later, you find yourself vaporized by the heat, now only a pile of ash in front of the door.\n");
     return 0;
    }
  }
  printf("You walk up to the now normal looking door, and open it. The new room is a long hallway. The walls seem to be constructed with piles of bones, and torches made of skulls light the path. At the end of the hallway is a door, with a message hastily carved into it.\n\t1. Read it\n");
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  blue();
  printf("\"DON'T BREATHE.\" ");
  reset();
  printf("Immediately, green gas starts to fill the hallway from the far end, which you recognize as poison. You notice a figure in the gas approaching you. You can't let yourself breathe, or else you'll inhale the poison, but you know you have no choice but to fight.\n\t1. Hold your breath and prepare for battle\n");
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  return 1;
}

int poisonFight(Character * char1)
{
  int poisonHealth = 25;
  int turnCount = 0;
  while(char1->health > 0 && poisonHealth > 0 && turnCount < 5)
  {
    ++turnCount;
    int defendCheck;
    defendCheck = charTurn(&poisonHealth, char1);
    if(poisonHealth > 0)
    {
      if(defendCheck == 1)
      {
        green();
        printf("The mysterious figure tries to attack, but you don't take any damage!\n");
        reset();
      }
      else
      {
        poisonTurn(&char1->health);
      }
    }
    if (turnCount == 5)
    {
      printf("You can feel your body breaking. You can't hold your breath any longer--you need to breathe.\n");
      printf("You take a breath, and it is your last. The air you gulp contains a poison unlike any other, and it works instantly.\n");
      return 0;
    }
  }
  if(char1->health <= 0)
    return 0;
  else
  {
    printf("Your last attack seemed to do it, and the mysterious figure disapates into the gas. The gas becomes normal air, and you can finally take a breath.\n\t1. Breathe\n");
    int choice;
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    return 1;
  }
}

void poisonTurn(int *charHealth)
{
  int move = rand() % 3;
  int damage;
  if(move == 0)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The figure hits you with a small vial of acid, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 1)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The figure lashes out with a dagger, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 2)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("You breathe in just a tiny bit of the poison in the air, taking %d damage.\n", damage);
    reset();
  }
}

int dungeon3(Character * char1)
{
  printf("After you recover, you look for a way to move forward. You see the door with the writing and the door you came in from.\n");
  int choice;
  if (char1->intelligence >= 8)
  {
    printf("Your intelligence of %d tells you that the door you came in will be locked, so you must proceed through the other door.\n\t1. Go through the door\n", char1->intelligence);
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
  }
  else
  {
    printf("Choose which door to use:\n");
    printf("\t1. The door you came in\n\t2. The door with the writing\n");
    input(&choice);
    while (choice > 2 || choice < 1)
    {
      printf("Bad input! Please try again!\n");
      input(&choice);
    }
    if(choice==1)
    {
      printf("You walk back to the door you came in from, but when you try to open it, you find out that it's locked. It looks like the only way out is forward, so you must proceed through the door with the writing.\n\t1. Proceed through the door\n");
    }
  }
  printf("The door opens up into a new room, empty except for a treasure chest sitting in the middle. Finally, you've made it to the end! You run up to the chest and crouch down next to it.\n\t1. Open it excitedly\n\t2. Open it cautiously\n");
  input(&choice);
  printf("You open the treasure chest, ready to see what's inside. Instead, as soon as you open it, you see teeth and the chest bites you, dealing 2 damage! It turns out this wasn't a treasure chest at all, but a mimic! You'll have to fight it to keep going.\n\t1. Here we go again\n");
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  char1->health -= 2;
  if(char1->health <= 0)
    return 0;
  return 1;
}

int mimicFight(Character * char1)
{
  int mimicHealth = 20;
  while(char1->health > 0 && mimicHealth > 0)
  {
    int defendCheck;
    defendCheck = charTurn(&mimicHealth, char1);
    if(mimicHealth > 0)
    {
      if(defendCheck == 1)
      {
        green();
        printf("The mimic tries to attack, but you don't take any damage!\n");
        reset();
      }
      else
      {
        mimicTurn(&char1->health);
      }
    }
  }
  if(char1->health <= 0)
    return 0;
  else
  {
    printf("Your last attack hits hard, and the mimic falls back to the ground, motionless.\n");
    printf("Looking around the room, you see another health potion laying on the ground, and something poking out from underneath a pile of bones in a corner of the room.\n\t1. Go drink the health potion\n\t2. Go investigate the pile of bones\n");
    int choice;
    int response = 0;
    input(&choice);
    while(choice < 1 || choice > 2)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      char1->health += 13;
      printf("You walk over to the health potion lying on the ground. It seems stronger than the last one you found. You pick it up, and quickly drink every last drop, regaining 13 health points. You now have %d health.\n\t1. That feels much better\n", char1->health);
      int answer;
      input(&answer);
      while(answer != 1)
      {
        printf("Bad Input! Please try again.\n");
        input(&answer);
      }
      printf("There is a door leading farther into the dungeon. Do you go through it, or go investigate the pile of bones?\n\t1. Go through the door\n\t2. Go investigate the pile of bones\n");
      input(&response);
      while(response < 1 || response > 2)
      {
        printf("Bad Input! Please try again.\n");
        input(&response);
      }
    }
    if(choice==2 || response == 2)
    {
      printf("You walk over to the pile of bones, and kick enough of them out of the way to see what's underneath. It looks to be an improved version of your weapon. Do you swap the weapon you're using now for the new, better one?\n\t1. Yes\n\t2. No\n");
      input(&choice);
      while(choice < 1 || choice > 2)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
      if(choice == 1)
      {
        printf("You swap out your weapon for the new one. Your attacks now all do an extra 2 damage.\n");
        damageBoost = 2;
      }
      else
      {
        printf("While the prospect of a new weapon is exciting, you decide to stick with what you have and move on.\n");
      }
      if(response == 0)
      {
        printf("There is a door leading farther into the dungeon. Do you go through it, or go drink the health potion?\n\t1. Go through the door\n\t2. Go drink the health potion\n");
        input(&choice);
        while(choice < 1 || choice > 2)
        {
          printf("Bad Input! Please try again.\n");
          input(&choice);
        }
        if(choice==2)
        {
          char1->health += 13;
          printf("You walk over to the health potion lying on the ground. It seems stronger than the last one you found. You pick it up, and quickly drink every last drop, regaining 13 health points. You now have %d health.\n\t1. That feels so much better\n", char1->health);
          int answer;
         input(&answer);
          while(answer != 1)
          {
            printf("Bad Input! Please try again.\n");
           input(&answer);
          }
        }
      }
    }
    return 1;
  }
}

void mimicTurn(int * charHealth)
{
  int move = rand() % 3;
  int damage;
  if(move == 0)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The mimic bites you, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 1)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The mimic's long tounge reaches out and lashes your face, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 2)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The mimic jumps forward and lands on your toes, dealing %d damage.\n", damage);
    reset();
  }
}

void dungeon4()
{
  printf("You walk up to the door, and push it open with a sigh. Doesn't this dungeon ever end? A spiral staircase takes you downwards, into a poorly lit chamber. The few lights flicker, and then die out. A second later, the candles roar back to life, brighter than before.\n\t1. Look around\n");
  int choice;
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  printf("You look around, revealing that the walls of the chamber are made of skeletons, some of which are starting to walk towards you. With each skeleton, the walls become weaker. You start to panic, but notice a hooded figure in the corner. He must be the necromancer controlling the skeletons. You understand that you need to take him out before the walls collapse.\n\t1. Let's get this over with\n");
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
}

int necromancerFight(Character * char1)
{
  int necromancerHealth = 30;
  int skeletonsHealth = 30;
  while(char1->health > 0 && necromancerHealth > 0 && skeletonsHealth > 0)
  {
    int defendCheck;
    int choice;
    MENU:printf("Choose a target for your turn:\n");
    printf("\t1. Necromancer\n\t2. Skeletons\n");
    input(&choice);
    if (choice < 1 || choice > 2)
    {
      printf("Bad input! Please try again!\n");
      goto MENU;
    }
    if (choice == 1)
    {
      defendCheck = charTurn(&necromancerHealth, char1);
      if(necromancerHealth > 0)
      {
        if(defendCheck == 1)
        {
          green();
          printf("The necromancer and his skeletons try to attack, but you don't take any damage!\n");
          reset();
        }
        else
        {
          necromancerTurn(&char1->health);
        }
      }
    }
    else
    {
      defendCheck = charTurn(&skeletonsHealth, char1);
      if(skeletonsHealth > 0)
      {
        printf("The skeleton you hit falls to the ground, but more come to take it's place.\n");
        if(defendCheck == 1)
        {
          green();
          printf("The necromancer and his skeletons try to attack, but you don't take any damage!\n");
          reset();
        }
        else
        {
          necromancerTurn(&char1->health);
        }
      }
    }
  }
  if(char1->health <= 0)
    return 0;
  else if(skeletonsHealth <= 0)
  {
    printf("As you take out another skeleton, more crawl forward from the walls. There aren't enough skeletons left at this point to continue supporting the room, and the walls start to crumble. You don't have enough time to escape, and are crushed by the ceiling as it caves in.\n");
    return 0;
  }
  else
  {
    printf("Your last attack shatters the necromancer's skull, and all the enemies crumble into dust. The walls that were crumbling have stabilized, and the room is safe.\n\t1. Awesome!\n");
    int choice;
    input(&choice);
    while(choice != 1)
    {
      printf("Bad Input! Please try again.\n");
     input(&choice);
    }
    return 1;
  }
}

void necromancerTurn(int *charHealth)
{
  int move = rand() % 3;
  int damage;
  if(move == 0)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("The necromancer levels his staff at you, shooting a bolt of energy that deals %d damage.\n", damage);
    reset();
  }
  if(move == 1)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("A skeleton walks up to you and hits you in the back of the head, dealing %d damage.\n", damage);
    reset();
  }
  if(move == 2)
  {
    damage = rand() % 3 + 1;
    *charHealth -= damage;
    green();
    printf("3 skeletons come up on all sides of you and take a poke at you, dealing %d damage.\n", damage);
    reset();
  }
}

void dungeon5()
{
  printf("A doorway opens before you. Inside is a chest overflowing with precious gems and metals, making a small fortune! This is certainly the reward for completing the dungeon!\n\t1. Escape with the treasure\n");
  int choice;
  input(&choice);
  while(choice != 1)
  {
    printf("Bad Input! Please try again.\n");
    input(&choice);
  }
  printf("You drag the chest all the way up to the top of the dugeon, now that the doors have all been opened. You escape into the beautiful morning air!\n\n");
  printf("\033[1;33m");
  printf("CONGRATULATIONS!!!!!!\nYou have completed the game!\nRest now, you've earned it!\n");
}

int charTurn(int * enemyHealth, Character * char1)
{
  printf("It's your turn to act!\n");
  int choice;
  MENU: if(!(strcmp(char1->Class,"Wizard")))
  {
    printf("\t1. What do my attacks do?\n\t2. Attack with staff\n\t3. Attack with fireball\n\t4. Defend with magic barrier\n\t5. How much health do I have left?\n");
    input(&choice);
    while(choice < 1 || choice > 5)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      WIZMENU: printf("Attack with staff does 3-5 damage. Attack with fireball does 6-8 damage. Defend with magic barrier prevents you from taking damage this turn.\nWhat would you like to do?\n");
      input(&choice);
      if(choice == 1)
        goto WIZMENU;
      while(choice < 2 || choice > 5)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
    }
    if(choice == 2)
    {
      printf("You attack with your staff!");
      lightAttack(enemyHealth);
      return 0;
    }
    if(choice == 3)
    {
      printf("You attack with fireball!");
      heavyAttack(enemyHealth);
      return 0;
    }
    if(choice == 4)
    {
      printf("You defend using magic barrier!\n");
      return 1;
    }
  }
  if(!(strcmp(char1->Class,"Fighter")))
  {
    printf("\t1. What do my attacks do?\n\t2. Attack with sword\n\t3. Attack with shield bash\n\t4. Defend with shield\n\t5. How much health do I have left?\n");
    input(&choice);
    while(choice < 1 || choice > 5)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      FIGHTMENU: printf("Attack with sword does 6-8 damage. Attack with shield bash does 3-5 damage. Defend with shield prevents you from taking damage this turn.\nWhat would you like to do?\n");
      input(&choice);
      if(choice == 1)
        goto FIGHTMENU;
      while(choice < 2 || choice > 5)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
    }
    if(choice == 2)
    {
      printf("You attack with your sword!");
      heavyAttack(enemyHealth);
      return 0;
    }
    if(choice == 3)
    {
      printf("You attack with shield bash!");
      lightAttack(enemyHealth);
      return 0;
    }
    if(choice == 4)
    {
      printf("You defend using your shield!\n");
      return 1;
    }
  }
  if(!(strcmp(char1->Class,"Healer")))
  {
    printf("\t1. What do my attacks do?\n\t2. Attack with holy staff\n\t3. Attack with divine smite\n\t4. Heal\n\t5. How much health do I have left?\n");
    input(&choice);
    while(choice < 1 || choice > 5)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      HEALMENU: printf("Attack with holy staff does 3-5 damage. Attack with divine smite does 6-8 damage. Heal heals any damage you take this turn.\nWhat would you like to do?\n");
      input(&choice);
      input(&choice);
      if(choice == 1)
        goto HEALMENU;
      while(choice < 2 || choice > 5)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
    }
    if(choice == 2)
    {
      printf("You attack with your holy staff!");
      lightAttack(enemyHealth);
      return 0;
    }
    if(choice == 3)
    {
      printf("You attack with divine smite!");
      heavyAttack(enemyHealth);
      return 0;
    }
    if(choice == 4)
    {
      printf("You heal yourself!\n");
      return 1;
    }
  }
  if(!(strcmp(char1->Class,"Ranger")))
  {
    printf("\t1. What do my attacks do?\n\t2. Attack with bow\n\t3. Attack with dagger\n\t4. Dodge\n\t5. How much health do I have left?\n");
    input(&choice);
    while(choice < 1 || choice > 5)
    {
      printf("Bad Input! Please try again.\n");
      input(&choice);
    }
    if(choice == 1)
    {
      RANGEMENU: printf("Attack with bow does 6-8 damage. Attack with dagger does 3-5 damage. Dodge prevents you from taking damage this turn.\nWhat would you like to do?\n");
      input(&choice);
      if(choice == 1)
        goto RANGEMENU;
      while(choice < 2 || choice > 5)
      {
        printf("Bad Input! Please try again.\n");
        input(&choice);
      }
    }
    if(choice == 2)
    {
      printf("You attack with your bow!");
      heavyAttack(enemyHealth);
      return 0;
    }
    if(choice == 3)
    {
      printf("You attack with your dagger!");
      lightAttack(enemyHealth);
      return 0;
    }
    if(choice == 4)
    {
      printf("You dodge the enemy!\n");
      return 1;
    }
  }
  if(choice == 5)
  {
    printf("You have %d health remaining\n", char1->health);
    goto MENU;
  }
  return 0;
}

void heavyAttack(int *enemyHealth)
{
  int damage = 6 + (rand() % 3) + damageBoost;
  *enemyHealth -= damage;
  printf(" You deal %d damage.\n", damage);
}

void lightAttack(int *enemyHealth)
{
  int damage = 3 + (rand() % 3) + damageBoost;
  *enemyHealth -= damage;
  printf(" You deal %d damage.\n", damage);
}

char *decrypt(char in[], char * passphrase)
{
  char *cPtr = in;
  int pIndex = 0;

  while(*cPtr != '\0')
  {
    if(*cPtr != ' ' && *cPtr != '\n' && *cPtr != '\t' && *cPtr != '\a' && *cPtr != '\b')
    {
      if(passphrase[pIndex] == ' ')
      {
        pIndex++;
      }
      unsigned c = *cPtr - (passphrase[pIndex] % 10) - 1; 
      if(c < 33)
      {
        c = c + 127 - 33;
      }

      *cPtr = c;
      pIndex++;

      if(passphrase[pIndex] == '\0')
      {
        pIndex = 0;
      }
    }
    cPtr++;
  }
  printf("Using that code, the deciphered message says: ");
  blue();
  printf("%s\n",in);
  reset();
  return in;
}