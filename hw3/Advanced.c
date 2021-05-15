#include <stdlib.h>
#include <time.h>
#include "Advanced.h"
#include "Constants.h"

void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	//calculate amount of pixels needed to be white
	int toWhite = n/100 * WIDTH * HEIGHT;
	int flag = 1;
	
	srand(time(NULL));
	int x,y;
	while(flag ==1){
		x = rand() %WIDTH;
		y = rand() %HEIGHT;
		if(toWhite>0){
			R[x][y] = 255;
			G[x][y] = 255;
			B[x][y] = 255;
			toWhite = toWhite -1;
		}
		else{
		flag =0;
		}
	}	
}
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	unsigned char tempR[WIDTH][HEIGHT];
	unsigned char tempG[WIDTH][HEIGHT];
	unsigned char tempB[WIDTH][HEIGHT];

	for(int i=0;i<WIDTH; i++){
		for(int j=0; j<HEIGHT-1; j++){
			tempR[i][j] = R[i][j];	
			tempG[i][j] = R[i][j];	
			tempB[i][j] = R[i][j];	
		} 
	}
	for(int i=1; i<WIDTH-1; i++){
		for(int j=1; j<HEIGHT-1; j++){
			//red
			int tLeftR = R[i-1][j-1];
			int tMidR = R[i][j-1];
			int tRightR = R[i+1][j-1];
			
			int midLeftR = R[i-1][j];
			int midR = R[i][j];
			int midRightR = R[i+1][j];
			
			int botLeftR = R[i-1][j+1];
			int botMidR = R[i][j+1];
			int botRightR = R[i+1][j+1];
		
			//blues
			int tLeftB = B[i-1][j-1];
			int tMidB = B[i][j-1];
			int tRightB = B[i+1][j-1];
			
			int midLeftB = B[i-1][j];
			int midB = B[i][j];
			int midRightB = B[i+1][j];
			
			int botLeftB = B[i-1][j+1];
			int botMidB = B[i][j+1];
			int botRightB = B[i+1][j+1];
		
			//greens	
			int tLeftG = G[i-1][j-1];
			int tMidG = G[i][j-1];
			int tRightG = G[i+1][j-1];
			
			int midLeftG = G[i-1][j];
			int midG = G[i][j];
			int midRightG = G[i+1][j];
			
			int botLeftG = G[i-1][j+1];
			int botMidG = G[i][j+1];
			int botRightG = G[i+1][j+1];
			
			int sumReds = (-1 *tLeftR) -tMidR - tRightR -midLeftR + (midR * 9) - midRightR - botLeftR - botMidR - botRightR;
			int sumBlues = (-1 *tLeftB) -tMidB - tRightB -midLeftB + (midB * 9) - midRightB - botLeftB - botMidB - botRightB;
			int sumGreens = (-1 *tLeftG) -tMidG - tRightG -midLeftG + (midG * 9) - midRightG - botLeftG - botMidG - botRightG;
	
			if(sumReds<0){
				sumReds=0;
			}
			else if(sumReds>255)
			{
				sumReds=255;
			}
	
			if(sumBlues<0){
				sumBlues =0;
			}
			else if(sumBlues>255){
				sumBlues = 255;
			}
		
			if(sumGreens<0){
				sumGreens =0;
			}
			else if(sumGreens>255)
			{
				sumGreens=255;
			}
			
			tempR[i][j] = sumReds;
			tempB[i][j] = sumBlues;
			tempG[i][j] = sumGreens;	
			
		}
	}
//recopies the temp array into the main array
	for(int a=0; a<WIDTH; a++){
		for(int b=0; b<HEIGHT; b++){
			R[a][b] = tempR[a][b];
			G[a][b] = tempG[a][b];
			B[a][b] = tempB[a][b];
		}
	}					
}//end Sharpen

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){

	int hexOne;
 	int fillZero =1;	
	for(int a =0; a<WIDTH; a++){
		for(int b=0; b<HEIGHT; b++){
			//clear out everything to the right of the designated bit
			if(fillZero ==1){
				R[a][b] = R[a][b] >> rbits;
				R[a][b] = R[a][b] << rbits;

				B[a][b] = B[a][b] >> bbits;
				B[a][b] = B[a][b] << bbits;

				G[a][b] = G[a][b] >> gbits;
				G[a][b] = G[a][b] << gbits;
			}
			//reds
			for(int c=0; c<rbits-1; c++){
				hexOne = 0x01;
				R[a][b] = R[a][b] | (hexOne<<(c));
				fillZero =0;			
			}
			//blues
			for(int c=0; c<bbits-1; c++){
				hexOne = 0x01;
				B[a][b] = B[a][b] | (hexOne<<(c));
				fillZero =0;
			}			
			//greens
			for(int c=0; c<gbits-1; c++){
				hexOne = 0x01;
				G[a][b] = G[a][b] | (hexOne<<(c));
				fillZero =0;			
			}

		}
		fillZero=1;
	}	
} 
