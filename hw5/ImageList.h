/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/13/2016                                                  */
/*                                                                   */
/* ImageList.h: header file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageEntry {
	/* to be implemented */
	ILIST *List;
	IENTRY *Next;
	IENTRY *Prev;
	IMAGE *RGBImage;
	YUVIMAGE *YUVImage;
};

struct ImageList {
	/* to be implemented */
	unsigned int Length; /* Length of the list */
	IENTRY *First; /*Pointer to the first entry, or NULL */
	IENTRY *Last; /*Pointer to the last entry, or NULL */

};
static IENTRY *NewImageEntry(IMAGE *i, YUVIMAGE *y);

void AppendImageEntry(ILIST *i, IENTRY *e);

static IMAGE *DeleteImageEntry(IENTRY *e);


/* Create a new image list */
ILIST *CreateImageList(void);

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list);

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage);

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage);

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end);

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor);

/* Reverse an image list */
void ReverseImageList(ILIST *list);

#endif
