#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct Character{
	char c;
	int frequency;
}character;

typedef struct HeapNode{
	char data;
	int frequency;
	struct HeapNode * left;
	struct HeapNode * right;
}heapNode;

typedef struct minHeap{
	struct HeapNode** element;
	int n;
	int size;
}minHeap;



int totalCharacter;

/*---------------------------------------- Finds the Left and Right Child ----------------*/
int left(minHeap * heap,int i){
	if((2*i)+1 >= heap->n){
		return -1;
	}else{
		return ((2*i)+1);
	}

}

int right(minHeap * heap,int i){
	if((2*i)+2 >= heap->n){
		return -1;
	}else{
		return ((2*i)+2);
	}

}
/*---------------------------------------- Finds the Last Leaf Node -----------------------*/
int lastParent(minHeap * heap, int i){
	//printf("%d\n",i);
	if(((i-1)/2) >= heap->n){
		return -1;
	}else{
		return ((i-1)/2);
	}

}
/*--------------------------------- Boolean checker whether it is the leaf or not ---------*/
int isLeaf(minHeap * h, int i){ // for array Heap

	if(left(h,i)==-1 || right(h,i) ==-1){
		if(left(h,i)!=-1){
			return 0;
		}
		return -1;
	}
	else{
		return 0;
	}
}

/*-----Debug--------*/
void dfs(heapNode *h){
	if(h==NULL) return;

	
	dfs(h->left);
	printf("%c\n",h->data);
	dfs(h->right);


	return;
}
/*--------------------- Dfs technique for printing codes------------------------------------------*/

void printItemList(heapNode * start, int * a, int level){
	if(start->left != NULL){
		a[level] = 0;
		printItemList(start->left,a,level+1);
	}

	if(start->right != NULL){
		a[level] =1;
		printItemList(start->right,a,level+1);
	}

	if(start->left == NULL && start->right == NULL){ // start printing from here
		printf("%c ",start->data);
		for(int i =0;i<level;i++){
			printf("%d",a[i]);
		}
		printf("\n");
	}
}
/*---------------------------------- Builds the Huffman tree ------------------*/
heapNode * newNode(char c, int frequency){

	heapNode * node = (heapNode*)malloc(sizeof(heapNode));
	node->left = NULL;
	node->right = NULL;
	node->frequency = frequency;
	node->data = c;
	return node;
}
/*--------------------- Create a character Matrix from Given File------------------*/
character * Create (char * fileName){

	character * array = malloc(sizeof(character) *20);
	char buff[255];
	char *token;
	int i=0;
	int j = 0;
	FILE *fptr;
	//fprintf(stderr,"File Finding");
	fptr = fopen (fileName,"r");

	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,",");
		array[i].c = *token;
		i++;
		while((token = strtok(NULL,","))){
			array[i].c = *token;
			i++;
		}

	fgets(buff,sizeof(buff),fptr);
		token = strtok(buff,",");
		array[j].frequency = atoi(token);
		j++;
		while((token = strtok(NULL,","))){
			array[j].frequency = atoi(token);
			j++;
		}

	if (i==j){
		totalCharacter = i;
	}
	else{
		totalCharacter =0;
		printf("File Inputs Not Proper. Please Check that each character has a certain frequency.\n");
		exit(0);
	}

	return array;
}


/*--------------------------------- Heapify Technique(siftDown) --------------------------*/
minHeap * siftDown( minHeap * h, int pos){

	if ((pos < 0) || (pos >= h->n)) return h; // Illegal position
	while (isLeaf(h,pos) == 0){//Keep swapping until you get to a leaf
		int j = left(h,pos); //Get left child
		//printf("%d\n",h->element[pos]);
		if(j+1 < h->n && (h->element[j]->frequency > h->element[j+1]->frequency))
			j++; // j is now index of child with lesser value
		if (h->element[pos]->frequency < h->element[j]->frequency) return h;
		else{
			//Swap
			heapNode * temp = h->element[pos];
			h->element[pos] = h->element[j];
			h->element[j] = temp;
			//printf(" I%d\n",h->element[pos]);
			//break;
		}
		pos = j;  // Move down
	}
	
return h;
}

/*-------------------------------------- Builds the Heap ---------------------------------*/
minHeap * buildHeap(minHeap *h){

	for(int i = lastParent(h,h->n-1);i>=0;i--){
		//printf("Index %d\n",i);
		h =siftDown(h,i);
		//printf("%d\n",h->element[i]);
	}

	return h;
}

/*-------------------------------------- Initialize and Creates a new Heap ----------------*/
minHeap * newHeap(character * h, int num , int max){

	minHeap * heap = (minHeap*)malloc(sizeof(minHeap));
	heap->size = max;
	heap->element = (heapNode**)malloc(heap->size * sizeof(heapNode*));
	for (int i = 0; i < max; i++)
        heap->element[i] = newNode(h[i].c, h[i].frequency); // each character and its freuency now is a node also
	heap->n = num;
	heap = buildHeap(heap);
	return heap;	
}
/*---------------------- Remove The minimum ---------------------------------*/
heapNode * removePriority(minHeap * h){
	if(h->n == 0) return NULL;
	heapNode * c = h->element[0];

	h->element[0] = h->element[h->n-1]; // last index 
	h->n--;
	h = siftDown(h,0);
	return c;
	
}
/*------------------------ Adding node to tree -------------*/
void addKey(minHeap * h, heapNode * p){

	h->n++;
	int index = h->n -1;
	if(index == 0) return;
	else{
		while(p->frequency < h->element[lastParent(h,index)]->frequency ){
			h->element[index] = h->element[lastParent(h,index)];
			index = lastParent(h,index);
		}
	}
	h->element[index] = p;
	
}
/*--------------------- Huffmann Coding Function ------------------*/
heapNode * huffmanCoding(minHeap * h){
	heapNode * l;
	heapNode * r;
	heapNode * parent;
	// build the tree extracting two minimum element.
	while(!(h->n ==1)){
		l = removePriority(h);
		r = removePriority(h);
		//printf("%c\n",l->data);
		//printf("%c\n",r->data);
		parent = newNode('#',l->frequency+r->frequency);
		parent->left = l;
		parent->right = r;

		addKey(h,parent);
	}

	heapNode * root = removePriority(h);
	//printf("parent left %c\n",parent->left->data);
	//printf("parent right %c\n",parent->right->data);
	//printf("parent %c\n",parent->data);
	return parent;
}

/*------------------------------------------Main Function---------------------------------*/
int main(int argc, char * argv[]){


	printf("----------------Huffman Coding-------------------\n");
	printf("\n");

	if(argc==2 && argv[1]!= NULL){
		character * matrix;
		minHeap * hp;
		int * d = malloc(sizeof(int)*100);
		int level =0;
		heapNode * hn;
		printf("Solving Huffman Coding for input file %s \n",argv[1]);
		if(access(argv[1],F_OK)!= -1 ){
			matrix = Create(argv[1]);
			
			//printf("TotalCharacter :%d\n",totalCharacter);
			hp = newHeap(matrix,totalCharacter,totalCharacter);

			heapNode * root = huffmanCoding(hp);
			
			printItemList(root,d,level);
			//dfs(root);
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