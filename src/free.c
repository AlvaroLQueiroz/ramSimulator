#include "free.h"
#include <stdlib.h>
#include <stdio.h>

/*
Ordena a lista pela posição inicial do bloco de memória em ordem crescente usando o algoritmo Bubble Sort.
*/
void sortFreeBlocksByPos(FREE **list){
	unsigned short change, auxInitial, auxSize;
	FREE *block;
	
	change = TRUE;

	while(change){
		change = FALSE;
		block = *list;

		while(block->next){
			if(block->initial > block->next->initial){
				change = TRUE;
				
				auxInitial= block->initial;
				auxSize = block->size;
				
				block->initial = block->next->initial;
				block->size = block->next->size;
				
				block->next->initial = auxInitial;
				block->next->size = auxSize;
			}
			
			block = block->next;
		}
	}
}

/*
Ordena a lista pelo tamanho do bloco de memória em ordem crescente usando o algoritmo Bubble Sort.
*/
void sortFreeBlocksBySize(FREE **list){
	unsigned short change, auxInitial, auxSize;
	FREE *block;
	
	change = TRUE;

	while(change){
		change = FALSE;
		block = *list;

		while(block->next){
			if(block->size > block->next->size){
				change = TRUE;
				
				auxInitial= block->initial;
				auxSize = block->size;
				
				block->initial = block->next->initial;
				block->size = block->next->size;
				
				block->next->initial = auxInitial;
				block->next->size = auxSize;
			}
			
			block = block->next;
		}
	}
}

/*
Verifica se ha blocos consecultivos usando um algoritmo semelhante ao Bubble Sort.
*/
void consecultiveFreeBlock(FREE **	list){
	FREE *actual, *next;
	unsigned short join;

	join = TRUE;
	
	while(join){
		join = FALSE;
		actual = *list;
		
		while(actual->next){
			if(actual->initial + actual->size == actual->next->initial){
				join = TRUE;
				
				actual->size += actual->next->size;
				next = actual->next->next;
				free(actual->next);
				actual->next = next;
			}
			if(actual->next){
				actual = actual->next;
			}
		}
	}
}

/*
Insiro um bloco na lista, ordeno-o pela posiçao inicial de cada bloco,
verifico há existencia de blocos consecultivos e depois reordeno pelo tamanho de cada bloco.
*/
void insertFreeBlock(FREE **list, unsigned int initial, unsigned int size){
	FREE *newBlock;
	
	newBlock = (FREE*) malloc(sizeof(FREE));
	if(!newBlock){
		printf("Erro ao alocar um ponteiro.");
		exit(0);
	}
	
	newBlock->initial = initial;
	newBlock->size = size;
	newBlock->next = *list;
	*list = newBlock;

	sortFreeBlocksByPos(list);
	consecultiveFreeBlock(list);
	sortFreeBlocksBySize(list);
}

/*
Apesar do nome ser 'find' esta função procura e remove um bloco quando ele é encontrado.
*/
FREE *findFreeBlock(FREE **list, unsigned int size){
	FREE *actual, *previous, *next, *block;

	block = (FREE*) malloc(sizeof(FREE));
	if(!block){
		printf("Erro ao alocar um ponteiro.");
		exit(0);
	}
	block->initial = 0;
	block->size = 0;
	
	if(*list){
		if((*list)->size >= size){
			block->initial = (*list)->initial;
			block->size = (*list)->size;
	
			next = (*list)->next;
			free(*list);
			*list = next;
		}
		else{
			actual = *list;
			previous = *list;

			while(actual){
				if(actual->size >= size){
					block->initial = actual->initial;
					block->size = actual->size;
					next = actual->next;
					free(previous->next);
					previous->next = next;
					actual = NULL;
				}
				else{
					previous = actual;
					actual = actual->next;
				}
			}
		}
	}
	
	return block;
}

void destroysFree(FREE *list){
	if(list){
		if(list->next){
			destroysFree(list->next);
		}
		free(list);
	}
}

