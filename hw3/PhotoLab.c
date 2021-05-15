#include<stdio.h>
#include "Constants.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Debug.h"
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
void PrintMenu();
#ifdef DEBUG
	AutoTest(R,G,B);
#endif
#ifndef DEBUG
int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];
    int n, targ_r, targ_g, targ_b, rep_r, rep_g, rep_b, thresh, x, y, z, th, l, m, k,rbits, bbits, gbits;
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
				printf("Please input noise percentage: ");
				scanf("%i", &n);
				Noise(n,R,G,B);
				break;
			case 12:
				Sharpen(R,G,B);
				break;
			case 13:
				printf("Enter the number of posterization bits for R chanel(1 to 8): ");
				scanf("%d", &rbits);
						
				printf("Enter the number of posterization bits for R chanel(1 to 8): ");
				scanf("%d", &gbits);
				
				printf("Enter the number of posterization bits for R chanel(1 to 8): ");
				scanf("%d", &bbits);
				Posterize(R, G, B, rbits, gbits, bbits);
				break;
			case 14: //MotionBlur()
				break;
			case 15:
				AutoTest(R, G, B);
				break;
			case 16	:
				flag = 0;
				break;
		
		} 
    }
    #endif
    return 0;
}
 /* end of main */


void PrintMenu(){
	printf("-----------------------------------------\n1: Load a PPM Image\n2: Save an image in PPM and JPEG Format\n3: Change a color image to Black & White\n4: Make a negative of an image\n5: Color filter animage\n6: Sketch the edge of an image\n7: Shuffle an image\n8: Flip an image vertically\n9: Mirror and image vertically\n10: Add Border to an image\n11: Add noise to an image\n12: Sharpen an image\n13:Posterize an image\n14: Motion Blur\n15: Test all functions\n16: Exit\nplease make your choice:");}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	char fname[5] = "HSSOE";
	char sname[SLEN];
	
	LoadImage(fname, R,G,B);
	BlackNWhite(R,G,B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG	
	printf("Black and White tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	Negative(R,G,B);
	strcpy(sname, "negative");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Negative tested!\n\n");
	#endif
		
	LoadImage(fname, R,G,B);
	ColorFilter(R,G,B,190,100,150,60,0,0,255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Color Filter tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	VFlip(R,G,B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("VFlip tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	VMirror(R,G,B);
	strcpy(sname, "vmirror");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("VMirror tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	Edge(R,G,B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Edge tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	Shuffle(R,G,B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Shuffle tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	Noise(30,R,G,B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Noise tested!\n\n");
	#endif
	
	LoadImage(fname, R,G,B);
	Sharpen(R,G,B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	#ifdef DEBUG
	printf("Sharpen tested!\n\n");
	#endif	

	LoadImage(fname, R,G,B);
	Posterize(R,G,B,7,7,7);
	strcpy(sname, "posterize");
	SaveImage(sname, R,G,B);
	#ifdef DEBUG
	printf("Posterize tested!\n\n");
	#endif
}
