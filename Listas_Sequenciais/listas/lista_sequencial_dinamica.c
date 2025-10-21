//Mesma coisa de sempre
#include <stdio.h>
#include <stdlib.h>

#include "lista_sequencial_dinamica.h"

//Atenção, funçao mudou, agora recebe uma capacidade = tamanho = n
ListaSequencial * cria_lista(int capacidade){

	//Ponteiro p/lista no caso a strcut, estou reservando um espaco na memorial para ela
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	//vetor a = vetor de elementos(int*) Malloc(tamanho + 1?) * tamanho de um elemento(int) 
	lista->a = (Elemento *) malloc ((capacidade + 1) * sizeof(Elemento));
	lista->capacidade = capacidade; //tamanho = capacidade = n
	lista->livre = 0; //Inicializa com 0 a primeira posicao a ser ocupada

	//retorna o ponteiro para a lista
	return lista;
}

//Mudancas, primeiro destruo o vetor da lista, depois a lista, destruir = liberar da memoria
void destroi_lista(ListaSequencial * lista){

	free(lista->a);
	free(lista);
}

//Mesma coisa
int tamanho(ListaSequencial * lista){

	return lista->livre;
}

//Mesma coisa
void imprime(ListaSequencial * lista){

	int i;

	printf("Lista:");

	for(i = 0; i < lista->livre; i++){

		printf(" %d", lista->a[i]);
	}

	printf("\n");
}

//Uso da sentinela - por isso capacidade + 1
int busca(ListaSequencial * lista, Elemento e){

	//incializa o contador
	int i;

	//sempre vai ter um espaco livre ja que capacidade = capacidade mas tamanho da lista = capacidade +1
	lista->a[lista->livre] = e; //a posicao vaga depois do ultimo valor a ser inserido recebe o valor que eu quero achar

	//nao precisamos mais do if, logo, menos iterações = menor custo
	for(i = 0; lista->a[i] != e; i++); //vai rodando ate nao der mais, pior caso = final da lista/livre + 1 (onde esta a sentinela)

	//caso o indice seja menor que livre = achamos, caso não, ele esta em livre - 1, onde colocamos a sentinela, logo, o elemento não existe na lista
	return (i < lista->livre) ? i : -1;
}

//Mudancas referentes a substituicao da constante no condicional por um atributo da lista que guarda o tamanho maximo da mesma
Boolean insere(ListaSequencial * lista, Elemento e, int indice){

	int i;

	if(lista->livre < lista->capacidade && indice >= 0 && indice <= lista->livre){

		for(i = lista->livre; i > indice; i--){

			lista->a[i] = lista->a[i - 1];
		}

		lista->a[indice] = e;
		lista->livre++;

		return TRUE;
	}

	return FALSE;
}

//Mesma coisa
Boolean remove_elemento(ListaSequencial * lista, Elemento e){

	int i;
	int indice = busca(lista, e);

	if(indice >= 0) {

		lista->livre--;

		for(i = indice; i < lista->livre; i++){

			lista->a[i] = lista->a[i + 1];
		}

		return TRUE;
	}

	return FALSE;
}

