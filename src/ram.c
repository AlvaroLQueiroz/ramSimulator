#include "ram.h"
#include "allocated.h"
#include "free.h"
#include "gfx.h"
#include <stdlib.h>
#include <stdio.h>

void newBlock(FREE **freeBlocks, ALLOCATED **allocatedBlocks, unsigned int *id){
	ALLOCATED *newAllocatedBlock;
	FREE *oldFreeBlock;
	unsigned int size;

	newAllocatedBlock = (ALLOCATED*) malloc(sizeof(ALLOCATED));
	if(!newAllocatedBlock){
		printf("Erro ao alocar um ponteiro.");
		exit(0);
	}
	
	printf("Informe o tamanho do bloco a ser alocado: ");
	do{
		scanf("%u", &size);
		if(size <= 0){
			printf("Tamanho incorreto.\nInforme o tamanho novamente: ");
		}
	}while(size <= 0);
	
	oldFreeBlock = findFreeBlock(freeBlocks, size);
	
	if(oldFreeBlock->initial){
		*id += 1;
		newAllocatedBlock->id = *id;
		newAllocatedBlock->initial = oldFreeBlock->initial;
		newAllocatedBlock->final = oldFreeBlock->initial + size - 1;
		
		if(oldFreeBlock->size - size > 0){
			insertFreeBlock(freeBlocks, oldFreeBlock->initial + size, oldFreeBlock->size - size);
		}

		insertAllocatedBlock(allocatedBlocks, newAllocatedBlock);
	}
	else{
		printf("Nao ha espaco suficiente para o bloco.\n");
	}
}

void removeBlock(FREE **freeBlocks, ALLOCATED **allocatedBlocks){
	unsigned id;
	ALLOCATED *oldAllocatedBlock;
	
	oldAllocatedBlock = (ALLOCATED*) malloc(sizeof(ALLOCATED));
	if(!oldAllocatedBlock){
		printf("Erro ao alocar um ponteiro.");
		exit(0);
	}
	
	printf("Informe o ID do bloco a ser removido: ");
	do{
		scanf("%u", &id);
		if(id <= 0){
			printf("ID incorreto.\nInforme o ID novamente: ");
		}
	}while(id <= 0);
	
	oldAllocatedBlock = removeAllocatedBlock(allocatedBlocks, id);
	
	if(oldAllocatedBlock->initial){
		insertFreeBlock(freeBlocks, oldAllocatedBlock->initial, oldAllocatedBlock->final - oldAllocatedBlock->initial + 1);
	}
	else{
		printf("Bloco nao encontrado.\n");
	}
}

void printRam(ALLOCATED *list, unsigned int memorySize){
	ALLOCATED *block;
	long *ram , line, column, allocated, freeBlocks;
	long counter;
	char msg[35];
	unsigned short allocatedORfree;

	block = NULL;
	ram = NULL;
	line = 0;
	column = 0;
	allocated = 0;
	freeBlocks = 0;
	counter = 0;
	allocatedORfree = 0;

	if(list){
		ram = (long*) malloc(sizeof(long) * memorySize);
		if(!ram){
			printf("Erro ao alocar um ponteiro.");
			exit(0);
		}

		gfx_set_color(0, 255, 0);
		for(counter = 0; (unsigned int)counter < memorySize; counter++){
			gfx_rectangle(column * 20, line * 20, column * 20 + 20, line * 20 + 20);		
			ram[counter] = 0;
			column++;
			if(column % 50 == 0){
				column = 0;
				line++;
			}
		}

		block = list;

		while(block){
			ram[block->initial - 1] = - block->id;
			allocated++;
			for(counter = block->initial; counter < block->final; counter++){
				ram[counter] = 1;
				allocated++;
			}
			block = block->next;
		}

		for(counter = 0; (unsigned int)counter < memorySize; counter++){
			if(allocatedORfree == 0 && ram[counter] == 0){
				freeBlocks++;
			}
			else if(allocatedORfree == 0 && ram[counter] != 0){
				ram[counter - freeBlocks + 1] = -freeBlocks;
				freeBlocks = 0;
				allocatedORfree = 1;
			}
			else if(allocatedORfree == 1 && ram[counter] == 0){
				allocatedORfree = 0;
				freeBlocks++;
			}
		}
		
		for(counter = 0; counter < memorySize; counter++){
			if(column % 50 == 0){
				column = 0;
				line++;
			}

			if(ram[counter] == 1){
				gfx_set_color(255, 0, 0);
				gfx_rectangle(column * 20, line * 20, column * 20 + 20, line * 20 + 20);
			}
			else if(ram[counter] < 0){
				gfx_set_color(255, 255, 255);
				snprintf(msg, 35, "%ld", -ram[counter]);
				gfx_text(column * 20, line * 20, msg);
			}
			column++;
		}

		free (ram);
	}
	else{
		gfx_set_color(0, 255, 0);
		snprintf(msg, 35, "%d", memorySize);
		gfx_text(column * 20, line * 20, msg);
		
		while((unsigned int)counter < memorySize - 1){
			gfx_rectangle(column * 20, line * 20, column * 20 + 20, line * 20 + 20);
			counter++;
			column++;
			if((counter + 1) % 50 == 0){
				line++;
				column = 0;
			}
		}
	}

	gfx_set_font_size(20);
	gfx_set_color(255, 255, 255);
	snprintf(msg, 35, "%.2f%% da memoria esta ocupada.", (float)(allocated * 100) / memorySize);
	gfx_text(5, 701, msg);
}

