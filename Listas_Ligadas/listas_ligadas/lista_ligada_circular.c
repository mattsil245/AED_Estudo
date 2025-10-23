//Importação padrão
#include <stdio.h>
#include <stdlib.h>

//Incluir a Interface (Classe Abstrata)
#include "lista_ligada_circular.h"

//Função para criação da lista + NO cabeca com Alocação dinâmica
ListaLigada * cria_lista(){

	//Aloca primeiramente o No cabeca com malloc
	No * cabeca =  (No *) malloc (sizeof(No));
	//Aponta para si mesmo (Estado Inicial provavelmente)
	cabeca->proximo = cabeca;

	//Aloca a estrutura Lista
	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->cabeca = cabeca; //Armazena o endereço do NO cabeca na variavel responsavel dentro da struct
	lista->tamanho = 0; //tamanho inicial = vazio = 0
	
	/*Retorna o ponteiro para a Lista*/
	return lista;
}

//Destruição da Lista - liberação da mesma
void destroi_lista(ListaLigada * lista){

	//Primeiro elemento esta armazenado no atributo proximo do No cabeça, agora temos uma ponte entre lista e Nos
	No * p = lista->cabeca->proximo;
	//No temporario que guarda os Nos que queremos remover, no caso todos
	No * tmp;

	//Enquanto o endereco nao for o do NO cabeca
	//Ok, agora entendi o circular, o comeco esta no proximo do No cabeca, e o ultimo aponta para ele novamente, e como sabemos que chegamos nele?
	//Simples, verificamos se o endereco atual  == endereco do no cabeca que esta dentro da struct Lista, ou sjea, Nao temos mais NULL para apontar o final da Lista
	//Todo mundo aponta para alguém
	while(p != lista->cabeca){
		
		//Temporario é o meu primeiro elemento e assim vai ate chegar no no cabeca, que é removido fora desse loop
		tmp = p;
		//O proximo elemento esta dentro do atributo proximo do NO p atual
		p = p->proximo; 
		//Liberamos o anterior depois de pegarmos o atual/posterior
		free(tmp);
	}

	//Como loop vai ate achar No cabeça, precisamos liberá-lo
	free(lista->cabeca);
	//Libera a estrutura Lista
	free(lista);
}

//Graças ao uso do atributo tamanho presente na Lista, agora o custo é fixo O(1)
int tamanho(ListaLigada * lista){

	//SO precisamos retornar o atributo
	return lista->tamanho;
}

//Mais facil, ao inves de verificamos se p é um endereço valido = Não NULL, agora só precisamos começar do proximo depois do NO cabeca (primeiro No real da lista)
//E enquanto o endereco for diferente do CAbeca, ou seja, nao chegamos ao final/voltamos ao inicio
//Vamos 'incrementar' o NO p, ou seja, pegar o endereco do proximo e verificar o for
void imprime(ListaLigada * lista){

	No * p; //Variavel auxiliar

	printf("Lista:");

	//Começa do 1º elemento presente no proximo dentro do NO cabeca ate chegarmos no No cabeca, tudo isso verificando se o endereco de P nao é o mesmo do No cabeça
	for(p = lista->cabeca->proximo; p != lista->cabeca; p = p->proximo){

		//Imprimimos o valor do elemento daquele P
		printf(" %ld", p->valor);
	}

	printf("\n");
}

//Ok, a busca é diferente em casos ordenados ou não
#ifdef LISTA_ORDENADA
//recebemos como parametro o ponteiro para a lista e o elemento e que queremos achar (trivial!)
int busca(ListaLigada * lista, Elemento e){

	//Inicializa o contador com 0
	int i = 0;
	//Primeiro elemento = proximo depois do no cabeça
	No * p = lista->cabeca->proximo;

	//Enquanto o endereco p nao for o mesmo do No cabeça e o valor atual de P for menor do que eu quero encontrar, pressume se quando parar que o proximo seja o Nosso e
	while(p != lista->cabeca && p->valor < e){

		//Proximo = proximo depois de p atual
		p = p->proximo;
		//Incrementa
		i++;
	}

	//Verifica o endereco nao é o cabeça, se nao for, verifica se o proximo que seria é igual ao nosso elemento e, caso nao for nenhuma das condições anterior, nosso elemento nao existe
	return p != lista->cabeca ? (p->valor == e ? i : -1) : -1;
}
#else
//BUsca nao ordenada, quase a mesma coisa
int busca(ListaLigada * lista, Elemento e){

	//Contador
	int i;
	//Auxiliar
	No * p;

	//Pera ai, isso aqui é parecido com a sentinela da busca sequencial dinamica
	lista->cabeca->valor = e; //Posto o elemento que eu quero achar no final/No cabeça

	//Temos coisas diferentes aqui
	//Inicaliza o primeiro No e o contador = 0
	//o condicionl é enquanto valor for diferente de e
	//Ou seja, melhor caso: achamos nosso valor
	//Pior caso: chegamos ate o final/comeco da lista = No cabeça
	//Incrementamos o contadoe e incrementamos o proximo elemento (p->proximo (endereço para o próximo Nó))
	for(i = 0, p = lista->cabeca->proximo; p->valor != e; p = p->proximo, i++);

	//Se o endereço for diferente do No cabeça, ou seja, o elemento existe na Lista, retorne seu indíce, caso não, retorne -1
	return p != lista->cabeca ? i : -1;
}
#endif

//Inserção em Listas Ordenadas
#ifdef LISTA_ORDENADA
//Recebe como parâmetro o ponteiro para a lista e o nosso Elemento e
Boolean insere(ListaLigada * lista, Elemento e){

	//Variavel que armazena o elemento atual
	No * p;
	//Armazena o No anterior
	No * anterior;
	//Aloca dinamicamente um novo No para o Elemento e
	No * novo = (No *) malloc(sizeof(No));

	//Atribui o valor e para o novo No
	novo->valor = e;

	//Anterior do primeiro = cabeça = final da lista
	anterior = lista->cabeca; 
	//Atual = primeiro da lista, proximo do No cabeça
	p = lista->cabeca->proximo;

	//Enquanto o atual nao for o final = enquanto o p atual for difente do no cabeca que aqui representa o final da lista
	while(p != lista->cabeca){

		//Se o nosso e for menor que o p atual, pare
		if(e < p->valor) break;
 			
		//Incremento
		//O anterior é o p atual
		anterior = p;
		//p = p atual -> proximo, elemento posterior do atual
		p = p->proximo;
	}
	
	//Se acharmos o while se encerrar, seja por estarmos no final da lista ou acharmos um valor p maior que o nosso e
	novo->proximo = p;	//O proximo elemento depois do nosso é o p que é maior que o nosso ou o No cabeça
	anterior->proximo = novo; //anterior que apontava para o p agora aponta para o que esta entre eles anterior < e < p

	//Incrementa o tamanho da lista
	lista->tamanho++;
	//Caso de tudo certo, retorne true
	return TRUE;
}
#else
//Caso queiramos uma inserção nao ordenada, ou seja, insiro onde eu quiser numa posicao indice arbritária
Boolean insere(ListaLigada * lista, Elemento e, int indice){

	//Variaveis de controle
	int i, antecessor;

	//No que armazena o endereco do No atual
	No * p;
	//Alocamos um novo No que ira armazenar o valor e
	No * novo = (No *) malloc(sizeof(No));

	//Armazenamos o elemento e no Novo No
	novo->valor = e;
	
	//Verifica se o indice é valido e é menor ou igual que o tamanho da lista 
	if(indice >= 0 && indice <= tamanho(lista)){

		//Começa do -1 devido ao No cabeça, -1 = cabeça, 0 = primeiro elemento
		i = -1;
		//Antecessor = indice - 1
		antecessor = indice - 1;
		//Elemento inicial = cabeça = -1
		p = lista->cabeca;

		//Enquanto i < antecessor, ja que ele vai pegar o antecessor no while
		while(i < antecessor){

			//Incrementa o contador
			i++;
			//proximo = p->proximo (endereço para o proximo elemento)
			p = p->proximo;
		}
		
		//o proximo NO que o nosso novo No aponta é para o posterior que seria p->proximo, ja que p é o elemento antecessor, vamos encaixar nosso Novo No depois dele
		novo->proximo = p->proximo;
		//Para referenciar, agora o antecessor aponta para o novo NO
		p->proximo = novo;
		
		//Incrementa o tamanho da Lista
		lista->tamanho++;
		return TRUE; //Se tudo der certo, retorna TRUE
	}

	//Caso não, retorna FALSE
	return FALSE;
}
#endif

//Liberação/Remoção de um elemento com base no seu valor
Boolean remove_elemento(ListaLigada * lista, Elemento e){

	//Variaveis de controle
	int i, antecessor;
	//Busca o indice/posicao onde aquele elemento se encontra 
	int indice = busca(lista, e);
	//No que armazena o elemento atual
	No * p;
	//Elemento a ser retirado
	No * tmp;

	//Se busca retornar um indicd valido = o elemento faz parta da Lista
	if(indice >= 0) {

		//Começamos do No cabeça
		i = -1;
		antecessor = indice - 1;
		p = lista->cabeca;

		//Enquanto i for menor que o antecessor, fazemos isso porque estamosno while e na ultima iteracao, p = anterior
		while(i < antecessor){

			//Incrementa
			i++;
			//Armazena o proximo elemento
			p = p->proximo;
		}
		
		//p = elemento anterior ao que a gente vai remover, p->proximo = elemento que queremos remover
		tmp = p->proximo;
		//p->proximo = aponta para o elemento que queremos remover, agora ele aponta para o elemento posterior ao que a gente vai remover, cortamos basicamnete o que esta no meio
		p->proximo = tmp->proximo;
		//Libera o NO
		free(tmp);

		//Decrementa o tamanho da lista
		lista->tamanho--;
		return TRUE; //Retorna true em caso de sucesso
	}

	return FALSE; //False no caso do elemento nao existir na lista
}
