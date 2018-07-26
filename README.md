# 2303HW2

Matthew Freed
Assignment 2
Game Of Life


Program Summary:

	This programs simulates Conway's "Game of Life". It represents population growth of individual cells in an "infinite" grid. This program uses a finite grid. Each generation of the grid changes depending on how the grid is initially populated and the adjacent cells to each individual cell in the grid.

Running the Program:

	To run the program, use the command ./Life X Y gens input [print] [pause]

	-Life is the file name
	-X is the amount of rows for the initial grid
	-Y is the amount of columns for the initial grid
	-input is the initial starter board file
	-print is either y or n, print will either print each generation or only the last one
	-pause is either y or n, pause activated (y) will require a user to press enter to continue to each new generation
	-if print is n, pause will default to n

Problems encountered:
	
	Wow this program was a douzy. I had run into issues mainly importing the files into the new array and then printing that array. The algorithm to update the next gen array also provided some difficulty but not as much as the file upload.

Loop Invariants:
	arrayCompare:
		i>=0, i<row, count will never be greater than the area of the array, j<=0, j<column
	addChars:
		i>=startRow, i<=endRow
	countNeighbors:
		i>= (row -1), i <=(row+1), count>=0, count<=8
	updateSurroundings:
		r>=0,r<=maxRow, c>=0, c<=macColumn, numN>=0
	playOne:
		i>=0, i<row, j>=0, j<column
	main:
		loop1:
			i>=0, i<rows
		loop2:
			i>=0, i<gens

		final loops:
			j>=0, j<rows, k>=0, k< columns
			

	
		

