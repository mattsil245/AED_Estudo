#include <stdio.h>
#include <stdlib.h>

#include "arvore_binaria_de_busca.h"

ArvoreBinaria * criar_arvore()
{

    ArvoreBinaria * arvore = (ArvoreBinaria*) malloc(sizeof(ArvoreBinaria));
    if(arvore == NULL){
        printf("Erro de alocação");
        exit(1);
    }

    arvore->raiz = NULL;
    return arvore;
}

No *criar_no(Elemento e)
{
    No * novo_no = (No*) malloc(sizeof(No));
    if(novo_no == NULL){
        printf("Erro de alocação");
        exit(1);
    }
    novo_no->e = e;
    novo_no->filho_esquerdo = novo_no->filho_direito = NULL;
    return novo_no;
}

No *inserir_no(No * raiz_atual, Elemento e){

    if(raiz_atual == NULL) return criar_no(e);

    if(e < raiz_atual->e){ 
        raiz_atual->filho_esquerdo = inserir_no(raiz_atual->filho_esquerdo, e);
    }
    else {
        raiz_atual->filho_direito = inserir_no(raiz_atual->filho_direito, e);
    } 

    return raiz_atual;
}

Boolean inserir(ArvoreBinaria * arvore, Elemento e)
{
    if(arvore == NULL) return F;
    arvore->raiz = inserir_no(arvore->raiz, e);
    return T;
}

void imprimir_em_ordem_aux(No *no_atual)
{
    if(no_atual == NULL) return;

    imprimir_em_ordem_aux(no_atual->filho_esquerdo);

    printf("%d ", no_atual->e);

    imprimir_em_ordem_aux(no_atual->filho_direito);
}

void imprimir_arvore(ArvoreBinaria *arvore)
{
    if(arvore == NULL){
        printf("Erro: Arvore nao foi criada\n"); 
        return;
    }
    if(arvore->raiz == NULL){ 
        printf("A arvore esta vazia\n"); 
        return;
    }

    printf("Elementos da arvore (em ordem): ");
    imprimir_em_ordem_aux(arvore->raiz);
    printf("\n");
}

No *buscar_no(No *raiz_atual, Elemento e)
{
    if(raiz_atual == NULL){
        return NULL;
    }

    if(raiz_atual->e == e){
        return raiz_atual;
    }

    if(e < raiz_atual->e){
        return buscar_no(raiz_atual->filho_esquerdo, e);
    }else{
        return buscar_no(raiz_atual->filho_direito, e);
    }
}

No *buscar(ArvoreBinaria *arvore, Elemento e)
{
    if(arvore == NULL){
        return NULL;
    }

    return buscar_no(arvore->raiz, e);
}

int contar_nos_aux(No *no_atual)
{
    if(no_atual == NULL){
        return 0;
    }

    return 1 + contar_nos_aux(no_atual->filho_esquerdo) + contar_nos_aux(no_atual->filho_direito);
}

int altura_aux(No *no_atual)
{
    if(no_atual == NULL){
        return 0;
    }

    int altura_esquerda = altura_aux(no_atual->filho_esquerdo);
    int altura_direita = altura_aux(no_atual->filho_direito);

    if(altura_esquerda > altura_direita){
        return 1 + altura_esquerda;
    }else{
        return 1 + altura_direita;
    }
}

int altura_arvore(ArvoreBinaria * arvore)
{
    if(arvore == NULL){
        return 0;
    }

    return altura_aux(arvore->raiz);
}

int tamanho_arvore(ArvoreBinaria *arvore)
{
    if(arvore == NULL){
        return 0;
    }

    return contar_nos_aux(arvore->raiz);
}

void liberar_nos_aux(No *no_atual)
{
    if(no_atual == NULL){
        return;
    }

    liberar_nos_aux(no_atual->filho_esquerdo);
    liberar_nos_aux(no_atual->filho_direito);

    free(no_atual);
}

void liberar_arvore(ArvoreBinaria *arvore)
{
    if(arvore == NULL){
        return;
    }

    liberar_nos_aux(arvore->raiz);
    free(arvore);
}

No *encontrar_menor(No *no_atual)
{
    while(no_atual != NULL && no_atual->filho_esquerdo != NULL){
        no_atual = no_atual->filho_esquerdo;
    }

    return no_atual;
}

No *encontrar_maior(No *no_atual)
{
    while(no_atual != NULL && no_atual->filho_direito != NULL){
        no_atual = no_atual->filho_direito;
    }

    return no_atual;
}

No *remover_no(No *raiz_atual, Elemento e)
{
    if(raiz_atual == NULL){
        return NULL;
    }

    if(e < raiz_atual->e){
        raiz_atual->filho_esquerdo = remover_no(raiz_atual->filho_esquerdo, e);
    } else if(e > raiz_atual->e){
        raiz_atual->filho_direito = remover_no(raiz_atual->filho_direito, e);
    } else{

        if(raiz_atual->filho_esquerdo == NULL && raiz_atual->filho_direito == NULL){
            free(raiz_atual);
            return NULL;
        }

        else if(raiz_atual->filho_esquerdo == NULL){
            No * temp = raiz_atual->filho_direito;
            free(raiz_atual);
            return temp;
        }

        else if(raiz_atual->filho_direito == NULL){
            No * temp = raiz_atual->filho_esquerdo;
            free(raiz_atual);
            return temp;
        }

        else{
            No * sucessor = encontrar_menor(raiz_atual->filho_direito);
            raiz_atual->e = sucessor->e;
            raiz_atual->filho_direito = remover_no(raiz_atual->filho_direito, sucessor->e);
        }
    }

    return raiz_atual;
}

void remover(ArvoreBinaria * arvore, Elemento e)
{
    if(arvore == NULL || arvore->raiz == NULL){
        return;
    }

    arvore->raiz = remover_no(arvore->raiz, e);
}
