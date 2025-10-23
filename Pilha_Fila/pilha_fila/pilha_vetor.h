#define FALSE 0
#define TRUE 1

#define PILHA

typedef int Boolean;
typedef int Elemento;

//Mesma coisa da estrutura de Lista Sequencial Dinamica
typedef struct {

	Elemento * a; //Vetor de Elementos
	int topo; //livre vai para topo, topo = elemento final (mesma coisa)
	int capacidade; //tamanho mazimo

} Pilha;

//Usuario informa o tamanho da Pilha
Pilha * cria_pilha(int capacidade);
void destroi(Pilha * pilha);
void imprime(Pilha * pilha);
int tamanho(Pilha * pilha);
//Remover e inserir por ultimo
Boolean push(Pilha * pilha, Elemento e);
Boolean pop(Pilha * pilha, Elemento * e);

