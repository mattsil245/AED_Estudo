#include <stdio.h>
#include "arvore_binaria.h"

int main(){
    ArvoreBinaria * arvore = criar_arvore();

    inserir(arvore, 10);
    inserir(arvore, 5);
    inserir(arvore, 15);
    inserir(arvore, 4);
    inserir(arvore, 7);
    inserir(arvore, 151);

    imprimir_arvore(arvore);
    printf("Altura: %d, Tamanho: %d\n", altura_arvore(arvore), tamanho_arvore(arvore)); // 0
    
    remover(arvore, 10);
    printf("Teste: %d\n", arvore->raiz->e);
    
    printf("Buscando o elemento 7...\n");
    No *no_encontrado = buscar(arvore, 7);

    if (no_encontrado != NULL) {
        printf("Encontrado! O valor e: %d\n", no_encontrado->e);
    } else {
        printf("Nao encontrado.\n");
    }

    remover(arvore, 10);
    imprimir_arvore(arvore);

    liberar_arvore(arvore);
    return 0;
}