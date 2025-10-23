//Constantes para representam TRUE e FALSE
#define FALSE 0
#define TRUE 1

//Alguma constante para ser utilizada a Lista Ordenada
//#define LISTA_ORDENADA

//Apelidos para variaveis do tipo inteiro
typedef int Boolean; //Valores
typedef int Elemento; //Estado

//Estrutura que guarda os elementos e seus sucessores
typedef struct _no_ { //Precisamos fornecer um nome temporário para ele ser chamado dentro da struct

	Elemento valor; //Armazena um Elemento
	struct _no_ * proximo; //Chama um ponteiro para a essa estrutura

} No; //Definimos o apelido da estrutura, agora sim podemos nos refeiir a ela como No ao inves de struct _no_

//Estrutura que armazena nossa lista, uma lista é um conjunto de Nos
typedef struct {
	
	No * primeiro; //Guarda a informação de quem é o primeiro Elemento

} ListaLigada; //Define um apelido para a lista

//Desse jeito percebemos que ao inves de uma struct que armazena um array de Elementos dentro dela, agora temos uma lista onde cada no é independente
//e precisa ser criado/alocado para inserir um novo valor e liberado da memoria para remocao, muitas regras/cuidados a serem tomados;

//Declaração das funções a serem implementadas
ListaLigada * cria_lista(); //Parece que não recebemos um valor maximo, faz sentido, não tem o que alocar, so vamos adicionando
void destroi_lista(ListaLigada * lista); //liberar memoria
//As outras implementações são dificeis de imaginar
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);

//Se a constante lista ordenada estiver ativa, vamos ordenar os elementos
#ifdef LISTA_ORDENADA
Boolean insere(ListaLigada * lista, Elemento e);
#else //Se não, mesma coisa na sequencial, escolhemos a posicao que eu quero colocar o meu Elemento e
Boolean insere(ListaLigada * lista, Elemento e, int indice);
#endif

//Remover deve ser uma liberação com alguns detalhes no nó e com regras para as extremidades
Boolean remove_elemento(ListaLigada * lista, Elemento e);
