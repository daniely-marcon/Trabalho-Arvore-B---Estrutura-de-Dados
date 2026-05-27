#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"funcoesB.h"
#define MAX 20

// funcao que irá alocar memoria na arvore 
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



// funcao que irá desalocar memorria para finalizar programa 
void finalizar(arvore_b *ptr){
	if(ptr != NULL){
		for(int i = 0; i <= ptr->n; i++){
			finalizar(ptr->filhos[i]);
		}
		free(ptr);
		free(ptr->chave);
		free(ptr->filhos);
	}
}

// funcao que irá imprimir chave e nivel da arvore
void imprimir(arvore_b *ptr, int nivel){
	if(ptr != NULL){
		printf("Nível %d: ", nivel);
		for(int i = 0; i < ptr->n; i++){
			printf("%s ", ptr->chave[i]);
		}
		printf("\n");
		for(int i = 0; i <= ptr->n; i++){
			imprimir(ptr->filhos[i], nivel + 1);
		}
	}
}


/*funcao que verificar se encontra a chave indicada na arvoreB
*/
arvore_b *buscaB(char nome[], arvore_b *ptr ){
	arvore_b *p = ptr;

	/* enquanto ponteiro não 
	aponta para nulo irá percorrer a arvore*/
	while(p != NULL){
		int i = 0;		
		/* enquanto  a chave for menor que o nome ou i menor que número de chaves , i avança*/
		while(i < p->n && strcmp(p->chave[i],nome) < 0){ 
			i++;
		}
		/* Verifica se i saiu do laço pq a chave foi encontrado e retorna o endereço se verdadeiro*/
		if(i < p->n && strcmp(p->chave[i],nome) == 0){
			 //chave encontrada
			return p;

		}
		/*Ponteiro recebe o endereço do filho e reinicia o laço */ 
		p = p->filhos[i];
	}

	return NULL; 
}

/*inserir em arvore com tratamento de cisao 
	Funcao que é chamada na main, insere chave na raiz quando esta é vazia,
	 Verifica se o número de nós está no limite, se sim, irá realizar o tratamento da cisao,
	 senao, chama funcao inserirB_N */
arvore_b *inserir_b(arvore_b * ptr, char nome[], int ordem) {

	arvore_b *p = ptr;
	

	if(p == NULL){
		p = aloca(ordem);
		p->n = 1; 
		p->chave[0] =(char*) malloc(strlen(nome) + 1);
		strcpy(p->chave[0],nome);
		return p; 

		
	} 
	/* se o numero de chaves estiver no limite, 
	aloca uma nova raiz e chama  funcao para dividir o no (cisao)*/
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



//inserir em arvore nao cheia 
void inserirB_N(arvore_b *ptr, char nome[], int ordem){

	arvore_b* p = ptr;
	
	/* Verifica se o nó é folha (1) */
	if(p->folha == 1){
			int j = p->n -1;

			/*Desloca chaves para direita e busca espaço para inserir nova chave*/
			while(j >= 0 && strcmp(p->chave[j], nome) > 0){
				p->chave[j+1] = p->chave[j];
				j--;
			}
			/*Apos sair do laço irá alocar memoria para o nome, copiar para posicao 
			e incrementar o numero de chaves do no*/
			p->chave[j+1] =(char*) malloc(strlen(nome) +1);
			strcpy(p->chave[j+1], nome);
			p->n++;
			}

	/*Nó não sendo folha irá cair nesse laço*/
	else{
			int i = 0;
			/*Enquanto i é menor que numero de chaves 
			e o conteúdo da chave é menor que o nome, i é incrementado*/
			while (i < p->n && strcmp(p->chave[i], nome) < 0) {
                i++;
            }

            /*Confirma se o filho[i] não está cheio
            , senao: realiza a chamada recursiva para continuar tentativa de insercao do nome
            se sim, chama a funcao para dividir o no  */

			if(p->filhos[i]->n == (2*ordem)-1){
				divide_no(p, i, ordem);

				/* Se o filho esta cheio, o pai recebeu o seu filho central, 
				 verifica-se i deve ser incrementado para chamada recursiva(chave[i] < nome)
				 ou nao*/

				if (strcmp(p->chave[i], nome) < 0) {
                    i++; // Vai para a direita
                }
			}

			inserirB_N(p->filhos[i], nome, ordem);
			
			
		}

}

/* funcao que irá realizar a operacao de cisao quando necessaria */

void divide_no(arvore_b *ptr, int i, int ordem){
	arvore_b *p_filho = ptr->filhos[i]; // guarda o filho do indice i que está cheio

	arvore_b *novo_irmao = aloca(ordem); // aloca memoria para novo irmao de i 
    novo_irmao->folha = p_filho->folha; // garante que novo irmao está no mesmo nivel que o filho[i]
    
    novo_irmao->n = ordem - 1; // n chaves do novo irmao

	for(int j = 0; j < ordem-1; j++){ // novo irmao recebe as chaves central em diante 
		novo_irmao->chave[j] = p_filho->chave[ordem + j];
	}
	if(p_filho->folha == 0){ // novo irmao recebe os filhos correspondentes
		for(int k = 0; k <= ordem-1; k++){
			novo_irmao->filhos[k] = p_filho->filhos[ordem + k];
		}
	}

	p_filho->n = ordem-1;  // decrementa o número de chaves do filho[i] que estava cheio


	/* Desloca para direita os filhos e chaves de ptr(pai) para abrir espaço para o novo_irmao(novo filho de ptr)
	até encontrar o indice i (posicao do novo filho)*/
	for(int j = ptr->n; j != i; j--){
		ptr->filhos[j+1] = ptr->filhos[j];
		ptr->chave[j] = ptr->chave[j-1];
	}
	ptr->filhos[i+1] = novo_irmao; // guarda endereco novo filho

	ptr->chave[i] = p_filho->chave[ordem-1]; //guarda a antiga chave central do filho[i]

	ptr->n++; // incrementa o numero de chaves


}

