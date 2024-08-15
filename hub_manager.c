#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct order 
{
    int order_no;            // Order number
    char username[30];       // Username of the customer who placed the order
    float weight;            // Weight of the package in kilograms
    float volume;            // Volume of the package in cubic meters
    float price;             // Price of the order in rupees
    char status[30];         // Current status of the order
    struct order *next;      // Pointer to the next node in the linked list
} orders;
orders* create()
{
    orders* newnode=(orders*)malloc(sizeof(orders));
    return newnode;
}
orders* read_orders(orders* head)
{
    FILE *fp;
    char ch,line[50];
    fp=fopen("order_details.txt","r");
    int i=0,temp_orderno;
    char temp_username[30],temp_status[30];
    float temp_weight,temp_volume,temp_price;
    orders* prev=head,*newnode;
    do
    {
        fscanf(fp,"%[^\n]",line);
        if(i%6==0)
        {
            temp_orderno=atoi(line);
            //printf("%d\n",temp_orderno);
        }
        else if(i%6==1)
        {
            strcpy(temp_username,line);
            //printf("%s\n",temp_username);
        }
        else if(i%6==2)
        {
            temp_weight=atof(line);
            //printf("%.2f\n",temp_weight);
        }
        else if(i%6==3)
        {
            temp_volume=atof(line);
            //printf("%.2f\n",temp_volume);
        }
        else if(i%6==4)
        {
            temp_price=atof(line);
            //printf("%.2f\n",temp_price);
        }
        else if(i%6==5)
        {
            strcpy(temp_status,line);
            //printf("%s\n",temp_status);
            //printf("%s\n",line);
            if(prev!=NULL)
            {
                newnode=create();
                prev->next=newnode;
                newnode->order_no=temp_orderno;
                strcpy(newnode->username,temp_username);
                newnode->weight=temp_weight;
                newnode->volume=temp_volume;
                newnode->price=temp_price;
                strcpy(newnode->status,temp_status);
                newnode->next=NULL;
                prev=newnode;
            }
            else
            {
                newnode=create();
                
                newnode->order_no=temp_orderno;
                strcpy(newnode->username,temp_username);
                newnode->weight=temp_weight;
                newnode->volume=temp_volume;
                newnode->price=temp_price;
                strcpy(newnode->status,temp_status);
                newnode->next=NULL;
                prev=newnode;
                head=newnode;
            }
        }
        ch=fgetc(fp);
        i++;
    }while(ch!=EOF);
    fclose(fp);
    return head;
}
void print_oll(orders* head)
{
    if(head==NULL)
    {
        //message
        return;
    }
    while(head!=NULL)
    {
        printf("Order no= %d\n",head->order_no);
        printf("username= %s\n",head->username);
        printf("weight = %.2f\n",head->weight);
        printf("volume= %.2f\n",head->volume);
        printf("price= %.2f\n",head->price);
        printf("status= %s\n",head->status);
        head=head->next;
    }
    
}

int search_update(orders* head,int keyint,char *keychar)
{
    if(head==NULL)
    {
        return 0;
    }
    else
    {
        orders* temp=head;
        while(temp!=NULL)
        {
            if(temp->order_no==keyint)
            {
                strcpy(temp->status,keychar);
                return 1;
            }
            else
            {
                temp=temp->next;
            }
        }
        return 0;
    }
}
int write_orders(orders* head)
{
    orders* temp=head;
    FILE *fp;
    fp=fopen("order_details.txt","w");
    if(temp==NULL)
    {
        
        fclose(fp);
        return 1;
    }
    else
    {
        while(temp!=NULL)
        {
            fprintf(fp,"%d\n%s\n%f\n%f\n%f\n%s\n",temp->order_no,temp->username,temp->weight,temp->volume,temp->price,temp->status);
            temp=temp->next;
        }
        fclose(fp);
        return 1;
    }
}

orders* get_tail(orders* head) {
    orders* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
}

orders* partition(orders* head, orders* end, orders** new_head, orders** new_end) {
    orders* pivot = end;
    orders* prev = NULL;
    orders* cur = head;
    orders* tail = pivot;

    while (cur != pivot) {
        if (cur->price < pivot->price) {
            if ((*new_head) == NULL) {
                (*new_head) = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) {
                prev->next = cur->next;
            }
            orders* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*new_head) == NULL) {
        (*new_head) = pivot;
    }

    (*new_end) = tail;

    return pivot;
}

orders* quick_sort_recur(orders* head, orders* end) {
    if (!head || head == end) {
        return head;
    }

    orders* new_head = NULL;
    orders* new_end = NULL;

    orders* pivot = partition(head, end, &new_head, &new_end);

    if (new_head != pivot) {
        orders* tmp = new_head;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;
        new_head = quick_sort_recur(new_head, tmp);
        tmp = get_tail(new_head);
        tmp->next = pivot;
    }

    pivot->next = quick_sort_recur(pivot->next, new_end);

    return new_head;
}

void quick_sort_price(orders** head_ref) {
    (*head_ref) = quick_sort_recur(*head_ref, get_tail(*head_ref));
}

int main(int argc, char const *argv[])
{
    orders *o_head=NULL;
    printf("***WELCOME TO RAPID ROUTE HUB MANAGEMENT SOFTWARE***\n");
    o_head=read_orders(o_head);
    print_oll(o_head);
    int ch,order_no;
    char status[30];
    while(1)
    {
        
        printf("Press 1 to update status\n");
        printf("Press 2 to sort orders by price\n");
        printf("Press 3 to print\n");
        printf("Press 4 to exit\n");
        printf("Press 5 to write back and exit\n");
        scanf("%d",&ch);
        if(ch==1)
        {
            printf("Enter order no and status\n");
            scanf("%d %[^\n]",&order_no,status);
            if(search_update(o_head,order_no,status))
                printf("Update successful\n");
            else
                printf("Update failed since order was not found\n");
        }
        else if(ch==2)
        {
            quick_sort_price(&o_head);
            printf("Successfully sorted\n");
        }
        else if(ch==3)
        {
            print_oll(o_head);
        }
        else if(ch==4)
        {
            break;
        }
        else
        {
            write_orders(o_head);
            break;
        }
    }

    return 0;
}
