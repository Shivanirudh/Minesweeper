#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<time.h>


struct Node{
	char content;
	int no_mines;
	struct Node *top_left;
	struct Node *top;
	struct Node *top_right;
	struct Node *left;
	struct Node *right;
	struct Node *bottom_left;
	struct Node *bottom;
	struct Node *bottom_right;
};

typedef struct Node Cell;

typedef struct{
	Cell *control;
	int grid_size;
}Grid;

Cell* createGrid(Cell* control,int grid_size);

Cell* populateGrid(Cell *control,int grid_size,int mine_position[][2],int no_mine);

void displayGrid(Cell *control,int grid_size);

void displayEmptyGrid(Cell *control,int grid_size);

void displayCurrentGrid(Cell* control,int grid_size,int attempts[][2],int attempt_index);
