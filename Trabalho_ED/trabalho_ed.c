/*Disciplina: Estruturas de Dados
  Autoras: Daniely Maximo Marcon e Giovanna Camila de O. Teodoro*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"funcoesB.h"
#define MAX 20


int main(){

	int ordem = 0; 
	int i  = 0;
	int op; 

	arvore_b *A_B = NULL;

	FILE *arquivo;
	char nome[MAX];
	char nome_arquivo[MAX];
	

	printf("Indique o nome do arquivo.txt que deseja ler: \n");

	scanf("%s", nome_arquivo);


	printf("Indique a ordem d da árvore B: \n");

	scanf("%d", &ordem);


	arquivo = fopen(nome_arquivo, "r");

	if(!arquivo){
		printf("Erro ao abrir arquivo \n");
	}
	else{
		printf("Arquivo aberto com sucesso!\n");

		while(fscanf(arquivo, "%s", nome) == 1){
    			A_B = inserir_b(A_B, nome, ordem);
		}

		printf("Leitura e insercao na Arvore B finaliza.");
		
	}
	
	do{
		printf("//----- //----- // ARVORE B //----- //----- //\n[1]- Buscar\n[2]- Inserir\n[9]- Finalizar\n------------------------------\nEntre com a sua opcao:");
		scanf("%d", &op);

		if(op == 1){
			printf("Indique o nome do pokemon a ser buscado: ");
            scanf("%s", nome);
            
     
            arvore_b *resultado = buscaB(nome, A_B);

            if (resultado != NULL) {
                int posicao = 0;
                while (posicao < resultado->n && strcmp(resultado->chave[posicao], nome) != 0) {
                    posicao++;
                }

                printf("Pokemon %s encontrado na arvore na posicao %d do no.\n", nome, posicao);


                printf("Conteudo completo do no: [");
                for (int i = 0; i < resultado->n; i++) {
                    printf("%s", resultado->chave[i]);
                    if (i < resultado->n - 1) {
                        printf(", ");
                    }
                }
                printf("].\n");

            } 
            else {
                printf("Pokemon %s nao encontrado na arvore.\n", nome);
            }

		}else if(op == 2){
			printf("Indique o nome do pokemon a ser inserido: ");

			scanf("%s", nome);
			arvore_b *resultado = buscaB(nome, A_B);

			if(resultado != NULL){
				printf("Pokemon %s já existe na arvore.\n",nome);

			}else{
				A_B = inserir_b(A_B, nome, ordem);
				printf("Pokemon %s inserido na arvore.\n",nome);

			}
		}
	
	}while(op != 9);

	if(op == 9){
		finalizar(A_B);
		printf("Arvore B finalizada. Memoria liberada.\n");
	}


	return 0;
}

