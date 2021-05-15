#include<stdio.h>
#include <string.h>
#include <math.h>
int main
//lool
//more stuff
	int poo = 1;
	char p2[] = "String";
	printf("%s\n", p2);
	char smth[2] = "a4";
	printf("%s\n", smth);
	smth[1] = poo;//qq
	//char poops = '1';
	//smth[1] = poops;
	printf("%s\n", smth);

	int intArr[2] = {5,5};
	intArr[0] = poo;
	printf("%i\n", intArr[0]);
	printf("%i\n", intArr[1]);
	PrintPosition();	
}

int[] ReturnKingPos(){
	int[2] kingLoc = {0,0};
	return kingLoc;	

}

void PrintPosition(){
	int[2] kingLoc= ReturnKingPos();
	printf("%i", kingLoc[0]);
}
