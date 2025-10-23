//Bibliotecas a serem utilizadas
#include <stdio.h>
#include <stdlib.h>

//Arquivo de Interface presente no mesmo diretório onde este arquivo se encontra, por isso o uso de ""
#include "lista_ligada.h"

//Função de Criação da Lista, nao recebemos parametro porque nao temos um tamanho maximo
ListaLigada * cria_lista(){

	//Aloco a struct Lista Ligada com Malloc
	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	//Faça o atributo elemento receber NULL ja que nao temos nenhum nó (nossa strcut que guarda o valor e o endereco p/ o proximo elemento) criado.
	lista->primeiro = NULL;
	
	//Retorna o ponteiro para a lista
	return lista;
}

//Liberação dos NOS que fazem parte da Lista Ligada, excluimos do primeiro para o ultimo
void destroi_lista(ListaLigada * lista){

	//Declaramos uma variavel P do tipo NO que guarda o ponteiro para o primeiro Elemento
	No * p = lista->primeiro;
	//Declaramos um variavel tmp que armazena o elemento P atual
	No * tmp;

	//Enquanto existir um proximo elemento, ou seja, enquanto o proximo Elemento for um endereco e nao NULL
	while(p){
		
		//No tmp recebe o endereco do p atual
		tmp = p;
		//P recebe o endereco do elemento posterior
		p = p->proximo;
		//Excluimos o primeiro, depois o tmp recebe o endereco do posterior(segundo) e o P o terceito e assim vai ate P receber NULL = acabou a Lista
		free(tmp); //Libera da memoria
	}

	//Depois de liberar todos os NOS, iremos liberar a struct Lista
	free(lista);
}

//Função para contar a quantidade de Nos presentes na Lista
int tamanho(ListaLigada * lista){

	//Declaramos a variavel que sera incrementada ao decorrer do codigo para contabilizar a quantidade de NOS
	int tamanho = 0; //0 = Nenhum Elemento contado

	//Variavel do Tipo NO que armazena o ponteiro para o proximo NO, como estamos no comeco da lista, vamos pegar o primeiro elemento (endereco) presente na struct Lista
	No * p = lista->primeiro;

	//Enquanto P for diferente de NULL, ou seja, for um endereço valido
	while(p){ //Verificamos se tem um endereco aqui
		
		tamanho++; //Se sim, vai entrar no loop e contabilizar +1 no tamanho
		p = p->proximo; //Guardamos o proximo No a ser verificado
	}

	//Depois de contar ate chegar NULL, vamos retornar o tamanho da Lista
	return tamanho;
}

//Imprimir todos os valores da Lista, Todos os NOs
void imprime(ListaLigada * lista){

	//Variavel do tipo No que armazena o endereco dos NOS
	No * p;

	printf("Lista:");

	//Laço de repetiçao controlado, começa do primeiro elemento da lista indicado pelo ponteiro primeiro dentro da lista
	//Tem como condicional enquanto o endereco for valido, ou seja p
	//O proximo valor a ser acrescentado/incrementado é p = endereço do proximo elemento indicado como proximo dentro da struct NO
	for(p = lista->primeiro; p; p = p->proximo){
		//Imprimir o valor presente no NO
		printf(" %d", p->valor);
	}

	printf("\n");
}

//se estivermos trabalhando com uma lista liigada ordenada
#ifdef LISTA_ORDENADA
//Recebe como parametro o ponteiro para a lista e o Elemento que queremos encontrar
int busca(ListaLigada * lista, Elemento e){

	//Declaramos uma variavel contador do tipo int
	int i = 0;
	//Inicializamos uma variavel do tipo NO que guarda o ponteiro para o proximo elemento
	No * p = lista->primeiro;

	//Enquanto p for um endereco valido e o valor presente naquele endereco for menor que e
	while(p && p->valor < e){

		//Guarda o proximo Endereco de Memoria
		p = p->proximo;
		//Incrementa o contador
		i++;
	}
	//Se p for um endereco valido entramos em um condicional: Caso não fosse (caso NULL): retornar -1
	//Se o valor presente naquele endereço for igual ao elemento e que eu quero encontrar, retorne o indice do mesmo, caso não, retorne -1
	return p ? (p->valor == e ? i : -1) : -1;
}
#else //Caso nao estejamos trabalhando c/ uma lista ordenada (crescente ou decrescente)
int busca(ListaLigada * lista, Elemento e){

	//Contador
	int i = 0;
	//Endereço do proximo elemento
	No * p = lista->primeiro;

	//Enquanto p for um endereco valido e o valor presente no elemento e for diferente de e, no pior caso (o elemento nao esta na lista), o fato do ultimo elemento
	//apontar para NULL (nenhum endereco), faz com que o loop termine
	while(p && p->valor != e){
		//Guarda o proximo elemento
		p = p->proximo;
		//incrementa o contador
		i++;
	}

	//Caso p for um endereco valido, encontramos nosso elemento e na lista, retornar o indice do mesmo
	//Caso o while tenha percorrido a lista inteira e não tenha achado o elemento e, p = NULL, logo, endereco invalido, retornar -1
	return p ? i : -1;
}
#endif
//Inserção em uma lista ordenada (respeitando a ordem crescente ou decrescente)
#ifdef LISTA_ORDENADA
//Recebemos nosso elemento e junto do ponteiro da lista
Boolean insere(ListaLigada * lista, Elemento e){

	//Armazena o elemento atual
	No * p;
	//Elemento anterior
	No * anterior;
	//Aloca um NO para o elemento e
	No * novo = (No *) malloc(sizeof(No));

	//Valor daquele NO é o nosso elemento e
	novo->valor = e;

	//Nao temos nenhum anterior atualmente 
	anterior = NULL;
	//Começamos do primeiro elemento da lista
	p = lista->primeiro;

	while(p){ //Enquanto p for um endereço valido

		//Se o nosso elemento for menor que o valor do Elemento e, pare
		if(e < p->valor) break;
 			
		//Anterior guarda o elemento p atual
		anterior = p;
		//Enquanto nosso p gaurda agora o proximo ponteiro
		p = p->proximo;
	}
	
	//Ao termino do while, seja forcado por encontrar um local para o elemento ou por p se tornar invalido
	novo->proximo = p; //Nosso novo vai apontar para o ultimo ponteiro p, seja ele um endereco real ou NULL (inserção no fim da lista)
		
	if(anterior) anterior->proximo = novo; //Se anterior for um endereco valido, não NULL, o No anterior ira apontar para o meu novo No
	else lista->primeiro = novo; //Se nao (insercao no começo da lista), muda o ponteiro da strcut Lista para apontar para o meu novo No

	return TRUE; //Caso de tudo certo, retorne true
}
#else //Se nao estivermos usando uma lista ordenada, ou seja, tanto faz a ordem, adiciono 'onde eu quiser', por isso a adição do parametro indice
Boolean insere(ListaLigada * lista, Elemento e, int indice){

	//Variaveis do tipo inteiro que provavelmente contabilizam o indice atual e o seu antecessor
	int i, antecessor;

	//No que armazena o No atual
	No * p;
	//ALocamos um novo NO para o nosso Elemento e
	No * novo = (No *) malloc(sizeof(No));

	//atributo valor do meu novo No recebe o valor do Elemento e
	novo->valor = e;
	
	//Se indice for valido, ou seja, for de indice 0(primeiro) ate aonde o ultimo elemento esta(nao podemos colocar depois, nao faz sentido)
	if(indice >= 0 && indice <= tamanho(lista)){

		//Caso a inserção ocorra no começo da lista
		if(indice == 0){

			//O novo NO aponta para o antigo primeiro elemento, ou seja, ele assume sua função, entao recebe o atributo primeiro da lista (endereco do primeiro elemento) no
			//atributo proximo
			novo->proximo = lista->primeiro;
			//Enquanto isso a lista agora tem como primeiro elemento o novo NO
			lista->primeiro = novo;
		}
		else { //Caso a inserção não ocorra no primeiro Elemento

			//Inicializa o contador como 0
			i = 0;
			//Antecessor = posicao que eu quero inseir - 1
			antecessor = indice - 1;
			//ponteiro/elemento atual aponta/começa do primeiro elemento da lista
			p = lista->primeiro; 

			//enquanto i que começa do for menor que o meu indice/posiçao onde eu quero inserir o elemetno e, incremente i e passe para o proximo NO
			while(i < antecessor){

				//Incrementando a cada execução
				i++;
				//No atual recebe o endereço para o proximo No
				p = p->proximo;
			}
		
			//Como sempre recebemos o proximo elemento no laço while, quando der falso, ja sabemos que o indice que a posicao onde queremos inserir esta presente no NO p
			novo->proximo = p->proximo; //Meu novo No recebe o endereco para o proximo do antigo elemento que ocupava esta posicao 
			p->proximo = novo; //Meu novo No esta sendo chamado/apontado pelo atributo proximo, ou seja, so estamos colocando ele na frente ou atras do antigo NO
		}

		//Se a inserção funcionar, retorna true
		return TRUE;
	}

	//No caso de indice inválido, retornar FALSE
	return FALSE;
}
#endif ///FIM do condicional


//Função para remover/liberar elemento, informamos o Elemento e que queremos remover na lista
Boolean remove_elemento(ListaLigada * lista, Elemento e){

	//Variaveis que armazenam o indicde anterior e atual
	int i, antecessor;
	//Encontramos a posicao se onde encontra o Elemennto que queremos remover
	int indice = busca(lista, e);
	//Ponteiro que armazena o No atual
	No * p;
	//Variavel que armazena o endereco que sera armazenado
	No * tmp;

	//Verifica se o Elemento foi encontrado dentro do Array
	if(indice >= 0) {

		//Aqui temos 2 casos: Se a remocao ocorre no inicio da lista (primeiro elemento) ou depois dele
		//Caso for no comeco, tem que mudar o ponteiro da estrutura lista, caso nao, precisa fazer outro role
		if(indice == 0){

			//Variavel que vai ser liberada = primeiro NO (endereco presente na struct Lista)
			tmp = lista->primeiro;
			//Pegamos o proximo elemento (2º) e passamos seu endereço para o ponteiro da lista struct = novo primeiro elemento
			lista->primeiro = tmp->proximo;
			//Liberamos o antigo primeiro elemento
			free(tmp);
		}
		else{ //Caso a remoção for depois, precisamos lidar com o No anterior e posterior

			//Começamos o indice como 0
			i = 0;
			//Antecessor = indice - 1
			antecessor = indice - 1;
			//Elemento atual = primeiro elemento da nossa lista
			p = lista->primeiro;

			//Enquanto i < antecessor
			while(i < antecessor){

				//Incremenata o contador
				i++;
				//Proximo elemento
				p = p->proximo;
			} //Executa ate chegar na posicao anterior a anterior
			
			//Como sempre fazemos a verificacao para o proximo, vamos estar no antecessor
			//p(antecessor)->proximo(o nosso elemento e) - o que eu quero remover
			tmp = p->proximo; //Variavel temporaria recebe o elemento que queremos remover
			//p = antecessor do que eu vou remover
			//proximo = o que eu vou remover
			//Logo, eu preciso apontar para o proximo do que eu quero remover, logo
			//p->proximo->proximo
			//Antecessor recebe sucessor, pegavamos o que tinha no meio e jogamos fora
			p->proximo = p->proximo->proximo;
			//Liberamos o elemento que queriamos depois de consertar o No
			free(tmp);
		}

		//Retornar true em caso de remoção bem sucedida		
		return TRUE;
	}

	//Caso Elemento e nao exista na lista, retorne falso
	return FALSE;
}
