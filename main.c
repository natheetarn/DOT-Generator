#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct graph{
    bool directed;
    bool weighted;
    int num_node;
    char **labels;
    int **matrix;
}Graph;
int read_graph(FILE** f,struct graph* g,int index){

    //read property
    char tmp1,tmp2;
    fscanf(*f,"%c %c",&tmp1,&tmp2);
    if(tmp1 == 'd' || tmp1 == 'D'){
        g[index].directed = true;
    }
    else if(tmp1 == 'u' || tmp2 == 'U') g[index].directed = false;
    else{
        printf("File format error / Reached end of file.\n");
        return -1;
    }

    if(tmp2 == 'W'|| tmp2 == 'w'){
        g[index].weighted = true;
    }
    else if(tmp2 == 'n' || tmp2 == 'N')g[index].weighted = false;
    else{
        printf("File format error./ Reached end of file.\n");
        return -1;
    }

    //read num nodes
    int tmp = 0;
    fscanf(*f,"%d",&tmp);
    g[index].num_node = tmp;
    // printf("Nodes: %d\n",tmp);

    //read labels
    char buffer[101];
    g[index].labels = (char**)malloc(g[index].num_node*sizeof(*g[index].labels));

    for(int i = 0; i < g[index].num_node; i++){
        fscanf(*f,"%100s",buffer);
        g[index].labels[i] = (char*)malloc(strlen(buffer));
        if(g[index].labels[i]){
            strcpy(g[index].labels[i],buffer);
        }
    }

    // for (int i = 0; i < g[index].num_node; i++){
    //     printf("Node %d's label: %s\n",i,g[index].labels[i]);
    // }

    //matrix
    g[index].matrix = (int**)malloc(g[index].num_node*sizeof(int*));// allocate array of int pointers
    for(int i = 0; i < g[index].num_node; i++){
        g[index].matrix[i] = (int*)malloc(g[index].num_node*sizeof(int));// allocate each pointers to int
    } 

    for(int i = 0 ; i < g[index].num_node; i++){
        for(int j = 0; j < g[index].num_node; j++){
            fscanf(*f,"%d",&g[index].matrix[i][j]);
            // printf("%d ",g[index].matrix[i][j]);
        }
        // printf("\n");
    }
    while(1){
        int c;
        c = fgetc(*f);
        if(c == '\n' || c==EOF){
            break;
        }
    }

    return 0;
}


int check_argument(int argc){
    if(argc != 3){
        printf("Argument count error\nUsage: program_name file_name number_of_graph");
        return -1;
    }
    return 0;
}

int write_to_file(struct graph* g, int index, char* out_file_name){
    FILE* out_file = fopen(out_file_name,"w");
    if(g[index].directed){
        fprintf(out_file,"digraph {\n");

        if(g[index].weighted){
            for(int i = 0; i < g[index].num_node ; i++){
                for(int j = 0; j < g[index].num_node; j++){
                    if(g[index].matrix[i][j] == 0) continue;
                    else{
                        fprintf(out_file,"\t%s -> %s [label = \"%d\"];\n",g[index].labels[i],g[index].labels[j],g[index].matrix[i][j]);
                    }
                }
            }
        }
        else if(!g[index].weighted){
            for(int i = 0; i < g[index].num_node ; i++){
                for(int j = 0; j < g[index].num_node; j++){
                    if(g[index].matrix[i][j] == 0) continue;
                    else{
                        fprintf(out_file,"\t%s -> %s;\n",g[index].labels[i],g[index].labels[j]);
                    }
                }
            }
        }
        fprintf(out_file,"}\n");
    }

    else if(!g[index].directed){
        fprintf(out_file,"graph {\n");
        if(g[index].weighted){
            for(int i = 0; i < g[index].num_node ; i++){
                for(int j = 0; j < g[index].num_node; j++){
                    if(g[index].matrix[i][j] == 0) continue;
                    else{
                        fprintf(out_file,"\t%s -- %s [label = \"%d\"];\n",g[index].labels[i],g[index].labels[j],g[index].matrix[i][j]);
                    }
                }
            }
        }
        else if(!g[index].weighted){
            for(int i = 0; i < g[index].num_node ; i++){
                for(int j = 0; j < g[index].num_node; j++){
                    if(g[index].matrix[i][j] == 0) continue;
                    else{
                        fprintf(out_file,"\t%s -- %s;\n",g[index].labels[i],g[index].labels[j]);
                    }
                }
            }
        }
        fprintf(out_file,"}\n");
    }

    
    fclose(out_file);
}
int main(int argc, char *argv[]){
    
    if(check_argument(argc) == -1){
        return -1;
    }
    
    FILE* fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("Error opening file");
        return -1;
    }
    int num_graph = atoi(argv[2]);
    

    struct graph* graphs = (struct graph*)malloc(num_graph*sizeof(struct graph*));

    //read all graphs and store in graphs(dynamically allocated array of struct graph)
    for (int i = 0 ; i < num_graph ; i++ ){
    if(read_graph(&fp,graphs,i) == -1) return -1;
    else{
        char tmp_name[sizeof"output100.txt"];
        sprintf(tmp_name,"file%03d.dot",i+1);
        write_to_file(graphs,i,tmp_name);
        printf("file%03d.dot created successfully\n",i+1);
    }
    }
    
    // write each graph to new file


    fclose(fp);
    free(graphs);
    



    
    
}