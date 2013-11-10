#include<stdio.h>
#include<stdlib.h>

int board_of_win_full(int **,char ****);
int box_win(int,int,char****,int);
int w_win(int **,int);
void print(FILE*,char ****);
void scan(FILE *,char ****);
int board_full(int,int,char ****);
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[x][y][i][j]!='.')
			continue;
			else return 0;
		}
	}
return 1;

}

int main()
{
	FILE* fp=fopen("board.dat","w");
	int i,j,k,l,player1_win=0,player2_win=0,x2=-1,y2=-1,x1,y1,x,y;
	int **win=(int**)malloc(sizeof(int*)*3);
	for(i=0;i<3;i++)
	win[i]=(int*)malloc(sizeof(int)*3);
	
	//initialising winning matrix to -1
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			win[i][j]=-1;
	}
	
	//using malloc for 4d matrix-board
	char ****board=(char****)malloc(sizeof(char***)*3);
	for(i=0;i<3;i++)
	{
		board[i]=(char***)malloc(sizeof(char**)*3);
		for(j=0;j<3;j++)
		{
			board[i][j]=(char**)malloc(sizeof(char*)*3);
			for(k=0;k<3;k++)
				board[i][j][k]=(char*)malloc(sizeof(char)*3);
		}
	}
	
	//initialising board matrix to '.'
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
					board[i][j][k][l]='.';
			}
		}
	}
	
	while(player1_win==0 && player2_win==0 && board_of_win_full(win,board)==0)
	{
		//print to 1st player
		print(fp,board);
		printf("%d %d\n",x2,y2);
		fprintf(fp,"%d %d\n",x2,y2);
		
		fclose(fp);
		sleep(1);
		system("clear");
		
		system("./a.out");
		
		fp=fopen("board.dat","r");
		scan(fp,board);
		fscanf(fp,"%d%d",&x,&y);
		fclose(fp);
		
		//a check to see whether any of the grids is won by player1 and mark that
		//particular element in 'w'matrix as '1'
		if(win[x][y]==-1 && box_win(x,y,board,1)==1)win[x][y]=1;
		
		if(win[x][y]!=-1 || board_full(board,x,y)==1){x1=-1;y1=-1;}
		else {x1=x;y1=y;}
		
		
		
		//to check whether player1 is won 
		if(w_win(win,1)==1){player1_win=1;break;}
		if(board_of_win_full(win,board)==1)break;
		
		//print to 2nd player
		fp=fopen("board.dat","w");
		print(fp,board);
		printf("%d %d\n",x1,y1);
		fprintf(fp,"%d %d\n",x1,y1);
		fclose(fp);
		
		sleep(1);
		system("clear");
		system("./a.out");
		
		fp=fopen("board.dat","r");
		scan(fp,board);
		fscanf(fp,"%d %d",&x,&y);
		
		fclose(fp);
		
		//a check to see whether any of the grids is won by player2 and mark that
		//particular element in 'w'matrix as '2'
		if(win[x][y]==-1 && box_win(x,y,board,2)==2)win[x][y]=2;
		
		if(win[x][y]!=-1 || board_full(board,x,y)==1){x2=-1;y2=-1;}
		else {x2=x;y2=y;}
		
		
		
		//to check whether player2 is won
		if(w_win(win,2)==2){player2_win=1;break;}
		
		fp=fopen("board.dat","w");
	}
	fclose(fp);
	
	if(player1_win==1)printf("Game is over.Player1 has won\n");
	else if(player2_win==1)printf("Game is over.Player2 has won\n");
	else if(player1_win==0 && player2_win==0)printf("It's tie.\n");
}


/*********************************************************************************
** func board_of_win_full to see the boxes of grid which aren't won are full or not.
** @param win -pointer to winning matrix
** @param board pointer.
** @param returns 1 if the game can't be further played ,else 0
*********************************************************************************/
int board_of_win_full(int **win,char ****board)
{
	int k,l,x,y;
	for(x=0;x<3;x++)
	{
		for(y=0;y<3;y++)
		{
			if(win[x][y]==-1)
			{
				for(k=0;k<3;k++)
				{
					for(l=0;l<3;l++)
					{
						if(board[x][y][k][l]!='.')
							continue;
						else 
							return 0;
					}
				}
			}
		}
	}
	return 1;
}

/****************************************************************************************
** box_win func to maintain 'win' matrix
** @param x,y : coordinates of the grid in the board
** @param board pointer to the board
** @player_no:player 1 or 2
** @return:returns the current player_no if that grid is won by the current player,else 0
****************************************************************************************/
int box_win(int x,int y,char ****board,int player_no)
{
	char a;
	if(player_no==1)a='X';
	else {a='O';}
	if((board[x][y][0][0]==a && board[x][y][0][1]==a && board[x][y][0][2]==a)||
	   (board[x][y][1][0]==a && board[x][y][1][1]==a && board[x][y][1][2]==a)||
	   (board[x][y][2][0]==a && board[x][y][2][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][0]==a && board[x][y][2][0]==a)||
	   (board[x][y][0][1]==a && board[x][y][1][1]==a && board[x][y][2][1]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][2]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][1]==a && board[x][y][2][0]==a))
	 return player_no;
	 else return 0;
}

/***************************************************************************************
** w_win func to check if game is won by anyone of the players
** @param player_no:player 1 or 2
** @param pointer to winning matrix 'w'
** @return:returns the current player_no if the current player is won,else 0
***************************************************************************************/
int w_win(int **w,int a)
{
	
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
void print(FILE *fp,char ****board)
{
	int i,j,k,l;
	for(i=0;i<3;i++)
	{
		for(k=0;k<3;k++)
		{
			for(j=0;j<3;j++)
			{
				for(l=0;l<3;l++)
				{
					fprintf(fp,"%c ",board[i][j][k][l]);
					printf("%c ",board[i][j][k][l]);
				}
			}
		fprintf(fp,"\n");
		printf("\n");
		}
	}	
}

/******************************************************************************
**sub function which helps scan function to scan the board
** @param fp:FILE pointer
** @param board :the pointer to the board
** scans all the elements of the grid.
******************************************************************************/	
void scan(FILE *fp,char ****board)
{
	int i,j,k,l;
	char bin;
	for(i=0;i<3;i++)
	{
		for(k=0;k<3;k++)
		{
			for(j=0;j<3;j++)
			{
				for(l=0;l<3;l++){
					fscanf(fp,"%c",&board[i][j][k][l]);
					fscanf(fp,"%c",&bin);
				}
			}
			fscanf(fp,"%c",&bin);
		}
	}
	
}


/****************************************************************************************
** board_full func to see whether all elements in board of that particular win matrix are
** filled.
** @param x,y : coordinates of the grid in the board
** @param board pointer to the board
** @return:returns 1 if entire grid is filled,else 0
****************************************************************************************/
int board_full(int x,int y,char ****board)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[x][y][i][j]!='.')
			continue;
			else return 0;
		}
	}
return 1;

}


			
