#include<stdio.h>
#include<stdlib.h>

int board_of_win_full(int **,char ****);
int box_win(int,int,char****,int);
int w_win(int **,int);
void print(FILE*,char ****);
void scan(FILE *,char ****);
int board_full(int,int,char ****);
int* compare(char ****,char ****);


int main()
{
	FILE* fp=fopen("Board.dat","w");
	int i,j,k,l,player1_win=0,player2_win=0,x2=-1,y2=-1,x1,y1,x,y,flagg,flag=1;
	int **win=(int**)malloc(sizeof(int*)*3);
	for(i=0;i<3;i++)
	win[i]=(int*)malloc(sizeof(int)*3);
	
	//initialising winning matrix to -1
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			win[i][j]=-1;
			
	//initialising a pointer and using malloc to a 4 element array
	int *arr=(int*)(malloc(4*(sizeof(int))));
	
	
	//using malloc for 4d matrix-board
	char ****board1=(char****)malloc(sizeof(char***)*3);
	char ****board2=(char****)malloc(sizeof(char***)*3);
	for(i=0;i<3;i++)
	{
		board1[i]=(char***)malloc(sizeof(char**)*3);
		board2[i]=(char***)malloc(sizeof(char**)*3);
		for(j=0;j<3;j++)
		{
			board1[i][j]=(char**)malloc(sizeof(char*)*3);
			board2[i][j]=(char**)malloc(sizeof(char*)*3);
			for(k=0;k<3;k++)
			{
				board1[i][j][k]=(char*)malloc(sizeof(char)*3);
				board2[i][j][k]=(char*)malloc(sizeof(char)*3);
			}
		}
	}
	
	//initialising board matrix to '.'
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			for(k=0;k<3;k++){
				for(l=0;l<3;l++)
				{
					board1[i][j][k][l]='.';
					board2[i][j][k][l]='.';
				}
			}
		}
	}
	
	
	while(player1_win==0 && player2_win==0 && board_of_win_full(win,board2)==0)
	{
		//print to 1st player
		print(fp,board2);
		
		printf("%d %d\n",x2,y2);
		fprintf(fp,"%d %d\n",x2,y2);
		
		fclose(fp);
		flag=0;
		sleep(1);
		system("clear");
		
		system("./a.out");
		
		fp=fopen("Board.dat","r");
		flag=1;
		scan(fp,board1);
		fscanf(fp,"%d %d",&x,&y);
		fclose(fp);
		flag=0;
		
		arr=compare(board2,board1);
		if(win[arr[0]][arr[1]]==-1 && box_win(arr[0],arr[1],board1,1)==1)
		win[arr[0]][arr[1]]=1;
		
		if((win[arr[2]][arr[3]]!=-1) || board_full(arr[2],arr[3],board1)==1)
		{x1=-1;y1=-1;}
		
		else
		{
		x1=x;
		y1=y;
		}
		
		//to check whether player1 is won 
		if(w_win(win,1)==1)
		{
			player1_win=1;
			flagg=1;
			break;
		}
		
		if(board_of_win_full(win,board1)==1)
		{
			flagg=1;
			break;
		}
		
		
		//print to second player	
		fp=fopen("Board.dat","w");
		flag=1;
		print(fp,board1);
		printf("%d %d\n",x1,y1);
		fprintf(fp,"%d %d\n",x1,y1);
		fclose(fp);
		flag=0;
		sleep(1);
		system("clear");
		system("./pratik");
		
		fp=fopen("Board.dat","r");
		flag=1;
		
		scan(fp,board2);
		fscanf(fp,"%d %d",&x,&y);
		
		fclose(fp);
		flag=0;
		
		arr=compare(board1,board2);
		if(win[arr[0]][arr[1]]==-1 && box_win(arr[0],arr[1],board2,2)==2)
		win[arr[0]][arr[1]]=2;
		
		if((win[arr[2]][arr[3]]!=-1) || board_full(arr[2],arr[3],board2)==1)
		{x2=-1;y2=-1;}
		
		else
		{
		x2=x;
		y2=y;
		}
		
		//to check whether player2 is won 
		if(w_win(win,2)==2)
		{
			player2_win=1;
			flagg=2;
			break;
		}
		
		if(board_of_win_full(win,board2)==1)
		{	
			flagg=2;
			break;
		}
			
		fp=fopen("Board.dat","w");
		flag=1;
	}
			
		
	if(flag==1)
	fclose(fp);
	
	
	fp=fopen("Board.dat","w");
	{
		if(flagg==1)print(fp,board1);
		else print(fp,board2);
	}
	if(player1_win==1)
		printf("Game is over.Player1 has won\n");
	else if(player2_win==1)
		printf("Game is over.Player2 has won\n");
	else if(player1_win==0 && player2_win==0)
		printf("It's tie.\n");
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
	if(player_no==1)
		a='X';
	else 
		a='O';
	if((board[x][y][0][0]==a && board[x][y][0][1]==a && board[x][y][0][2]==a)||
	   (board[x][y][1][0]==a && board[x][y][1][1]==a && board[x][y][1][2]==a)||
	   (board[x][y][2][0]==a && board[x][y][2][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][0]==a && board[x][y][2][0]==a)||
	   (board[x][y][0][1]==a && board[x][y][1][1]==a && board[x][y][2][1]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][2]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][0]==a && board[x][y][1][1]==a && board[x][y][2][2]==a)||
	   (board[x][y][0][2]==a && board[x][y][1][1]==a && board[x][y][2][0]==a))
	 	return player_no;
	 else 
	 	return 0;
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
	else
		return 0;
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
					fprintf(fp,"%c",board[i][j][k][l]);
					printf("%c ",board[i][j][k][l]);
				}
			}
		fprintf(fp,"\n");
		printf("\n");
		}
	}	
}

/******************************************************************************
** function to scan the board board from file
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
		for(j=0;j<3;j++)
			if(board[x][y][i][j]!='.')
				continue;
			else
				return 0;
return 1;

}

/***********************************************************************************************
** compare func to compare previous and recent boards and note the required indices into a array
** @param prev:pointer to previous board
** @param recent:pointer to recent board
** @return:returns the array withrequired elements
*************************************************************************************************/
int* compare(char ****prev,char **** recent)
{
	int i,j,k,l;
	int *arr=(int *)malloc(4*sizeof(int));
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
				if(prev[i][j][k][l]!=recent[i][j][k][l])
					{
					arr[0]=i;arr[1]=j;arr[2]=k;arr[3]=l;
					return arr;
					}
				}
			}
		}
	}

}


