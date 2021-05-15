/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

static IENTRY *NewImageEntry(IMAGE *i, YUVIMAGE *y);
static IMAGE *DeleteImageEntry(IENTRY *e);
// allocates a new image entry
static IENTRY *NewImageEntry(IMAGE *i, YUVIMAGE *y){
	IENTRY *e;
	e = malloc(sizeof(IENTRY));
	if(!e){
		perror("Out of memory! Aborting...");
		exit(10);
	}/* fi */
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->RGBImage =NULL;
	e->YUVImage = NULL;

	if(i == NULL){	
		e->RGBImage = NULL;
		e->YUVImage = y;
	}
	else{
		e->RGBImage = i;
		e->YUVImage = NULL;
	}
	return e;
}

void AppendImageEntry(ILIST *l, IENTRY *e){
	//update new entry
	e->Prev = l->Last;
	e->Next = NULL;
	e->List = l;
	//update the Last of the last entry in the original list	
	l->Last = e;
	
}


//deletes an image entry
static IMAGE *DeleteImageEntry(IENTRY *e){
	IMAGE *i;
	assert(e);
	i = e->RGBImage;
	free(e);
	return i;
}//end of DeleteImageEntry
/*
static YUVIMAGE *DeleteYUVImageEntry(IENTRY *e){
	YUVIMAGE *i;
	assert(e);
	i = e->YUVImage;
	free(e);
	return i;
}
*/

/* Create a new image list */
ILIST *CreateImageList(void)
{
	/* to be implemented */
	ILIST *list;
	list = malloc(sizeof(ILIST));
	if(! list){
		perror("Out of memory! Aborting...");
		exit(10);
	}/* fi */
	list->Length = 0;	
	list->First = NULL;
	list->Last = NULL;	
	return list;
} /* end of CreateImageList */

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	/* to be implemented */
	IENTRY *e, *n; //2pointers for ientry
	IMAGE *i;
	assert(list);
	e = list->First; // need 2 because we alter e? so e becomes the value of first and n becomes 
	while(e){
		n = e->Next;
		i = DeleteImageEntry(e);
		DeleteImage(i);
		e = n;
	}
	free(list);
}//end of DeleteStudentList

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	/* to be implemented */
	IENTRY *e = NULL;
	assert(list);
	assert(RGBimage);
	e = NewImageEntry(RGBimage,NULL);
	if(list->Last){ //checks if last has a value
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;//last spot becomes e
	}
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;	
	}
	list->Length++;
} //end of AppendRGBImage

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	/* to be implemented */
	IENTRY *e = NULL;
	assert(list);
	assert(YUVimage);
	e = NewImageEntry(NULL, YUVimage);
	if(list->Last){ //first condition is to see 
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->Last->Next = e;
		list->Last = e;
	}
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;	
		list->Last = e;
	}
	list->Length++;
}//end of AppendYUVimage

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	//adjusts first to point at start
	IENTRY *e;
	e = list->First;
	for(int i =0; i<start; i++){
		  e = e->Next;

	}
	list->First =e;
	
	//adjusts last to point at end
	IENTRY *n;
	n = list->Last;
	for(int a =0; a<end; a++){
		n = n->Prev;
	}
	list->Last = n;

	//updates the length of the list
	list->Length = end - start;		
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	/* to be implemented */
	IENTRY *e;
	ILIST *l = CreateImageList();
	e = list->First;
	while(e){//check if e exists
		//probably put in begining to get the "First"
		AppendImageEntry(l, e);
		for(int i=0; i< factor; i++){
			if(e->Next != NULL){ //check if the following image entries exist
		 		e = e->Next;
			}
			else{
				return; //to end the function
			}//end if
		}//end for
	}
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	/* to be implemented */
	ILIST *l = CreateImageList();
	IENTRY *m;
	
	m = list->Last;
	for(int i =0; i< list->Length; i++){
		AppendImageEntry(l,m);
		m = m->Prev;
	}//end for
}

/* EOF */
