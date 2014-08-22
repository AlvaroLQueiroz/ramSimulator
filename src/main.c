#include "gfx.h"
#include "free.h"
#include "allocated.h"
#include "ram.h"
#include <stdio.h>

int main(){
	FREE *freeBlocks;
	ALLOCATED *allocatedBlocks;
	unsigned int memorySize, id;
	char option;
	unsigned short quit;
	SDL_Event event;
	
	freeBlocks = NULL;
	allocatedBlocks = NULL;
	memorySize = 0;
	id = 0;
	option = 's';
	quit = 0;
	
	system("clear");
	
	printf("Informe o tamanho da memoria: ");
	do{
		scanf("%u", &memorySize);
		if(memorySize <= 0){
			system("clear");
			printf("Tamanho incorreto.\nInforme o tamanho novamente: ");
		}
		else if(memorySize > 1750){
			system("clear");
			printf("Valor muito alto, o mesmo nao pode ser representado graficamente por este programa.\n Informe o tamanho novamente: ");
		}
	}while(memorySize < 1 || memorySize > 1750);
	
	insertFreeBlock(&freeBlocks, 1, memorySize);

	do{
		system("clear");
		printf("\t\tMENU\t\t\n");
		printf("A - para alocar um bloco.\n");
		printf("E - para excluir um bloco.\n");
		printf("V - para visualisar a memoria.\n");
		printf("S - para sair.\n");
		option = getchar();
		scanf("%c", &option);
		option = tolower(option);
		
		if(option == 'a'){
			newBlock(&freeBlocks, &allocatedBlocks, &id);
		}
		else if(option == 'e'){
			removeBlock(&freeBlocks, &allocatedBlocks);
		}
		else if(option == 'v'){
			gfx_init("Random Access Memory (Pressione uma tecla para sair)");
			gfx_set_font_size(9);
			printRam(allocatedBlocks, memorySize);
			gfx_paint();
			while(!quit){/*Loop principal*/
				while(SDL_PollEvent(&event)){/*Verifica se ocorreu algum evento*/
					switch(event.type){/*Seleciona o tipo de evento*/
						case SDL_QUIT:/*Clique no botão de fechar*/
							quit = 1;/*sair do loop principal*/
							break;
						case SDL_KEYDOWN:/*Tecla pressionada*/
							quit = 1;/*sair do loop principal*/
							break;
					}
				}
			}
			quit = 0;
			gfx_quit();
		}
		else if(option == 's'){
		}
		else{
			printf("Opcao invalida. Pressione ENTER para continuar.");
		}
	}while(option != 's');
	
	destroysFree(freeBlocks);
	destroysAllocated(allocatedBlocks);

	return 0;
}

