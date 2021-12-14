#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct graph{
    bool directed;
    bool weighted;
    int num_node;
    char **labels;
    int **matrix;
}Graph;
void read_num_node(FILE** f,struct graph* g,int index){
    int tmp = 0;
    fscanf(*f,"%d",&tmp);
    g[index].num_node = tmp;
    printf("Nodes: %d\n",tmp);

}
int read_adjacency_matrix(FILE** f,struct graph* g,int index){
    g[index].matrix = (int**)malloc(g[index].num_node*sizeof(int*));// allocate array of int pointers
    for(int i = 0; i < g[index].num_node; i++){
        g[index].matrix[i] = (int*)malloc(g[index].num_node*sizeof(int));// allocate each pointers to int
    } 

    for(int i = 0 ; i < g[index].num_node; i++){
        for(int j = 0; j < g[index].num_node; j++){
            fscanf(*f,"%d",&g[index].matrix[i][j]);
        }
    }
}
void read_labels(FILE** f,struct graph* g,int index){
    char buffer[101];
    g[index].labels = (char**)malloc(g[index].num_node*sizeof(*g[index].labels));

    for(int i = 0; i < g[index].num_node; i++){
        fscanf(*f,"%100s",buffer);
        g[index].labels[i] = (char*)malloc(strlen(buffer));
        if(g[index].labels[i]){
            strcpy(g[index].labels[i],buffer);
        }
    }

    for (int i = 0; i < g[index].num_node; i++){
        printf("Node %d's label: %s\n",i,g[index].labels[i]);
    }
}

int read_graph_property(FILE** f,struct graph* g,int index){
    char tmp1,tmp2;
    fscanf(*f,"%c %c",&tmp1,&tmp2);
    printf("%c %c\n",tmp1,tmp2);
    if(tmp1 == 'd' || tmp1 == 'D'){
        g[index].directed = true;
    }
    else if(tmp1 == 'u' || tmp2 == 'U') g[index].directed = false;
    else{
        printf("File format error.");
        return -1;
    }

    if(tmp2 == 'W'|| tmp2 == 'w'){
        g[index].weighted = true;
    }
    else if(tmp2 == 'n' || tmp2 == 'N')g[index].weighted = false;
    else{
        printf("File format error.2");
        return -1;
    }
    return 0;
}

int check_argument(int argc){
    if(argc != 3){
        printf("Argument count error\nUsage: program_name file_name output_file_name");
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
        else if(g[index].weighted){
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
    int num_graph = 0;
    fscanf(fp,"%d",&num_graph);
    

    struct graph* graphs = (struct graph*)malloc(num_graph*sizeof(struct graph*));

    //read all graphs and store in graphs(dynamically allocated array of struct graph)
    for (int i = 0 ; i < num_graph ; i++ ){
        if(read_graph_property(&fp,graphs,i)==-1){
        return -1;
    }
    read_num_node(&fp,graphs,i);
    read_labels(&fp,graphs,i);
    read_adjacency_matrix(&fp,graphs,i);
    }
    
    // write each graph to new file
    char out_name[20];
    strcpy(out_name, argv[2]);
    char tmp_name[20];
    strcpy(tmp_name,out_name);
    for (int j = 0 ; j  < num_graph ; j++){
        sprintf(tmp_name,"%s%d",tmp_name,j);
        
        write_to_file(graphs,j,tmp_name);
    }



    
    
}