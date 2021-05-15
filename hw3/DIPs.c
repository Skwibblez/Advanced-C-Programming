#include<stdio.h>
#include "DIPs.h"
#include "Constants.h"
#include "FileIO.h"
#include <time.h>
#include "Advanced.h"
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
				unsigned char B[WIDTH][HEIGHT]){
	for(int i=0; i<WIDTH;i++){

		for(int j=0; j<HEIGHT; j++){
			unsigned char newIntensity = (char)((R[i][j] + G[i][j] + B[i][j])/3);	
			R[i][j] = newIntensity;
			B[i][j] = newIntensity;
			G[i][j] = newIntensity;	
		}
	}
	printf("Black and White operation is done!\n\n");							
}




void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	for(int i=0;i<WIDTH;i++){
		for(int j =0; j<HEIGHT;j++){
			R[i][j] = 255 - R[i][j];
			B[i][j] = 255 - B[i][j];
			G[i][j] = 255 - G[i][j];
				
			
		}
	}
	printf("Negative operation is done\n\n");	
}

/* color filter */

void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b){
	
	for(int i=0; i<WIDTH;i++){
		for(int j=0; j<HEIGHT;j++){
			if(((R[i][j] >= target_r - threshold) && (R[i][j] <= target_r +threshold))
			&&((B[i][j]>=target_b - threshold) && (B[i][j]<= target_b+threshold))
			&&((G[i][j]>=target_g - threshold) && (G[i][j]<= target_g+threshold))){
					
				R[i][j] = replace_r;
				B[i][j] = replace_b;
				G[i][j] = replace_g;
			
			}
		}
	}
		
			
				printf("Color filter operation is done! \n\n");		
}



/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]){
		
			unsigned char tempArrR[WIDTH][HEIGHT];
			unsigned char tempArrG[WIDTH][HEIGHT];
			unsigned char tempArrB[WIDTH][HEIGHT];
			 
			for(int k=0; k<WIDTH; k++){
				for(int m=0; m<HEIGHT; m++){
					tempArrR[k][m] = R[k][m];
					tempArrG[k][m] = G[k][m];
					tempArrB[k][m] = B[k][m];
				}
			 }
			
		
								
	for(int i = 1;i< WIDTH-1; i++){
		for(int j =1; j<HEIGHT-1; j++){
			//Red
			int a = R[i-1][j-1];
			int b = R[i][j-1];
			int c = R[i+1][j-1];
	
			int d = R[i-1][j];
			int e = R[i][j];
			int f = R[i+1][j];

			int g = R[i-1][j+1];
			int h = R[i][j+1];
			int k = R[i+1][j+1];
		
			//Blues
			int aa = B[i-1][j-1];
			int bb = B[i][j-1];
			int cc = B[i+1][j-1];

			int dd = B[i-1][j];
			int ee = B[i][j];
			int ff = B[i+1][j];

			int gg = B[i-1][j+1];
			int hh = B[i][j+1];
			int kk = B[i+1][j+1];
		
			//Greens
			int aaa = G[i-1][j-1];
			int bbb = G[i][j-1];
			int ccc = G[i+1][j-1];

			int ddd = G[i-1][j];
			int eee = G[i][j];
			int fff = G[i+1][j];

			int ggg = G[i-1][j+1];
			int hhh = G[i][j+1];
			int kkk = G[i+1][j+1];
				
			int sum1 = (-1*a)-b-c-d+(8*e)-f-g-h-k;
			int sum2 = (-1)*aa-bb-cc-dd+(8*ee)-ff-gg-hh-kk;				
			int sum3 = (-1*aaa)-bbb-ccc-ddd+(8*eee)-fff-ggg-hhh-kkk;	
		
			if(sum1<0){
				sum1 = 0;
			}
			else if(sum1>255){
				sum1 = 255;
			}
			
			if(sum2<0){
				sum2 = 0;
			}
			else if(sum2>255){
				sum2 = 255;
			}
			
			if(sum3<0){
				sum3 = 0;
			}
			else if(sum3>255){
				sum3 = 255;
			}
		        
			tempArrR[i][j] = sum1;
			tempArrB[i][j] = sum2;
			tempArrG[i][j] = sum3;	
		}
	}
			
			for(int a = 0; a<WIDTH;a++){
				for(int b =0;b<HEIGHT; b++){
					R[a][b] = tempArrR[a][b];
					G[a][b] = tempArrG[a][b];
					B[a][b]=  tempArrB[a][b];
				}		
			}
			printf("Edge operation is done!\n\n");					
}


/* mirror image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]){

	unsigned char tempArrR[WIDTH][HEIGHT];
	unsigned char tempArrB[WIDTH][HEIGHT];
	unsigned char tempArrG[WIDTH][HEIGHT];
	int resetH;
	int counterW =WIDTH-1;

	for(int i =0; i<WIDTH; i++){
		for(int j =0; j<HEIGHT; j++){
	
			tempArrR[i][j] = R[i][j];	
			tempArrG[i][j] = G[i][j];	
			tempArrB[i][j] = B[i][j];
		}
	}
	
	for(int i = WIDTH-1; i>=0; i--){
		resetH =0;
		
		for(int j = HEIGHT-1; j>=0; j--){
			
			R[counterW][resetH] = tempArrR[i][j];
			G[counterW][resetH] = tempArrG[i][j];
			B[counterW][resetH] = tempArrB[i][j];
			resetH++;
		}
		counterW--;
	}
	printf("VFlip operation is done!\n\n");
}


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]){
			
			unsigned char tempArrR1[WIDTH][HEIGHT];
			unsigned char tempArrB1[WIDTH][HEIGHT];
			unsigned char tempArrG1[WIDTH][HEIGHT];
			
		int counter = 15;
		int boxes[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int firstWidth;
		int firstHeight;
		int tempWidth, tempHeight;
		int counter2 =0;
		srand(time(NULL));
		//randomizes the temporary array based on the original array
			for(int num =0; num<=counter; num++){
		 		int r = rand()%16;
				
				while(boxes[r] ==1){
					r = rand()%16;
				}
				boxes[r] = 1;
				firstWidth = (r%4)*150;
				firstHeight = (r/4)*100;

				tempWidth = (counter2%4) *150;
				tempHeight = (counter2/4) *100;		

				for(int cao = 0; cao<150; cao++){
					for(int diu = 0; diu<100; diu++){
						
						tempArrR1[tempWidth+cao][tempHeight+diu] = R[firstWidth+cao][firstHeight+diu];
						tempArrB1[tempWidth+cao][tempHeight+diu] = B[firstWidth+cao][firstHeight+diu];
						tempArrG1[tempWidth+cao][tempHeight+diu] = G[firstWidth+cao][firstHeight+diu];
					}
				}	
	
				counter2++;		
			}
			
		//copies back into original array
		for(int i =0; i<WIDTH; i++){
			for(int j =0; j<HEIGHT; j++){
				R[i][j] = tempArrR1[i][j];
				B[i][j] = tempArrB1[i][j];
				G[i][j] = tempArrG1[i][j];
			}	
		}
	printf("Shuffle operation is done!");
}


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width){
	printf("This was extra credit so not mandartory");
}

void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	
	int counter;
	for(int n =0; n<WIDTH; n++){
		counter =0;
		for(int m=HEIGHT/2; m<HEIGHT; m++){
			R[n][m] = R[n][m-(1+(2* counter))];
			G[n][m] = G[n][m-(1+(2* counter))];	
			B[n][m] = B[n][m-(1+(2* counter))];
			counter++;	
		}
	}
	
	printf("VMirror operation is done!");
}

 

/* EOF */
