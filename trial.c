#include<stdio.h>
#include<stdlib.h>
void capture( FILE *fp , char ****board , int *x , int *y );
void wincapture( char ****board , char **win);
char gridcheck( char ****board , int i , int j);
void mysym( char ****board , char *sym );
void printboard( char ****board , int x , int y );
void bestmove( char ****board , char **win , int *x , int *y , int *playx , int *playy , char mysym , char ensym);
void gridwin(char ****board , char **win , int x , int y , int ***placex  , char mysym , char ensym);
void enwinstop(char ****board , char **win , int x , int y , int ***placex , char mysym , char ensym);
void numofplays(char **** board , int ** numofx , int **numofo );
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
	int cpx,cpy,cenx,ceny;
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
	gridwin( board , win , *x , *y , placex , mysym , ensym);
	
	enwinstop( board , win , *x , *y , placeo , mysym , ensym);
	
	int  **numofx , **numofo;
	numofx=(int **)malloc(sizeof(int *)*3);
	numofo=(int **)malloc(sizeof(int *)*3);
	for(i=0;i<3;i++){
		numofx[i]=(int *)malloc(sizeof(int)*3);
		numofo[i]=(int *)malloc(sizeof(int)*3);
	}
	
	numofplays( board , numofx , numofo );
	
	// change these coordinates
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
