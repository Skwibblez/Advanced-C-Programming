/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	/* to be implemented */
	MOVIE *frame;
	frame = malloc(sizeof(MOVIE));
	if(!frame){
		perror("Out of memory! Aborting...");
		exit(10);
	}/* fi */
	ILIST *list;
	list = malloc(sizeof(ILIST));
	if(!list){
		perror("out of memory! Aborting...");
		exit(10);
	}/* fi */
	frame->Frames = list;
	return frame;
}

unsigned char clip(int x){
	
	if(x<0){
		return 0;
	}else if(x>255){
		return 255;
	}else{
		return x;
	}	
}


/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	IENTRY *e, *n;
	IMAGE *i;
	assert(movie);
	e = movie->Frames->First;
	while(e){
		n = e->Next;
		i = DeleteImageEntry(e);
		DeleteImage(i);
		e = n;
	} 
	
	free(movie);
	/* to be implemented */
}
/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	/* to be implemented */
	IENTRY *e;
	e = movie->Frames->First;
	
	IMAGE *image = CreateImage(e->YUVImage->W, e->YUVImage->H);
	
	unsigned char *rPointer = image->R;
	unsigned char *gPointer = image->G;
	unsigned char *bPointer = image->B;

	unsigned char *Y = e->YUVImage->Y;
	unsigned char *U = e->YUVImage->U;
	unsigned char *V = e->YUVImage->V;
	int i;
	for(i=0; i< movie->Frames->Length; i++){
		/*creates a pointer of type unsigned char(type for Y) then goes into the
		entry of the original list then gets the Y, U and V values */
		unsigned char yVal = Y[i];
		unsigned char uVal = U[i];
		unsigned char vVal = V[i];
	
		/*Begins conversion of Y, U and V following the 
		assignment guides equation
		Create new point of type YUVIMAGE*/
		
		unsigned char C = yVal -16;
		unsigned char D = uVal - 128;
		unsigned char E = vVal - 128;
		
		unsigned char preClipR = (298 * C + 409 * E + 128) >> 8;
		unsigned char preClipG = (298 * C - 100 * D - 208 * E + 128) >> 8;
		unsigned char preClipB = (298 * C + 516 * D + 128) >> 8;
		
		
		
		//
		IMAGE *secImage = CreateImage(e->YUVImage->W , e->YUVImage->H);

		rPointer[i] = clip(preClipR);
		gPointer[i] = clip(preClipG);
		bPointer[i] = clip(preClipB);	


		secImage->R = rPointer;
		secImage->G = gPointer;
		secImage->B = bPointer;
	
		//ADDED THIS LINE TO SET OLD RGBIMAGE TO THE NEW ONE WHICH HAS A VAL 
		e->RGBImage = secImage;	
		e = e->Next;
	}
	e = movie->Frames->First;
	for(i =0; i< movie->Frames->Length; i++){
			DeleteYUVImage(e->YUVImage);
			e = e->Next;
	}
	
}

/* Convert a RGB movie to a YUV movie */

void RGB2YUVMovie(MOVIE *movie)
{
	/* to be implemented */
	IENTRY *e;
	e = movie->Frames->First;
	IMAGE *image = CreateIamge(e->YUVImage->W, e->YUVImage->H);
	
	unsigned char *rPointer = image->R;
	unsigned char *gPointer = image->G;
	unsigned char *bPointer= image->B;
	
	unsigned char *Y = e->YUVImage->Y;
	unsigned char *U = e->YUVImage->U;
	unsigned char *V = e->YUVImage->V;
	int i;
	
	for(i =0; i<movie->Frames->length; i++){
		unsigned char yVal = Y[i];
		unsigned char uVal = U[i];
		unsigned char vVal = V[i];

		yVal = clip((( 66 * rPointer[i] + 129 * gPointer[i] + 25 * bPointer[i] + 128) >> 8)+16);
		uVal = clip(((-38 * rPointer[i] - 74 * gPointer[i] + 25 * bPointer[i] + 128) >> 8) +128);
		vVal = clip(((118 * rPointer[i] - 94 * gPointer[i] - 18 * bPointer[i] + 128) >> 8) + 128);
	
		IMAGE *secImage = CreateImage(e->YUVImage->W, e->YUVImage->H);

		rPointer[i] = clip(preClipR);
		gPointer[i] = clip(preClipR);
		bPointer[i] = clip(preClipB);

		secImage->R = rPointer;
		secImage->G = gPointer;
		secImage->B = bPointer;
		
		e->RGBImage = secImage;
		e = e->Next;		
	}	
			
	e = movie->Frames->First;
	for(i=0; i<movie->Frames->Length; i++){
		DeleteRGBImage(e->RGBImage);
		e = e->Next;

	}

}

	

/* EOF */
