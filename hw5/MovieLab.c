/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;
	char *fwmk = NULL;
	char *fnum = NULL;
	char *wxh = NULL;
	char *ste = NULL;	
	char *fct = NULL;
	unsigned int width = 480;
	unsigned int height = 270;
		

	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/
		
		if( strcmp(argv[x], "-s") == 0){
			x++;
			if(x<argc){
				wxh = argv[x];
			}
			else{
				fputs("Missing argument for -s!\n", stderr);
				PrintUsage();
				exit(10);
			}
		}
		
		if (strcmp(argv[x],"-f")== 0){
                       	x++;
                        if (x <argc){
                                fnum = argv[x];
                        }
                        else{
                                fputs("Missing argument for -f!\n", stderr);
                                PrintUsage();
                                exit(10);
                        }
                }
		
		//IMPLEMENTED AGING FUNCTION
		char *p;
		char *token;
		char *secToken;
		char *a = argv[x];
		char *search = "x";
		
			
	
		token = strtok(a, search);
		secToken = strtok(NULL, search);
		//converts it to a number

		unsigned int aWidth = strtoul(token, &p, 10);
		if( *(p) != '\0'){
			fputs("Invalid width\n", stderr);
			PrintUsage();
			exit(10);
		} 
		unsigned int aHeight = strtoul(secToken, &p, 10);
		if(*(p) != '\0'){
			fputs("Invalid width\n", stderr);
			PrintUsage();
			exit(10);
		}
		//check arguments: fnum needs to be a pointer to char, 
		unsigned int intFnum = strtoul(fnum, &p, 10);
		if(*(p) != '\0'){
			fputs("Invalid width\n", stderr);
			PrintUsage();
			exit(10);
		}

		//LOAD A MOVIE
		//argv[2] is the input file name, arv[6] is the framenumber
		MOVIE *movie = LoadMovie(fin, intFnum, aWidth, aHeight);
		
		ILIST *tempList = movie->Frames;
		IENTRY *currentEntry = tempList->First;
		
		IMAGE *currentImage = currentEntry->YUVImage;

		int frameCounter, entryCounter;
		if (strcmp(argv[x], "-aging") == 0) {
			for(entryCounter =0; entryCounter< intFnum; entryCounter++){
				Aging(currentImage);	
				currentEntry = currentEntry->Next;	
			}
		}
		

		currentEntry = movie->Frames->First;
		//IMPLEMENT HFLIP FUNCTION
		if(strcmp(argv[x], "-hflip") == 0){
			for(entryCounter =0; entryCounter < intFnum; entryCounter++){
				HFlip(currentImage);
				currentEntry = currentEntry->Next;
				currentImage = currentEntry->YUVImage
			}		
		}
		currentEntry = movie->Frames->First;	
		if(strcomp(argv[x], "-edge") == 0){
			for(entryCounter =0; entryCounter < intFnum; entryCounter++){
				Edge(currentImage);
				currentEntry = currentEntry->Next;
				currentImage = currentEntry->YUVImage;
			}
		}
		char *anotherP;
		char *anotherToken;
		char *anotherToken2;	
		char b[] = argv[x];
		char *anotherSearch = "-";

		token = strtok(b, anotherSearch);
		anotherToken2 = strtok(NULL, anotherSearch);
		
		unsigned int startingVal = strtoul(anotherToken, &anotherP, 10);
		if(*anotherP != '\0'){
			fputs("Invalid start\n", stderr);
			PrintUsage();
			exit(10);
		}
		
		unsigned int endingVal = strtoul(anotherToken2, &anotherP, 10);
		if(*anotherP != '\0'){
			fputs("Invalid start\n", stderr);
			PrintUsage();
			exit(10);
		}	
		

		currentEntry = movie->Frames->First;
		if(strcomp(argv[x], "-crop") == 0){
			if(x< argc -1){
				ste = argv[x+1];
			}
			else{
				printf("Missing argument for the input start to end!\n");
				return 5;
			} /*esle*/
			x+=;
			CropImageList(tempList, startingVal, endingVal);
		}	 
		
		if(strcomp(argv[x], "-fast") == 0){
			if(x < argc -1){
				fct = argv[x+1];		
			}
			else{
				printf("Missing argument for the factor!\n");
				return 5;
			} /*esle*/
			x+=2;
			continue;
		}

		if(strcomp(argv[x], "-reverse") == 0){
			ReverseImageList(tempList);
		}


		srand(time(NULL));
		int r = rand() % (watermarkImage->W + 1);
		int r2 = rand() % (watermarkImage->H + 1);

		currentEntry = movie->Frames->First;
		currentImage = currentEntry->YUVImage;
		if(strcomp(argv[x], "-watermark") == 0){
			if(x <argc -1){
				fwmk = argv[x+1];
				while(myCounter < fnum){
                        		for(entryCounter =0; entryCounter < 15; entryCounter++){
						if(currentEntry->Next != NULL){
                        	        		Watermark(currentImage, watermarkImage, r, r2);
							currentEntry = currentEntry->Next;
                        	        		currentImage = currentEntry->YUVImage;
						}
                 	        	}
					//randomize the position after 15 frames
					r = rand() % (watermarkImage->W +1);
					r2 = rand() % (watermarkImage->H + 1);
					myCounter+=15;
				}
			}
			else{
				printf("Missing argument for file name!\n");
				return 5;
			}/* esle */
			x+=2;
		}


		if(strcomp(argv[x], "-spotlight") == 0){}
			

		/* to be implemented */

		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

	/* to be implemented */

	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
	
	MOVIE *movie = CreateMovie(width, height);
	ILIST *list = movie->Frames;
	int i;
	for(i = 0; i< frameNum; i++){
		AppendYUVImage(list,LoadOneFrame(fname,i, width, height));
		 
	}
	return movie;	
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
