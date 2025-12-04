/* Consider a process control block with the following fields
a) Process id 
b)Process states
c)Priority
write A c program to create a singly linked list of PCB nodesand perform the below operations
1)Read the details for the processes and create the linked structure.Ensure the process is added to the existing linked list based
on the priority value. The lower the priority value, the higher the priority. Validate the priority value to be only positive integer.
2)Display all the process with ID,Sate and priority.
3)Display all the processes with the highest prioity
4)Remove all the processes whose state ="dead from the list and display the list
*/

# include<stdio.h>  
#include<stdlib.h>
# include<malloc.h>  
  
typedef struct node  
    {  
    int priority;  
    int info;  
    struct node *link;  
}NODE;  
NODE *front = NULL;  

 
void insert(int data,int priority)  
{  
    NODE *temp,*q;  
    temp = (NODE *)malloc(sizeof(NODE));  
    temp->info = data;  
    temp->priority = priority;  
     
    if( front == NULL || priority < front->priority )  
    {  
        temp->link = front;  
        front = temp;  
    }  
    else  
    {  
        q = front;  
        while( q->link != NULL && q->link->priority <= priority )  
            q=q->link;  
        temp->link = q->link;  
        q->link = temp;  
    }  
}  
  
  
  
void del()  
{  
    NODE *temp;  
    
    if(front == NULL)  
        printf("Queue Underflow\n");  
    else  
    {  
        temp = front;  
        printf("Deleted item is %d\n", temp->info);  
        front = front->link;  
        free(temp);  
    }  
  
  
void display()  
{  
    NODE *ptr;  
    ptr = front;  
    if(front == NULL)  
        printf("Queue is empty\n");  
    else  
    {     
        printf("Queue is :\n");  
        printf("Priority Item\n");  
        while(ptr != NULL)  
        {  
            printf("%5d        %5d\n",ptr->priority,ptr->info);  
            ptr = ptr->link;  
        }  
    }  
}  
  
   
int main()  
{  
    int choice, data, priority;  
    do  
    {  
        printf("1.Insert\n");  
        printf("2.Delete\n");  
        printf("3.Display\n");  
        printf("4.Quit\n");  
        printf("Enter your choice : ");  
        scanf("%d", &choice);  
        switch(choice)  
        {  
            case 1:  
                printf("Enter the data which is to be added in the queue : ");  
                scanf("%d",&data);  
                printf("Enter its priority : ");  
                scanf("%d",&priority);  
                insert(data,priority);  
                break;  
            case 2:  
                del();  
                break;  
            case 3:  
                display();  
                break;  
            case 4:  
            break;  
                default :  
                printf("Wrong choice\n");  
        }  
    }while(choice!=4);  
  
    return 0;  
}  
}


