#include <stdio.h>
#include <stdlib.h>

int main(){
    int tamanho = 10;
    int * a = (int*) calloc(tamanho,sizeof(int));

    int newTam = tamanho + 3;
    a = (int*) realloc(a, newTam * sizeof(int));

    for(int i=0; i<newTam; i++){
        printf("%d: %d ", i, a[i]);
    }

}