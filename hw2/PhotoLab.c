/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017                 */
/*                                                                   */
/* modifications: (Saeed Karimi Bidhendi)                            */
/* 09/27/17 RD	adjusted for lecture usage                           */
/*********************************************************************/

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/

const int WIDTH  = 600;	/* image width */
const int HEIGHT = 400;	/* image height */
const int SLEN   =  80;	/* max. string length */

/*** function declarations ***/

void PrintMenu();


/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);



void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/

int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];
    int n, targ_r, targ_g, targ_b, rep_r, rep_g, rep_b, thresh, x, y, z, th, l, m, k;
    char fileName[SLEN];
    int flag =1;

	if (LoadImage("HSSOE", R, G, B) != 0)
    { return 10; }
     
    while(flag==1){
		PrintMenu();
		scanf("%i",&n);
	    switch(n){
			case 1:
				printf("Please input the file name: ");
				scanf("%s", fileName);
				LoadImage(fileName, R, G, B);		
				break;
			case 2:
				SaveImage(fileName, R, G, B);
				break;
			case 3:
				BlackNWhite(R,G,B);
				break;
   	 		case 4:
				Negative(R,G,B);
				break;
   		 	case 5:
			
				
				printf("Enter Red component for the target color: ");
				scanf("%i", &x);
				targ_r = x;
						
				printf("Enter Green component for the target color: ");
				scanf("%i", &y);
				targ_g = y;
					
				printf("Enter Blue component for the target color: ");
				scanf("%i", &z);
				targ_b = z;
				
				printf("Enter threshold for the color difference: ");
				scanf("%i", &th);
				thresh = th;
	
				printf("Enter value for Red component in the target color: ");
				scanf("%i", &l);
				rep_r = l;
	
				printf("Enter value for Green component in the target color: ");
				scanf("%i", &m);
				rep_g = m;
		
							
				printf("Enter value for Blue component in the target color: ");
				scanf("%i", &k);
				rep_b = k;

				ColorFilter(R, G, B, targ_r, targ_g,targ_b,thresh, rep_r, rep_g, rep_b);
				break;		
			case 6:
				Edge(R, G, B);	
				break;
			case 7:
				Shuffle(R,G,B);
				break;
			case 8:
				VFlip(R, G, B);
				break;
			case 9:
				VMirror(R, G, B);
				break;
			case 10:
				//AddBorder(R, G,B, color[SLEN], border_width);
				break;
			case 11:
				AutoTest(R, G, B);
				break;
			case 12:
				flag = 0;
				break;
		
		} 
    }
    return 0;
}
 /* end of main */


/*** function definitions ***/

/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */

//defined PrintMenu
void PrintMenu(){
	printf("-----------------------------------------\n1: Load a PPM Image\n2: Save an image in PPM and JPEG Format\n3: Change a color image to Black & White\n4: Make a negative of an image\n5: Color filter animage\n6: Sketch the edge of an image\n7: Shuffle an image\n8: Flip an image vertically\n9: Mirror and image vertically\n10: Add Border to an image\n11: Test all functions\n12: Exit\nplease make your choice:");


}



int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];      
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was read.\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved. \n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored.\n", fname_tmp);
        return 0;
}

void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
				unsigned char B[WIDTH][HEIGHT]){
//seppuku pt.1	
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

//FKKKKK MEEE
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
			
			/*
			int newBoundWIDTH = WIDTH/4;
			int newBoundHEIGHT = HEIGHT/4;
			int rangeArray[16][2];
			int rangeArrayHEIGHT[4][2];
			int rangeArrayWIDTH[4][2];

			rangeArray[0][0] = 0;
			rangeArrayWIDTH[0][1] = newBoundWIDTH;
			rangeArrayHEIGHT[0][1] = newBoundHEIGHT;
			
			
			//Finds coords for width
			for(int i =1; i<100; i++){
				for(int j = 0; j<2; j++){
					if(j==0){
						rangeArrayWIDTH[i][j] = rangeArrayWIDTH[i-1][j+1];		
					}else{
						rangeArrayWIDTH[i][j] = rangeArrayWIDTH[i][j-1] + newBoundWIDTH;
					} 
				}
			}
			//Finds coords for height
			for(int eye =1;eye <100; eye++){
				for(int jay = 0; jay<2; jay++){
					if(jay==0){
						rangeArrayHEIGHT[eye][jay] = rangeArrayHEIGHT[eye-1][jay+1];		
					}else{
						rangeArrayHEIGT[eye][jay] = rangeArrayHEIGHT[eye][jay-1] + newBoundHEIGHT;
					} 
				}
			}
						
			for(int aye = 0; aye<WIDTH;aye++){
				for(int jake = 0; jake<HEIGHT; jake++){
					
				}
			} */			
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

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	char fname[5] = "HSSOE";
	char sname[SLEN];

	LoadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw"); 
	SaveImage(sname, R, G, B);
	printf("Black and White tested!\n\n");

	LoadImage(fname, R, G, B);
	Negative(R,G,B);
	strcpy(sname, "negative");
	SaveImage(sname, R,G,B);
	printf("Negative tested!\n\n");

	LoadImage(fname, R,G,B );
	ColorFilter(R,G,B,190,100,150,60,0,0,255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");

	LoadImage(fname, R,G,B );
	VFlip(R,G,B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("VFlip tested!\n\n");
	
		
	LoadImage(fname, R,G,B );
	VMirror(R,G,B);
	strcpy(sname, "vmirror");
	SaveImage(sname, R, G, B);
	printf("VMirror tested!\n\n");
	
	LoadImage(fname, R,G,B );
	Edge(R,G,B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge tested!\n\n");

	
	LoadImage(fname, R,G,B );
	Shuffle(R,G,B);
	strcpy(sname, "shuffle");
	SaveImage(sname, R, G, B);
	printf("Shuffle tested!\n\n");

}




/*

 
        .
        .
        .
        .
        .
 
 
 
*/




/* EOF */
