#include<stdio.h>

/***************************************************************
** engine func which returns the winner of the game 1 or 2
** @param board the pointer to the board
** @return :it returns winner(player_no) of the game :1 or 2
** @tejaswini 
****************************************************************/

int engine(int ****board)
{
	static int i,j,player1_win=0,player2_win=0,x1,y1,x2=-1,y2=-1,by_player1,by_player2;
	
	//'w'is a winning 3x3 matrix, which keeps track of the grids won by players
	int **w=(int**)malloc(sizeof(int*)*3);
	for(i=0;i<3;i++)
	int w[i]=(int*)malloc(sizeof(int)*3);
	
	//initializing all elements of w to -1
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		w[i][j]=-1;
	}
	
	//a while loop which runs until the game is won by anyone of the players
	while(player1_win==0 && player2_win==0)
	{
		//print to 1st player
		print(board);
		
		sleep(2);
        system("clear");
		
		by_player1=monster(board,x2,y2,w);
		
		//decoding the x,y coordinates of grid of board marked by player2
		x1=by_player1/3;y1=by_player1%3;
		
		//a check to see whether any of the grids is won by player1 and mark that
		//particular element in 'w'matrix as '1'
		if(w[x1][y1]==-1 && box_win(x1,y1,board,1)==1)w[x1][y1]=1;
		
		//to check whether player1 is won 
		if(w_win(w,1)==1){player1_win=1;break;}
		
		//print to 2nd player
		print(board);
		
		sleep(2);
        system("clear");
		
		by_player2=monster(board,x1,y1,w);
		
		//decoding the x,y coordinates of grid of board marked by player1
		x2=by_player2/3;y2=by_player2%3;
		
		//a check to see whether any of the grids is won by player2 and mark that
		//particular element in 'w'matrix as '2'
		if(w[x2][y2]==-1 && box_win(x2,y2,board,2)==2)w[x2][y2]=2;
		
		//to check whether player2 is won
		if(w_win(w,2)==2){player2_win=1;break;}
	}
	if(player1_win==1)return 1;
	else if(player2_win==1)return 2;
}
	
	
/****************************************************************************************
** box_win func to maintain 'w' matrix
** @param x,y : coordinates of the grid in the board
** @param board pointer to the board
** @player_no:player 1 or 2
** @return:returns the current player_no if that grid is won by the current player,else 0
****************************************************************************************/
int box_win(int x,int y,int ****board,int player_no)
{
	int a=player_no;
	if((board[x][y][0][0]==a && board[x][y][0][1]==a && board[x][y][0][2]==a)||
	   (board[x][y][1][0]==a && board[x][y][1][1]==a && board[x][y][1][2]==a)||
	   (board[x][y][2][0]==a && board[x][y][2][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][0]==a && board[x][y][2][0]==a)||
	   (board[x][y][0][1]==a && board[x][y][1][1]==a && board[x][y][2][1]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][2]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][1]==a && board[x][y][2][0]==a))
	 return a;
	 else return 0;
}

/***************************************************************************************
** w_win func to check if game is won by anyone of the players
** @param player_no:player 1 or 2
** @param pointer to winning matrix 'w'
** @return:returns the current player_no if the current player is won,else 0
***************************************************************************************/
int w_win(int **w,int player_no)
{
	int a=player_no;
	if((w[0][0]==a && w[0][1]==a && w[0][2]==a)||
	   (w[1][0]==a && w[1][1]==a && w[1][2]==a)||
	   (w[2][0]==a && w[2][1]==a && w[2][2]==a)||
	   (w[0][0]==a && w[1][0]==a && w[2][0]==a)||
	   (w[0][1]==a && w[1][1]==a && w[2][1]==a)||
	   (w[0][2]==a && w[1][2]==a && w[2][2]==a)||
	   (w[0][0]==a && w[1][1]==a && w[2][2]==a)||
	   (w[0][2]==a && w[1][1]==a && w[2][0]==a))
	  return a;
	else return 0;
}

/****************************************************************************
** func print to print the whole board as 2x2 matrix
** @param pointer to board
** prints whole board as 2x2 matrix
****************************************************************************/	
void print(int ****board)
{
	print_as_two_by_two_matrix(0,board);
	print_as_two_by_two_matrix(1,board);
	print_as_two_by_two_matrix(2,board);
	
}

/******************************************************************************
**sub function which helps print function to print the board
** @param x1:the first x coordinate of the board(the x coordinate of the grid)
** @param board :the pointer to the board
** prints all the elements in the x1 th row of the grid as required 2x2 matrix
******************************************************************************/	
void print_as_two_by_two_matrix(int x1,int ****board)
{
	int i;
	for(i=0;i<3;i++)
	{
	if(board[x1][0][0][i]==-1)
	printf("|___| ");
	else if(board[x1][0][0][i]==1)
	printf("|_x_| ");
	else if(board[x1][0][0][i]==2)
	printf("|_o_| ");
	}
	
	for(i=0;i<3;i++)
	{
	if(board[x1][1][0][i]==-1)
	printf("|___| ");
	else if(board[x1][1][0][i]==1)
	printf("|_x_| ");
	else if(board[x1][1][0][i]==2)
	printf("|_o_| ");
	}
	
	
	for(i=0;i<3;i++)
	{
	if(board[x1][2][0][i]==-1)
	printf("|___| ");
	else if(board[x1][2][0][i]==1)
	printf("|_x_| ");
	else if(board[x1][2][0][i]==2)
	printf("|_o_| ");
	}
	
	printf("\n");
	
	for(i=0;i<3;i++)
	{
	if(board[x1][0][1][i]==-1)
	printf("|___| ");
	else if(board[x1][0][1][i]==1)
	printf("|_x_| ");
	else if(board[x1][0][1][i]==2)
	printf("|_o_| ");
	}
	
	for(i=0;i<3;i++)
	{
	if(board[x1][1][1][i]==-1)
	printf("|___| ");
	else if(board[x1][1][1][i]==1)
	printf("|_x_| ");
	else if(board[x1][1][1][i]==2)
	printf("|_o_| ");
	}

	
	for(i=0;i<3;i++)
	{
	if(board[x1][2][1][i]==-1)
	printf("|___| ");
	else if(board[x1][2][1][i]==1)
	printf("|_x_| ");
	else if(board[x1][2][1][i]==2)
	printf("|_o_| ");
	}
	
	printf("\n");
	
	for(i=0;i<3;i++)
	{
	if(board[x1][0][2][i]==-1)
	printf("|___| ");
	else if(board[x1][0][2][i]==1)
	printf("|_x_| ");
	else if(board[x1][0][2][i]==2)
	printf("|_o_| ");
	}

	
	for(i=0;i<3;i++)
	{
	if(board[x1][1][2][i]==-1)
	printf("|___| ");
	else if(board[x1][1][2][i]==1)
	printf("|_x_| ");
	else if(board[x1][1][2][i]==2)
	printf("|_o_| ");
	}

	
	for(i=0;i<3;i++)
	{
	if(board[x1][2][2][i]==0)
	printf("|___| ");
	else if(board[x1][2][2][i]==1)
	printf("|_x_| ");
	else if(board[x1][2][2][i]==2)
	printf("|_o_| ");
	}

	
	printf("\n");
}
		
