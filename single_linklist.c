#include<stdio.h>
#include<stdlib.h>
// struct node 
struct node{
	int data;
	struct node *next;
};
// decleration of funtion 
void insertAtEnd(struct node**,int);
void display(struct node*);
void insertAtBeg(struct node **,int);
void insertAtPos(struct node **,int, int);
void deleteFirst(struct node **);
void deleteAtLast(struct node **);
void deleteAtPos(struct node **,int);
void revdisplay(struct node *);
void revlink(struct node **);
void writeToFile(struct node *);
void readFromFile(struct node **);
void freeAll(struct node **);
int NodeCount(struct node *);
void deleteByEle(struct node **,int);
int main(){
	struct node *head=NULL;
	int choice,ele,pos;
	while(1){
		printf("<-------------------------------------------------------------------------------------->\n");
		printf("0->exit\t\t\t1->insert at last\t2->display\t\n3->insert at begining\t4->insert at position\t5->delete at first\n6->delete at last\t");
		printf("7->delete at position\t8->reverse display\n9->memory reverse\t10->write to file\t11->read from file\n12->node count\t\t13->delete by element\n");
		printf("<-------------------------------------------------------------------------------------->\n");
		printf("choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 0: printf("All data will be erased. Make sure to save the data to the file.\n Press 1 to quit and 0 to continue: ");
				scanf("%d",&choice);
				if(choice==1){
					freeAll(&head);
					exit(0);  
				}
				break;  
			case 1: printf("enter the element\n");
				scanf("%d",&ele);
				insertAtEnd(&head,ele);
				break;
			case 2: display(head);
				break;
			case 3: printf("enter the element\n");
				scanf("%d",&ele);
				insertAtBeg(&head,ele);
				break;
			case 4: printf("enter the index\n");
				scanf("%d",&pos);
				printf("enter the element\n");
				scanf("%d",&ele);
				insertAtPos(&head,pos,ele);
				break;
			case 5: deleteFirst(&head);
				break;
			case 6: deleteAtLast(&head);
				break;
			case 7: printf("enter the index\n");
				scanf("%d",&pos);
				deleteAtPos(&head,pos);
				break;
			case 8: revdisplay(head);
				printf("\n");
				break;	
			case 9: revlink(&head);
				break;
			case 10: writeToFile(head);
				break;
			case 11: readFromFile(&head);
				break;
			case 12: printf("Node count = %d\n",NodeCount(head));
				break;
			case 13: printf("enter the element: ");
				 scanf("%d",&ele);
				 deleteByEle(&head,ele);
				 break;
			default: printf("invalid choice\n");
		}//end of switch case
	}//end of while 
	return 0;
}// end of main
// fun to insert at first position 
void insertAtEnd(struct node **q, int x){
	struct node *temp,*t1;
	
	t1=*q;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
		
	if(*q==NULL)
		*q=temp;
	else{
		while(t1->next!=NULL)
			t1=t1->next;
		t1->next=temp;
	}
}
// fun to display node list
void display(struct node *q){
	if(q==NULL)
		printf("No node exists\n");
	else{
		while(q!=NULL){
			printf("%d\t",q->data);
			q=q->next;
		}
	}
	printf("\n");
}
// fun to insert node at first podition
void insertAtBeg(struct node **q,int x){
	struct node *temp;

	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	
	temp->next=*q;
	*q=temp;
}
// fun to insert node at any vaild position 
void insertAtPos(struct node **q,int pos, int x){
	if(pos==1){
		insertAtBeg(q,x);
		return;
	}
	struct node *temp,*t1;
	t1=*q;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	
	for(int i=2;i<pos;i++){
		if(t1->next!=NULL)
			t1=t1->next;
		else{
			printf("Invalid position\n");
			return;
		}
	}
	temp->next=t1->next;
	t1->next=temp;
}
// delete at first node
void deleteFirst(struct node **q){
	struct node *temp;
	temp=*q;
	*q=(*q)->next;
	free(temp);
}
// delete at last node 
void deleteAtLast(struct node **q){
	struct node *t;
	t=*q;
	if((*q)->next==NULL){
		free(*q);
		*q=NULL;
	}
	else{	
		while(t->next->next!=NULL)
			t=t->next;
		free(t->next);
		t->next=NULL;
	}
}
// delete at position 
void deleteAtPos(struct node **q,int pos){
	struct node *t,*temp;
	t=*q;
	if(pos<2)
		deleteFirst(q);
	else{
		pos-=2;
		while(pos--)
			t=t->next;
		temp=t->next->next;
		free(t->next);
		t->next=temp;
	}
} 
// fun to display nodes in reverse   
void revdisplay(struct node *q){
	if(q!=NULL){
		revdisplay(q->next);
		printf("%d\t",q->data);
	}
}
// fun to reverse the link list 
void revlink(struct node **q){
	struct node *ptr,*t1;
	t1=ptr=NULL;
	while((*q)!=NULL){
		ptr=*q;
		*q=(*q)->next;
		ptr->next=t1;
		t1=ptr;
	}
	*q=t1;
}
// fun to write data present in list into file 
void writeToFile(struct node *q){
	FILE *f = fopen("list.txt","w");
	while(q!=NULL){
		fprintf(f,"%d\t",q->data);
		q=q->next;
	}
	fclose(f);
}
// fun to read data present in file and creates the link list 
void readFromFile(struct node **q){
	FILE *f = fopen("list.txt","r");
	if(f==NULL){
		printf("File doesn't exit, data can't retrieve\n");
		return;
	}
	int data;
	fscanf (f, "%d", &data);    
	while (!feof (f))
	{  
		insertAtEnd(q,data);
		fscanf (f, "%d", &data); 	    
	}
	fclose(f);
}
// fun to free the all the node in link list 
void freeAll(struct node **q){
	struct node *temp;
	
	while(*q!=NULL){
		temp=*q;
		(*q)=(*q)->next;
		free(temp);
	}
}
// fun to count the numbers of node present in link list
int NodeCount(struct node *q){
	int count = 0;
	while(q!=NULL){
		q=q->next;
		count++;
	}
	return count;
}
// fun to delelte the data present in link list by ele
void deleteByEle(struct node **q,int ele){
	struct node *t1=*q,*temp=*q;
	int flag=1;
	if(*q==NULL)
		printf("No node exists\n");
	else if((*q)->data==ele){
		deleteFirst(q);
		flag=0;
	}
	else{
		temp=temp->next;
		int count = 2;
		while(temp!=NULL){
			if(temp->data==ele){
				deleteAtPos(q,count);
				flag=0;
			}
			temp=temp->next;
			count++;	
		}
	}
	if(flag)
		printf("Element not found\n");
	else
		printf("First Nodes of %d is deleted\n",ele);
}
