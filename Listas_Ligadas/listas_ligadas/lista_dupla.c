//Importe
#include <stdio.h>
#include <stdlib.h>

//Interface
#include "lista_dupla.h"

//Implementacao das funções
ListaLigada * cria_lista(){ //Função que aloca a lista

	//Alocamos um NO
	No * cabeca =  (No *) malloc (sizeof(No));
	//O proximo e o anterior aponta para si mesmo
	cabeca->proximo = cabeca;
	cabeca->anterior = cabeca;

	//Criamos a nossa lista
	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->cabeca = cabeca; //Cabeca = No criado
	lista->tamanho = 0; //Lista vazia
	
	return lista; //Retorno de endereço
}

//Mesma coisa da circular
void destroi_lista(ListaLigada * lista){

	//Primeiro = proximo depois do cabeça
	No * p = lista->cabeca->proximo;
	//No temporario que armazena os elementos que iremos excluir
	No * tmp;

	//Enquanto p for diferente de cabeca = nao chegou no fim
	while(p != lista->cabeca){
		
		//Temporario = meu p atual
		tmp = p;
		//P agora guarda o proximo
		p = p->proximo;
		//Libera o antigo p
		free(tmp);
	}

	//SO sobra cabeca(fim da lista e ao mesmo tempo comeco) e lista
	free(lista->cabeca); //Liberar No
	free(lista); //Liberar Lista
}

//Mesma coisa, cada inserção ja contabiliza, so precisamos retornar esse valor
int tamanho(ListaLigada * lista){

	return lista->tamanho;
}

//Imprime do comeco -> fim e do fim -> comeco
void imprime(ListaLigada * lista){

	//Variavel que armazena o NO atual
	No * p;

	printf("Lista:");

	//Vai de p = proximo depois do cabeça (primeiro elemento) ate cabeca = fim da lista, incrementa passando o ponteiro para o proximo NO
	for(p = lista->cabeca->proximo; p != lista->cabeca; p = p->proximo){

		printf(" %d", p->valor); //Imprime
	}

	printf(" [ ");

	//Vai de cabeca->anterior(ultimo elemento antes de cabeca) ate o primerio que vem depois de cabeca, incrementa com o anterior
	for(p = lista->cabeca->anterior; p != lista->cabeca; p = p->anterior){

		printf("%d ", p->valor); //Imprime
	}

	printf("]\n");
}

//Função desconhecida que tem como parametro nosso Elemento e e o indice da lista, mas no caso é o ponteiro para ele
No * busca_no(ListaLigada * lista, Elemento e, int * indice){

	//Criamos um ponteiro que armazena o primeiro elemento da lista
	No * p = lista->cabeca->proximo;
	//Inicializamos com 0
	*indice = 0;

	//Enquanto p nao for o final da lista (cabeça) e o valor for menor do que eu quero remover
	while(p != lista->cabeca && p->valor < e){

		//parti para o proximo elemento
		p = p->proximo;
		//incrementa
		(*indice)++;
	}

	//verifica se p nao é no cabeça, ou seja, se o elemento realmente foi encontrado, se sim, verifica se o valor que era maior ou igual é o meu elemento e, se sim, devolve
	///o endereço dele
	return p != lista->cabeca ? (p->valor == e ? p : NULL) : NULL;
}

//retorna o indice
int busca(ListaLigada * lista, Elemento e){

	//Inicaliza o indice
	int indice;
	//Passa o endereco do mesmo para a funcao que ira retornar o endereco
	No * no = busca_no(lista, e, &indice);

	//verifica se foi encontrado o valor, se sim, retorna o indice
	return no ? indice : -1;
}

//Inserção de um novo elemento, passa o endereço da lista e o Elemento que queremos inserir
Boolean insere(ListaLigada * lista, Elemento e){

	//Armazena NO atual
	No * p;
	//Aloca um novo NO
	No * novo = (No *) malloc(sizeof(No));

	//Guarda o valor 
	novo->valor = e;
	//Proximo e anterior = NULL (não sabemos ainda)
	novo->proximo = novo->anterior = NULL;

	//Primeiro elemento vem depois do cabeça (cabeca->proximo)
	p = lista->cabeca->proximo;

	//Enquanto nao voltarmos para o cabeca, ou seja, o final da lista
	while(p != lista->cabeca){

		//Se e for menor que o valor atual, pare
		if(e < p->valor) break;
 			
		//Proximo elemento/No
		p = p->proximo;
	}
	
	//Ate chegar em uma posicao menor ou a lista acabar
	//Caso for no final = proximo = cabeca, caso nao, proximo = valor maior que e
	novo->proximo = p;
	//Anterior = anterior de p, podendo ser cabeca na primeira posicao ou o No anterior
	novo->anterior = p->anterior;
	//Anterior agora aponta para o nosso No atual
	p->anterior->proximo = novo;
	//Nosso no Novo é o elemento anterior do posterior
	p->anterior = novo;

	//Incrementa a lista
	lista->tamanho++;
	return TRUE;
}

//Muito foda, com as funcoes acima fica mais facil de remover
Boolean remove_elemento(ListaLigada * lista, Elemento e){

	//Inicializa variavel indice por causa da funcao abaixo
	int indice;
	//Busca o no que iremos remover
	No * a_remover = busca_no(lista, e, &indice);

	//verifica se o endereco é valido, ou seja, nao nulo
	if(a_remover) {

		//resumidamente, o elemento anterior tem um atributo proximo, ele recebe o proximo do meu elemento que vou remover
		a_remover->anterior->proximo = a_remover->proximo;
		//Ja o proximo elemento depois do que eu vou remover, tem um anterior, esse anterior é o No que eu vou remover, agora esse anterior aponta para o anterior do qual eu
		//vou remover, basicamente corto o que tava no meio,mas antes disso custuro as ligações
		a_remover->proximo->anterior = a_remover->anterior;

		//Depois de arrumar os atributos, libero o elemento da memoria
		free(a_remover);

		//Decremento o tamanho da lista
		lista->tamanho--;
		return TRUE; //Retorno TRUE
	}

	//Caso o elemento e nao exista na lista, retorno FALSE
	return FALSE;
}
