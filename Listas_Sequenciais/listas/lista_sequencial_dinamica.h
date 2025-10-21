//Constantes de lógica mantidas, porém constante da tamanho foi removida
#define FALSE 0
#define TRUE 1

//Mesma coisa as declarações
typedef int Boolean;
typedef int Elemento;

typedef struct {
	//vetor agora nao tem tamanho fixo, agora é so um ponteiro, array de inteiros
	Elemento * a;
	//Continua igual
	int livre;
	//Nova variável para guardar o tamanho do array dinamicamente
	int capacidade;

} ListaSequencial;

//Agora criar lista recebe um parametro de tamanho n = capacidade = tamanho do array
ListaSequencial * cria_lista(int n);
//O resto continua igual, pelo menos na declaração e parametros
void destroi_lista(ListaSequencial * lista);
int tamanho(ListaSequencial * lista);
void imprime(ListaSequencial * lista);
int busca(ListaSequencial * lista, Elemento e);
Boolean insere(ListaSequencial * lista, Elemento e, int indice);
Boolean remove_elemento(ListaSequencial * lista, Elemento e);

