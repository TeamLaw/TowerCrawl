#ifndef TOWERCRAWL_H_
#define TOWERCRAWL_H_

struct Entity
{
	COORD coord;//X Y coordinate location in room
	char marker;//char displayed on screen for the entity
	int row;//Horizontal location on floor
	int col;//Vertical location on floor
	int floorLoc;//Floor location in tower
	int health;//Current health
	int maxHealth;//Max health
	int damage;//attack power
	int typeCheck;//determines the type of entity (-1 = chest, 0 = normal mob, 1 = boss)
};

struct Room
{//One enemy per room
	int xSize;
	int ySize;
	int nDoor;
	int sDoor;
	int eDoor;
	int wDoor;
	struct Entity enemy;
};

struct Floor
{//Hardcoded 3x3 rooms for the floor
	struct Room rooms[3][3];
	struct Entity chest;
};

struct Tower
{//Hardcoded 7 floors
	struct Floor floors[7];
};

int checkPlayerPos(int, int);
void drawRoom();
void drawHealth();
void playerMove();
void createEntities(struct Room *, int);
void createPlayer();
void createRooms();
void enemyMove();
void drawEntities(int, int, struct Entity *);
void moveCursor(int, int);
int randomNum(int, int);//accepts min and max integer and returns: min <= num < max

#endif

