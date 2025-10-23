//Continuamos a declarar as constantes de valores Booleanos
#define FALSE 0
#define TRUE 1

//Podemos utilizar a ordenação de elementos na lista ligada circular também
//#define LISTA_ORDENADA

//Nossos apelidos para diferentes variaveis do tipo int que tem funções diferentes
typedef int Boolean; //Retorno Booleano (TRUE ou FALSE)
typedef int Elemento; //Valor dos Elementos de cada NO

//Struct No intocada
typedef struct _no_ { //Definimos um nome tempoparaio para poder apontar pra ela dentro dela

	//Valor presente naquele NO
	Elemento valor;
	//Ponteiro para o proximo NO
	struct _no_ * proximo;

} No; //Apelidamos a nossa Struct

//Mudanças:
//Ao inves de apontarmos para NULL (lista vazia) ou para o primeiro elemento em caso de lista c/ Nos
//Temos um No cabeca que provavelmente serve como auxiliar/sentinela
//Alem disso, finalmente temos uma variavel que conta a quantidade de Nos presentes na Lista
typedef struct {

	//Quantidade de Nos
	int tamanho;	
	//Auxiliar em alguma coisa
	No * cabeca;

} ListaLigada; //Declaração da Lista Ligada

//Mesma coisa de sempre
ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e); //Caso especial?

//Busca aqui é da mesma maneira sendo ordenada ou não, o unico especial é a inserção
#ifdef LISTA_ORDENADA
Boolean insere(ListaLigada * lista, Elemento e);
#else
Boolean insere(ListaLigada * lista, Elemento e, int indice);
#endif

Boolean remove_elemento(ListaLigada * lista, Elemento e);
