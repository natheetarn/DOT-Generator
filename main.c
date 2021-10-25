#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc, char *argv[]){
    
    if(argc != 3){
        printf("Argument count error\nUsage: %s file_name output_file_name",argv[0]);
        return -1;
    }
    FILE* fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("Error opening file");
        return -1;
    }
    //read graph properties: directed, undirected, weighted/not
    bool directed = 0;
    bool weighted = 0;
    char tmp1,tmp2;
    fscanf(fp,"%c %c",&tmp1,&tmp2);
    printf("%c %c\n",tmp1,tmp2);
    if(tmp1 == 'd' || tmp1 == 'D'){
        directed = true;
    }
    else if(tmp1 == 'u' || tmp2 == 'U') directed = false;
    else{
        printf("File format error.");
        return -1;
    }

    if(tmp2 == 'W'|| tmp2 == 'w'){
        weighted = true;
    }
    else if(tmp2 == 'n' || tmp2 == 'N')weighted = false;
    else{
        printf("File format error.");
        return -1;
    }

    // read number of nodes
    int num_node = 0;
    fscanf(fp,"%d",&num_node);
    printf("Nodes: %d\n",num_node);
    
    //read labels
    char buffer[101];
    char **labels = (char**)malloc(num_node*sizeof(*labels));

    for(int i = 0; i < num_node; i++){
        fscanf(fp,"%100s",buffer);
        labels[i] = (char*)malloc(strlen(buffer));
        if(labels[i]){
            strcpy(labels[i],buffer);
        }
    }

    for (int i = 0; i < num_node; i++){
        printf("Node %d's label: %s\n",i,labels[i]);
    }

    //read adjacencey matrix
    int **matrix = (int**)malloc(num_node*sizeof(int*));// allocate array of int pointers
    for(int i = 0; i < num_node; i++){
        matrix[i] = (int*)malloc(num_node*sizeof(int));// allocate each pointers to int
    }

    for(int i = 0 ; i < num_node; i++){
        for(int j = 0; j < num_node; j++){
            fscanf(fp,"%d",&matrix[i][j]);
        }
    }
    // matrix printing for debug
    // for(int i = 0 ; i < num_node; i++){
    //     for(int j = 0; j < num_node; j++){
    //         printf("%d ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    FILE* out_file = fopen(argv[2],"w");
    
    if(directed)
}