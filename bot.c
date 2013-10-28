#include<stdio.h>
void monster( int**** board , int x , int y , int **w)
{	static x1=-1,x2=-1,y1=-1,y2=-1;
	// Initial move @jpsagar
	if((x==-1)&&(y==-1)&&(free(w))){
		board[1][1][1][1]=1;
		return;
	}
	
	// Trying to push the opponent into the middle grid until it is filled
	// @jpsagar
	if(full( board , 1 , 1)!=-1){
		board[x][y][1][1]=1;
		return;
	}
	// Its for trying to enter into some new grid and initialing opposite 
	// grid for stopping it to win the game	
	if(completelyfree(board,x,y)){
		board[x][y][x][y]=1;
		x1=x;
		y1=y;
		if((x1==0)&&(y1==0)){
			x2=2;
			y2=2;
		}
		if((x1==2)&&(y1==2)){
			x2=1;
			y2=1;
		}
		if((x1==1)&&(y1==0)){
			x2=1;
			y2=2;
		}
		if((x1==1)&&(y1==2)){
			x2=1;
			y2=0;
		}
		if((x1==2)&&(y1==0)){
			x2=0;
			y2=2;
		}
		if((x1==0)&&(y1==2)){
			x2=2;
			y2=0;
		}
		return;
	}
	// If the whole board is allowed to play then I will put that back 
	// through the second grid if possible if not lock in the second grid
	if((x==-1)&&(y==-1)){
		if(board[x2][y2][x1][y1]!=-1){
			board[x2][y2][x1][y1]=1;
			return;
		}else{
			board[x2][y2][x2][y2]=1;
			return;
	}
	// First preference is given to the first grid(x1,y1) and second is to 
	// the second grid (x2,y2)
	if(board[x][y][x1][y1]==-1){
		board[x][y][x1][y1]=1
		return;
	}else{
		board[x][y][x2][y2]=1;
		return;
	}		
}

/*
 * Function to check that no boxes are won
 * @param w winning matrix
 * @return '1' if nothing is won else return '0'
 * @jpsagar
 */
int free(int **w){
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(w[i][j]!=-1)
				return 0;
	return 1;
}

/*
 * Function to verify whther the specific grid is fully occupied or not
 * @param board the board
 * @param x the x co-ordinate of the grid
 * @param y the y co-ordinate of the grid
 * @return it returns the encoding of the empty position if free else '-1'
 * @jpsagar
 */
int full(int ****board, int x, int y){
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(board[x][y][i][j]==-1)
				return(i*3+j);
	return -1;
}

/*
 * Function to verify whther the specific grid is fully occupied or not
 * @param board the board
 * @param x the x co-ordinate of the grid
 * @param y the y co-ordinate of the grid
 * @return it returns '1' if completely free else '0'
 * @jpsagar
 */
int completelyfree(int ****board, int x, int y){
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(board[x][y][i][j]!=-1)
				return 0;
	return 1;
}
