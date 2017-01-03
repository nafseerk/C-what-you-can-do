#include<stdio.h>
#include<stdlib.h>



int place(int X[][9],int row,int num,int table[][9])
//returns 1 if "num" can be placed in position "row","X[row,num]". Else return 0
//X[row,num] gives the column number of "num" in "row"
{
int i;
if(num<1||num>9||row<0||row>8)return 0;
num=num-1;   //num is used as column index of solution array X.

for(i=0;i<9 && i!=num;i++)
 if(table[row][i]==X[row][num])return 0;

for(i=0;i<row;i++)            // check positions of same number upto row-1
 if( X[i][num]==X[row][num] || ( (i/3==row/3) && (X[i][num]/3==X[row][num]/3) ) )
  return 0;
for(i=row+1;i<9;i++)
if(table[i][num]!=-1 && (table[i][num]==X[row][num] || ( (i/3==row/3) && (table[i][num]/3==X[row][num]/3) ) ))
  return 0;

for(i=0;i<num;i++)        // check if some other placed in same position
 if(X[row][i]==X[row][num])
  return 0;
for(i=num+1;i<9;i++)
 if(table[row][i]!=-1&&table[row][i]==X[row][num])
  return 0;


return 1;

}

void read_table(int problem[][9],int table[][9])
{
int i,j;
printf("Enter the sudoku\nput 0 for blanks\n");

//initialise solution array
for(i=0;i<9;i++)
 for(j=0;j<9;j++)
  table[i][j]=-1;


for(i=0;i<9;i++)
 for(j=0;j<9;j++)
  {
  scanf("%d",&problem[i][j]);
  if(problem[i][j]!=0)table[i][problem[i][j]-1]=j;
  }


}

void print_sudoku(int X[][9])
{
int i,j;
int temp[9][9];

for(i=0;i<9;i++)
 for(j=0;j<9;j++)
  temp[i][X[i][j]]=j+1;

for(i=0;i<9;i++)
 {
 for(j=0;j<9;j++)
  printf("%d  ",temp[i][j]);
 printf("\n");
 }

}

void sudoku(int X[][9],int table[][9],int problem[][9])
{
int row,number;
long int n=0;
row=0;
number=0;   //numbers 0 to 9-1 since it is used as column index of solution array

X[0][0]=-1;

while(number>=0)
{
if(table[row][number]!=-1)X[row][number]=table[row][number];
else
 {
 X[row][number]=X[row][number]+1;
 while(X[row][number]<9 && place(X,row,number+1,table)==0)
  X[row][number]=X[row][number]+1;
 }
if(X[row][number]<9)
 {
 if(row==8)
  {
  if(number==8){n++; printf("Sudoku no.%ld\n",n);print_sudoku(X); }
  else { row=0; number++; X[row][number]=-1;}
  }
 else
  {
  row++;
  X[row][number]=-1;
  }

 }
else if(row==0)
 {
  number--;
  row=8;
  while(table[row][number]!=-1)
  {
  if(row==0){number--; row=8;}
  row--;
  }
  }
else
 {
 row--;
 while(table[row][number]!=-1)
  {
  if(row==0){number--; row=8;}
  row--;
  }
 }

}


}


int main()
{
int solution[9][9];
int problem[9][9],table[9][9];
read_table(problem,table);
sudoku(solution,table,problem);
}
