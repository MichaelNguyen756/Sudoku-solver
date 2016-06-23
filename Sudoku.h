#include <iostream>
#include <stack>

using namespace std;

#define HORBOX 3
#define VERBOX 3

#define TOPLEFTCORNERCHAR 201
#define TOPRIGHTCORNERCHAR 187
#define BOTTOMLEFTCORNERCHAR 200
#define BOTTOMRIGHTCORNERCHAR 188

#define CENTRECHAR 197
#define DOUBLECENTRECHAR 206

#define TOPMIDDLECHAR 203
#define BOTTOMMIDDLECHAR 202
#define LEFTMIDDLECHAR 204
#define RIGHTMIDDLECHAR 185

#define HORIZONTALLINECHAR 196
#define HORIZONTALDOUBLELINECHAR 205
#define VERTICALLINECHAR 179 
#define VERTICALDOUBLELINECHAR 186
#define BLANK 32

#define SIZE 9
#define EMPTY 0
#define SQUARES 3
#define ROWMODE 1
#define COLMODE 2

typedef int* IntArrPointer;
typedef IntArrPointer* DoubleIntArrPointer;

void displayArray(int array[SIZE][SIZE]);
void displayPossible(DoubleIntArrPointer *possible);
void displayPossibleSingle(DoubleIntArrPointer *possible, int num);

void setUpGiven(int array[SIZE][SIZE]);
void setUpPossible(DoubleIntArrPointer *possible);
void setUpChecks(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE]);
void setUpGivenPossibility(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE]);

void updateLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE]);
void changeLength(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE], int solution, int row, int col);

bool isSolved(int arrayLength[SIZE][SIZE]);

void enterSequential(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void enterBox(DoubleIntArrPointer *possible, int array[SIZE][SIZE], int arrayLength[SIZE][SIZE], int num);
void enterNumber(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int num, int mode);

void updateTrickColumn(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void updateTrickRow(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE]);
void updateTrickColAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum);
void updateTrickRowAdvanced(DoubleIntArrPointer *possible, int solution[SIZE][SIZE], int possibleLen[SIZE][SIZE], int testNum);

bool isEqualArray(int arrayOne[SIZE][SIZE], int arrayTwo[SIZE][SIZE]);

struct Border{
	char firstBorder;
	char content;
	char innerBorder;
	char secondBorder;
	char endBorder;
};

void drawBorder(Border &border);
void setBorder(Border &border, int firstBorder, int content, int innerBorder, int secondBorder, int endBorder);
