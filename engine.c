#include<stdio.h>
#include<stdlib.h>

int box_win(int,int,char****,int);
int w_win(int **,int);
void print(FILE*,char ****);
void print_as_two_by_two_matrix(fp,int,char ****);
void scan(FILE *,char ****);
void to_scan(FILE *,int,char ****);

int main()
{
	FILE* fp=fopen("bot.text","r+");
	int i,j,k,player_1=0;player_2=0,x2=-1,y2=-1,x,y;
	int **win=(int**)malloc(sizeof(int*)*3);
	for(i=0;i<3;i++)
	win[i]=(int*)malloc(sizeof(int)*3);
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		win[i][j]=-1;
	}
	
	char ****board=(char****)malloc(sizeof(char***)*3);
	for(i=0;i<3;i++)
	{
		*win[i]=(char***)malloc(sizeof(char**)*3);
		for(j=0;j<3;j++)
		{
			*win[i][j]=(char**)malloc(sizeof(char*)*3);
			for(k=0;k<3;k++)
			win[i][j][k]=(char*)malloc(sizeof(char)*3);
		}
	}
	
	for(i=0;i<3;i++)
	{
		for(j=0;j>3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				board[i][j][k][l]='.';
			}
		}
	}
	
	while(player1_win==0 && player2_win==0)
	{
		//print to 1st player
		print(fp,board);//check..........
		fprintf(fp,"%d %d\n",x2,y2);
		
		system("./bot1");
		
		scan(fp,board);
		fscanf(fp,"%d %d",&x,&y);
		
		if(win[x][y]!=-1){x1=-1;y1=-1;}
		else {x1=x;y1=y;}
		
		//a check to see whether any of the grids is won by player1 and mark that
		//particular element in 'w'matrix as '1'
		if(win[x][y]==-1 && box_win(x1,y1,board,1)==1)win[x1][y1]=1;
		
		//to check whether player1 is won 
		if(w_win(w,1)==1){player1_win=1;break;}
		
		//print to 2nd player
		print(fp,board);//check........
		fprintf(fp,"%d %d\n",x1,y1);
		
		system("./bot2");
		
		scan(fp,board);
		fscanf(fp,"%d %d",&x,&y);
		
		if(win[x][y]!=-1){x2=-1;y2=-1;}
		else {x2=x;y2=y;}
		
		//a check to see whether any of the grids is won by player2 and mark that
		//particular element in 'w'matrix as '2'
		if(w[x][y]==-1 && box_win(x2,y2,board,2)==2)w[x2][y2]=2;
		
		//to check whether player2 is won
		if(w_win(w,2)==2){player2_win=1;break;}
	}
	fclose(fp);
	
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
int box_win(int x,int y,char ****board,int player_no)
{
	char a;
	if(player_no==1)a='X';
	else {a='O'};
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
void print(FILE *fp,char ****board)
{
	print_as_two_by_two_matrix(fp,0,board);
	print_as_two_by_two_matrix(fp,1,board);
	print_as_two_by_two_matrix(fp,2,board);
	
}


/********************************************************************************
**sub function which helps print function to print the board to file and terminal
** @param fp:pointer to FILE
** @param x1:the first x coordinate of the board(the x coordinate of the grid)
** @param board :the pointer to the board
** prints all the elements in the x1 th row of the grid as required 2x2 matrix
********************************************************************************/	
void print_as_two_by_two_matrix(FILE *fp,int x1,char ****board)
{
	int i;
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][0][0][i]);
	printf("%c "board[x1][0][0][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][1][0][i]);
	printf("%c "board[x1][1][0][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][2][0][i]);
	printf("%c "board[x1][2][0][i]);
	}
	fprintf(fp,"\n");
	printf("\n");
	
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][0][1][i]);
	printf("%c "board[x1][0][1][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][1][1][i]);
	printf("%c "board[x1][1][1][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][2][1][i]);
	printf("%c "board[x1][2][1][i]);
	}
	fprintf(fp,"\n");
	printf("\n");
	
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][0][2][i]);
	printf("%c "board[x1][0][2][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][1][2][i]);
	printf("%c "board[x1][1][2][i]);
	}
	for(i=0;i<3;i++)
	{
	fprintf(fp,"%c ",board[x1][2][2][i]);
	printf("%c "board[x1][2][2][i]);
	}
	fprintf(fp,"\n");
	printf("\n");
}

/****************************************************************************
** func scan to scan the whole board as 2x2 matrix from file.
** @param pointer to board and FILE -fp
** scans whole board as 2x2 matrix
****************************************************************************/
void scan(FILE *fp,char ****board)
{
	to_scan(fp,0,board);
	to_scan(fp,1,board);
	to_scan(fp,2,board);
	
}


/******************************************************************************
**sub function which helps scan function to scan the board
** @param fp:FILE pointer
** @param x1:the first x coordinate of the board(the x coordinate of the grid)
** @param board :the pointer to the board
** scans all the elements in the x1 th row of the grid as required 2x2 matrix
******************************************************************************/	
void to_scan(FILE *fp,int x1,char ****board)
{
	int i;
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][0][0][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][1][0][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][2][0][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][0][1][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][1][1][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][2][1][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][0][2][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][1][2][i]);
	
	for(i=0;i<3;i++)
	fscanf(fp," %c",&board[x1][2][2][i]);
	
}
			
