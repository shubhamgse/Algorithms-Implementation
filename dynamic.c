#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int n; // Total No. of items.
int m; // Knapsack capacity.

typedef struct item{
	int profit;
	int weight;
}item;
int * include;
void printItem(int b[n+1][m+1], int remaingProfit,item * array){

	if(remaingProfit ==0)return;

	/*int found =0;

	int i = n1;
		int j= m1;
		for(j= m;j>=0;j--){
			if(remaingProfit == b[i][j]){
				found = 0;
				printItem(b,remaingProfit,i-1,m, array);
				break;
			}
			else{

				found = 1;
			}

		}

		if(found == 1){

			printf("Item %d\t Profit %d \t Weight %d \n", i+1,array[i+1].profit,array[i+1].weight);

			remaingProfit = remaingProfit - array[i+1].profit;

			printItem(b,remaingProfit,i,m,array);


		}

	*/	

	for(int i = 0 ; i<=n;i++){
		for(int j =0; j<=m;j++){

			if(remaingProfit == b[i][j]){
				include[i]= 1;
				remaingProfit = remaingProfit - array[i].profit;
				printItem(b,remaingProfit,array);
				return;
			}
		}
	}

}

//-------------------------Knapsack Implementation-----------------------------

void knapsack(item * array){

	int b[n+1][m+1];


	for(int w = 0; w <= m; w++){
		b[0][w] = 0; //Empty row 0
	}


	for(int k = 1; k <= n; k++){
		b[k][0] = 0; //Empty column 0

		for(int w = 1; w <= m; w++){

			if(array[k].weight <= w && b[k-1][w - array[k].weight] + array[k].profit > b[k-1][w]){
				b[k][w] = b[k-1][w - array[k].weight] + array[k].profit;
				//include[k] =1;
			}
			else{
				b[k][w] = b[k-1][w];
				//include[k] =0;
			}

		}
	}


	/*printf("-------------------------------------------------------------\n");
	int i;
	for ( i = 0; i <= n; i++)
	{
		printf("|");
		int j;
		for ( j = 0; j <= m; j++)
		{
			
			printf(" %d\t| ",b[i][j]);
		}
		
		printf("\n");
	}
	printf("-------------------------------------------------------------\n");*/


	//--------------------Code to print the solution that is item number and profit
	printf("Total Profit earned : %d\n",b[n][m]);
	//printf("Item %d\t Profit %d \t Weight %d \n", n,array[n].profit,array[n].weight);
	int rp = b[n][m];//- array[n].profit;
	printItem(b,rp,array);
		
}



/*--------------------- Print matrix------------------------------------------*/

void printItemList(item * array){
	int temp=0; 
	printf("Items Selected are :\n");
	for(int i =0; i<=n; i++){
		if(include[i] == 1){
			temp += array[i].weight;
			printf("Item%d\t",i);
			printf("Profit %d\t",array[i].profit);
			printf("Weight %d\n",array[i].weight);
		}
	}
	printf("Total Weight : %d\n",temp);
}

/*--------------------- Create a Weight Matrix from Given File------------------*/
item * Create (char * fileName){

	item * array = malloc(sizeof(item) *10);
	char buff[255];
	char *token;
	int i = 0;
	int j = 0;
	FILE *fptr;
	//fprintf(stderr,"File Finding");
	fptr = fopen (fileName,"r");
	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,"");
		n = atoi(token);
		include = malloc(sizeof(int)*n);
	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,"");
		m = atoi(token); 

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
		array[j].weight = 0;
		j++;
		token = strtok(buff,",");
		array[j].weight = atoi(token);
		j++;
		
		while((token = strtok(NULL,","))){
			array[j].weight = atoi(token);
			j++;
		}

		for(int i=0;i<=n;i++){
			include[i] = 0;
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
		printf("Solving Knapsack Problem using Dynamic Programming Algorithm for input file %s \n",argv[1]);
		if(access(argv[1],F_OK)!= -1 ){
			matrix = Create(argv[1]);
			//printf("Total Items : %d\n",n);
			//printf("Total Capacity of Knapsack :%d\n",m);
			//printItemList(matrix);
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