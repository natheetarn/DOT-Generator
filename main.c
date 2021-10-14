#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int n = 0;
    char buffer[101];
    printf("Enter number of nodes: ");
    scanf("%d",&n);

    char **labels = (char **)malloc(n*sizeof(*labels));

    for(int i = 0; i < n; i++){
        printf("Enter label for node %d: ",i);
        scanf("%100s",buffer);
        labels[i] = (char*)malloc(strlen(buffer));
        if(labels[i]){
            strcpy(labels[i],buffer);
        }
    }

    for (int i = 0; i < n; i++){
        printf("%s\n",labels[i]);
    }

}