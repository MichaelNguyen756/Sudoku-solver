#include <iostream>
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

struct Border{
	char firstBorder;
	char content;
	char innerBorder;
	char secondBorder;
	char endBorder;
};

void drawBorder(Border &border);
void setBorder(Border &border, int firstBorder, int content, int innerBorder, int secondBorder, int endBorder);

int main(){
	Border smallBorder, bigBorder, blankContent, topBorder, bottomBorder;
	
	setBorder(smallBorder, VERTICALDOUBLELINECHAR, HORIZONTALLINECHAR, CENTRECHAR, VERTICALDOUBLELINECHAR, VERTICALDOUBLELINECHAR);
	setBorder(bigBorder, LEFTMIDDLECHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, DOUBLECENTRECHAR, RIGHTMIDDLECHAR);
	setBorder(blankContent, VERTICALDOUBLELINECHAR, BLANK, VERTICALLINECHAR, VERTICALDOUBLELINECHAR, VERTICALDOUBLELINECHAR);
	setBorder(topBorder, TOPLEFTCORNERCHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, TOPMIDDLECHAR, TOPRIGHTCORNERCHAR);
	setBorder(bottomBorder, BOTTOMLEFTCORNERCHAR, HORIZONTALDOUBLELINECHAR, HORIZONTALDOUBLELINECHAR, BOTTOMMIDDLECHAR, BOTTOMRIGHTCORNERCHAR);
	
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
			
			drawBorder(blankContent);
		}		
	}
	drawBorder(bottomBorder);
}

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
