#include"MinesweeperImpl.h"

int myFloor(double x){
	int i;
	for(i=0;i<=x;i++);
	return i-1;
}

int main(){
	int grid_size=0;
	
	int option;
	
	do{
		system("clear");
		printf("\t WELCOME TO MINESWEEPER \n");
		printf("\n \tPlease make your choice \n");
		printf("\n \t[1]Start New Game\n \t[0]Exit ");
		printf("\n \tYour choice: ");scanf("%d",&option);
	
		if(option==1){
			printf("\n \tEnter grid size ");scanf("%d",&grid_size);
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
					if(mine_position[i][0]==mine_position[j][0] && mine_position[i][1]==mine_position[j][1]){
						i--;
					}
				}
			}
			
			Grid grid;	
			grid.control=(Cell*)malloc(sizeof(Cell));
			grid.grid_size=grid_size;
			
			grid.control=createGrid(grid.control,grid.grid_size);
		
			grid.control=populateGrid(grid.control,grid.grid_size,mine_position,no_mine);
			
			displayEmptyGrid(grid.control,grid.grid_size);
			system("clear");
			
			for(int i=0;i<4;i++){
				printf("\n \tLoading Game meta data: ");
				if(i==0){
					printf("Start\n \t");
					printf("Loading Game meta data: ######");
				}
				if(i!=0)
					printf("######");
				if(i==3)
					printf("\n \tDone\n");
				sleep(1);
				
			}
			system("clear");
			
			int attempts[100][2];
			int attempt_index=-1;
			
			attempts[attempt_index][0]=0;
			attempts[attempt_index][1]=0;
			
			while(attempts[attempt_index][0]!=-1&&attempts[attempt_index][1]!=-1){
				
				//All cells except mines uncovered
				if(attempt_index==((grid.grid_size*grid.grid_size)-no_mine-1))
					break;
					
				
				system("clear");
				
				printf("\n \tTo Exit And View Solution, Enter -1 -1\n ");			
				
				//Display Current Status of grid
				displayCurrentGrid(grid.control,grid_size,attempts,attempt_index);
				
				//User attempt
				
				do{
					printf("\n \tEnter cell coordinates to uncover ");
				
					++attempt_index;
					scanf("%d",&attempts[attempt_index][0]);
					scanf("%d",&attempts[attempt_index][1]);
					
					if(attempts[attempt_index][0]<1||attempts[attempt_index][1]<1||attempts[attempt_index][0]>grid_size||attempts[attempt_index][1]>grid_size){
						attempt_index--;
						if(attempts[attempt_index+1][0]==-1||attempts[attempt_index+1][1]==-1){
							attempt_index++;
							break;
						}
						printf("\n \tIndex out of bounds. Re-enter \n");
					}
					
				}while(attempts[attempt_index][0]<1||attempts[attempt_index][1]<1||attempts[attempt_index][0]>grid_size||attempts[attempt_index][1]>grid_size);
				
				int solution=0;
				
				if(attempts[attempt_index][0]!=-1&&attempts[attempt_index][1]!=-1){	
					//displayCurrentGrid(grid.control,grid.grid_size,attempts,attempt_index);
					Cell *tmp=grid.control;
					tmp=tmp->right;
					
					printf("\t  ");
					//Column Indices
					for(int i=0;i<grid.grid_size;i++)
						printf("  %d ",i+1);
					printf("\n");
					printf("\t  ");
					for(int i=0;i<grid.grid_size;i++)
						printf("____");
					printf("\n");
					
					
					for(int i=0;i<grid.grid_size;i++){

						printf("\t");
						//Row index
						printf("%d |",i+1);

						for(int j=0;j<grid.grid_size&&!solution;j++){
							int flag=0;
							for(int a=0;a<=attempt_index&&!solution;a++){
								
								flag=0;
								if(attempts[a][0]==i+1&&attempts[a][1]==j+1){
									
									tmp=grid.control;
									tmp=tmp->right;
									flag=1;
									for(int k=1;k<=i;k++)
										tmp=tmp->bottom;
									for(int k=1;k<=j;k++)
										tmp=tmp->right;

									//Content of Cell
									if(tmp->content=='M'){
										printf(" %c |",tmp->content);
										solution=1;
										break;
									}
									else{
										printf(" %d |",tmp->no_mines);
									}
									break;
								}
							}
							if(flag==0){
								
									printf("   |");
							}
							
						}
						
						printf("\n");
						printf("\t  ");

						//Successive row demarcation
						for(int k=0;k<grid.grid_size;k++)
							printf("____");
						printf("\n");
					}
					//End
				}
				
				if(solution){
					system("clear");
					printf("\n \tSOLUTION:\n\n");
					displayGrid(grid.control,grid.grid_size);
					printf("\n \tYOU LOST!!!GAME OVER :(\n");
					sleep(2);
					exit(0);
				}
				
				if(attempts[attempt_index][0]==-1||attempts[attempt_index][1]==-1){
					system("clear");
					printf("\n \tSOLUTION:\n\n");
					displayGrid(grid.control,grid.grid_size);
					printf("\n \tGAME TERMINATED :/\n");
					sleep(2);
					exit(0);
				}
					
			}
			if(attempt_index==(grid_size*grid_size-no_mine-1)){
				system("clear");
				displayGrid(grid.control,grid.grid_size);
				printf("\n \tCONGRATULATIONS!!! YOU HAVE COMPLETED THE GAME :D\n");
				sleep(2);exit(0);
			}
			
		}
		else if(option!=0){
			printf("\n \tInvalid option");
		}
		else;
	}while(option);
}
		
				
				
				
	
