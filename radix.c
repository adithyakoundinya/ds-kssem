#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
// Creating 10 Buckets naming 0 - 9 
struct Bucket
{
	struct Node *front;
	struct Node *rear;
}bucket[10];

// Node Structure that sits inside a bucket 
struct Node
{
	unsigned int info;
	struct Node *link;
};

// To Enqueue an integer into a bucket b
void enqueue(struct Bucket *b, int x) {
	struct Node* temp = 
		(struct Node*)malloc(sizeof(struct Node));
	temp->info =x; 
	temp->link = NULL;
	if(b->front == NULL && b->rear == NULL){
		b->front = b->rear = temp;
		return;
	}
	b->rear->link = temp;
	b->rear = temp;
}

// To Dequeue an integer into a bucket b
int dequeue(struct Bucket *b) 
{
	int value;	
	struct Node* temp = b->front;
	if(b->front == NULL) {
		//printf("Queue is Empty\n");
		return -1;
	}
	value=b->front->info;
	if(b->front == b->rear) {
		b->front = b->rear = NULL;
	}
	else {
		b->front = b->front->link;
	}
	free(temp);
	return value;
}

int findDepth(int inArray[],int numOfElements)
{
	int i,max=0,d=0;	
	//Finding the Maximum Element in an array
	for(i=0;i<numOfElements;i++)
	{
		if(max<inArray[i])
			max=inArray[i];
	}
	//Finding number of Digits in Maximum Number
	while(max!=0)
	{
		max/=10;
		++d;
	}
	return d;
}

void radixSort(int inputArray[],int numOfElements, int d)
{
	int i,j,k=0,tempD,tempNum;	
	for(i=0;i<d;i++)
	{
		printf("\nIteration %d\n",i);				
		//Find the Least Significant Bit of all the numbers 		
		for(j=0;j<numOfElements;j++)
		{		
			tempNum=inputArray[j]/pow(10,i);
			tempD=d-i;
			while(tempD!=1)
			{	
				tempNum = tempNum%((int)pow(10,--tempD));
			}
			printf("enqueing %d into-%d\n",inputArray[j],tempNum);
			enqueue(&bucket[tempNum], inputArray[j]);
		}
		k=0;
		for(j=0;j<10;j++)
		{
			for(;;)
			{
				tempNum = dequeue(&bucket[j]);
				if(tempNum==-1)
					break;
				else
				{				
					printf("dequeing %d from bucket-%d\n",tempNum,j);				
					inputArray[k++]=tempNum;
				}
			}
		}
	}
}

int main()
{
	int inputArray[MAX],i,j,numOfElements,d;

	printf("Enter the Number of Elements to be Sorted\n");
	scanf("%d",&numOfElements);
	
	printf("Enter the elements one by one\n");
	for(i=0;i<numOfElements;i++)
	{
		scanf("%d",&inputArray[i]);
	}
	//Finding the number of iterations required for radix sort	
	d=findDepth(inputArray,numOfElements);
	printf("Before Sorting Array looks like...\n");
	for(i=0;i<numOfElements;i++)
	{
		printf("%d\t",inputArray[i]);
	}
	radixSort(inputArray,numOfElements,d);
	printf("The sorted Array is\n");
	for(i=0;i<numOfElements;i++)
	{
		printf("%d\t",inputArray[i]);
	}
}	
