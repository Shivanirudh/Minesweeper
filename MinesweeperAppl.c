#include"MinesweeperImpl.h"

int myFloor(double x){
	int i;
	for(i=0;i<=x;i++);
	return i-1;
}

int main(){
	int grid_size=0;
	
	printf("Enter grid size ");scanf("%d",&grid_size);
	int no_mine;
	no_mine=myFloor(0.15625*grid_size*grid_size);
	
	int mine_position[100][2];
	
	srand(time(0));
	
	for(int i=0;i<no_mine;i++){
		mine_position[i][0]=rand()%grid_size;
		mine_position[i][1]=rand()%grid_size;
		//mine_position[i][0]=i;
		//mine_position[i][1]=i;
		for(int j=0;j<i;j++){
			if(mine_position[i][0]==mine_position[j][0]&&mine_position[i][1]==mine_position[j][1]){
				i--;
			}
		}
	}
	printf("\n%d\n",no_mine);
	for(int i=0;i<no_mine;i++)
		printf("%d %d\n",mine_position[i][0],mine_position[i][1]);
	
	Cell *control=(Cell*)malloc(sizeof(Cell));
	
	control=createGrid(control,grid_size);
	
	control=populateGrid(control,grid_size,mine_position,no_mine);
	
	displayGrid(control,grid_size);
	
	displayEmptyGrid(control,grid_size);
}
	
		
				
				
				
						
