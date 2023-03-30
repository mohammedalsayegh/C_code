// Namd:Mohammed Alsayegh
// This program load super large CSV file to buffer array of structs

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct record_t{
    unsigned int number;
    char seq[25];
    struct record_t *next;
}*head;

int main(void) {
    //file var
    FILE *fp;
    
    //time var
    time_t start,end;
    double dif;

    //struct array var
    int num_arr,arr_size;
    struct record_t *temp;
    num_arr=98000;
    arr_size=1024;

    //open the csv file
    fp = fopen("data4.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }
    
    struct record_t *A[num_arr];
    time (&start);
    for(int i=0;i<num_arr;i++){
        head = (struct record_t *)malloc(sizeof(struct record_t));
        fscanf(fp, "%d,%25s", &head->number, head->seq);
        head -> next = NULL;
        temp = head;
        for(int j=1;j<arr_size;j++){
            struct record_t *new = (struct record_t *)malloc(sizeof(struct record_t));
            fscanf(fp, "%d,%25s", &new->number, new->seq);
            new -> next = NULL;
            temp -> next = new;
            temp = new;
        }
        A[i] = head;
        if(!(i%1000)) printf("block number: %d\n", i);
    }
    time (&end);
    dif = difftime (end,start);
    printf ("malloc took %.2lf seconds to run.\n", dif);

    printf("no Errors\n");
    fclose(fp);
    return 0;
}