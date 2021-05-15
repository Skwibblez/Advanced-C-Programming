#include "Advanced.h"
#include <math.h>
#include "Image.h"

IMAGE *AddNoise(IMAGE *image,int n){
	int x, y, i;
	int num = (n * (image->H) * (image->W) ) /100;
	srand(time(NULL));

	for(i =0; i <num; i++){
		x = ( (double)rand()/RAND_MAX )* ((image->W) -1);
		y = ( (double)rand()/RAND_MAX ) * ( (image->H) -1);
		
		SetPixelR(image, x,y, 255);
		SetPixelG(image, x,y, 255);
		SetPixelB(image, x,y, 255);
	}

}//end AddNoise

IMAGE *Sharpen(IMAGE *image){
	int x,y,m,n,a,b;
	int tmpR =0;
	int tmpG = 0;
	int tmpB = 0;
		
	
	
}


IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits){
	CreateImage((image->W), (image->H));//needs to name this
	int x,y;
	for(x=0; x< (image->W); x++){
		for(y =0; y< (image->H); y++){
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++){
				SetPixelR(image, x,y, one);
				one <<= 1;
			}
			one = ~one;
			
			one = 1;
			for(i =0; i<gbits-1; i++){
				SetPixelG(image, x, y, one);
				one<<=1;
	
			}
			one = ~one;
			one = 1;
			for(i=0; i<bbits-1; i++){
				SetPixelB(image,x,y,one);
				one<<=1;	
			}			
			one = ~one;
			SetPixelB(image, x, y, one);
		}
	}

}//end posterize



IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount){
	int x,y,m;
	unsigned int temp_r, temp_g, temp_b;
	
	for(x=0; x< (image->W); x++){
		for(y=0; y<HEIGHT; y++){
			temp_r = GetPixelR(image, x,y);
			temp_b = GetPixelB(image,x,y);
			temp_g = GetPixelG(image,x,y);i

			for(m =1; m<=BlurAmount; m++){
				if((x+m) < (image->W)){
					temp_r = temp_r + GetPixelR(image, (x+m), y) * 0.5/BlurAmount;
					temp_g = temp_g + GetPixelG(image, (x+m), y) * 0.5/BlurAmount;
					temp_b = temp_b + GetPixelB(image, (x+m), y) * 0.5/BlurAmount;
				}
			}
		}
		SetPixelR(image, x,y, temp_r);
		SetPixelG(image, x,y, temp_g);
		SetPixelB(image, x,y, temp_b);
	}

}//end motion blur
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){}








IMAGE *Crop(IMAGE *image, int x, int y, int W, int H){
	//add x to 0 and add y to 0 to find the left most corner ( starting points)
	//must shift pixels to get the accurate spot
	//then x + W to find the width
	//then y + H to find the height
	//x must be less than w, y must be less than H
	for(int b =0; b< H; b++)
		for(int a =0; a<W; a++){
			SetPixelR(image, a+y, b+x, GetPixelR(image, x,y));
			SetPixelG(image, a+y, b+x, GetPixelG(image, x,y));	
			SetPixelB(image, a+y, b+x, GetPixelB(image, x,y));	
	
	}
	return CreateImage(W,H);

}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
	double factor = (double)(259 * (contrast + 255)) / (double) (255 * (259 - contrast));
	
	int new_pixel_value = (int)(factor * (pixel_value - 128) + 128);
	for(int b= 0; b< (image->H); b++){
		for(int a =0; a< (image->W); a++){
			SetPixelR(x, y, new_pixel_value);
			SetPixelG(x, y, new_pixel_value);
			SetPixelB(x, y, new_pixel_value);
		}
	}
	return image;
}





IMAGE *Resize(IMAGE *image, int percentage){
		
	
		
	image->W = image->W * (percentage/100.00);
	image->H = image->H * (percentage/100.00);
	
	//int newX = oldX * (percentage/100.00);
	//int newY =  * (percentage/100.00);
	//big resize
	if(percentage > 100){

		if(percentage/100.00 == ceil(percentage/100.00)){
			for(int i=0; i<percentage/100.00; i++){
				for(int j=0; j<percentage/100.00; j++){
					SetPixelR(image, i, j, GetPixelR(image, i, j)); 	
				}
			}
		}
		else{
			for(int i=0; i< ceil(percentage/100.00); i++){
				for(int j=0; j< ceil(percentage/100.00); j++){
					SetPixelR(image, i, j, GetPixelR(image, i, j));
				
				}
			
			}

		}
	}
	//small resize
	if(percentage <100){

		for(int i = 0; i < percentage/100.00; i++){
			for(int j = 0; j< percentage/100.00; j++){
				SetPixelR(image, i , j, GetPixelR(image, i, j));
			}
		}
			
		
	

 
	}

	
	return image;
	
	
}

