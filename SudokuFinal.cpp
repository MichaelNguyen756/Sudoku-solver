#include "Sudoku.h"

int main(){
	//Set up the borders drawn onto the console
	Border smallBorder, bigBorder, blankContent, topBorder, bottomBorder;
	
	setBorder(smallBorder, VERTICALDOUBLELINECHAR, HORIZONTALLINECHAR, CENTRECHAR, VERTICALDOUBLELINECHAR, VERTICALDOUBLELINECHAR);
	setBorder(bigBorder, LEFTMIDDLECHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, DOUBLECENTRECHAR, RIGHTMIDDLECHAR);
	setBorder(blankContent, VERTICALDOUBLELINECHAR, BLANK, VERTICALLINECHAR, VERTICALDOUBLELINECHAR, VERTICALDOUBLELINECHAR);
	setBorder(topBorder, TOPLEFTCORNERCHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, TOPMIDDLECHAR, TOPRIGHTCORNERCHAR);
	setBorder(bottomBorder, BOTTOMLEFTCORNERCHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, BOTTOMMIDDLECHAR, BOTTOMRIGHTCORNERCHAR);
	
	//Initialise multi-dimensional arrays
	DoubleIntArrPointer *possibleResult;
	possibleResult = new DoubleIntArrPointer[SIZE];
	int finalSolution [SIZE][SIZE];
	int possibleLength [SIZE][SIZE];
	
	//Put the given solution into the set array
	setUpGiven(finalSolution);
	setUpPossible(possibleResult);
	setUpGivenPossibility(possibleResult, finalSolution, possibleLength);
	setUpChecks(possibleResult, finalSolution, possibleLength);
	
	//Solve the puzzle
	while(!isSolved(possibleLength)){
		enterSequential(possibleResult, finalSolution, possibleLength);
		
		updateTrickColumn(possibleResult, finalSolution, possibleLength);
		updateTrickRow(possibleResult, finalSolution, possibleLength);
		
		for(int i = 1; i <= 9; i++){
			enterBox(possibleResult, finalSolution, possibleLength, i);
			enterNumber(possibleResult, finalSolution, possibleLength, i, ROWMODE);
			enterNumber(possibleResult, finalSolution, possibleLength, i, COLMODE);
			updateTrickRowAdvanced(possibleResult, finalSolution, possibleLength, i);
			updateTrickColAdvanced(possibleResult, finalSolution, possibleLength, i);
		}
	}
	
	//Draw the solution from the solution array
	for (int bigVerBox = 0; bigVerBox < VERBOX; bigVerBox++){
		for (int smallVerBox = 0; smallVerBox < VERBOX; smallVerBox++){
			if(smallVerBox == 0){				
				if (bigVerBox == 0){
					drawBorder(topBorder);
				}else{
					drawBorder(bigBorder);
				}
			}else{
				drawBorder(smallBorder);
			}
			
			for (int bigBox = 0; bigBox < HORBOX; bigBox++){
				for (int smallBox = 0; smallBox < HORBOX; smallBox++){
					if(smallBox == 0){
						if(bigBox != 0){
							printf("%c", blankContent.secondBorder);
						}else{
							printf("%c", blankContent.firstBorder);
						}
					}else{
						printf("%c", blankContent.innerBorder);
					}
					printf("%d", finalSolution[bigBox*3 + smallBox][bigVerBox*3 + smallVerBox]);
				}
			}
			printf("%c\n", blankContent.endBorder);
		}		
	}
	drawBorder(bottomBorder);
}

//Methods (functions)
void setBorder(Border &border, int firstBorder, int content, int innerBorder, int secondBorder, int endBorder){
	border.firstBorder = (char) firstBorder;
	border.content = (char) content;
	border.innerBorder = (char) innerBorder;
	border.secondBorder = (char) secondBorder;
	border.endBorder = (char) endBorder;
}

void drawBorder(Border &border){
	for (int bigBox = 0; bigBox < HORBOX; bigBox++){
		for (int smallBox = 0; smallBox < HORBOX; smallBox++){
			if(smallBox == 0){
				if(bigBox != 0){
					printf("%c", border.secondBorder);
				}else{
					printf("%c", border.firstBorder);
				}
			}else{
				printf("%c", border.innerBorder);
			}
			printf("%c", border.content);
		}
	}	
	printf("%c\n", border.endBorder);
}

void changeLength(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int solutionNum, int row, int col){
	int change, changeCol, changeRow;
	
	//row
	for(change = 0; change < SIZE; change++){
		if(solution[row][change] == EMPTY){
			possible[row][change][solutionNum - 1] = 0;
		}
	}
				
	//column
	for(change = 0; change < SIZE; change++){
		if(solution[change][col] == EMPTY){
			possible[change][col][solutionNum - 1] = 0;
		}
	}
				
	//box
	for(changeRow = (row/3)*3; changeRow < ((row/3)*3 + 3); changeRow++){
		for(changeCol = (col/3)*3; changeCol < ((col/3)*3 + 3); changeCol++){
			if(solution[changeRow][changeCol] == EMPTY){
				possible[changeRow][changeCol][solutionNum - 1] = 0;
			}
		}
	}
				
	updateLength(possible, possibleLen);
}

void enterBox(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num){
	stack <int> single;
	int count, row, col, minirow, minicol, savedRow, savedCol, clear;
	
	for(row = 0; row < SQUARES; row++){
		for(col = 0; col < SQUARES; col++){
			count = 0;
			
			for(minirow = 0; minirow < SQUARES; minirow++){
				for(minicol = 0; minicol < SQUARES; minicol++){
					if(possible[row*3 + minirow][col*3 + minicol][num - 1] != EMPTY){
						count++;
						single.push(col*3 + minicol);
						single.push(row*3 + minirow);
					}
				}
			}
			
			if(count == 1){
				savedRow = single.top();
				single.pop();
				savedCol = single.top();
				single.pop();
				
				solution[savedRow][savedCol] = num;
				for(clear = 0; clear < SIZE; clear++){
					possible[savedRow][savedCol][clear] = 0;
				}
			
				possibleLen[savedRow][savedCol] = 0;
				
				changeLength(possible, solution, possibleLen, num, savedRow, savedCol);
			}else{
				while(!single.empty()){
					single.pop();
				}
			}
		}
	}
}

void enterNumber(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num, int mode){
	stack <int> single;
	int count, row, col, checkOne, checkTwo, savedRow, savedCol, clear; 
	
	for(checkOne = 0; checkOne < SIZE; checkOne++){
		count = 0;
		
		for(checkTwo = 0; checkTwo < SIZE; checkTwo++){
			if(mode == ROWMODE){
				row = checkOne;
				col = checkTwo;
			}else if (mode == COLMODE){
				row = checkTwo;
				col = checkOne;
			}
			
			if(possible[row][col][num-1] != EMPTY){
				count++;
				single.push(col);
				single.push(row);
			}
		}
		
		if(count == 1){
			savedRow = single.top();
			single.pop();
			savedCol = single.top();
			single.pop();
			
			solution[savedRow][savedCol] = num;
			for(clear = 0; clear < SIZE; clear++){
				possible[savedRow][savedCol][clear] = 0;
			}
			possibleLen[savedRow][savedCol] = 0;
			
			changeLength(possible, solution, possibleLen, num, savedRow, savedCol);
		}else{
			while(!single.empty()){
				single.pop();
			}
		}
	}
}

void enterSequential(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]){
	int i, j, k;
	
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			if(possibleLen[i][j] == 1){
				int solutionNum = 0;
				
				for(k = 0; k < SIZE; k++){
					if(possible[i][j][k] != EMPTY){
						solutionNum = possible[i][j][k];
						possible[i][j][k] = 0;
						possibleLen[i][j] = 0;
					}
				}
				
				if(solutionNum != 0){
					solution[i][j] = solutionNum;

					changeLength(possible, solution, possibleLen, solutionNum, i, j);
				}
				
			}
		}
	}
}

bool isSolved(int arrayLength[SIZE][SIZE]){
	int row, col;
	
	for(row = 0; row < SIZE; row++){
		for(col = 0; col < SIZE; col++){
			if(arrayLength[row][col] != EMPTY){
				return false;
			}
		}
	}
	
	return true;
}

void setUpChecks(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE]){
	stack <int> done;
	
	for(int rowBox = 0; rowBox < SQUARES; rowBox++){
		for (int colBox = 0; colBox < SQUARES; colBox++){
			
			for(int row = 0; row < 3; row++){
				for (int col = 0; col < 3; col++){
					if (array[rowBox*3 + row][colBox*3 + col] != EMPTY){
						done.push(array[rowBox*3 + row][colBox*3 + col]);
					}
				}
			}
			
			while(!done.empty()){		
				for (int row = 0; row < 3; row++){
					for (int col = 0; col < 3; col++){
						if (array[rowBox*3 + row][colBox*3 + col] == EMPTY){
							possible[rowBox*3 + row][colBox*3 + col][done.top() - 1] = EMPTY;
						}
					}	
				}
		
				done.pop();
			}
		}
	}
	
	for(int row = 0; row < SIZE; row++){
		for (int i = 0; i < SIZE; i++){
			if (array[row][i] != EMPTY){
				done.push(array[row][i]);
			}
		}

		while(!done.empty()){		
			for (int i = 0; i < SIZE; i++){
				if (array[row][i] == EMPTY){
					possible[row][i][done.top() - 1] = EMPTY;
				}
			}
		
			done.pop();
		}
	}
	
	for(int col = 0; col < SIZE; col++){
		for (int i = 0; i < SIZE; i++){
			if (array[i][col] != EMPTY){
				done.push(array[i][col]);
			}
		}

		while(!done.empty()){		
			for (int i = 0; i < SIZE; i++){
				if (array[i][col] == EMPTY){
					possible[i][col][done.top() - 1] = EMPTY;
				}
			}
		
			done.pop();
		}
	}
	
	updateLength(possible, arrayLength);
}

void setUpPossible(DoubleIntArrPointer *possible){
	for (int i = 0; i < SIZE; i++){
		possible[i] = new IntArrPointer[SIZE];
	}
	
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			possible[i][j] = new int[SIZE];
		}
	}
}

void setUpGiven(int array[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			array[i][j] = EMPTY;
		}
	}
	
//	array[0][0] = 7;
//	array[0][1] = 9;
	array[0][2] = 7;
//	array[0][3] = 4;
//	array[0][4] = 5;
	array[0][5] = 1;
	array[0][6] = 3;
//	array[0][7] = 3;
//	array[0][8] = 5;
	
	array[1][0] = 3;
//	array[1][1] = 9;
//	array[1][2] = 8;
//	array[1][3] = 9;
	array[1][4] = 5;
//	array[1][5] = 3;
	array[1][6] = 6;
//	array[1][7] = 3;
//	array[1][8] = 7;
	
	array[2][0] = 5;
//	array[2][1] = 3;
	array[2][2] = 8;
//	array[2][3] = 6;
	array[2][4] = 3;
//	array[2][5] = 7;
//	array[2][6] = 1;
//	array[2][7] = 1;
	array[2][8] = 4;
	
//	array[3][0] = 1;
	array[3][1] = 8;
//	array[3][2] = 5;
//	array[3][3] = 3;
	array[3][4] = 6;
//	array[3][5] = 9;
	array[3][6] = 9;
//	array[3][7] = 3;
//	array[3][8] = 1;
	
	array[4][0] = 7;
//	array[4][1] = 8;
//	array[4][2] = 1;
//	array[4][3] = 3;
//	array[4][4] = 4;
//	array[4][5] = 9;
//	array[4][6] = 8;
//	array[4][7] = 3;
	array[4][8] = 6;
	
//	array[5][0] = 4;
//	array[5][1] = 8;
	array[5][2] = 4;
//	array[5][3] = 3;
	array[5][4] = 1;
//	array[5][5] = 9;
//	array[5][6] = 8;
	array[5][7] = 7;
//	array[5][8] = 3;
	
	array[6][0] = 2;
//	array[6][1] = 7;
//	array[6][2] = 1;
//	array[6][3] = 3;
	array[6][4] = 8;
//	array[6][5] = 9;
	array[6][6] = 4;
//	array[6][7] = 1;
	array[6][8] = 3;
	
//	array[7][0] = 1;
//	array[7][1] = 9;
	array[7][2] = 6;
//	array[7][3] = 3;
	array[7][4] = 7;
//	array[7][5] = 2;
//	array[7][6] = 8;
//	array[7][7] = 5;
	array[7][8] = 8;
	
//	array[8][0] = 1;
//	array[8][1] = 3;
	array[8][2] = 5;
	array[8][3] = 9;
//	array[8][4] = 6;
//	array[8][5] = 8;
	array[8][6] = 7;
//	array[8][7] = 3;
//	array[8][8] = 4;

}

void setUpGivenPossibility(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE]){
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				if(array[i][j] == EMPTY){
					possible[i][j][k] = k + 1;
				}else{
					possible[i][j][k] = 0;
				}
			}
			
			if(array[i][j] == EMPTY){
				arrayLength[i][j] = 9;
			}else{
				arrayLength[i][j] = 0;
			}
		}
	}
}

void updateLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE]){
	int count;
	
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			count = 0;
			
			for(int k = 0; k < SIZE; k++){
				if (possible[i][j][k] != EMPTY){
					count++;
				}
			}
			
			array [i][j] = count;
		}
	}
}

void updateTrickColAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum){
	stack <int> column;
	int stat;
	bool isSame;
	
	for(int rowBox = 0; rowBox < SQUARES; rowBox++){
		for(int colBox = 0; colBox < SQUARES; colBox++){
			stat = 0;
			isSame = true;
			
			for(int row = 0; row < SQUARES; row++){
				for(int col = 0; col < SQUARES; col++){
					if(possible[3*rowBox + row][3*colBox + col][testNum - 1] != EMPTY){
						column.push(col);
					}
				}
			}
		
			if(!column.empty()){
				stat = column.top();
			}else{
				isSame = false;
			}
			
			//Check if that number only appears in one column
			while(!column.empty()){
				
				column.pop();
				
				if(!column.empty() && (column.top() != stat)){
					isSame = false;
					
					while(!column.empty()){
						column.pop();
					}
				}
			}
			
			if(isSame == true){
				//Update the corresponding columns
					if(rowBox == 0){
						for(int i = 3; i < 9; i++){
							if(solution[i][3*colBox + stat] == EMPTY){
								possible[i][3*colBox + stat][testNum - 1] = 0;
							}
						}
					}else if (rowBox == 1){
						for(int i = 0; i < 3; i++){
							possible[i][3*colBox + stat][testNum - 1] = 0;
						}
						
						for(int i = 6; i < 9; i++){
							possible[i][3*colBox + stat][testNum - 1] = 0;
						}
					}else if(rowBox == 2){
						for(int i = 0; i < 6; i++){
							if(solution[i][3*colBox + stat] == EMPTY){
								possible[i][3*colBox + stat][testNum - 1] = 0;
							}
						}
					}
					updateLength(possible, possibleLen);
			}
			
			while(!column.empty()){
				column.pop();
			}
		}
	}
}

void updateTrickRowAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum){
	stack <int> rowStack;
	
	for(int rowBox = 0; rowBox < SQUARES; rowBox++){
		for(int colBox = 0; colBox < SQUARES; colBox++){
			int stat = 0;
			bool isSame = true;
			
			for(int row = 0; row < SQUARES; row++){
				for(int col = 0; col < SQUARES; col++){
					if(possible[3*rowBox + row][3*colBox + col][testNum - 1] != EMPTY){
						rowStack.push(row);
					}
				}
			}
		
			if(!rowStack.empty()){
				stat = rowStack.top();
			}else{
				isSame = false;
			}
			
			//Check if that number only appears in one column
			while(!rowStack.empty() && rowStack.size() > 1){
				
				rowStack.pop();
				
				if(!rowStack.empty() && rowStack.top() != stat){
					isSame = false;
					
					while(!rowStack.empty()){
						rowStack.pop();
					}
				}
			}

			
			
			if(isSame == true){
				//Update the corresponding columns
					if(colBox == 0){
						for(int i = 3; i < 9; i++){
							if(solution[3*rowBox + stat][i] == EMPTY){
								possible[3*rowBox + stat][i][testNum - 1] = 0;
							}
						}
					}else if (colBox == 1){
						for(int i = 0; i < 3; i++){
							possible[3*rowBox + stat][i][testNum - 1] = 0;
						}
						
						for(int i = 6; i < 9; i++){
							possible[3*rowBox + stat][i][testNum - 1] = 0;
						}
					}else if(colBox == 2){
						for(int i = 0; i < 6; i++){
							if(solution[3*rowBox + stat][i] == EMPTY){
								possible[3*rowBox + stat][i][testNum - 1] = 0;
							}
						}
					}
					updateLength(possible, possibleLen);
			}
			
			while(!rowStack.empty()){
				rowStack.pop();
			}
		}
	}
}

void updateTrickColumn(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]){
	for(int colBox = 0; colBox < SQUARES; colBox++){
		for(int rowBox = 0; rowBox < SQUARES; rowBox++){
			int fullCount = 0;
			
			//Look at box
			for (int row = 0; row < SQUARES; row++){
				for(int col = 0; col < SQUARES; col++){
					if (solution[3*rowBox + row][3*colBox + col] != EMPTY){
						fullCount++;
					}
				}
			}
		
			if(fullCount >= 6){
				for(int col = 0; col < SQUARES; col++){
					int sequenceCount = 0;
					stack <int> num;		
					
					for(int row = 0; row < SQUARES; row++){
						if(solution[3*rowBox + row][3*colBox + col] == EMPTY){
							sequenceCount++;
						}
					}
		
					if(sequenceCount == 2 && fullCount == 7){
						for(int row = 0; row < SQUARES; row++){
							if(solution[3*rowBox + row][3*colBox + col] == EMPTY){
								for(int i = 0; i < SIZE; i++){
									if(possible[3*rowBox + row][3*colBox + col][i] != EMPTY){
										num.push(possible[3*rowBox + row][3*colBox + col][i]);
									}
								}
							}
						}			
						
					}else if(sequenceCount == 3 && fullCount == 6){
						for (int row = 0; row < SQUARES; row++){
							for(int i = 0; i < SIZE; i++){
								if(possible[3*rowBox + row][3*colBox + col][i] != EMPTY){
									num.push(possible[3*rowBox + row][3*colBox + col][i]);
								}
							}
						}
					}
					
					//Update the corresponding columns
					if(rowBox == 0){
						while(!num.empty()){
							for(int i = 3; i < 9; i++){
								if(solution[i][3*colBox + col] == EMPTY){
									possible[i][3*colBox + col][num.top() - 1] = 0;
								}
							}
							num.pop();
						}
					}else if (rowBox == 1){
						while(!num.empty()){
							for(int i = 0; i < 3; i++){
								possible[i][3*colBox + col][num.top() - 1] = 0;
							}
							
							for(int i = 6; i < 9; i++){
								possible[i][3*colBox + col][num.top() - 1] = 0;
							}
							num.pop();
						}
					}else if(rowBox == 2){
						while(!num.empty()){
							for(int i = 0; i < 6; i++){
								if(solution[i][3*colBox + col] == EMPTY){
									possible[i][3*colBox + col][num.top() - 1] = 0;
								}
							}
							num.pop();
						}
					}
					updateLength(possible, possibleLen);
				}
			}
		}
	}
}

void updateTrickRow(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]){
	for(int colBox = 0; colBox < SQUARES; colBox++){
		for(int rowBox = 0; rowBox < SQUARES; rowBox++){
			int fullCount = 0;
			
			//Look at box
			for (int col = 0; col < SQUARES; col++){
				for(int row = 0; row < SQUARES; row++){
					if (solution[3*rowBox + row][3*colBox + col] != EMPTY){
						fullCount++;
					}
				}
			}
		
			if(fullCount >= 6){
				for(int row = 0; row < SQUARES; row++){
					int sequenceCount = 0;
					stack <int> num;		
					
					for(int col = 0; col < SQUARES; col++){
						if(solution[3*rowBox + row][3*colBox + col] == EMPTY){
							sequenceCount++;
						}
					}
		
					if(sequenceCount == 2 && fullCount == 7){
						for(int col = 0; col < SQUARES; col++){
							if(solution[3*rowBox + row][3*colBox + col] == EMPTY){
								for(int i = 0; i < SIZE; i++){
									if(possible[3*rowBox + row][3*colBox + col][i] != EMPTY){
										num.push(possible[3*rowBox + row][3*colBox + col][i]);
									}
								}
							}
						}			
						
					}else if(sequenceCount == 3 && fullCount == 6){
						for (int col = 0; col < SQUARES; col++){
							for(int i = 0; i < SIZE; i++){
								if(possible[3*rowBox + row][3*colBox + col][i] != EMPTY){
									num.push(possible[3*rowBox + row][3*colBox + col][i]);
								}
							}
						}
					}
					
					//Update the corresponding rows
					if(colBox == 0){
						while(!num.empty()){
							for(int i = 3; i < 9; i++){
								if(solution[3*rowBox + row][i] == EMPTY){
									possible[3*rowBox + row][i][num.top() - 1] = 0;
								}
							}
							num.pop();
						}
					}else if (colBox == 1){
						while(!num.empty()){
							for(int i = 0; i < 3; i++){
								possible[3*rowBox + row][i][num.top() - 1] = 0;
							}
							
							for(int i = 6; i < 9; i++){
								possible[3*rowBox + row][i][num.top() - 1] = 0;
							}
							num.pop();
						}
					}else if(colBox == 2){
						while(!num.empty()){
							for(int i = 0; i < 6; i++){
								if(solution[3*rowBox + row][i] == EMPTY){
									possible[3*rowBox + row][i][num.top() - 1] = 0;
								}
							}
							num.pop();
						}
					}
					updateLength(possible, possibleLen);
				}
			}
		}
	}
}
