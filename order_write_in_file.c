#include<stdio.h>
#include<stdlib.h>

void write_file(int order_no,char* username, float weight,float volume, float price,char* status)
{
    FILE *fp;
    fp=fopen("order_details.txt","a");
    fprintf(fp,"%d\n%s\n%f\n%f\n%f\n%s\n",order_no,username,weight,volume,price,status);
    fclose(fp);
}
int main(int argc, char const *argv[])
{
    write_file(123,"jfdn",678.4,93.9,23.9,"To be packed");
    return 0;
}
