//Continuamos a usar constantes para retorno booleano
#define FALSE 0
#define TRUE 1

//Apelidos continuamos os mesmos
typedef int Boolean; //Boolean para retorno true e false
typedef int Elemento; //Elemento para se referir aos valores que iremos inserir na lista

//Mesma coisa a estrutura
typedef struct {

	Elemento * a; //Ponteiro de Elementos, array de elementos
	int livre; //Variavel para indicar a proxima posicao a ser ocupada e tambem o tamanho da lista
	int capacidade; //Valor maximo/alocado para o vetor 'a'

} ListaSequencial;

//Continua igual com excecao da funcao inserir
ListaSequencial * cria_lista(int n);
void destroi_lista(ListaSequencial * lista);
int tamanho(ListaSequencial * lista);
void imprime(ListaSequencial * lista);
int busca(ListaSequencial * lista, Elemento e); //Podemos implementar a busca binaria (dividr a lista c/ recursao para achar o valor com um costo log n)
Boolean insere(ListaSequencial * lista, Elemento e); //Como ja previsto, nao informamos mais a posicao que eu quero inserir, cabe a funcao verificar aonde o elemento sera inserido
Boolean remove_elemento(ListaSequencial * lista, Elemento e);//Deslocamento provavelmente continuara o mesmo

