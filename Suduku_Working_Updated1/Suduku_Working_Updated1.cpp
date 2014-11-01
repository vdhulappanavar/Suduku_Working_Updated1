// CompleteSuduko1.cpp : Defines the entry point for the console application.
//developed by : Vidya Dhulappanavar

//*************************************************************************************************
//***********Pre-Proccessor Directives************************************************************
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
//***********Pre-Proccessor Directives************************************************************
//*************************************************************************************************

//***************************************************************************************************************
//*******************************Constants***********************************************************************
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define GRID_CELL_SIZE_X 4
#define GRID_CELL_SIZE_Y 3
//*******************************Constants***********************************************************************
//***************************************************************************************************************


//***************************************************************************************************************
//**************USER DEFINED FUNCTIONS***************************************************************************
void intilize_sudoko();
int backtrack(int oldrow , int oldcol, int *newrow , int *newcol);
void BacktrackFor1stGird();
void InitilizeOutputMatrix();
void FindSolution();
void printgridIndex();
void placeNumber(int row , int col);
int getno(int i,int j);
int checkNumber(int sno, int row ,int col);
int CheckRow(int sno , int row, int col);
int CheckCol(int sno , int row, int col);
int checkOriginal(int row,int col);
int CheckBox(int sno , int row, int col);
void printInputMatrix();
void printOutputMatrix();
void BacktrackFor1stGird();
void GotoXY(int x, int y);
void gotoxy(int x, int y);
void print1stPage();
void printSingleGrid(int x , int y);
void printGrid();
void Intilize1stValue();
void ReadAtXY();
void Delay();
void InitilizeInputMatrix();
void moveNext(int *xpos , int  *ypos);
int CheckIfInvalid();
void print2ndPage();
void printMenu();
//**************USER DEFINED FUNCTIONS**************************************************************************
//***************************************************************************************************************

//***************************************************************************************************************
int IndexCount=0;
int FirstGridRow=0 , FirstGirdCol=0;
int InputMatrix[9][9];
int OutputMatrix[9][9];

int BoxIndex[9][2]={ {2,2} , {2,5} , {2,8} , {5,2} , {5,5} , {5,8} , {8,2} , {8,5}, {8,8} };
int xrefinitial=72, yrefinitial=21;
int xreffinal=xrefinitial+(8*GRID_CELL_SIZE_X) , yreffinal=yrefinitial+(8*GRID_CELL_SIZE_Y);
//***************************************************************************************************************


//***************************************************************************************************************
//******************STRUCTURES***********************************************************************************
struct pos
{
	int row;
	int col;

} orgSudo[9],gridIndex[60];


struct pos1
{
	int X;
	int Y;
}b;
//******************STRUCTURES***********************************************************************************
//***************************************************************************************************************


int _tmain(int argc, _TCHAR* argv[])
{
	intilize_sudoko();
	print1stPage();
	fflush(stdin);
	system("cls");
	print2ndPage();
	fflush(stdin);
	system("cls");
	printMenu();
    fflush(stdin);
	system("cls");
	/*printGrid();
	GotoXY(xrefinitial,yrefinitial);
	ReadAtXY();*/
	getch();
	return 0;
}

void intilize_sudoko()
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			InputMatrix[i][j]=0;
			OutputMatrix[i][j]=0;
		}
	}
}


void Intilize1stValue()
{
	int i,j, flag=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(OutputMatrix[i][j]==0)
			{
				FirstGridRow=i;
				FirstGirdCol=j;
				flag=1;
				break;
			}
			if(flag==1)
				break;
		}
	}
}

void print2ndPage()
{
   printf("SUDOKU:\n\t Sudoku is a number puzzle in which The objective is to fill a 9×9 grid with digits so that each column, each row, and each of the nine 3×3 sub-grids that compose the grid");
   printf("\nThe puzzle was popularized in 1986 by the Japanese puzzle company Nikoli, under the name Sudoku");
   printf("\nPress Enter to go to the next page");
   getch();
}

void printMenu()
{
	int ch,i;
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t");
	for(i=0;i<130;i++)
	{
		printf("*");
	}
	printf("\n");
	printf("\t\t\t*%45cWhat does this application/programe do?%45c\n",32, 42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%28cThis application/programe can find the solution to a user entered sudoku %28c\n",32,42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%40cOPTIONS:%81c\n",32,42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%40cEnter 1-to get a blank sudoku grid%55c\n",32,42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%40cEnter 2-to print a pre defined sudoku%52c\n",32,42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%40cEnter 3 or q or press esc-to quit the game%47c\n",32,42);
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t*%40cEnter Your Choice and then press Enter Key:%46c\n",32,'*');
	printf("\n\t\t\t*%129c\n",'*');
	printf("\t\t\t");
	for(i=0;i<130;i++)
	{
		printf("*");
	}
	GotoXY(110, 29);
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printGrid();
			GotoXY(xrefinitial,yrefinitial);
			ReadAtXY();	
			break;
		case 2:
			read_no();
			Intilize1stValue();
			FindSolution();
			GotoXY(3, 77);
			printOutputMatrix();
			getch();				
			break;
		case 3:
		case 113:
		case 27:
	}
}

void BacktrackFor1stGird()
{
	int i, value;
	value=OutputMatrix[FirstGridRow][FirstGirdCol];
	for(i=1;i<9;i++)
	{
	
	   if((i != value) && (checkNumber(i, FirstGridRow  ,FirstGirdCol)))
	   {
		   OutputMatrix[FirstGridRow][FirstGirdCol]=i;
	   }
	}
}

void InitilizeOutputMatrix()
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			OutputMatrix[i][j]=InputMatrix[i][j];
		}
	}
}



void FindSolution()
{  
	int i,j;
	for(i=0;i<9;i++)
	{
	  for(j=0;j<9;j++)
	  {
         if(OutputMatrix[i][j]==0) 
		 {
			 placeNumber(i,j);
		 }
      }
	}
}

void placeNumber(int row , int col)
{ 
	int i=row,j=col;
  	int newrow, newcolumn;
	int value;
	if (row > 9 || col > 9 || row < 0 || col < 0)
		return;
	value=getno(i,j);
	if(value!=-1)
		 OutputMatrix[i][j]=value;
	else 
	{
		OutputMatrix[i][j] = 0;
		int retVal = backtrack(i,j, &newrow, &newcolumn);
		if (retVal == -1)
		{
			return;
		}
        placeNumber(newrow , newcolumn);
		placeNumber(i,j);
	}

}

int getno(int i,int j)
{
	int sno=OutputMatrix[i][j]+1;
	if(checkOriginal(i,j))
	{
		return OutputMatrix[i][j];
	}

	while(!checkNumber(sno , i , j) && sno <= 9)
	{
		sno++;
	}
	if(sno==10)
		return -1;
	return sno;
}

int checkNumber(int sno, int row ,int col)
{
	if(CheckRow(sno , row , col))
	{
		if(CheckCol(sno ,row, col))
		{
			if(CheckBox( sno , row, col))
			{
				return true;
			}
		}
	}
	return false;
}

int CheckRow(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
	{
		if(sno==OutputMatrix[row][i] && col != i)
			return false;
	}
	return true;
}

int CheckCol(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
		if(sno==OutputMatrix[i][col] && row != i)
			return false;
	return true;
}

int CheckBox(int sno , int row, int col)
{
	int i,j, boxrow , boxcol;
	for(i=0;i<9;i++)
	{
		if(row <= BoxIndex[i][0] && col <= BoxIndex[i][1])
		{
			boxrow=BoxIndex[i][0]-2;
			boxcol=BoxIndex[i][1]-2;
			break;
		}
	}

	for(i=0;i<3;i++)
	{
        for(j=0;j<3;j++)
		{
			if(i+boxrow!=row && j+boxcol!=col && OutputMatrix[i+boxrow][j+boxcol]==sno)
				return false;
		}
	}
	return true;
}
int checkOriginal(int row,int col)
{
	int i;
	for(i=0;i<IndexCount;i++)
	{
		if(row==gridIndex[i].row && col==gridIndex[i].col)
			return true;
	}
	return false;
}

int backtrack(int oldrow , int oldcol, int *newrow , int *newcol)
{
	*newrow=oldrow;
	*newcol=oldcol;
	if(*newrow==0 && *newcol==0)
		return -1;
	if(oldcol< 9 && oldcol>0)
		*newcol=oldcol-1;
	else if(oldcol==0 && *newrow > 0)
	{
		*newrow=oldrow-1;
		*newcol=8;
	}

	if(*newrow < 0 || *newcol < 0)
	{
		*newrow = 0;
		*newcol = 0;
		return -1;
	}
	if(checkOriginal(*newrow, *newcol))
		return backtrack(*newrow, *newcol , newrow, newcol);
	else
		return 1;
}

void printInputMatrix()
{
	int i,j;
	printf("Input Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", InputMatrix[i][j]);
		}
		printf("\n");
	}
}
void printOutputMatrix()
{
	int i,j;
	printf("Output Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", OutputMatrix[i][j]);
		}
		printf("\n");
	}
}

void printgridIndex()
{
	int i,j;
	printf("grid index \n");
	for(i=0;i<IndexCount;i++)
	{
			printf("%3d  %3d", gridIndex[i].row , gridIndex[i].col);
	}
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void print1stPage()
{
	GotoXY(60,20);
	printf("*************************************\n");
	GotoXY(60,21);
	printf("*************************************\n");
	GotoXY(72,22);
	printf("WELCOME TO THE SUDOKU GAME");
	GotoXY(72,23);
	printf("*************************************\n");
	GotoXY(72,24);
	printf("*************************************\n");
	int ch = getch();
	if (ch == 127)
		printf("Backspace");
	//fflush(stdout);

}

void printSingleGrid(int x, int y)
{
	GotoXY(x,y);
	printf("%c%c%c%c%c",218,196,196,196,191);
	GotoXY(x,y+1);
	printf("%c   %c",179,179);
	GotoXY(x,y+2);
	printf("%c   %c",179,179);
	GotoXY(x,y+3);
	printf("%c%c%c%c%c",192,196,196,196,217);
}

void printGrid()
{
	int i,j,x=70 , y=19;
	char ch;
	for(i=0;i<9;i=i++)
	{
		for(j=0;j<9;j++)
		{
			printSingleGrid(x,y);
			x=x+GRID_CELL_SIZE_X;
		}
		x=70;
		y=y+GRID_CELL_SIZE_Y;
	}
}

void ReadAtXY()
{
	char key;
	int ch;
	int val,i=0;
	int xpos=xrefinitial,ypos=yrefinitial;
	do
	{
		key=getch();
		val = key;
		if(key==127 || key == 8)
		{
			GotoXY(xpos,ypos);
			printf(" ");
		}
		if(key==RIGHT && xpos==xreffinal && ypos<(yreffinal) && ypos>=yrefinitial)//37)
		{
			ypos=ypos+GRID_CELL_SIZE_Y; xpos=xrefinitial; GotoXY(xpos,ypos);
		}
		
		else if(key==RIGHT && xpos<(xreffinal)/*107*/ && xpos>=xrefinitial)
		{
			xpos=xpos+GRID_CELL_SIZE_X; GotoXY(xpos,ypos);
		}
		
		//checkin if the cursor is in first column and in any row other than the first row;
		if(key==LEFT && xpos==xrefinitial && ypos<=(yreffinal) && ypos>yrefinitial)
		{
			ypos=ypos-GRID_CELL_SIZE_Y; xpos=xreffinal; GotoXY(xpos,ypos);
		}
		
		else if(key==LEFT && xpos<=xreffinal && xpos>xrefinitial)
		{
			xpos=xpos-GRID_CELL_SIZE_X; GotoXY(xpos,ypos);
		}
		if(key==UP&& ypos>yrefinitial && ypos<=(yreffinal))
		{
			ypos=ypos-GRID_CELL_SIZE_Y; GotoXY(xpos,ypos);
		}
		if(key==DOWN && ypos>=yrefinitial && ypos<(yreffinal))
		{
			ypos=ypos+GRID_CELL_SIZE_Y; GotoXY(xpos,ypos);
		}
		if (key == 's') //Submit to solve
		{
			InitilizeOutputMatrix();
			GotoXY(3, 40);
			printInputMatrix();
			if(CheckIfInvalid())
			{
				Intilize1stValue();
				FindSolution();
				GotoXY(3, 77);
				printOutputMatrix();
				getch();
				break;
			}
			else
			{
				GotoXY(xrefinitial, yreffinal+5);
				printf("INVALID SUDOKO");
				system("cls");
				printMenu();
			}
		}
		/*if (key == 27) //ESC
		{
			break;
		}*/
				
		if(key>'0' && key<='9')
		{
			val = key - 48;
			InputMatrix[(ypos/GRID_CELL_SIZE_Y)-7][(xpos/GRID_CELL_SIZE_X)-18]=val;
			gridIndex[IndexCount].row=(ypos/GRID_CELL_SIZE_Y)-7;
			gridIndex[IndexCount].col=(xpos/GRID_CELL_SIZE_X)-18;
			IndexCount++;
			printf("%d",val);
			moveNext(&xpos , &ypos);
		}
		
	}
	while(1);
}

int CheckIfInvalid()
{
	int i=0,flag=0;
	for(i=0;i<IndexCount;i++)
	{
		if(checkNumber(InputMatrix[gridIndex[IndexCount].row][gridIndex[IndexCount].col] , gridIndex[IndexCount].row , gridIndex[IndexCount].row))
		{
			flag=0;
		}

		else
		{
			return false;
		}

		return true;
	}
}
void moveNext(int *xpos , int *ypos)
{
	//checking if the postion lies in between the 1st col and last col and if so moving to the right cell
	if(*xpos<xreffinal && *ypos>=yrefinitial && *ypos<=(yreffinal) && *xpos>=xrefinitial)
	{
		*xpos=*xpos+GRID_CELL_SIZE_X;
		GotoXY(*xpos, *ypos);
	}
	//checkig if the cursor is in the last column the we move the cursor to the 1st cell of the next row
	else if(*xpos==(xreffinal) && *ypos>=yrefinitial && *ypos<(yreffinal))
	{
		*ypos=*ypos+GRID_CELL_SIZE_Y;
		*xpos=xrefinitial;
		GotoXY(xrefinitial , *ypos);
	}
	//checking if the cursor is in the last row last coulmn then we move the cursor to the first cell
	else if(*xpos==(xreffinal) && *ypos==(yreffinal))
	{
		*xpos=xrefinitial;
		*ypos=yrefinitial;
		GotoXY(xrefinitial, yrefinitial);
	}
	
}

void Delay()
{
    long double i;
    for(i=0; i<=(10000000); i++);
}

void InitilizeInputMatrix()
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			InputMatrix[i][j]=0;
		}
	}
}

void read_no()
{
	int gIndex=0;
	//Grid-1
	{
		InputMatrix[0][1] = 1;
		gridIndex[gIndex].row = 0;
		gridIndex[gIndex].col = 1;
		gIndex++;	

		InputMatrix[0][3] = 2;
		gridIndex[gIndex].row = 0;
		gridIndex[gIndex].col = 3;
		gIndex++;

		InputMatrix[0][5] = 8;
		gridIndex[gIndex].row = 0;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[1][3] = 9;
		gridIndex[gIndex].row = 1;
		gridIndex[gIndex].col = 3;
		gIndex++;

		InputMatrix[1][5] = 5;
		gridIndex[gIndex].row = 1;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[1][7] = 7;
		gridIndex[gIndex].row = 1;
		gridIndex[gIndex].col = 7;
		gIndex++;


		InputMatrix[2][0] = 2;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 0;
		gIndex++;

		InputMatrix[2][1] = 5;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 1;
		gIndex++;
		
		InputMatrix[2][2] = 6;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 2;
		gIndex++;

		InputMatrix[2][3] = 1;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 3;
		gIndex++;
		
		InputMatrix[2][6] = 3;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 6;
		gIndex++;

		InputMatrix[2][7] = 8;
		gridIndex[gIndex].row = 2;
		gridIndex[gIndex].col = 7;
		gIndex++;
	}
	//Grid-2
	{
		InputMatrix[3][5] = 6;
		gridIndex[gIndex].row = 3;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[3][7] = 1;
		gridIndex[gIndex].row = 3;
		gridIndex[gIndex].col = 7;
		gIndex++;

		InputMatrix[3][8] = 8;
		gridIndex[gIndex].row = 3;
		gridIndex[gIndex].col = 8;
		gIndex++;

		InputMatrix[4][0] = 5;
		gridIndex[gIndex].row = 4;
		gridIndex[gIndex].col = 0;
		gIndex++;

		InputMatrix[4][1] = 6;
		gridIndex[gIndex].row = 4;
		gridIndex[gIndex].col = 1;
		gIndex++;

		InputMatrix[4][4] = 1;
		gridIndex[gIndex].row = 4;
		gridIndex[gIndex].col = 4;
		gIndex++;

		InputMatrix[4][7] = 9;
		gridIndex[gIndex].row = 4;
		gridIndex[gIndex].col = 7;
		gIndex++;

		InputMatrix[4][8] = 2;
		gridIndex[gIndex].row = 4;
		gridIndex[gIndex].col = 8;
		gIndex++;

		InputMatrix[5][0] = 8;
		gridIndex[gIndex].row = 5;
		gridIndex[gIndex].col = 0;
		gIndex++;
		
		InputMatrix[5][1] = 7;
		gridIndex[gIndex].row = 5;
		gridIndex[gIndex].col = 1;
		gIndex++;

		InputMatrix[5][3] = 4;
		gridIndex[gIndex].row = 5;
		gridIndex[gIndex].col = 3;
		gIndex++;


	}

	//Grid-3
	{
		InputMatrix[6][1] = 4;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 1;
		gIndex++;


		InputMatrix[6][2] = 2;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 2;
		gIndex++;


		InputMatrix[6][5] = 1;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 5;
		gIndex++;


		InputMatrix[6][6] = 9;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 6;
		gIndex++;


		InputMatrix[6][7] = 5;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 7;
		gIndex++;


		InputMatrix[6][8] = 7;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 8;
		gIndex++;


		InputMatrix[7][1] = 9;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 1;
		gIndex++;

		InputMatrix[7][3] = 3;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 2;
		gIndex++;

		InputMatrix[7][5] = 7;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[8][3] = 5;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 3;
		gIndex++;

		InputMatrix[8][5] = 2;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[8][7] = 3;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 7;
		
		IndexCount=gIndex;
	}

}
