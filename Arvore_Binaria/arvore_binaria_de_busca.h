#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#define T 1
#define F 0

typedef int Boolean;
typedef int Elemento;

typedef struct _no_{
    Elemento e;
    struct _no_ * filho_esquerdo;
    struct _no_ * filho_direito;
} No;

typedef struct{
    No * raiz;
} ArvoreBinaria;

ArvoreBinaria * criar_arvore();
//No * criar_no(Elemento e);
//No *inserir_no(No * raiz_atual, Elemento e);
Boolean inserir(ArvoreBinaria * arvore, Elemento e);
//void imprimir_em_ordem_aux(No * no_atual);
void imprimir_arvore(ArvoreBinaria * arvore);
//No * buscar_no(No * raiz_atual, Elemento e);
No * buscar(ArvoreBinaria * arvore, Elemento e);
//int contar_nos_aux(No * no_atual);
//int altura_aux(No * no_atual);
int altura_arvore(ArvoreBinaria * arvore);
int tamanho_arvore(ArvoreBinaria * arvore);
//void liberar_nos_aux(No * no_atual);
void liberar_arvore(ArvoreBinaria * arvore);
//No * encontrar_menor(No * no_atual);
//No * remover_no(No * raiz_atual, Elemento e);
void remover(ArvoreBinaria * arvore, Elemento e);

#endif