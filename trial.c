#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void capture( FILE *fp , char ****board , int *x , int *y );
void wincapture( char ****board , char **win);
char gridcheck( char ****board , int i , int j);
void mysym( char ****board , char *sym );
void printboard( char ****board , int x , int y );
void bestmove( char ****board , char **win , int *x , int *y , int *playx , int *playy , char mysym , char ensym);
void gridwin(char ****board , char **win , int x , int y , int ***placex  , char mysym , char ensym);
void enwinstop(char ****board , char **win , int x , int y , int ***placex , char mysym , char ensym);
void numofplays(char **** board , int ** numofx , int **numofy );
void nextmove( char ****board , char **win , int *x , int *y , int *playx , int *playy , char mysym , char ensym , int ** numofme , int **numofen , int ***placeme , int ***placeen);
int w_win(char **w, char a , int *** place , int x , int y , int *  ,int *  );
int* possible(char ****board , int x , int y , char mysym);
int main(){ 
	char **** board;
	board=(char ****)malloc(sizeof(char ***)*3);
	int i,j,k;
	for(i=0;i<3;i++){
		board[i]=(char ***)malloc(sizeof(char **)*3);
		for(j=0;j<3;j++){
			board[i][j]=(char **)malloc(sizeof(char *)*3);
			for(k=0;k<3;k++){
				board[i][j][k]=(char *)malloc(sizeof(char)*3);
			}
		}
	}
	
	FILE *fp;
	fp=fopen("board.dat","r");
	int x,y;
	capture( fp , board , &x , &y );
	fclose(fp);
	
	char sym , ensym ;
	mysym( board , &sym );
	
	if( sym == 'X')
		ensym = 'O';
	else
		ensym = 'X';
	
	char ** win;
	win=(char **)malloc(sizeof(char *)*3);
	
	for(i=0;i<3;i++)
		win[i]=(char *)malloc(sizeof(char)*3);
		
	
	wincapture( board , win );
	

	
	int playx,playy;

	bestmove( board , win , &x , &y , &playx , &playy , sym , ensym );
	
	board[x][y][playx][playy]=sym;
	
	printboard(board , playx , playy);
	
	free(board);
	free(win);
	
	return ;
	
}
/* Function to capture the info from the file
 * @param x,y are the positions where to play to be captured from the file
 * @param fp is the file pointer
 * @param board pointer to the board
 */
void capture( FILE *fp , char ****board , int *x , int *y ){
	int i,j,m,n;
	char bin;
	for(i=0;i<3;i++){
		for(m=0;m<3;m++){
			for(j=0;j<3;j++){
				for(n=0;n<3;n++){
					fscanf(fp,"%c%c",&board[i][j][m][n],&bin);
				}
			}
		fscanf(fp,"%c",&bin);
		}
	}
	fscanf(fp,"%d %d",x,y);
	return ;
}

/* Function to create the winning matrix
 * @param board pointer to the board
 * @param win is the winning matrix
 */
void wincapture( char ****board , char **win){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			win[i][j] = gridcheck( board , i , j );
		}
	}
	return ;
}
/* Function to check whether the following grid is won by someone or not
 * @param i,j are the position of grid where to check 
 * @param board pointer to the board
 * @return the symbol of the winner of the grid
 */
char gridcheck( char ****board , int i , int j){
	if(((board[i][j][0][0]==board[i][j][0][1])==board[i][j][0][2])!='.'){
		return board[i][j][0][0];
	}
	if(((board[i][j][1][0]==board[i][j][1][1])==board[i][j][1][2])!='.'){
		return board[i][j][1][0];
	}
	if(((board[i][j][2][0]==board[i][j][2][1])==board[i][j][2][2])!='.'){
		return board[i][j][2][0];
	}
	
	if(((board[i][j][0][0]==board[i][j][1][0])==board[i][j][2][0])!='.'){
		return board[i][j][0][0];
	}
	if(((board[i][j][0][1]==board[i][j][1][1])==board[i][j][2][1])!='.'){
		return board[i][j][0][1];
	}
	if(((board[i][j][0][2]==board[i][j][1][2])==board[i][j][2][2])!='.'){
		return board[i][j][0][2];
	}
	
	if(((board[i][j][0][0]==board[i][j][1][1])==board[i][j][2][2])!='.'){
		return board[i][j][0][0];
	}
	if(((board[i][j][2][0]==board[i][j][1][1])==board[i][j][2][0])!='.'){
		return board[i][j][1][1];
	}
	
	return '.';
}

/* Function to find my present symbol
 * @param board pointer to the board
 * @param sym the char pointer to the symbol
 */
void mysym( char ****board , char *sym ){
	int xcount=0,ocount=0,i,j,m,n;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			for(m=0;m<3;m++){
				for(n=0;n<3;n++){
					if(board[i][j][m][n]=='X')
						xcount++;
					if(board[i][j][m][n]=='O')
						ocount++;
				}
			}
		}
	}
	if(xcount==ocount)
		*sym = 'X';
	else
		*sym = 'O';
	
	return;
}
/* Function to print the board to the file
 * @param x,y are the position of grid where bot played
 * @param board pointer to the board
 */
void printboard( char ****board , int x , int y ){
	int i,j,m,n;
	FILE *fp;
	fp=fopen("board.dat","w");
	for(i=0;i<3;i++){
		for(m=0;m<3;m++){
			for(j=0;j<3;j++){
				for(n=0;n<3;n++){
					fprintf(fp,"%c ",board[i][j][m][n]);
				}
			}
		fprintf(fp,"\n");
		}
	}
	fprintf(fp,"%d %d",x,y);
	fclose(fp);
	return ;
}

/*
 * Function to play the best move possible at this stage
 * @param board the board of the game
 * @param win the winning matrix
 * @param x,y the position where to play the next move
 * @param playx,playy the pointer to the position where the next play is played
 * @param mysym the bots symbol
 * @param ensym the bots enemy symbol
 */
void bestmove( char ****board , char **win , int *x , int *y , int *playx , int *playy , char mysym , char ensym){
	int ***placex,***placeo;
	// x=me o=enemy
	placex=(int ***)malloc(sizeof(int **)*3);
	placeo=(int ***)malloc(sizeof(int **)*3);
	
	
	int i,j,k;
	
	for(i=0;i<3;i++){
		placex[i]=(int **)malloc(sizeof(int *)*3);
		placeo[i]=(int **)malloc(sizeof(int *)*3);
		for(j=0;j<3;j++){
			placex[i][j]=(int *)malloc(sizeof(int)*5);
			placeo[i][j]=(int *)malloc(sizeof(int)*5);
			for(k=0;k<5;k++){
				placex[i][j][k]=-1;
				placeo[i][j][k]=-1;
			}
		}
	}
	// Function	
	gridwin( board , win , *x , *y , placex , mysym , ensym);
	
	// Function
	enwinstop( board , win , *x , *y , placeo , mysym , ensym);
	
	int  **numofx , **numofo;
	numofx=(int **)malloc(sizeof(int *)*3);
	numofo=(int **)malloc(sizeof(int *)*3);
	for(i=0;i<3;i++){
		numofx[i]=(int *)malloc(sizeof(int)*3);
		numofo[i]=(int *)malloc(sizeof(int)*3);
	}
	
	// Function
	numofplays( board , numofx , numofo );
	
	// change these coordinates
	if(mysym=='X')
		nextmove(board , win , x , y , playx , playy , mysym , ensym , numofx , numofo , placex , placeo);
	else
		nextmove(board , win , x , y , playx , playy , mysym , ensym , numofo , numofx , placex , placeo);
		
	return ;
}

/* Function to find whether the present matrix can be won or not
 * @param board pointer to the board
 * @param win is the winning matrix
 * @param x,y position of the grid where to play
 * @param playx,playy position where we played it is (-1,-1) if we can't win this grid any way
 * @param mysym,ensym symbols of mine and enemies
 */ 
void gridwin(char ****board , char **w , int x , int y , int ***placex , char mysym , char ensym){
	int i;
	int p;
	if((x==-1)&&(y==-1)){
		int j,k;
		for(j=0;j<3;j++){
			for(k=0;k<3;k++){
				p=0;
				for(i=0;i<3;i++){
					if((board[j][k][i][0]==board[j][k][i][1])&&(board[j][k][i][1]==mysym)&&(board[j][k][i][0]==mysym)){
						if(board[j][k][i][2]=='.'){
							placex[j][k][p++] = i*3+2;
						}
						
					}
			
					if((board[j][k][i][1]==board[j][k][i][2])&&(board[j][k][i][1]==mysym)&&(board[j][k][i][2]==mysym)){
						if(board[j][k][i][1]=='.'){
							placex[j][k][p++] = i*3+0;
						}
					
					}
				
					if((board[j][k][i][0]==board[j][k][i][2])&&(board[j][k][i][0]==mysym)&&(board[j][k][i][2]==mysym)){
						if(board[j][k][i][2]=='.'){
							placex[j][k][p++] = i*3+1;
						}
		
					}
				}
				
				for(i=0;i<3;i++){
					if((board[j][k][0][i]==board[j][k][1][i])&&(board[j][k][1][i]==mysym)){
						if(board[j][k][2][i]=='.'){
							placex[j][k][p++] = 2*3+i;
						}
						
					}
					
					if((board[j][k][2][i]==board[j][k][1][i])&&(board[j][k][1][i]==mysym)){
						if(board[j][k][1][i]=='.'){
							placex[j][k][p++] = 0*3+i;
						}
			
					}
				
					if((board[j][k][0][i]==board[j][k][2][i])&&(board[j][k][2][i]==mysym)){
						if(board[j][k][2][i]=='.'){
							placex[j][k][p++] = 1*3+i;
						}
			
					}
				}
			
		
				if((board[j][k][0][0]==board[j][k][1][1])&&(board[j][k][0][0]==mysym)){
					if(board[j][k][2][2]=='.'){
						placex[j][k][p++] = 2*3+2;
					}
			
				}
			
				if((board[j][k][1][1]==board[j][k][2][2])&&(board[j][k][2][2]==mysym)){
					if(board[j][k][0][0]=='.'){
						placex[j][k][p++] = 0;
					}
					
				}
				
				if((board[j][k][0][0]==board[j][k][2][2])&&(board[j][k][2][2]==mysym)){
					if(board[j][k][1][1]=='.'){
						placex[j][k][p++] = 1*3+1;
					}
		
				}
			
				if((board[j][k][0][2]==board[j][k][1][1])&&(board[j][k][1][1]==mysym)){
					if(board[j][k][2][0]=='.'){
						placex[j][k][p++] = 2*3;
					}
			
				}
			
				if((board[j][k][1][1]==board[j][k][2][0])&&(board[j][k][2][0]==mysym)){
					if(board[j][k][0][2]=='.'){
						placex[j][k][p++] = 2;
					}
			
				}
		
				if((board[j][k][0][2]==board[j][k][2][0])&&(board[j][k][2][0]==mysym)){
					if(board[j][k][1][1]=='.'){
						placex[j][k][p++] = 1*3+1;
					}
	
				}
					
			}
		}
	return ;
	}
	p=0;
	for(i=0;i<3;i++){
		if((board[x][y][i][0]==board[x][y][i][1])&&(board[x][y][i][1]==mysym)){
			if(board[x][y][i][2]=='.'){
				placex[x][y][p++] = i*3+2;
			}
			
		}
		
		if((board[x][y][i][1]==board[x][y][i][2])&&(board[x][y][i][2]==mysym)){
			if(board[x][y][i][1]=='.'){
				placex[x][y][p++] = i*3;
			}
		
		}
	
		if((board[x][y][i][0]==board[x][y][i][2])&&(board[x][y][i][2]==mysym)){
			if(board[x][y][i][2]=='.'){
				placex[x][y][p++] = i*3+1;
			}

		}
	}
	
	for(i=0;i<3;i++){
		if((board[x][y][0][i]==board[x][y][1][i])&&(board[x][y][1][i]==mysym)){
			if(board[x][y][2][i]=='.'){
				placex[x][y][p++] = 2*3+i;
			}
			
		}
		
		if((board[x][y][1][i]==board[x][y][2][i])&&(board[x][y][2][i]==mysym)){
			if(board[x][y][1][i]=='.'){
				placex[x][y][p++] = i;
			}
		
		}
	
		if((board[x][y][0][i]==board[x][y][2][i])&&(board[x][y][2][i]==mysym)){
			if(board[x][y][2][i]=='.'){
				placex[x][y][p++] = 1*3+i;
			}

		}
	}
	
	
	if((board[x][y][0][0]==board[x][y][1][1])&&(board[x][y][1][1]==mysym)){
		if(board[x][y][2][2]=='.'){
			placex[x][y][p++] = 2*3+2;
		}
		
	}
		
	if((board[x][y][1][1]==board[x][y][2][2])&&(board[x][y][2][2]==mysym)){
		if(board[x][y][0][0]=='.'){
			placex[x][y][p++] = 0;
		}
	
	}
	
	if((board[x][y][0][0]==board[x][y][2][2])&&(board[x][y][2][2]==mysym)){
		if(board[x][y][1][1]=='.'){
			placex[x][y][p++] = 1*3+1;
		}

	}
		
	if((board[x][y][0][2]==board[x][y][1][1])&&(board[x][y][1][1]==mysym)){
		if(board[x][y][2][0]=='.'){
				placex[x][y][p++] = 2*3;
			}
		
	}
		
	if((board[x][y][1][1]==board[x][y][2][0])&&(board[x][y][2][0]==mysym)){
		if(board[x][y][0][2]=='.'){
			placex[x][y][p++] = 2;
		}
	
	}
	
	if((board[x][y][0][2]==board[x][y][2][0])&&(board[x][y][2][0]==mysym)){
		if(board[x][y][1][1]=='.'){
			placex[x][y][p++] = 1*3+1;
		}

	}	
	
	return ;
}

/* Function to find whether the present matrix can be won by enemy or not
 * @param board pointer to the board
 * @param win is the winning matrix
 * @param x,y position of the grid where to play
 * @param playx,playy position where we played it is (-1,-1) if enemy can't win this grid any way
 * @param mysym,ensym symbols of mine and enemies
 */ 
void enwinstop(char ****board , char **w , int x , int y , int ***placex , char mysym , char ensym){
	int i,p;
	if((x==-1)&&(y==-1)){
		for(x=0;x<3;x++){
			for(y=0;y<3;y++){
				p=0;
				for(i=0;i<3;i++){
					if((board[x][y][i][0]==board[x][y][i][1])&&(board[x][y][i][1]==ensym)){
						if(board[x][y][i][2]=='.'){
							placex[x][y][p++] = i*3+2;
						}
				
					}
		
					if((board[x][y][i][1]==board[x][y][i][2])&&(board[x][y][i][2]==ensym)){
						if(board[x][y][i][0]=='.'){
							placex[x][y][p++] = i*3;
						}
		
					}
		
					if((board[x][y][i][0]==board[x][y][i][2])&&(board[x][y][i][2]==ensym)){
						if(board[x][y][i][1]=='.'){
							placex[x][y][p++] = i*3+1;
						}

					}
				}
	
				for(i=0;i<3;i++){
					if((board[x][y][0][i]==board[x][y][1][i])&&(board[x][y][1][i]==ensym)){
						if(board[x][y][2][i]=='.'){
							placex[x][y][p++] = 2*3+i;
						}
				
					}
		
					if((board[x][y][1][i]==board[x][y][2][i])&&(board[x][y][2][i]==ensym)){
						if(board[x][y][0][i]=='.'){
							placex[x][y][p++] = i;
						}
		
					}
	
					if((board[x][y][0][i]==board[x][y][2][i])&&(board[x][y][2][i]==ensym)){
						if(board[x][y][1][i]=='.'){
							placex[x][y][p++] = 1*3+i;
						}

					}
				}
	
	
				if((board[x][y][0][0]==board[x][y][1][1])&&(board[x][y][1][1]==ensym)){
					if(board[x][y][2][2]=='.'){
							placex[x][y][p++] = 2*3+2;
						}
		
				}
		
				if((board[x][y][1][1]==board[x][y][2][2])&&(board[x][y][2][2]==ensym)){
					if(board[x][y][0][0]=='.'){
						placex[x][y][p++] = 0;
					}
		
				}	
	
				if((board[x][y][0][0]==board[x][y][2][2])&&(board[x][y][2][2]==ensym)){
					if(board[x][y][1][1]=='.'){
						placex[x][y][p++] = 1*3+3;
					}

				}
		
				if((board[x][y][0][2]==board[x][y][1][1])&&(board[x][y][1][1]==ensym)){
					if(board[x][y][2][0]=='.'){
							placex[x][y][p++] = 2*3;
						}
		
				}
			
				if((board[x][y][1][1]==board[x][y][2][0])&&(board[x][y][2][0]==ensym)){
					if(board[x][y][0][2]=='.'){
						placex[x][y][p++] = 2;
					}
	
				}
	
				if((board[x][y][0][2]==board[x][y][2][0])&&(board[x][y][2][0]==ensym)){
					if(board[x][y][1][1]=='.'){
						 placex[x][y][p++]= 1*3+1;
					}

				}
			}
		}
	return ;
	}
	p=0;
	for(i=0;i<3;i++){
		if((board[x][y][i][0]==board[x][y][i][1])&&(board[x][y][i][1]==ensym)){
			if(board[x][y][i][2]=='.'){
				placex[x][y][p++] = i*3+2;
			}
			
		}
		
		if((board[x][y][i][1]==board[x][y][i][2])&&(board[x][y][i][2]==ensym)){
			if(board[x][y][i][0]=='.'){
				placex[x][y][p++] = i*3;
			}
		
		}
	
		if((board[x][y][i][0]==board[x][y][i][2])&&(board[x][y][i][2]==ensym)){
			if(board[x][y][i][1]=='.'){
				placex[x][y][p++] = i*3+1;
			}

		}
	}
	
	for(i=0;i<3;i++){
		if((board[x][y][0][i]==board[x][y][1][i])&&(board[x][y][1][i]==ensym)){
			if(board[x][y][2][i]=='.'){
				placex[x][y][p++] = 2*3+i;
			}
			
		}
		
		if((board[x][y][1][i]==board[x][y][2][i])&&(board[x][y][2][i]==ensym)){
			if(board[x][y][0][i]=='.'){
				placex[x][y][p++] = i;
			}
		
		}
	
		if((board[x][y][0][i]==board[x][y][2][i])&&(board[x][y][2][i]==ensym)){
			if(board[x][y][1][i]=='.'){
				placex[x][y][p++] = 1*3+i;
			}

		}
	}
	
	
	if((board[x][y][0][0]==board[x][y][1][1])&&(board[x][y][1][1]==ensym)){
		if(board[x][y][2][2]=='.'){
			placex[x][y][p++] = 2*3+2;
			}
		
	}
		
	if((board[x][y][1][1]==board[x][y][2][2])&&(board[x][y][2][2]==ensym)){
		if(board[x][y][0][0]=='.'){
			placex[x][y][p++] = 0;
		}
	
	}
	
	if((board[x][y][0][0]==board[x][y][2][2])&&(board[x][y][2][2]==ensym)){
		if(board[x][y][1][1]=='.'){
			placex[x][y][p++] = 1*3+1;
		}

	}
		
	if((board[x][y][0][2]==board[x][y][1][1])&&(board[x][y][1][1]==ensym)){
		if(board[x][y][2][0]=='.'){
			placex[x][y][p++] = 2*3;
		}
		
	}
		
	if((board[x][y][1][1]==board[x][y][2][0])&&(board[x][y][2][0]==ensym)){
		if(board[x][y][0][2]=='.'){
			placex[x][y][p++] = 2;
		}
	
	}
	
	if((board[x][y][0][2]==board[x][y][2][0])&&(board[x][y][2][0]==ensym)){
		if(board[x][y][1][1]=='.'){
			placex[x][y][p++] = 1*3+1;
		}

	}	
	
	return ;
}

/***********************************************************************************
** func numofplays to keep track of how many boxes have been played by both players
** @param board -pointer to board
** @param numofx-pointer to a 2x2 matrix which stores no. of x's in grid
** @param numofy-pointer to 2x2 matrix which stores no. of O's in grid
** returns with numofx and numofy filled
***********************************************************************************/
void numofplays (char ****board,int **numofx,int** numofy)
{
	int i,j,k,l,count1=0,count2=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			count1=0;count2=0;
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
				if(board[i][j][k][l]=='X')count1++;
				else if(board[i][j][k][l]=='O')count2++;
				}
			}
		numofx[i][j]=count1;
		numofy[i][j]=count2;
		}
	}
	
}

/***************************************************************************************
** w_win func to check if game is won by anyone of the players
** @param player_no:player 1 or 2
** @param pointer to winning matrix 'w'
** @return:returns the current player_no if the current player is won,else 0
***************************************************************************************/

// change the comments


int w_win(char **w,char a,int *** place,int x,int y,int *dx,int *dy)
{
	if(x==-1 && y==-1)
	{
		if(w[0][0]==a && w[0][1]==a){*dx=0;*dy=2;return 1;}
		if(w[0][0]==a && w[0][2]==a){*dx=0;*dy=1;return 1;}
		if(w[0][1]==a && w[0][2]==a){*dx=0;*dy=0;return 1;}
		
		if(w[1][0]==a && w[1][1]==a){*dx=1;*dy=2;return 1;}
		if(w[1][0]==a && w[1][2]==a){*dx=1;*dy=1;return 1;}
		if(w[1][1]==a && w[1][2]==a){*dx=1;*dy=0;return 1;}
		
		if(w[2][0]==a && w[2][1]==a){*dx=2;*dy=2;return 1;}
		if(w[2][0]==a && w[2][2]==a){*dx=2;*dy=1;return 1;}
		if(w[2][1]==a && w[2][2]==a){*dx=2;*dy=0;return 1;}
		
		if(w[0][0]==a && w[1][0]==a){*dx=2;*dy=0;return 1;}
		if(w[0][0]==a && w[2][0]==a){*dx=1;*dx=0;return 1;}
		if(w[1][0]==a && w[2][0]==a){*dx=0;*dy=0;return 1;}
		
		if(w[0][1]==a && w[1][1]==a){*dx=2;*dy=1;return 1;}
		if(w[0][1]==a && w[2][1]==a){*dx=1;*dx=1;return 1;}
		if(w[1][1]==a && w[2][1]==a){*dx=0;*dy=1;return 1;}
		
		if(w[0][2]==a && w[1][2]==a){*dx=2;*dy=2;return 1;}
		if(w[0][2]==a && w[2][2]==a){*dx=1;*dx=2;return 1;}
		if(w[1][2]==a && w[2][2]==a){*dx=0;*dy=2;return 1;}
		
		if(w[0][0]==a && w[1][1]==a){*dx=2;*dy=2;return 1;}
		if(w[0][0]==a && w[2][2]==a){*dx=1;*dy=1;return 1;}
		if(w[2][2]==a && w[1][1]==a){*dx=0;*dy=0;return 1;}
		
		if(w[0][2]==a && w[1][1]==a){*dx=2;*dy=0;return 1;}
		if(w[0][2]==a && w[2][0]==a){*dx=1;*dy=1;return 1;}
		if(w[1][1]==a && w[2][0]==a){*dx=0;*dy=2;return 1;}
		
		else return 0;
		
	}
	
	
	else if(w[x][y]!='.'){
	*dx=x;
	*dy=y;
	return 0;
	}
	else {
	*dx=x;*dy=y;
	
		if(place[x][y][0]!=-1){
			w[x][y]=a;
			if((w[0][0]==a && w[0][1]==a && w[0][2]==a)||
	   		(w[1][0]==a && w[1][1]==a && w[1][2]==a)||
	   		(w[2][0]==a && w[2][1]==a && w[2][2]==a)||
	   		(w[0][0]==a && w[1][0]==a && w[2][0]==a)||
	   		(w[0][1]==a && w[1][1]==a && w[2][1]==a)||
	   		(w[0][2]==a && w[1][2]==a && w[2][2]==a)||
	   		(w[0][0]==a && w[1][1]==a && w[2][2]==a)||
	   		(w[0][2]==a && w[1][1]==a && w[2][0]==a))
	   		{w[x][y]='.';
	   		return 1;}
	   	}
	   	else {w[x][y]='.';return 0;}
	 }
}

int* possible(char ****board , int x , int y , char mysym){

	int *arr=(int *)malloc(sizeof(int)*24);
	int i,j;
	for(i=0;i<24;i++)
		arr[i]=-1;
	int k=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if((board[x][y][i][j]==mysym))
			{
				if ( (3*i+j)==1 ||(3*i+j)==3 ||(3*i+j)==5|| (3*i+j)==7 ) 
				{
					if (board[x][y][i][(j+1)%3]=='.' && board[x][y][i][(j+2)%3]=='.'){
						arr[k++]=((i*3)+(j+1)%3);
						arr[k++]=((i*3)+(j+2)%3);
					}
					if (board[x][y][(i+1)%3][j]=='.' && board[x][y][(i+2)%3][j]=='.'){
						arr[k++]= ((i+1)%3)*3 +j;
						arr[k++]=((i+2)%3)*3 +j;
					}
				}
				if ((3*i+j)==0 ||(3*i+j)==8) 
				{
					if (board[x][y][(i+1)%3][(j+1)%3]=='.' && board[x][y][(i+2)%3][(j+2)%3]=='.')
					{
						arr[k++]=( ((i+1)%3)*3 + (j+1)%3);
						arr[k++]=( ((i+2)%3)*3 + (j+2)%3);
					}
					if (board[x][y][i][(j+1)%3]=='.' && board[x][y][i][(j+2)%3]=='.'){
						arr[k++]=((i*3)+(j+1)%3);
						arr[k++]=((i*3)+(j+2)%3);
					}
					if (board[x][y][(i+1)%3][j]=='.' && board[x][y][(i+2)%3][j]=='.'){
						arr[k++]= ((i+1)%3)*3 +j;
						arr[k++]=((i+2)%3)*3 +j;
					}	
				}
				if ((3*i+j)==2 ||(3*i+j)==6) 
				{
					if (board[x][y][(i+1)%3][(j-1)%3]=='.' && board[x][y][(i+2)%3][(j-2)%3]=='.')
					{
						arr[k++]=( ((i+1)%3)*3 + (j-1)%3);
						arr[k++]=( ((i+2)%3)*3 + (j-2)%3);
					}
					if (board[x][y][i][(j+1)%3]=='.' && board[x][y][i][(j+2)%3]=='.'){
						arr[k++]=((i*3)+(j+1)%3);
						arr[k++]=((i*3)+(j+2)%3);
					}
					if (board[x][y][(i+1)%3][j]=='.' && board[x][y][(i+2)%3][j]=='.'){
						arr[k++]= ((i+1)%3)*3 +j;
						arr[k++]=((i+2)%3)*3 +j;
					}	
				}
				else
				{
					if (board[x][y][(i+1)%3][(j-1)%3]=='.' && board[x][y][(i+2)%3][(j-2)%3]=='.')
					{
						arr[k++]=( ((i+1)%3)*3 + (j-1)%3);
						arr[k++]=( ((i+2)%3)*3 + (j-2)%3);
					}
					if (board[x][y][i][(j+1)%3]=='.' && board[x][y][i][(j+2)%3]=='.'){
						arr[k++]=((i*3)+(j+1)%3);
						arr[k++]=((i*3)+(j+2)%3);
					}
					if (board[x][y][(i+1)%3][j]=='.' && board[x][y][(i+2)%3][j]=='.'){
						arr[k++]= ((i+1)%3)*3 +j;
						arr[k++]=((i+2)%3)*3 +j;
					}	
					if (board[x][y][(i+1)%3][(j+1)%3]=='.' && board[x][y][(i+2)%3][(j+2)%3]=='.')
					{
						arr[k++]=( ((i+1)%3)*3 + (j+1)%3);
						arr[k++]=( ((i+2)%3)*3 + (j+2)%3);
					}
				}				
			}	
		}		
	}
}

void nextmove( char ****board , char **win , int *x , int *y , int *playx , int *playy , char mysym , char ensym , int ** numofme , int **numofen , int ***placeme , int ***placeen){
	int dx,dy;
	dx=*x;
	dy=*y;
	int *arr=(int *)malloc(sizeof(int)*9);
	int lollipop=w_win( win , mysym , placeme , *x , *y , &dx , &dy);
	int freeboard=1;
	int i,j,k,l;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			for(k=0;k<3;k++){
				for(l=0;l<3;l++){
					if(board[i][j][k][l]!='.')
						freeboard=0;
				}
			}
		}
	}
	
	if((dx==-1)&&(dy==-1)&&(freeboard==1)){
		srand(time(NULL));
		int nfree=rand();
		dx=nfree%3;
		nfree=rand();
		dy=nfree%3;
	}
	
	// x==-1 case not taken care
	// take care of dx and dy VERY IMPORTANT .....................................
	// for winning the given grid without letting to win the game
	int genx,geny;
	if((placeme[dx][dy][0]!=-1)&&(!(w_win( win , ensym , placeen , *x , *y , &genx , &geny)))){
		for(i=0;placeme[dx][dy][i]!=-1;i++){
			arr[i]=placeme[dx][dy][i];
		}
		i--;
		srand(time(NULL));
		int n=rand();
		if(i!=0)
			i=n%i;
		n=arr[i];
		*playx=n/3;
		*playy=n%3;
		return;
	}	
	
	// If we win for sure
	if(w_win( win , mysym , placeme , *x , *y , x , y)){
		int n=placeme[*x][*y][0];
		*playx = n/3;
		*playy = n%3;
		return ;
	}
	// x==-1 case not taken care
	// for opponent playing in a empty grid
	int check=0;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(numofme[i][j]==0)&&(numofen[i][j]==0)){
				arr[k++]=i*3+j;
				check=1;
			}
		}
	}
	if(check!=0){
		k--;
		srand(time(NULL));
		int n=rand();
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
	
	// x==-1 case not taken care
	// for putting opponent not win the grid neither stop you from winning the grid
	int flagwin=0;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(placeen[i][j][0]==-1)&&(placeme[i][j][0]==-1)){
				arr[k++]=i*3+j;
				flagwin=1;
			}
		}
	}
	if(flagwin!=0){
		k--;
		srand(time(NULL));
		int n=rand();
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
	
	// x==-1 case not taken care
	// for putting opponent in a grid where he played zero times
	int flag=0;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(numofen[i][j]==0)){
				arr[k++]=i*3+j;
				flag=1;
			}
		}
	}
	if(flag!=0){
		k--;
		srand(time(NULL));
		int n=rand();
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
	
	
	
	// x==-1 case not taken care
	// for putting opponent in a grid where he played only once
	int flag1=0;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(numofen[i][j]==1)){
				arr[k++]=i*3+j;
				flag1=1;
			}
		}
	}
	if(flag1!=0){
		k--;
		srand(time(NULL));
		int n=rand();
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
	
	
	
	// x==-1 case not taken care
	// for pushing into grid where he can't win and I can win
	int flaglost=0;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(placeen[i][j][0]==-1)&&(placeme[i][j][0]!=-1)){
				arr[k++]=i*3+j;
				flaglost=1;
			}
		}
	}
	if(flaglost!=0){
		k--;
		srand(time(NULL));
		int n=rand();
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
	
	
	
	// x==-1 case not taken care of
	// for putting him in a grid where he can win and I has played least
	int flaglose=0,min=9,index=-1;
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if((board[dx][dy][i][j]=='.')&&(placeen[i][j][0]!=-1)&&(!(w_win( win , ensym , placeen , *x , *y , &genx , &geny)))){
				arr[k++]=i*3+j;
				if(numofme[i][j]<min){
					index=k-1;
					min = numofme[i][j];
				}
				flaglose=1;
			}
		}
	}
	if(index!=-1){
		k=index;
		int n=arr[k];
		if(k!=0)
			k=n%k;
		n=arr[k];
		*playx=n/3;
		*playy=n%3;
		return;
	}
}
