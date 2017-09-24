#ifndef Game_Interactions
#define Game_Interactions 1

#ifndef stdio 
#define stdio 1
#include <stdio.h>
#endif

#include "TowerCrawl.h"
//gameInteractions.c
void drawEncounters(struct Player *, struct Sprite *);
void gameLogic(struct Player*, struct Sprite* Monster, enum PlayerChoice);
void MonsterAction(struct Player*, struct Sprite*);

#endif