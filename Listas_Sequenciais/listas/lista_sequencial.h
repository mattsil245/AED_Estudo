#define FALSE 0 //False
#define TRUE 1 //True
#define TAMANHO_MAXIMO 100000 //Tamanho maximo da minha lista

//Declara um apelido para variaveis do tipo inteiro
typedef int Boolean; //Logica 0 e 1
typedef int Elemento; //Tipo do array

//Estrutura da Lista Sequencial
typedef struct {

	//Elemento - tipo de dado(int) a[] -> vetor [TAMANHO_MAXIMO] = valor maximo
	Elemento a[TAMANHO_MAXIMO];
	//ultima posicao ocupada ou a proxima depois da ultima
	int livre;

} ListaSequencial; //Desse jeito fica mais facil para declarar (apelido)

//Metodos/Funcoees a serem implementadas em outro arquvio, parecido com a ideia de classe abstrata do POO
ListaSequencial * cria_lista(); //Cria lista com malloc
void destroi_lista(ListaSequencial * lista); //Liberar com free
int tamanho(ListaSequencial * lista); //livre = tamanho
void imprime(ListaSequencial * lista); //for com printf
int busca(ListaSequencial * lista, Elemento e); //for com if
Boolean insere(ListaSequencial * lista, Elemento e, int indice); //Insercao com sucesso = 1. do contrario = 0
Boolean remove_elemento(ListaSequencial * lista, Elemento e); //Remocao com sucesso = 1, do contrário = 0

