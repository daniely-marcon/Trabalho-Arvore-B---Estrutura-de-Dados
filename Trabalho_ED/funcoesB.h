/*Disciplina: Estruturas de Dados
  Autoras: Daniely Maximo Marcon e Giovanna Camila de O. Teodoro*/
typedef struct arvore_b{
	int n ; // numero de chaves armazenadas 
	char **chave; // Chave armazenada no no 
	struct arvore_b **filhos; // numero de filhos que o no possui 
	int folha; // indicaçao se é um no folha ou nao 


} arvore_b; 

/* function prototypes */
arvore_b *aloca(int ordem);
arvore_b *inserir_b(arvore_b *ptr, char nome[], int ordem);
void inserirB_N(arvore_b *ptr, char nome[], int ordem);
void divide_no(arvore_b *ptr, int i, int ordem);
arvore_b *buscaB(char nome[], arvore_b *ptr);
void finalizar(arvore_b *ptr);


