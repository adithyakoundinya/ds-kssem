/*Address Calculation Sort*/
/*It uses a hash function that can sort only 2 digit nos.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

struct list
{
	int info;
	struct list *next;
}*node[10]={NULL};

struct list *create()
{
	struct list *temp=(struct list *)malloc(sizeof(struct list));
	if(temp==NULL)
	{
		printf("\nMemory Allocation Error!");
		exit(1);
	}
	return temp;
}

struct list *makenode(int num)
{
	struct list *temp;
	temp=create();
	temp->info=num;
	temp->next=NULL;
	return temp;
}

struct list *insert(struct list *s,int num)
{
	struct list *ptr,*temp;
	ptr=s;
	temp=makenode(num);
	if(s==NULL)
		s=temp;
	else
	{
		/*code for placing new node at appropriate
		position in the subfile*/
		while((ptr->next->info<=num) && (ptr->next!=NULL))
		{	
			ptr=ptr->next;
		}
		if(temp->info<ptr->info)
		{
			temp->next=ptr;
			s=temp;
		}
		else
		{
			temp->next=ptr->next;
			ptr->next=temp;
		}
	}
	return s;
}

/*A hash function that operates upon two digit
numbers only*/

int hashfun(int n)
{
	return (n/10);
}

void addr_calc(int arr[],int size)
{
	int i,j=0,pos;
	for(i=0;i<size;i++)
	{
		pos=hashfun(arr[i]);
		node[pos]=insert(node[pos],arr[i]);
	}
	for(i=0;i<10;i++)
	{	
		while(node[i]!=NULL)
		{	
			arr[j++]=node[i]->info;
			node[i]=node[i]->next;
		}
	}
	printf("\nSorted output is: ");
	for(i=0;i<size;i++)
		printf("%d\t",arr[i]);
}

void main()
{
	int arr[MAX],i,n;
	printf("Enter total numbers to sort");
	scanf("%d",&n);
	printf("Enter numbers?");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	addr_calc(arr,n);
}
