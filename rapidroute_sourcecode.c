#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define V 15
#define INF 99999 
#define PRICE_PER_KG 10.0 
#define PRICE_PER_CUBIC_METER 20.0 
#define PRICE_PER_KM 11.0
int n,first,second;
void ofg(int b[])
{  int largest;
   b[0]=largest;
   printf("%d\n",n);
    for(int j=1;j<=n+1;j++)
    {
        if(b[j]>largest)
        {
            largest=b[j];
        }
    }

      printf("\n2.Second shortest path: %d km",largest);
      second=largest;
      printf("\t Estimated price = %d",largest*3);
      printf("\t Estimated delivery= 3 days");

}
void registration(char* username,char* password)
{
    FILE *filePointer ;
    filePointer=fopen("test1.txt","a");
    fprintf(filePointer,"\n%s,%s",username,password);
    fclose(filePointer);
}
int validate_u_p(char* line,char* username,char* password)
{
    int i=0,j=0,flag=0;
    for ( i = 0; line[i]!='\0'&&username[i]!='\0'&&line[i]!=','; i++)
    {
        //printf("%c %c\n",line[i],username[i]);
        if(username[i]!=line[i])
        {
            
            flag=1;
            return 0;
        }
    }
    //printf("\n");
    if(username[i]!='\0')
    {
        return 0;
    }
    for(++i,j=0;line[i]!='\0'&&password[j]!='\0';i++,j++)
    {
        //printf("%c %c\n",line[i],password[j]);
        if(password[j]!=line[i])
        {
            return 0;
        }
    }
    if(password[j]!='\0'||line[i]!='\0')
    {
        return 0;
    }
    return 1;
    
}
int login(char* username,char* password)
{
    FILE *filePointer ;
    int flag=0,i;
    filePointer=fopen("test1.txt","r");
    char line[50],ch;
    do
    {
        fscanf(filePointer,"%s",line);
        if(validate_u_p(line,username,password)==1)
        {
            
            fclose(filePointer);
            return 1;
        }
        
        //printf("%s\n",line);
        ch=fgetc(filePointer);
    }while(ch!=EOF);
    fclose(filePointer);
    return 0;
}
int minDistance(int dist[], bool sptSet[])
{

	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}
void frstop(int o[],int n)
{
    int price,days;
   
     for(int i=0;i<15;i++)
     {
        if(i==n)
        {
            printf("1. shortest distance = %d km \t",o[i]);
             price=o[i]*5;
             first=o[i];
        }
        
     }
    printf(" estimated price = %d \t",price);
    printf(" Estimated delivery days = 2 days");
}
void option(int dist[])
{
    int o[100];
    for(int i=0;i<15;i++)
    {
        o[i]=dist[i];
    }
    
    printf("Destination =  ");
    scanf("%d",&n);
    frstop(o,n);
     
    
}
void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t\t\t %d\n", i, dist[i]);
}
void dijkstra(int graph[V][V], int src)
{
	int dist[V]; 
	bool sptSet[V]; 
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet);	
		sptSet[u] = true;
		for (int v = 0; v < V; v++)

		
			if (!sptSet[v] && graph[u][v]
				&& dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

    option(dist);

}
int signup(int h)
{
     char username[50],password[50];
                int y;
                    if(h==1)
                    {
                 printf("Enter username: ");
                 scanf("%s", username);// read string
                 printf("Enter password: ");
                 scanf("%s", password);
                 registration(username,password);
                
                    }
                    else if(h==2)

                    {   printf("Enter username: ");
                        scanf("%s", username);// read string
                         printf("Enter password: ");
                        scanf("%s", password);
                         y=login(username,password);
                      
                    }
                    return y;
                        
}
void dij2(int graph[V][V], int src,int dest)
{ int dist[15];
int visited[15],parent[15]; 
    int i,j,shortest,next_shortest,min_distance;
    // Initialize all vertices as unvisited and distance as infinity
    for(i=0;i<16;i++)
    {
        visited[i]=0;
        dist[i]=INF;
        parent[i]=-1;
    }
    // Distance to source vertex is 0
    dist[src]=0;
    // Traverse all vertices
    for(i=0;i<16;i++)
    {
        shortest=-1;
        next_shortest=-1;
        min_distance=INF;
        // Find unvisited vertex with shortest distance
        for(j=0;j<15;j++)
        {
            if(!visited[j] && dist[j]<min_distance)
            {
                next_shortest=shortest;
                shortest=j;
                min_distance=dist[j];
            }
            else if(!visited[j] && dist[j]<INF && dist[j]>dist[next_shortest])
            {
                next_shortest=j;
            }
        }
        // Mark visited vertex and update distances of its neighbors
        visited[shortest]=1;
        for(j=0;j<16;j++)
        {
            if(graph[shortest][j]!=0 && !visited[j])
            {
                if(dist[shortest]+graph[shortest][j]<dist[j])
                {
                    dist[j]=dist[shortest]+graph[shortest][j];
                    parent[j]=shortest;
                }
            }
        }
    }
    // Print the second shortest path
  
  
    i=dest;
    while(i!=-1)
    {
        

        i=parent[i];
    }
      int b[15];
for(int d=0;d<15;d++)
{
    b[d]=dist[d];
}

ofg(b);
}
void write_file(int order_no,char* username, float weight,float volume, float price,char* status)
{
    FILE *fp;
    fp=fopen("order_details.txt","a");
    fprintf(fp,"%d\n%s\n%f\n%f\n%f\n%s\n",order_no,username,weight,volume,price,status);
    fclose(fp);
}
int main()
{
  
  
	int graph[V][V] = { { 0,300,0,2000,500,0,0,0,0,0,0,0,0,0,0 },
						{ 300,0,0,700,400,2200,0,0,0,0,0,0,0,0,0},
						{ 0,0,0,1400,0,1500,700,0,0,0,0,0,0,0,0 },
						{ 2000,700,1400,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 500,400,0,0,0,0,0,1200,0,0,0,0,0,0,0 },
						{ 0,2200,1500,0,0,0,0,0,700,2900,0,0,0,0,0 },
						{ 0,0,700,0,0,0,0,0,0,0,1000,0,0,0,0 },
						{ 0,0,0,0,1200,0,0,0,0,2100,0,0,0,0,0 },
						{ 0,0,0,0,0,700,0,0,0,0,0,1000,0,0,0 },
						{ 0,0,0,0,0,2900,0,2100,0,0,0,0,0,2400,0},
						{ 0,0,0,0,0,0,1000,0,0,0,0,0,2200,0,0},
						{ 0,0,0,0,0,0,0,0,1000,0,0,0,100,0,400},
						{ 0,0,0,0,0,0,0,0,0,0,2200,100,0,0,0},
						{ 0,0,0,0,0,0,0,0,0,2400,0,0,0,0,1300},
						{ 0,0,0,0,0,0,0,0,0,0,0,400,0,1300,0}};
                       printf("                                         *****Welcome to Rapid-Route*****\n");
    printf("                      A Logistics Company offering secure and reliable delivery of consignments\n");


    printf("The Cities  are \n0-->Bangalore, 1-->Chennai,  2-->Hyderabad,  3-->Kolkata,  4-->Panaji,  5-->Delhi,  6-->Mumbai,  7-->Bhopal,  \n8-->Lucknow,  9-->Trivandrum,  10-->Amravati,  11-->Chandigarh,  12-->Shimla,  13-->Ranchi,  14-->Jaipur\n");

                int t=0,s,h;;
                 
                printf("Enter 1 for signup\nEnter 2 for login \n");
                int u;
                scanf("%d",&h);
                 if(h==1)
                 {
                    signup(1);
                 }
                 else if(h==2)
                 {
                  
                        u=signup(2);
                    
                    
                 }
                 if(u==1)
                 {
                 printf("From source = ");
                 scanf("%d",&s);
                 dijkstra(graph,s);
                 dij2(graph,s,n);
                 //dij3(graph,s,n);
                 

                 }
                 int q;
                 printf("\nEnter your selection = ");
                 scanf("%d",&q);
                 int ct = 0;
    FILE *file = fopen("count.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &ct);
        fclose(file);
    }
    ct++;
    file = fopen("count.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", ct);
        fclose(file);
         
    }
    int order_no;
    char username[100]; 
    float weight;
    float volume; 
    float price;
    
    order_no=ct;
                 if(q==1)
                 {
                    printf("Enter username = ");
                    scanf("%s", username);
                    printf("\nEnter Weight = ");
                    scanf("%f",&weight);
                    printf("\nEnter Volume = ");
                    scanf("%f",&volume);
                    price=price = weight * PRICE_PER_KG + volume * PRICE_PER_CUBIC_METER + first * PRICE_PER_KM;
                    char status[100]= "Orderplaced";
                    write_file(order_no,username,weight,volume,price,status);
                    printf("%d\n%s\n%f\n%f\n%f\n%s\n",order_no,username,weight,volume,price,status);
                    
                 }
                else if(q==2)
                {
                     printf("Enter username = ");
                    scanf("%s", username);
                    printf("\nEnter Weight = ");
                    scanf("%f",&weight);
                    printf("\nEnter Volume = ");
                    scanf("%f",&volume);
                    price=price = weight * PRICE_PER_KG + volume * PRICE_PER_CUBIC_METER + second * PRICE_PER_KM;
                    char status[100]= "Orderplaced";
                    write_file(order_no,username,weight,volume,price,status);
                    printf("%d\n%s\n%f\n%f\n%f\n%s\n",order_no,username,weight,volume,price,status);
                }
                 return 0;
}
       
     
