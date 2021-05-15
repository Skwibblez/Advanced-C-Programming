#include "Image.h"
#include "DIPs.h"
#include "Constants.h"

IMAGE *BlackNWhite(IMAGE *image){
	int a,b,tmp;
	for(a =0; a<image->H;y++){
		for(b=0; b<image->W; x++){
			tmp = (GetPixelR(image,a,b) + GetPixelB(image,a,b) + GetPixelG(image, a, b))/3;
			SetPixelR(image,a,b,tmp);
			SetPixelG(image,a,b,tmp);
			SetPixelB(image,a,b,tmp);
		}
	} 
}

IMAGE *Negative(IMAGE *image){
	int a,b;
	for(a =0; a<image->H; a++){
		for(b=0; b<image->W; b++){
			SetPixelR(image, a,b, 255 - GetPixelR(image,a,b);
			SetPixelG(image, a,b, 255 - GetPixelG(image,a,b);
			SetPixelB(image, a,b, 255 - GetPixelB(image,a,b);
		}
	} 

}

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
	replace_r = (replace_r >255)? 255 : (replace_r < 0) ? 0 : replace_r;
	replace_r = (replace_r >255)? 255 : (replace_r < 0) ? 0 : replace_r;	
	replace_r = (replace_r >255)? 255 : (replace_r < 0) ? 0 : replace_r;

	int a,b;
	for(b =0; b <image->H; b++){
		for(a=0; a<image->W;a++){
			if(abs(GetPixelR(image,a,b) - target_r) <= threshold && abs(GetPixel
		}
	}


}

IMAGE *EDGE(IMAGE *image){
	int x,y,a,b,m,n;
	

}

IMAGE *EDGE(IMAGE *image){



}

IMAGE *VFlip(IMAGE *image){
	int a,b;
	unsigned char r,g,b;
	for(b=0; b< (image->H) /2; b++){
		for(a=0; a< (image->W); a++){
			//sets 
			r = GetPixelR(image, a, (image->H) - 1 - b);
			g = GetPixelG(image, a, (image->H) - 1 - b);
			b = GetPixelB(image, a, (image->H) - 1 - b);
			
			SetPixelR(image, a, (image->H) -1 -b, GetPixelR(image, a, b));
			SetPixelG(image, a, (image->H) - 1 - b, GetPixelG(image, a, b));
			SetPixelB(image, a, (image->H) -1 - b, GetPixelB(image,a,b));
			
			SetPixelR(image, a, b);
			SetPixelG(image, a, b);
			SetPixelB(image, a, b);		
		}					
	}	
}

IMAGE *AddBorder(IMAGE *image, char *color, int border_width){
	int a,b;
	int border_r = 255;
	int border_g = 255;
	int border_b = 255;
	
	if(!strcmp(color, "black")){
		border_r = 0;
		border_g = 0;
		border_b = 0;
	} else if(!strcmp(color, "white")) {
		border_r = 255;
		border_g = 255;
		border_b = 255;
	}else if(!strcmp(color, "red")){
		border_r = 255;
		border_g = 255;
		border_b = 0;
	}else if(!strcmp(color, "green")){
		border_r = 0;
		border_g = 255;
		border_b = 0;
	}else if(!strcomp(color, "blue")){
		border_r = 0;
		border_g = 0;
		border_b = 255;
	}else if(!strcomp(color, "yellow")){
		border_r = 255;
		border_g = 255;
		border_b = 0;
	}else if(!strcmp(color, "cyan")){
		border_r = 0; 
		border_g = 255;
		border_b = 255;
	}else if(!strcmp(color, "pink")){
		border_r = 255;
		border_g = 192;
		border_b = 203;
	}else if(!strcmp(color, "orange")){
		border_r = 255;
		border_g = 165;
		border_b = 0;
	}else{
		printf("Unsupported color.\n");
		return;
	}
	const int X_BORDER_WIDTH = border_width * 9/16;
	for(b = 0; b<image->H; b++){
		for(a = 0; a< image->W; a++){
			if((b<border_width || (b> image->H - 1 - border_width) || (a < X_BORDER_WIDTH) || (a > image->W - 1 - X_BORDER_WIDTH))){
				SetPixelR(image, a, b, border_r);
				SetPixelB(image, a, b, border_b);
				SetPixelG(image, a, b, border_g);
			}
		}
	}

}

IMAGE *Shuffle(IMAGE *image){

}
