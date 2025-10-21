//Biblioteca padrão + stdlib para o uso do malloc p/ alocação dinâmica
#include <stdio.h>
#include <stdlib.h>

//Inclui nosso arquivo.h, o uso de aspas é para ele procurar no diretório onde esse arquivo.c se encontra antes do local que fica os .h padrão
#include "lista_sequencial_ordenada.h"

//Função para criação da lista, recebe com parâmetro a capacida maxima da lista
ListaSequencial * cria_lista(int capacidade){

	//Aloca um espaco do tamanho da lista, provavelemtne uns 12 bytes
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	//Aloca dinamicamente o vetor de Elementos com malloc, agora o tamanho = capacidade, nao precisamos mais de sentinela para a busca
	lista->a = (Elemento *) malloc (capacidade * sizeof(Elemento));
	//capacidade da lista = capacidade fornecida pelo usuário
	lista->capacidade = capacidade;
	//Lista->livre = 0 (primeira posicao a ser inserida)
	lista->livre = 0;

	//retorna o ponteiro para a lista
	return lista;
}

//Liberação da lista da memória, recebe o endereço(ponteiro) para a lista
void destroi_lista(ListaSequencial * lista){

	//Acessamos o vetor alocado dinamicamente pela lista e liberamos
	free(lista->a);
	//Liberamos a struct Lista
	free(lista);
}

//Tamanho = livre
int tamanho(ListaSequencial * lista){

	return lista->livre;
}

//Imprime a lista de 0 -> ultimo elemento ocupado(livre-1). Custo sempre O(n)
void imprime(ListaSequencial * lista){

	//Declara o contador
	int i;

	//Mensagem que indica a lista
	printf("Lista:");

	//laço que vai de  até  livre-1(ultima posicao preenchida)
	for(i = 0; i < lista->livre; i++){
		//Imprimir os valores do tipo inteiros, numa eventual mudança de tipo de Elemento, necessitamos mudar isso aqui
		printf(" %d", lista->a[i]);
	}

	//Pular linha
	printf("\n");
}

//Agora temos a busca binária, basicamente, como os elementos estao ordenados do menor para o maior, podemos acessar o meio da lista e ver para onde podemos deslocar
//Se e < meio da lista = procuramos na esquerda. Do contrário (e>meio da lista), nos deslocamos para a direita ainda acessando o meio
//Resumindo, dividimos a lista em 2 para achar o nosso elemento, custo O(log n)
//A função recebe como parâmetro o ponteiro para a lista e o Elemento e que eu quero encontrar
int busca(ListaSequencial * lista, Elemento e){

	// busca binária! ;)

	//Iniciamos do 1ª indice
	int ini = 0;
	//ultimo elemento = livre - 1
	int fim = lista->livre - 1;
	//Declaramos a variavel meio
	int meio;

	//Laço controlado = enquanto ainda estamos dentro da lista
	while(ini <= fim){

		//meio = inicio da lista + final dela(ex: 0 = 10)/2 = 5
		meio = (ini + fim) / 2;

		//Se o nosso elemento for igual ao valor que está no meio da lista, achamos o nosso valor, esse seria o melhor caso, ele esta bem no meio da lista original
		if(e == lista->a[meio] ) return meio;
		//Caso nao for, o nosso elemento é menor que esse meio? se sim, final da lista = meio - 1, ja que o nosso elemento nao esta no meio, agora temos ini -> meio-1(fim)
		//Basicamente dividimos em um problema menor
		if(e < lista->a[meio]) fim = meio - 1;
		//Caso nao for menor, o nosso elemento certamento é maior, ou seja, o nosso elemento esta a direita do meio, inicio da lista começa em meio + 1, ja que meio nao é o nosso valor
		if(e > lista->a[meio]) ini = meio + 1; //meio + 1 -> fim, a ordenacao da lista nos permite encontrar muito mais rapido um valor
	}
		
	//caso nao acharmos o valor, retorne -1
	return -1;
}

//Agora nao informamos mais aonde queremos inserir o elemento e, a propria funcao vai encaixar o elemento e
Boolean insere(ListaSequencial * lista, Elemento e){

	//Declara o contador
	int i;

	//Verifica se a posicao livre ainda é menor que a capacidade maxima da lista
	if(lista->livre < lista->capacidade) {

		//laço que vai da posicao vazia(livre) ate aonde um elemento a seja maior que o nosso elemento e e que a posicao seja maior que a primeira(0)
		for(i = lista->livre; i > 0 && lista->a[i - 1] > e ; i--){

			//Ainda deslocamos os nossos elementos a direita
			lista->a[i] = lista->a[i - 1];
		}

		//O valor presente na posicao i-1 se refere a um elemento menor que e, logo i é a posicao que e deve assumir
		lista->a[i] = e;
		//Incrementa a lista = aumenta o tamanho da mesma
		lista->livre++;

		//Se tudo deu certo, retornar TRUE
		return TRUE;
	}

	//Caso não tenha mais espaço na lista, retorne falso
	return FALSE;
}

//A diferença principal é no custo
Boolean remove_elemento(ListaSequencial * lista, Elemento e){

	//Contador declarado
	int i;
	//Usando busca binária para encontra o elemento e
	int indice = busca(lista, e);

	//Verifica se foi encontrado o elemento
	if(indice >= 0) {

		//Decrementa a lista
		lista->livre--;

		//Laço de posicao que eu quero remover ate o penultimo elemento atual(livre --)
		for(i = indice; i < lista->livre; i++){

			//desloca os elementos para a esquerda
			lista->a[i] = lista->a[i + 1];
		}

		//Retornar TRUE se der tudo certo
		return TRUE;
	}

	//Caso o valor e nao exista dentro da lista, retornar FALSE
	return FALSE;
}

