#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int n; // Total No. of items.
int c; // Knapsack capacity.

typedef struct item{
	int profit;
	int weight;
	int upperbound;
}item;

typedef struct Node{
	item * array;
	struct Node * left, * right;
}node;

int maxprofit,num =0;
int bestset[100];
int include[100];

int kwf4(int i, int profit, int weight, item * matrix){

	int x[n];
	int bound = profit;

	for(int j = 1; j<=n; j++){	//Initialize item variables to 0
		x[j] = 0;
	}

	while(weight < c && i<=n){
		if(weight + matrix[i].weight <= c){
			x[i] = 1;
			weight = weight + matrix[i].weight;
			bound = bound + matrix[i].profit;
		}
		else{
			x[i] = (c - weight)/ matrix[i].weight;
			weight = c;
			bound = bound + matrix[i].profit * x[i];
		}
		i = i+1;
	}

	return bound;

}
/*--------------------- Print matrix------------------------------------------*/

void printItemList(item * array){
	for(int i =0; i<n; i++){
		printf("Item%d\n",i+1);
		printf("Profit %d\n",array[i].profit);
		printf("Weight %d\n",array[i].weight);
	}
}

/*--------------------- Create a Weight Matrix from Given File------------------*/
item * Create (char * fileName){

	item * array = malloc(sizeof(item) *10);
	char buff[255];
	char *token;
	int i=0;
	int j = 0;
	FILE *fptr;
	//fprintf(stderr,"File Finding");
	fptr = fopen (fileName,"r");
	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,"");
		n = atoi(token);
	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,"");
		c = atoi(token); 

	fgets(buff,sizeof(buff),fptr);
		array[i].profit = 0;
		i++;
		token = strtok(buff,",");
		array[i].profit = atoi(token);
		i++;

		while((token = strtok(NULL,","))){
			array[i].profit = atoi(token);
			i++;
		}

	fgets(buff,sizeof(buff),fptr);
		array[j].profit = 0;
		j++;
		token = strtok(buff,",");
		array[j].weight = atoi(token);
		j++;
		while((token = strtok(NULL,","))){
			array[j].weight = atoi(token);
			j++;
		}

	return array;
}
/*--------------------------- Checking Promising Node ---------------------------------*/
int promising(int i, int profit, int weight, item * matrix){
	// cannot get a solution by expanding node i
	if(weight >=c)
		return 0;

	// compute upper bound
	int bound = kwf4(i+1, profit, weight, matrix);

	return (bound > maxprofit);

}
/*--------------------------- recursive knapsack function ------------------------------*/
void knapsack(int i, int profit, int weight, item * matrix){
	if(weight <=c && profit > maxprofit){
		//save the better solution
		maxprofit = profit;
		num =i;
		//include bestset
		for(int k =1; k<=n;k++){
			bestset[k] = include[k];
		}
	}

	if(promising(i,profit,weight, matrix)){
		include[i+1] = 1;
		knapsack(i+1,profit+matrix[i+1].profit,weight + matrix[i+1].weight,matrix);
		include[i+1] = 0;
		knapsack(i+1,profit,weight, matrix);

	}
}
/*------------------------------------------- Knapsack Main Function --------------------*/
void Knapsack(item * matrix){
	num =0;
	maxprofit = 0;
	int TotaWeight = 0;
	knapsack(0,0,0,matrix);
	printf("Max Profit earned is %d\n",maxprofit);
	printf("Items Selected are :\n");
	for(int i = 1;i<=num;i++){
		//printf best set
		if(bestset[i] == 1){
			TotaWeight = TotaWeight + matrix[i].weight;
			printf("Item%d\t",i);
			printf("Profit %d\t",matrix[i].profit);
			printf("Weight %d\n",matrix[i].weight);
		}
	}
	printf("Total Weight in Knapsack is %d\n",TotaWeight);
}

/*------------------------------------------Main Function---------------------------------*/
int main(int argc, char * argv[]){


	printf("----------------Knapsack Algorithm-------------------\n");
	printf("\n");

	if(argc==2 && argv[1]!= NULL){
		item * matrix;
		int ** d;
		printf("Solving Knapsack Problem using Backtracking Algorithm for input file %s \n",argv[1]);
		if(access(argv[1],F_OK)!= -1 ){
			matrix = Create(argv[1]);
			//printf("Total Items : %d\n",n);
			//printf("Total Capacity of Knapsack :%d\n",m);
			Knapsack(matrix);
			//printItemList(matrix);
		}
		else{
			printf("Input File Not Found\n");
			return 0;
		}
	}
	else{
		printf("\n");
		printf("Not correct User inputs......\n");
		printf("Please re-run the program with correct user inputs.\n");
	}
	return 0;
}
/*---------------------------------------------END---------------------------------------*/