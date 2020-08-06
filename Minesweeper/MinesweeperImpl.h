#include"MinesweeperProto.h"

Cell* createGrid(Cell* control,int grid_size){
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
	return control;
}

Cell* populateGrid(Cell *control,int grid_size,int mine_position[][2],int no_mine){
	
	int mine_ctr=0;
	for(int i=0;i<grid_size;i++){
		for(int j=0;j<grid_size;j++){
			
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
				else
					pos->content='\0';
			}
		}
	}
	
	for(int i=0;i<grid_size;i++){
		for(int j=0;j<grid_size;j++){
			mine_ctr=0;
			
			Cell *pos=control;
			pos=pos->right;	
			for(int k=1;k<=i;k++)
				pos=pos->bottom;
			for(int k=1;k<=j;k++)
				pos=pos->right;
					
			if(pos->no_mines!=-1){
			
				//Top Left
				if(pos->top_left && pos->top_left->no_mines ==-1){
					mine_ctr++;
				}
				
				//Top
				if(pos->top && pos->top->no_mines ==-1){
					mine_ctr++;
				}
				
				//Top Right
				if(pos->top_right && pos->top_right->no_mines ==-1){
					mine_ctr++;
				}
				//Left
				
				if(pos->left  && pos->left->no_mines ==-1){
					mine_ctr++;
				}
				
				
				//Right
				if(pos->right && pos->right->no_mines ==-1){
					
					mine_ctr++;
				}
				
				
				//Bottom Left
				if(pos->bottom_left && pos->bottom_left->no_mines ==-1){
					
					mine_ctr++;
				}
								
			
				//Bottom
				if(pos->bottom && pos->bottom->no_mines ==-1){
				
					mine_ctr++;
				}
				
			
				//Bottom Right
				if(pos->bottom_right && pos->bottom_right->no_mines ==-1){
					
					mine_ctr++;
				}
			
			}
			if(pos->content=='M')
				pos->no_mines=-1;
			else
				pos->no_mines=mine_ctr;	
			
		}
	}
	return control;
}
			
void displayGrid(Cell *control,int grid_size){
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
			if(tmp->content=='M')
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
		
void displayEmptyGrid(Cell *control,int grid_size){
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
			printf("   |");
		}
								
		printf("\n");
		printf("\t  ");

		//Successive row demarcation
		for(int k=0;k<grid_size;k++)
			printf("____");
		printf("\n");
	}
}	

void displayCurrentGrid(Cell* control,int grid_size,int attempts[][2],int attempt_index){
	if(attempt_index==-1)
		displayEmptyGrid(control,grid_size);
	else{
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
				int flag=0;
				for(int a=0;a<=attempt_index;a++){
					flag=0;
					if(attempts[a][0]==i+1&&attempts[a][1]==j+1){
						tmp=control;
						tmp=tmp->right;
				
						flag=1;
						for(int k=1;k<=i;k++)
							tmp=tmp->bottom;
						for(int k=1;k<=j;k++)
							tmp=tmp->right;

						//Content of Cell
						if(tmp->content=='M')
							printf(" %c |",tmp->content);
						else
							printf(" %d |",tmp->no_mines);
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
			for(int k=0;k<grid_size;k++)
				printf("____");
			printf("\n");
		}
	}
}				
