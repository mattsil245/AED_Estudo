#define FALSE 0
#define TRUE 1

//Talvez possamos implementar futuramente a ordenação dos elementos na lista duplamente ligada
#define LISTA_ORDENADA

//Apelidos continuam
typedef int Boolean;
typedef int Elemento;

//Adição do no anterior
typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;
	struct _no_ * anterior;

} No;

//Mesma coisa
typedef struct {

	int tamanho;	
	No * cabeca;

} ListaLigada;

//Diferenças na inserção, caso do parametro indice
ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);
Boolean insere(ListaLigada * lista, Elemento e);
Boolean remove_elemento(ListaLigada * lista, Elemento e);
