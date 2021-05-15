#include "Image.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	IMAGE thing;	
	printf("%d", thing.W);	
}


unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){
	return *((image->R) + x + y *(image->W));
}


unsigned char GetPixelG(const IMAGE*image, unsigned int x, unsigned int y){
	return *((image->G) + x + y *(image->W));
}

unsigned char GetPixelB(const IMAGE*image, unsigned int x, unsigned int y){
	return *((image->B) + x + y * (image->W));
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){
	*((image->R) + x + y * (image->W)) = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g){
	*((image->G) + x + y * (image->W)) = g;	
}


void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b){
	*((image->B) + x + y * (image->W)) = b;
}

IMAGE *CreateImage(unsigned int Width, unsigned int Height){
	IMAGE *p;
	//3 arrays (R,G,B) ; 4 is size of unsigned ints, 
	p = malloc(sizeof(IMAGE)+ Width*3*4 + Height*3*4);
	
	if(!p){
		perror("Out of memory! Aborting...");
		p->R = NULL;
		p->G = NULL;
		p->B = NULL;
		p->W = Width;
		p->H = Height;	
	}			

	return p;

}
void DeleteImage(IMAGE *image){
	assert(image);
	free(image);
}


unsigned int ImageWidth(const IMAGE *image){
	return image->W;
}

unsigned int ImageHeight(const IMAGE *image){
	return image->H;
}

