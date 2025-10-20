//importar as bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>

//incluir a 'classe abstrata'
#include "lista_sequencial.h"

//Funções a serem implementadas

//criar lista com malloc, atualmente valor fixo definido dentro da struct
ListaSequencial * cria_lista(){
	
	//Instanciar a lista do tipo Lista Sequencial
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->livre = 0; //Instanciar o atributo livre que controla aonde vai ser inserido um novo elemento

	return lista; //retorna a lista criada, no caso o ponteiro
}

//Destruiar a lista com free = liberar da memória a lista
void destroi_lista(ListaSequencial * lista){

	free(lista);
}

//Retorna o tamanho da lista com o auxilio do atributo livre, tmamanho = ate onde a lista vai = indice vai ate a ultima posicao ocupada ou livre?
int tamanho(ListaSequencial * lista){
	//retorna o valor atraves do atributo
	return lista->livre;
}

//printf simples que imprime os valores da lista do primeiro elemento ate ate o livre-1, logo, descobrimos que livre = posicao vazia
void imprime(ListaSequencial * lista){

	int i;

	printf("Lista:");

	//laço que percorre a lista(vetor) do indice 0(1° posição) até posição vazia(livre)-1 = posicao com o ultimo valor inserido
	for(i = 0; i < lista->livre; i++){
		//imprime os valores sendo 'a' o nome do vetor
		printf(" %d", lista->a[i]);
	}

	printf("\n");
}

//Busca um valor x na lista, do tipo Elemento(int disfarçado)
int busca(ListaSequencial * lista, Elemento e){

	int i;

	//mesmo array da funcao imprimir
	for(i = 0; i < lista->livre; i++){
		//compara valor atual com valor que queremos, se achar retornar o indice que ele ocupa
		if(lista->a[i] == e) return i;
	}

	//se rodar o array todo e nao achar, retorne -1
	return -1;
}

//Funçao para adicionar valores, complicada
//recebe o ponteiro da minha lista, o valor que eu quero inserir, e o indice aonde eu quero encaixar
Boolean insere(ListaSequencial * lista, Elemento e, int indice){

	int i;

	//condicional para adicionar algum valor
	//blz, vamos distrinchar
	//lista->livre < n(constante) = posicao vazia é menor que o tamanho maximo = ainda cabe mais
	//indice>=0 = e indice<=lista->livre - esta dentro da posicao que podemos inserir, ou seja, esta dentro de 0 ate posicao livre
	//nao podemos deixar espaco vazio, ou seja, preciamso preencher onde esta livre

	if(lista->livre < TAMANHO_MAXIMO && indice >= 0 && indice <= lista->livre){

		//loop para deslocar os elementos da direita da onde queremos inserir+1 para uma casa a frente
		
		for(i = lista->livre; i > indice; i--){
			//elemento atual pega o anterior, elementos estao sendo deslocados para a direita
			lista->a[i] = lista->a[i - 1];
		}

		//como o laço acima vai ate indice + 1, o indice atual é a posição que queremos inserir
		lista->a[indice] = e; //recebe o valor que queremos inserir
		lista->livre++; //'aumenta' o tamanho da lista, posicao livre aumenta

		//caso der tudo certo = return TRUE
		return TRUE;
	}

	//caso o condicional falhe por falta de espaço ou indice invalido, retornar FALSE
	return FALSE;
}

//função para remover elemento, recebe o ponteiro da lista e o elemento que queremos remover
Boolean remove_elemento(ListaSequencial * lista, Elemento e){

	int i;
	//agora fica mais facil pois usamos funcao busca para achar o elemento e retornar seu indice
	int indice = busca(lista, e);

	//condicional porque ele retorna -1 se nao achar/tiver o elemento
	if(indice >= 0) {

		//decrementa o tamanho da lista
		lista->livre--;

		//loop que começa de posicao que eu quero inserir ate a posicao livre - 1;
		for(i = indice; i < lista->livre; i++){

			//desloca os elementos da direita para esquerda, pega o elemento que esta em indice + 1;
			lista->a[i] = lista->a[i + 1];
		}

		//Caso de tudo certo, retorna true
		return TRUE;
	}

	//caso nao passe no condicional, ou seja, o elemento nao existe dentro da lista, retorne false
	return FALSE;
}

