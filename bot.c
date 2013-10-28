#include<stdio.h>
void monster( int**** board , int x , int y , int **w)
{	
	// Initial move @jpsagar
	if((x==-1)&&(y==-1)&&(free(w))){
		board[1][1][1][1]=1;
		return ;
	}
	
	// Trying to push the opponent into the middle grid until it is filled
	// @jpsagar
	if(full( board , 1 , 1)!=-1){
		board[x][y][1][1]=1;
		return ;
	}else{
		if()
		board[x][y][x][y]=1;
		return ;
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
