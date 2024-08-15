#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct order 
{
    int order_no;
    char username[30];
    float weight;
    float volume;
    float price;
    char status[30];
    struct order *next;
}orders;
orders* create()
{
    orders* newnode=(orders*)malloc(sizeof(orders));
    //check for failed case
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
        printf("%d\n",head->order_no);
        printf("%s\n",head->username);
        printf("%.2f\n",head->weight);
        printf("%.2f\n",head->volume);
        printf("%.2f\n",head->price);
        printf("%s\n",head->status);
        head=head->next;
    }
    
}
char* search_fetch(orders* head, int keyint)
{
    if (head == NULL) {
        return "Order Not_found";
    }
    orders* temp = head;
    while (temp != NULL) {
        if (temp->order_no == keyint) {
            char* keychar = (char*)malloc(sizeof(char)*30);
            strcpy(keychar, temp->status);
            return keychar;
        }
        temp = temp->next;
    }
    return "Order Not_found";
}

int main(int argc, char const *argv[])
{
    orders *o_head=NULL;
    int c,keyint;
    char output[30];
    printf("***WELCOME TO RAPID ROUTE CUSTOMER PORTAL***");
    o_head=read_orders(o_head);
    while(1)
    {
        printf("Enter 1 to track\nEnter 2 to exit\n");
        scanf("%d",&c);
        if(c==1)
        {
            printf("Enter the order no\n");
            scanf("%d",&keyint);
            strcpy(output,search_fetch(o_head,keyint));
            printf("status=%s\n",output);
        }
        else
        {
            break;
        }
    }
    //print_oll(o_head);
    return 0;
}
