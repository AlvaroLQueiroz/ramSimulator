#include "allocated.h"
#include <stdlib.h>
#include <stdio.h>

void insertAllocatedBlock(ALLOCATED **list, ALLOCATED *newBlock){
	ALLOCATED *block;
	
	if(*list == NULL){
		newBlock->previous = *list;
		newBlock->next = *list;
		*list = newBlock;
	}
	else{
		block = *list;
		
		while(block->next){
			block = block->next;
		}
		
		newBlock->previous = block;
		newBlock->next = block->next;
		block->next = newBlock;
	}
}		

ALLOCATED *removeAllocatedBlock(ALLOCATED **list, unsigned int id){
	ALLOCATED *block, *previous, *next;
	ALLOCATED *oldAllocatedBlock;
	
	oldAllocatedBlock = (ALLOCATED*) malloc(sizeof(ALLOCATED));
	if(!oldAllocatedBlock){
		printf("Erro ao alocar um ponteiro.");
		exit(0);
	}
	
	oldAllocatedBlock->id = 0;
	oldAllocatedBlock->initial = 0;
	oldAllocatedBlock->final = 0;

	if(*list){	
		if((*list)->id == id && !(*list)->next){
			oldAllocatedBlock->id = (*list)->id;
			oldAllocatedBlock->initial = (*list)->initial;
			oldAllocatedBlock->final = (*list)->final;
			free(*list);
			*list = NULL;
		}
		else if((*list)->id == id){
			oldAllocatedBlock->id = (*list)->id;
			oldAllocatedBlock->initial = (*list)->initial;
			oldAllocatedBlock->final = (*list)->final;
			
			next = (*list)->next;
			next->previous = (*list)->previous;
			free(*list);
			*list = next;
		}
		else{
			block = *list;
		
			while(block && block->id != id){
				block = block->next;
			}
		
			if(block){
				oldAllocatedBlock->id = block->id;
				oldAllocatedBlock->initial = block->initial;
				oldAllocatedBlock->final = block->final;
				if(block->next){
					previous = block->previous;
					next = block->next;
					free(previous->next);
					previous->next = next;
					next->previous = previous;
				}
				else{
					previous = block->previous;
					next = block->next;
					free(previous->next);
					previous->next = next;
				}
			}
		}
	}
	
	return oldAllocatedBlock;
}

void destroysAllocated(ALLOCATED *list){
	if(list){
		if(list->next){
			destroysAllocated(list->next);
		}
		free(list);
	}
}

