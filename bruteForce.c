#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

int n; // Total No. of items.
int m; // Knapsack capacity.

typedef struct item{
	int profit;
	int weight;
}item;

int bestChoice=0;
int maxProfit =0;

void knapsack(item * array){
	int tempweight = 0;
	int tempvalue = 0;
	int tempID =0;


	for(int i = 0; i < pow(2,n); i++){ // 2^n possibilities are there
		//i =3. possibilities are 0,1,2,3,4,5,6,7.
		tempID = i; // 0,1,2,3,4,5,6,7.
		tempvalue = 0;
		tempweight = 0;

		for(int j=0; j<n;j++){ // scan through entire list of items

			if(tempID%2 ==1 ){
				tempweight = tempweight + array[j].weight;
				tempvalue = tempvalue + array[j].profit;
			}
			tempID = tempID/2;

		}

		if(tempweight <= m && tempvalue > maxProfit){ // check weight obtained is less then knapsack capacity. Consider only optimal profit.
			maxProfit = tempvalue;
			bestChoice = i; // inicates item no.
		}


	}


}


/*--------------------- Print matrix------------------------------------------*/

void printItemList(item * array){
	int TotalWeight =0;
	//printf("Best Choice is %d\n",bestChoice);
	printf("Total Profit Earned : %d\n", maxProfit);
	printf("Selected Items are : \n");
	for(int i =0; i<n; i++){
		if(bestChoice%2 ==1){
			TotalWeight = TotalWeight + array[i].weight;
			printf("Item%d\t",i+1);
			printf("Profit %d\t",array[i].profit);
			printf("Weight %d\n",array[i].weight);
		}
		bestChoice = bestChoice/2;
	}
	
	printf("Total weight in Kanpsack : %d\n",TotalWeight);

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
		m = atoi(token); 

	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,",");
		array[i].profit = atoi(token);
		i++;
		while((token = strtok(NULL,","))){
			array[i].profit = atoi(token);
			i++;
		}

	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,",");
		array[j].weight = atoi(token);
		j++;
		while((token = strtok(NULL,","))){
			array[j].weight = atoi(token);
			j++;
		}

	return array;
}

/*------------------------------------------Main Function---------------------------------*/
int main(int argc, char * argv[]){


	printf("----------------Knapsack Algorithm-------------------\n");
	printf("\n");

	if(argc==2 && argv[1]!= NULL){
		item * matrix;
		int ** d;
		printf("Solving Knapsack Problem using BruteForce Algorithm for input file %s \n",argv[1]);
		if(access(argv[1],F_OK)!= -1 ){
			matrix = Create(argv[1]);
			//printf("Total Items : %d\n",n);
			//printf("Total Capacity of Knapsack :%d\n",m);
			knapsack(matrix);
			printItemList(matrix);
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
/*--------------------------END-----------------------------*/