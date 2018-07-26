/* Game of Life
 * Matt Freed
 * Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"


/** arrayCompare function. USed to compare 2 arrays to check similairity
 * @param array1 one of the arrays you wish to compare
 * @param array2 the second array you wish to compare
 * @param row the total rows of the array to compare
 * @param column the total columns of the arrays you wish to compare
 *
 * @return count which is the number of differences between the 2 arrays
 *
 */
int arrayCompare(char** array1, char** array2,int row, int column){
	int count = 0;//keeps track of the number of differences between the 2 arrays
	for (int i=0;i<row;i++){//loops through the rows and columns of the array, comparing each cell to find differences
		for(int j=0;j<column;j++){
			if(array1[i][j]!=array2[i][j]){//if the cells !=, add 1 to the difference count
				count++;
			}
		}
		//invariants: i>=0, i<row, count will never be greater than the area of the array
		//j<=0, j<column
	}
	if (count>0){//if there is any difference in the array, that means there was not a duplicate
		return 1;
	}
	return 0;
}

/** maxLineDimension function. Determines the maximum height and width of the input file
 * @param file the file being input
 * @param pheight the pointer to the height of the file to find
 * @param pwidth the pointer to the width of the file to compare
 *
 *
 * @return EXIT_SUCCESS when completed
 *
 */
//determines maximum size of input file
int maxLineDimension(FILE* file, int* pheight, int* pwidth){
	int width = 0, height = 1, maxLineLength = 0;//initializes the width and height of the array
	char current;//keeps track of the current character from fgetc()
	while((current=fgetc(file)) != EOF)//while you arent at the end of the file. determines largest width/height
	{
		if (current !='\n'){// checks to see if an end line, if not increase the width size
			width++;
		}
		else {
			height++;//increase the height by 1 if you do reach an endline
			width=0;//restart the width to 0 to determine the next line length
		}
		if (maxLineLength < width){//if the width is largest than the previous width, this is the new max size
			maxLineLength = width;
		}
	}
	*pheight=height;//pointer of height is now set to new height
	*pwidth = maxLineLength;//pointer of width is now set to new max width
	rewind(file);//rewinds the file to the beginning
	return EXIT_SUCCESS;
}
/** addChars function. takes the input file and adds the characters to the initial grid
 * @param file the input file
 * @param grid pointer to the 2d array you wish to add chars to
 * @param startRow is the row you wish to start printing to
 * @param startColumn is the column you wish to start printing to
 * @param endRow the final row to print to when inserting characters
 *
 * @return EXIT_SUCCESS when completed
 *
 */
int addChars(FILE* file, char** grid, int startRow, int startColumn, int endRow){
	for (int i = startRow; i<= endRow;i++){//loops specified row
		int j=startColumn;// sets startColumn to an incrementable variable
		char current;// keeps track of the current fgetc value
		while((current=fgetc(file))!=EOF){//while the file has not reached its end, continue to run
			if (current != '\n'){//if the current value is not an endline, assign the char to this row/column
				if(current == 'o'){//set all o's to spaces
					grid[i][j] = ' ';
					j++;
				}
				else{//otherwise insert the x's into the array
					grid[i][j] = current;
					j++;
				}
			}
			else{//start on next row and reset the column
				i++;
				j=startColumn;
			}
		}
	}
	//i>=startRow, i<=endRow
	rewind(file);// rewind the cursor back to the beginning to be able to read correctly again
	return EXIT_SUCCESS;
}
/** middle function. Used to find the middle of an array
 * @param rc is either row or column to find the middle
 *
 * @return the middle column/row location
 *
 */
int middle(int rc){
	int middleC;//represents the middle of the row/column
	if (rc%2!=0){//determine if array is size even or odd, find center
		middleC=((rc+1)/2);
		}
	else{
		middleC=((rc)/2);
		}
	return middleC;
	}

/** loadGrid function. Used to load the initial grid and load in the main file to this grid
 * @param file is the input file
 * @param grid is the initial grid
 * @param row is the total rows of the main grid
 * @param column the total columns of the main grid
 *
 * @return EXIT_SUCCESS when this function is executed
 *
 */
int loadGrid(FILE* file, char** grid, int row, int column){
	int height, width; //height and width of starting small grid
	int middleR, middleC; //middle row and column of the base grid
	int startR, startC, endR;//center of grid where file should start and stop

	maxLineDimension(file, &height, &width);//calls the maxLineDimension function
	middleC=middle(column);//finds the middle column
	//printf("middleC=%d \n",middleC);
	middleR=middle(row);//finds the middle row
	//printf("middleR=%d\n", middleR);

	startR=(middleR-(height/2));//starting point of the file print for row
	startC=(middleC-(width/2));//starting point for the file print of column
	endR=(middleR+(height/2));//ending row
	//printf("startR=%d \n",startR);
	//printf("startC=%d \n",startC);
	//printf("endR=%d \n",endR);


	addChars(file, grid, startR, startC, endR);//adds the characters to the centered grid

	return EXIT_SUCCESS;
}
/** countNeighbors function. Counts the surrounding neighbors of the given cell
 * @param g is the grid currently getting checked
 * @param row is the total rows
 * @param col is the total columns
 * @param w is the width of the array
 * @param h is the height of the array
 *
 * @return count which is the number of neighbors that cell has
 *
 */
int countNeighbors(char** g,int row,int col,int w,int h){
	int count = 0;//initial neighbor count set to 0. keeps track of neighbors
	for(int i = row-1;i<=row+1;i++){//from the row above the cell moving to the row below the cell
		for(int j=col-1;j<=col+1;j++){//from the column on the left of the cell to the column to the right of the cell
			if((i==row && j==col) || i<0 || j<0 || i>w || j>h){//if there is no left or right column/row, continue. dont count the cell itself
				continue;
			}
			else if(g[i][j] == 'x'){//if the cells adjacent contain an x, increase the count by 1
				count++;
			}
		}
		//invariants: i>= (row -1), i <=(row+1), count>=0, count<=8
	}
	return count;
}
/** updateSurroundings function. updates the generation from the previous to the next. populates the new array
 * @param gridA is the current array
 * @param gridB is the next generation array
 * @param row the current row
 * @param column the current column
 * @param maxRow is the maxRow of the array
 * @param maxColumn is the max column size of the array
 *
 * @return EXIT_SUCCESS when completed
 *
 */
int updateSurroundings(char** gridA, char** gridB, int row, int column, int maxRow, int maxColumn){

	for(int r = 0; r<=maxRow;r++){//starting at row 0 to last row
		for(int c = 0; c<=maxColumn;c++){//starting from first column to last column
			int numN = countNeighbors(gridA,r,c,maxRow,maxColumn);// numN is equal to the amount of adjacent x's to the cell
			if(numN<=1 || numN>=4){//determines the cell output
				gridB[r][c] = ' ';
			}
			else if(numN == 2){//determines cell output
				gridB[r][c] = gridA[r][c];
			}
			else{//determines cell output
				gridB[r][c] = 'x';
			}
		}
		//invariants: r>=0,r<=maxRow, c>=0, c<=macColumn, numN>=0
	}

	return EXIT_SUCCESS;
}
/** playONE function. Cycles through one generation of the game
 * @param gridA is the initial array
 * @param gridB is the next generation array
 * @param row the total rows of the array to compare
 * @param column the total columns of the arrays you wish to compare
 *
 * @return EXIT_SUCCESS when completed
 *
 */
int playOne(char** gridA, char** gridB,int row, int column){
	int maxColumn = (column-1);//the max position of the column in the array
	int maxRow=row-1;//the max row position in the array
	for(int i = 0; i<row; i++){//updates the next generation array. loops through rows
		for(int j = 0; j<column; j++){//loops through columns
			updateSurroundings(gridA,gridB,i,j,maxRow, maxColumn);
		}
	}
	//invariants: i>=0, i<row, j>=0, j<column

	return EXIT_SUCCESS;
}

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 */

int main(int argc, char **argv) {
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int rows; // Number of rows in the grid
	int columns; // Number of columns in the grid
	int gens; // Number of generations to produce
	int doPrint; // 1 if user wants to print each generation, 0 if not
	int doPause; // 1 if user wants to pause after each generation, 0 if not
	char **gridA; // A 2D array to hold the pattern
	char **gridB; //Holds the updated new grid
	char **gridC; //A 2D array to hold the previous gridA pattern
	char currentGen = 'A'; //the current generation for looping

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]);
	gens = atoi(argv[3]);
	if (gens<=0){//if the input is less than 1 will return an error
		printf("generations has to be greater than 0\n");
		return EXIT_FAILURE;
	}
	inputFileName = argv[4];

	//checks to see which argument was passed through command line for doPrint and doPause
	switch(argc){
		case 6:
			switch(argv[5][0]){
				case 'y':
					doPrint = 1;
					break;
				case 'n':
					doPrint = 0;
					break;
				default:
					printf("Usage:\n");
					printf("  ./life rows columns generations inputFile [print] [pause]\n Print = y or n");
					return EXIT_FAILURE;
			}
			break;
		case 7:
			switch(argv[5][0]){
				case 'y':
					doPrint = 1;
					switch(argv[6][0]){
						case 'y':
							doPause = 1;
							break;
						case 'n':
							doPause = 0;
							break;
						default:
							printf("Usage:\n");
							printf("  ./life rows columns generations inputFile [print] [pause]\n Pause = y or n");
							return EXIT_FAILURE;
					}
					break;
				case 'n':
					doPrint = 0;
					switch(argv[6][0]){
						case 'y':
							doPause = 1;
							break;
						case 'n':
							doPause = 0;
							break;
						default:
							printf("Usage:\n");
							printf("  ./life rows columns generations inputFile [print] [pause]\n Pause = y or n");
							return EXIT_FAILURE;
					}
					break;
				default:
					printf("Usage:\n");
					printf("  ./life rows columns generations inputFile [print] [pause]\n Print = y or n");
					return EXIT_FAILURE;
			}
			break;
	}
	/* Here is how you would allocate an array to hold the grid.
	*/
	gridA = make2Dchar(rows, columns);//allocates array sizes
	gridB = make2Dchar(rows, columns);
	gridC = make2Dchar(rows, columns);

	// You should check that it succeeded.
	if (gridA == NULL){//checks if null grid size for memory error
		printf("Memory Allocation Error\n");
		return EXIT_FAILURE;
	}

	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");//opens the input file
	if (!input) {//if not a valud input, print out error message
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}
	//initializes gridA with spaces
	for (int i =0; i<rows; i++){
		for(int j = 0; j<columns;j++ ){
			gridA[i][j] = ' ';
		}
	//i>=0, i<rows
	}

	loadGrid(input,gridA,rows,columns);

	//prints the generations
	for(int i=0; i<gens;i++){
		//checks for duplicate and oscillations
		if(arrayCompare(gridA,gridB,rows,columns)==0){//checks duplicates/Osc for array A and B
			if(currentGen=='B'){
				printf("Duplicate pattern as previous print A");
				printf("Generations played: %d \n",(i+1));
			}
			else{
				printf("Oscillation");
				printf("Generations played: %d \n",(i+1));
			}
			return EXIT_SUCCESS;
		}

		if(arrayCompare(gridB,gridC,rows,columns)==0&&i>1){//checks duplicates/Osc for array B and C
			if(currentGen=='C'){
				printf("Duplicate pattern as previous print B");
				printf("Generations played: %d \n",(i+1));
			}
			else{
				printf("Oscillation");
				printf("Generations played: %d \n",(i+1));
			}
			return EXIT_SUCCESS;
		}
		if(arrayCompare(gridC,gridA,rows,columns)==0&&i>1){//checks duplicates/Osc for array C and A
			if(currentGen=='A'){
				printf("duplicate pattern as previous print C");
				printf("Generations played: %d \n",(i+1));
			}
			else{
				printf("Oscillation");
				printf("Generations played: %d \n",(i+1));
			}
			return EXIT_SUCCESS;
		}
		if(i==0){//prints the first initial generation of the file
			if(doPrint==1){//if doprint is active
				printf("\n Generation 1\n");
				for (int j=0; j<rows; j++){//prints the initial grid
					for(int k = 0; k<columns;k++ ){
						printf("%c",gridA[j][k]);
					}
						printf("\n");
				}
			printf("\n");
			}
			continue;//skips the rest of the ifs to continue the generation
		}

		if (doPause==1){//if pause is y, ask for user input after every generation
				printf("\n Press enter to continue \n");
				scanf("%*c");
				}

		if (currentGen == 'A'){//loops through the generation set, printing the updated generation
			playOne(gridA,gridB,rows,columns);
			currentGen = 'B';
			if (doPrint==1){
				printf("Generation %d \n",(i+1));
				for (int j =0; j<rows; j++){//prints the grid
						for(int k = 0; k<columns;k++ ){
							printf("%c",gridB[j][k]);
							}
							printf("\n");
						}
				printf("\n");
			}

		}
		else if(currentGen == 'B'){//loops through the generation set, printing the updated generation
			playOne(gridB,gridC,rows,columns);
			currentGen = 'C';
			if (doPrint==1){
				printf("Generation %d \n",(i+1));
				for (int j =0; j<rows; j++){//prints the grid
					for(int k = 0; k<columns;k++ ){
						printf("%c",gridC[j][k]);
						}
						printf("\n");
						}
				printf("\n");
					}

		}
		else{//loops through the generation set, printing the updated generation
			playOne(gridC,gridA, rows, columns);
			currentGen = 'A';
			if (doPrint==1){
				printf("Generation %d \n",(i+1));
				for (int j =0; j<rows; j++){//prints the grid
					for(int k = 0; k<columns;k++ ){
						printf("%c",gridA[j][k]);
						}
						printf("\n");
						}
				printf("\n");
				}
		}

	}
	//invariant: i>=0, i<gens

	printf("end of generations \n");//prints the endding result
	printf("Generations played: %d \n",gens);//prints the number of generations played
	printf("Final Board: \n");
	if (currentGen=='A'){//prints the final board
		for (int j =0; j<rows; j++){//prints the grid
			for(int k = 0; k<columns;k++ ){
				printf("%c",gridA[j][k]);
					}
				printf("\n");
					}
				printf("\n");
					}
	//invariants: j>=0, j<rows, k>=0, k< columns
	else if (currentGen=='B'){
		for (int j =0; j<rows; j++){//prints the grid
			for(int k = 0; k<columns;k++ ){
				printf("%c",gridB[j][k]);
							}
				printf("\n");
							}
				printf("\n");
							}
	//invariants: j>=0, j<rows, k>=0, k< columns
	else{
		for (int j =0; j<rows; j++){//prints the grid
			for(int k = 0; k<columns;k++ ){
				printf("%c",gridC[j][k]);
							}
				printf("\n");
							}
				printf("\n");
							}
	//invariants: j>=0, j<rows, k>=0, k< columns

	return EXIT_SUCCESS;
}
