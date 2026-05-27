#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 20

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


int main(){

	int ordem; 
	int i  = 0;

	arvore_b *A_B = NULL;

	FILE *arquivo;
	char nome[MAX];

	printf("Indique a ordem d da árvore B: ");

	scanf("%d", &ordem);


	arquivo = fopen("pokemon_names.txt", "r");
	if (!arquivo){
		printf("Erro ao abrir arquivo");
	}else{
		
		while((feof(arquivo)==0)){
			fscanf(arquivo, "%s", nome);
			A_B = inserir_b(A_B, nome, ordem);

		}
		
	}



	int op; 

	


	do{
		printf("//----- //----- // ARVORE B //----- //----- //\n[1]- Buscar\n[2]- Inserir\n[9]- Finalizar\n------------------------------\nEntre com a sua opcao:");
		scanf("%d",&op);
		if(op==1){

		}else if(op==2){

		}
	}while(op!=9);


	return 0;
}



arvore_b *buscaB(char nome[], arvore_b *ptr ){
	arvore_b *p = ptr;
	
	

	while(p != NULL){
		int i = 0;		

		while(i <= p->n && strcmp(p->chave[i],nome) < 0){
			i++;
		}
		if(i < p->n && strcmp(p->chave[i],nome) == 0){
			 //chave encontrada
			return p;

		}
		p = p->filhos[i];
	}

	return NULL; 
}



void divide_no(arvore_b *ptr, int i, int ordem){
	arvore_b *p_filho = ptr->filhos[i];

	arvore_b *novo_irmao = aloca(ordem);
    novo_irmao->folha = p_filho->folha;
    
    novo_irmao->n = ordem - 1;

	for(int j = 0; j < ordem-1; j++){
		novo_irmao->chave[j] = p_filho->chave[ordem + j];
	}
	if(p_filho->folha == 0){
		for(int k = 0; k <= ordem-1; k++){
			novo_irmao->filhos[k] = p_filho->filhos[ordem + k];
		}
	}

	p_filho->n = ordem-1; 

	for(int j = ptr->n; j != i; j--){
		ptr->filhos[j+1] = ptr->filhos[j];
		ptr->chave[j] = ptr->chave[j-1];
	}
	ptr->filhos[i+1] = novo_irmao;

	ptr->chave[i] = p_filho->chave[ordem-1];

	ptr->n++;


}





void inserirB_N(arvore_b *ptr, char nome[], int ordem){

	arvore_b* p = ptr;
	
	
	if(p->folha == 1){
			int j = p->n -1;

			while(j >= 0 && strcmp(p->chave[j], nome) > 0){
				p->chave[j+1] = p->chave[j];
				j--;
			}
			p->chave[j+1] = malloc(strlen(nome) +1);
			strcpy(p->chave[j+1], nome);
			p->n++;
			}


		else{
			int i = 0;
			while (i < p->n && strcmp(p->chave[i], nome) < 0) {
                i++;
            }
			if(p->filhos[i]->n == (2*ordem)-1){
				divide_no(p, i, ordem);

				if (strcmp(p->chave[i], nome) < 0) {
                    i++; // Vai para a direita
                }
			}

			inserirB_N(p->filhos[i], nome, ordem);
			
			
		}

}

arvore_b * aloca(int ordem){
	arvore_b * nova = (arvore_b*) malloc(sizeof(arvore_b));
	nova->n = 0;
	nova->folha = 1;

	int max_chaves = (2 * ordem) - 1;
	nova->chave = (char**) malloc(max_chaves * sizeof(char*));
	nova->filhos = (arvore_b**) malloc((max_chaves + 1)* sizeof(arvore_b*));

	for(int i = 0; i <= max_chaves; i++){
		nova->filhos[i] = NULL;
	}

	return nova ;
}


arvore_b *inserir_b(arvore_b * ptr, char nome[], int ordem) {

	arvore_b *p = ptr;
	

	if(buscaB(nome, p) != NULL){
		printf("Pokemon '%s' já existe na arvore.\n", nome);
		return ptr;

	}
	
	
	if(p == NULL){
		p = aloca(ordem);
		p->n = 1; 
		p->chave[0] = malloc(strlen(nome) + 1);
		strcpy(p->chave[0],nome);
		return p; 

		
	} 
	if(p->n == (2*ordem)-1){
		arvore_b *nova_raiz = aloca(ordem);
		nova_raiz->folha = 0;
		nova_raiz->filhos[0] = p;
		divide_no(nova_raiz, 0, ordem);
		inserirB_N(nova_raiz, nome, ordem);
		return nova_raiz;

	}
	else{
		inserirB_N(p,nome,ordem);
		return ptr;
	}

}
