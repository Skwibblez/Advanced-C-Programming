//Josephus.c: our first C program
//author: Hugh Fong
//10/8/17
//#firstTimeProgrammingInC :D
#include<stdio.h>
int main() {
	//Get number of people in the circle from input and fill it up with 1s
	int n;
	printf("How many people in the circle?");
	scanf("%d", &n);
	printf("You entered %d\n", n);
	int circle[1000];
	for(int i =0; i<n; i++){
		circle[i] = 1;
	}
	//Set surv as boolean for the while loop
	int surv;
	int killer =2;
	int counter =0;
	int dead = -1;
	int numKillers = 0;
	int maxKill= 0;
	while(surv!=1){
		//check each element in the array for people who are alive
		for(int j =0; j<n; j++){
			if(circle[j]!=dead){
				counter++;
				
				//check for the winner by seeing if there is only one killer left and that the loop has went through each element at least once already
				if((numKillers ==1) && (counter> n)){
					surv =1; 
					printf("The spot %d is safe\n", j+1);
					break;
				}		
				//determines if the element will be a survivor or a killer since the killer is always the odd number among the remainding people that are alive						
				if(counter%2 ==0){
					//decrease numKillers by 1 if the element happens to be a killer
					if(circle[j] >= killer){
						numKillers = numKillers-1;
				//		printf("killers: %d\n", numKillers);
					}
					else{}
					//kill off that element and print it
					circle[j] = dead;
				//	printf("circle[%i] is dead\n", j);
				}
				//turn people that are "neutral" into killers and increase the number of killers by one
				else if(circle[j] == 1){
					circle[j] = killer;
					numKillers = numKillers +1;

				}
				//increments the person's internal kill count by 1
				//im using the value of them as the number they actually killed
				if((counter%2== 1) && (circle[j] != -1)){
					circle[j] = circle[j] +1;	
				} 
				//corrects the number of maxKill because setting them as killer is too much and further incrementing them by 1 afterwards means they are 2 above their actual kill count
				if(circle[j] > maxKill){
					maxKill = circle[j] - 2;
				}
				//exception to handle the case where number of people in the circle is 1
				if(n ==1){
					maxKill = 0;
				}
			}
		}
	
}
printf("Most executions by an individual is : %i\n", maxKill);
return 0;

}
