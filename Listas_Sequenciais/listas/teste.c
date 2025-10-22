//Arquvio que testa as implementações ja vistas, para compilar é necessário compilar este arquivo junto com o arquivo de implementacao das funções
//Ex: quero compilar teste.c que esta usando lista_sequencial_ordenada.c
//gcc teste.c lista_sequencial_ordenada.c -o teste
#include <stdio.h> //Importe padrão

//Interfaces a serem utilizadas

//#include "lista_sequencial.h"
//#include "lista_sequencial_dinamica.h"
#include "lista_sequencial_ordenada.h"

//Função Principal
int main(){

	//Variável inicializada - provavelmente elemento que queremos achar/encontrar
	int x;

	//Cria a lista com tamanho 10000
	ListaSequencial * lista = cria_lista(10000);

	//Usa a função imprimir para imprimir os valores
	imprime(lista);
	printf("------------------------------------------------------------------------------------\n");

	//Inserção dos elementos na lista_sequencial e lista_sequencial_ordenada, aonde é posível escolher a posição/indíce que você quer inserir o valor
	/*
	insere(lista, 3, 0);
	insere(lista, 1, 1);
	insere(lista, 5, 2);
	insere(lista, 4, 3);
	insere(lista, 2, 4);
	*/
	
	//Inserção na lista_sequencial_ordenada
	insere(lista, 3);
	insere(lista, 1);
	insere(lista, 5);
	insere(lista, 4);
	insere(lista, 2);

	//Imprimir a lista
	imprime(lista);
	//Usando a função tamanho que utiliza o atributo livre para informar o tamanho atual da lista
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	//Teste de valores a seres buscados na lista com função busca, a função vale para todas as implementações
	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));
	
	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	//Inserção de duas interfaces diferentes, sequencial: padrao x ordenada
	//insere(lista, 6, 2);
	insere(lista, 6);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	//Busca depois da inserção de um novo elemento
	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	//Função que desloca os elementos para a esquerda/apaga x valor
	remove_elemento(lista, 6);
	remove_elemento(lista, 5);
	imprime(lista);
	printf("tamanho da lista: %d\n", tamanho(lista));

	printf("------------------------------------------------------------------------------------\n");

	//Busca novamente
	x = 1;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 5;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	x = 6;
	printf("indice do elemento %d: %d\n", x, busca(lista, x));

	printf("------------------------------------------------------------------------------------\n");

	//Liberação da lista na memória
	destroi_lista(lista);
	//Retorno padrão por convenção
	return 0;
}

