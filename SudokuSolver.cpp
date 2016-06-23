#include <iostream>
#include <stack>
using namespace std;

#define SIZE 9
#define EMPTY 0
#define ROW 1
#define COL 2
#define BOX 3
#define SQUARES 3

typedef int* IntArrPointer;
typedef IntArrPointer* DoubleIntArrPointer;

void displayArray(int array[SIZE][SIZE]);
void displayPossible(DoubleIntArrPointer *possible);

void setUpGiven(int array[SIZE][SIZE]);
void setUpPossible(DoubleIntArrPointer *possible);
void setUpChecks(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE]);

void updateLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE]);
void changeLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE], int solution, int row, int col);

bool isSolved(int arrayLength[SIZE][SIZE]);

void enterSequential(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void enterRow(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num);
void enterCol(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num);
void enterBox(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE], int num);

void updateTrickColumn(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void updateTrickRow(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void updateTrickColAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum);
void updateTrickRowAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum);

int main(){
	DoubleIntArrPointer *possibleResult;
	possibleResult = new DoubleIntArrPointer[SIZE];
	int given [SIZE][SIZE];
	int finalSolution [SIZE][SIZE];
	int possibleLength [SIZE][SIZE];
	int previous [SIZE][SIZE];
	
	setUpGiven(given);
	setUpGiven(finalSolution);
	setUpPossible(possibleResult);
	
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				if(given[i][j] == EMPTY){
					possibleResult[i][j][k] = k + 1;
				}else{
					possibleResult[i][j][k] = 0;
				}
			}
			
			if(given[i][j] == EMPTY){
				possibleLength[i][j] = 9;
			}else{
				possibleLength[i][j] = 0;
			}
		}
	}

	setUpChecks(possibleResult, given, possibleLength);
	
//	displayPossible(possibleResult);
//	cout << endl;
	displayArray(possibleLength);
	cout << endl;
//	displayArray(solution);
//	cout << endl;

	for(int i = 1; i <= 9; i++){
		enterBox(possibleResult, finalSolution, possibleLength, i);
	}

	enterSequential(possibleResult, finalSolution, possibleLength);
	
	for(int i = 1; i <= 9; i++){
		enterCol(possibleResult, finalSolution, possibleLength, i);
	}
	
	for(int i = 1; i <= 9; i++){
		enterBox(possibleResult, finalSolution, possibleLength, i);
	}
	
	for(int i = 1; i <= 9; i++){
		enterCol(possibleResult, finalSolution, possibleLength, i);
	}
	
	updateTrickColumn(possibleResult, finalSolution, possibleLength);
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	for(int i = 1; i <= 9; i++){
		enterCol(possibleResult, finalSolution, possibleLength, i);
	}
	
	for(int i = 1; i <= 9; i++){
		enterBox(possibleResult, finalSolution, possibleLength, i);
	}
	
	for(int i = 1; i <= 9; i++){
		updateTrickColAdvanced(possibleResult, finalSolution, possibleLength, i);
	}
	
	for(int i = 1; i <= 9; i++){
		updateTrickRowAdvanced(possibleResult, finalSolution, possibleLength, i);
	}
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	for(int i = 1; i <= 9; i++){
		enterBox(possibleResult, finalSolution, possibleLength, i);
	}
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	for(int i = 1; i <= 9; i++){
		enterBox(possibleResult, finalSolution, possibleLength, i);
	}
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	enterSequential(possibleResult, finalSolution, possibleLength);
	
	enterSequential(possibleResult, finalSolution, possibleLength);

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////TESTING/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//	int rowBox = 0;
//	int colBox = 1;
//	
//	stack <int> rowStack;
//	
//	int testNum = 6;
//
//	int stat = 0;
//	bool isSame = true;
//	
//	for(int row = 0; row < SQUARES; row++){
//		for(int col = 0; col < SQUARES; col++){
//			if(possibleResult[3*rowBox + row][3*colBox + col][testNum - 1] != EMPTY){
//				rowStack.push(row);
//			}
//		}
//	}
//
//	if(!rowStack.empty() && rowStack.size() > 1){
//		stat = rowStack.top();
//	}else{
//		isSame = false;
//	}
//	
//	//Check if that number only appears in one row
//	while(!rowStack.empty()){
//		rowStack.pop();
//		
//		if(!rowStack.empty() && rowStack.top() != stat){
//			isSame = false;
//			
//			while(!rowStack.empty()){
//				rowStack.pop();
//			}
//		}
//	}
//	
//	if(isSame){
//		//Update the corresponding columns
//			if(colBox == 0){
//				for(int i = 3; i < 9; i++){
//					if(finalSolution[3*rowBox + stat][i] == EMPTY){
//						possibleResult[3*rowBox + stat][i][testNum - 1] = 0;
//					}
//				}
//			}else if (colBox == 1){
//				for(int i = 0; i < 3; i++){
//					possibleResult[3*rowBox + stat][i][testNum - 1] = 0;
//				}
//				
//				for(int i = 6; i < 9; i++){
//					possibleResult[3*rowBox + stat][i][testNum - 1] = 0;
//				}
//			}else if(colBox == 2){
//				for(int i = 0; i < 6; i++){
//					if(finalSolution[3*rowBox + stat][i] == EMPTY){
//						possibleResult[3*rowBox + stat][i][testNum - 1] = 0;
//					}
//				}
//			}
//			updateLength(possibleResult, possibleLength);
//	}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////TESTING/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
	
	
	displayArray(possibleLength);
	cout << endl;
//	displayPossible(possibleResult);
//	cout << endl;
	displayArray(finalSolution);
	cout << endl;	
}

bool isSolved(int arrayLength[SIZE][SIZE]){
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			if(arrayLength[row][col] != EMPTY){
				return false;
			}
		}
	}
	
	return true;
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
		
			if(!rowStack.empty() && rowStack.size() > 1){
				stat = rowStack.top();
			}else{
				isSame = false;
			}
			
			//Check if that number only appears in one column
			while(!rowStack.empty()){
				
				rowStack.pop();
				
				if(!rowStack.empty() && rowStack.top() != stat){
					isSame = false;
					
					while(!rowStack.empty()){
						rowStack.pop();
					}
				}
			}
			
			if(isSame){
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
		}
	}
}

void updateTrickColAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum){
	stack <int> column;
	
	for(int rowBox = 0; rowBox < SQUARES; rowBox++){
		for(int colBox = 0; colBox < SQUARES; colBox++){
			int stat = 0;
			bool isSame = true;
			
			for(int row = 0; row < SQUARES; row++){
				for(int col = 0; col < SQUARES; col++){
					if(possible[3*rowBox + row][3*colBox + col][testNum - 1] != EMPTY){
						column.push(col);
					}
				}
			}
		
			if(!column.empty() && column.size() > 1){
				stat = column.top();
			}else{
				isSame = false;
			}
			
			//Check if that number only appears in one column
			while(!column.empty()){
				
				column.pop();
				
				if(!column.empty() && column.top() != stat){
					isSame = false;
					
					while(!column.empty()){
						column.pop();
					}
				}
			}
			
			if(isSame){
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
					
					//Update the corresponding columns
					if(rowBox == 0){
						while(!num.empty()){
							for(int i = 3; i < 9; i++){
								if(solution[3*rowBox + row][i] == EMPTY){
									possible[3*rowBox + row][i][num.top() - 1] = 0;
								}
							}
							num.pop();
						}
					}else if (rowBox == 1){
						while(!num.empty()){
							for(int i = 0; i < 3; i++){
								possible[3*rowBox + row][i][num.top() - 1] = 0;
							}
							
							for(int i = 6; i < 9; i++){
								possible[3*rowBox + row][i][num.top() - 1] = 0;
							}
							num.pop();
						}
					}else if(rowBox == 2){
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

void enterRow(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num){
	stack <int> single;
	for(int row = 0; row < SIZE; row++){
		int count = 0;
		
		for(int col = 0; col < SIZE; col++){
			if(possible[row][col][num-1] != EMPTY){
				count++;
				single.push(col);
				single.push(row);
			}		
		}
		
		if(count == 1){
			int savedRow = single.top();
			single.pop();
			int savedCol = single.top();
			single.pop();
			
			solution[savedRow][savedCol] = num;
			for(int clear = 0; clear < SIZE; clear++){
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

void enterCol(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num){
	stack <int> single;
	for(int col = 0; col < SIZE; col++){
		int count = 0;
		
		for(int row = 0; row < SIZE; row++){	
			if(possible[row][col][num-1] != EMPTY){
				count++;
				single.push(col);
				single.push(row);
			}
		}
		
		if(count == 1){
			int savedRow = single.top();
			single.pop();
			int savedCol = single.top();
			single.pop();
			
			solution[savedRow][savedCol] = num;
			for(int clear = 0; clear < SIZE; clear++){
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

void enterBox(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num){
	stack <int> single;
	for(int row = 0; row < SQUARES; row++){
		for(int col = 0; col < SQUARES; col++){
			int count = 0;
			
			for(int minirow = 0; minirow < SQUARES; minirow++){
				for(int minicol = 0; minicol < SQUARES; minicol++){
					if(possible[row*3 + minirow][col*3 + minicol][num-1] != EMPTY){
						count++;
						single.push(col*3 + minicol);
						single.push(row*3 + minirow);
					}
				}
			}
			
			if(count == 1){
				int savedRow = single.top();
				single.pop();
				int savedCol = single.top();
				single.pop();
				
				solution[savedRow][savedCol] = num;
				for(int clear = 0; clear < SIZE; clear++){
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

void enterSequential(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(possibleLen[i][j] == 1){
				int solutionNum = 0;
				
				for(int k = 0; k < SIZE; k++){
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

void displayPossible(DoubleIntArrPointer *possible){	
	for (int row = 0; row < SIZE; row++){
		cout << "Row " << row + 1 << ":" << endl;
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
					cout << possible[row][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}
}

void displayArray(int array[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			cout << array[i][j] << " ";
		}
		
		cout << endl;
	}
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
	
	array[0][2] = 7;
	array[0][5] = 1;
	array[0][6] = 3;
	
	array[1][0] = 3;
	array[1][4] = 5;
	array[1][6] = 6;
	
	array[2][0] = 5;
	array[2][2] = 8;
	array[2][4] = 3;
	array[2][8] = 4;
	
	array[3][1] = 8;
	array[3][4] = 6;
	array[3][6] = 9;
	
	array[4][0] = 7;
	array[4][8] = 6;
	
	array[5][2] = 4;
	array[5][4] = 1;
	array[5][7] = 7;
	
	array[6][0] = 2;
	array[6][4] = 8;
	array[6][6] = 4;
	array[6][8] = 3;
	
	array[7][2] = 6;
	array[7][4] = 7;
	array[7][8] = 8;
	
	array[8][2] = 5;
	array[8][3] = 9;
	array[8][6] = 7;
}

void updateLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE]){
	int count = 0;
	
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				if (possible[i][j][k] != EMPTY){
					count++;
				}
			}
			
			array [i][j] = count;
			count = 0;
		}
	}
}

void changeLength(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int solutionNum, int row, int col){
	//row
	for(int change = 0; change < SIZE; change++){
		if(solution[row][change] == EMPTY){
			possible[row][change][solutionNum - 1] = 0;
		}
	}
				
	//column
	for(int change = 0; change < SIZE; change++){
		if(solution[change][col] == EMPTY){
			possible[change][col][solutionNum - 1] = 0;
		}
	}
				
	//box
	for(int changeRow = (row/3)*3; changeRow < ((row/3)*3 + 3); changeRow++){
		for(int changeCol = (col/3)*3; changeCol < ((col/3)*3 + 3); changeCol++){
			if(solution[changeRow][changeCol] == EMPTY){
				possible[changeRow][changeCol][solutionNum - 1] = 0;
			}
		}
	}
				
	updateLength(possible, possibleLen);
}
