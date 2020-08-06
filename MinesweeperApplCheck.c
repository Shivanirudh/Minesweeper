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
	
	//control=createGrid(control,grid_size);
	
	for(int i=0;i<grid_size;i++){
		for(int j=0;j<grid_size;j++){
			Cell *c=(Cell*)malloc(sizeof(Cell));
			c->top_left=NULL;c->top=NULL;c->top_right=NULL;
			c->left=NULL;c->right=NULL;
			c->bottom_left=NULL;c->bottom=NULL;c->bottom_right=NULL;
			c->content='\0';c->no_mines=0;
			//Control Connect
			if(i==0&&j==0)
				control->right=c;
			
			//First Row
			if(i==0){
				c->top_left=NULL;c->top=NULL;c->top_right=NULL;
				//First Column
				if(j==0){
					c->left=NULL;c->bottom_left=NULL;
				}
				//Last Column
				if(j==grid_size-1){
					c->right=NULL;c->bottom_right=NULL;
				}
				
				Cell *tmp=control;
				tmp=tmp->right;
				
				//Left
				for(int k=1;k<j;k++)
					tmp=tmp->right;
				if(j!=0){
					tmp->right=c;
					c->left=tmp;
				}
				
				//Right
				c->right=NULL;
				
			}
			//Last Row
			else if(i==grid_size-1){
				c->bottom_left=NULL;c->bottom=NULL;c->bottom_right=NULL;
				
				//First Column
				if(j==0){
					c->left=NULL;c->top_left=NULL;
				}
				
				//Last Column
				if(j==grid_size-1){
					c->right=NULL;c->top_right=NULL;
				}
				
				Cell *tmp=control;
				tmp=tmp->right;
				
				
				for(int k=1;k<grid_size-1;k++)
					tmp=tmp->bottom;
				for(int k=1;k<j;k++)
					tmp=tmp->right;
				//Top Left
				if(j!=0){
					tmp->bottom_right=c;
					c->top_left=tmp;
					tmp=tmp->right;
				}
				
				//Top
				tmp->bottom=c;
				c->top=tmp;
				tmp=tmp->right;
				
				//Top Right
				if(j!=grid_size-1){
					tmp->bottom_left=c;
					c->top_right=tmp;
				}
				
				tmp=control;
				tmp=tmp->right;
				
				for(int k=1;k<=grid_size-1;k++)
					tmp=tmp->bottom;
				for(int k=1;k<j;k++)
					tmp=tmp->right;
				
				//Left
				if(j!=0){
					tmp->right=c;
					c->left=tmp;
				}
				
				//Right
				c->right=NULL;
			}
			//Rows except first and last
			else{
				Cell *tmp=control;
				tmp=tmp->right;
				
				//First Column
				if(j==0){
					c->left=NULL;c->top_left=NULL;c->bottom_left=NULL;
				}
				//Last Column
				if(j==grid_size-1){
					c->right=NULL;c->top_right=NULL;c->bottom_right=NULL;
				}
				
				for(int k=1;k<i;k++)
					tmp=tmp->bottom;
				for(int k=1;k<j;k++)
					tmp=tmp->right;
				
				//Top Left
				if(j!=0){
					tmp->bottom_right=c;
					c->top_left=tmp;
					tmp=tmp->right;
				}
				
				//Top
				tmp->bottom=c;
				c->top=tmp;
				tmp=tmp->right;
				
				//Top Right
				if(j!=grid_size-1){
					tmp->bottom_left=c;
					c->top_right=tmp;
				}
				
				tmp=control;
				tmp=tmp->right;
				
				for(int k=1;k<=i;k++)
					tmp=tmp->bottom;
				for(int k=1;k<j;k++)
					tmp=tmp->right;
				
				//Left
				if(j!=0){
					tmp->right=c;
					c->left=tmp;
				}
				
				//Right
				c->right=NULL;
			}
		}
	}
	
	//control=populateGrid(control,grid_size,mine_position,no_mine);
	
	int mine_ctr=0;
	for(int i=0;i<grid_size;i++){
		for(int j=0;j<grid_size;j++){
			mine_ctr=0;
			
			Cell *pos=control;
			pos=pos->right;
			
			for(int k=1;k<=i;k++)
				pos=pos->bottom;
			for(int k=1;k<=j;k++)
				pos=pos->right;
				
			//Loading Content 
			for(int a=0;a<no_mine;a++){
				if(i==mine_position[a][0]&&j==mine_position[a][1]){
					pos->content='M';
					pos->no_mines=-1;
					break;
				}
				else{
					pos->content='\0';
					pos->no_mines=0;
				}
			}
			
			//if(pos->no_mines!=-1){
				printf("\n%d 1\n",mine_ctr);
				//Top Left
				
				if(pos->top_left){
					printf("\nTL: %d",pos->top_left->no_mines);
					if(pos->top_left->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 2\n",mine_ctr);
				//Top
				
				if(pos->top){
					printf("\nT: %d",pos->top->no_mines);
					if(pos->top->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 3\n",mine_ctr);
				//Top Right
				
				if(pos->top_right){
					printf("\nTR: %d",pos->top_right->no_mines);
					if( pos->top_right->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 4\n",mine_ctr);
				//Left
				
				if(pos->left){
					printf("\nL: %d",pos->left->no_mines);
					if( pos->left->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 5\n",mine_ctr);
				//Right
				
				if(pos->right){
					printf("\nR: %d",pos->right->no_mines);
					if(pos->right->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 6\n",mine_ctr);
				//Bottom Left
				
				if(pos->bottom_left){
					printf("\nBL: %d",pos->bottom_left->no_mines);
					if(pos->bottom_left->no_mines ==-1)
						mine_ctr++;
				}
								
				printf("\n%d 7\n",mine_ctr);
				//Bottom
				
				if(pos->bottom){
					printf("\nB: %d",pos->bottom->no_mines);
					if( pos->bottom->no_mines ==-1)
						mine_ctr++;
				}
				
				printf("\n%d 8\n",mine_ctr);
				//Bottom Right
				
				if(pos->bottom_right){
					printf("\nBR: %d",pos->bottom_right->no_mines);
					if( pos->bottom_right->no_mines ==-1)
						mine_ctr++;
				}
				printf("\n%d 9\n",mine_ctr);
			//}
			pos->no_mines=mine_ctr;	
			printf("\nFinal:(%d,%d) %d\n",i,j,pos->no_mines);
		}
	}
	
	//displayGrid(control,grid_size);
	Cell *tmp=control;
	tmp=tmp->right;
	
	printf("\t  ");
	//Column Indices
	for(int i=0;i<grid_size;i++)
		printf("  %d ",i+1);
	printf("\n");
	printf("\t  ");
	for(int i=0;i<grid_size;i++)
		printf("____");
	printf("\n");
	
	for(int i=0;i<grid_size;i++){

		printf("\t");
		//Row index
		printf("%d |",i+1);

		for(int j=0;j<grid_size;j++){
			tmp=control;
			tmp=tmp->right;

			for(int k=1;k<=i;k++)
				tmp=tmp->bottom;
			for(int k=1;k<=j;k++)
				tmp=tmp->right;

			//Content of Cell
			if(tmp->no_mines==-1)
				printf(" %c |",tmp->content);
			else
				printf(" %d |",tmp->no_mines);

		}

		printf("\n");
		printf("\t  ");

		//Successive row demarcation
		for(int k=0;k<grid_size;k++)
			printf("____");
		printf("\n");
	}
}
	
		
				
				
				
						
