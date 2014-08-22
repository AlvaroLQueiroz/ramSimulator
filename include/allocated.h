/*

Biblioteca para gerenciamento de uma lista duplamente encadeada sem nó cabeça.

Author: Alvaro L. S. Q. Mariano (fabricio.paula@gmail.com)

Year: 2014

*/

#ifndef _ALLOCATED_H_
#define _ALLOCATED_H_

#define TRUE 1
#define FALSE 0

/*Estrutura de blocos alocados*/
typedef struct A{
	unsigned int id;/*Identificação do bloco*/
	unsigned short initial;/*Endereço inicial*/
	unsigned short final;/*Endereço final*/
	
	struct A *previous;/*Proximo bloco*/
	struct A *next;/*Bloco anterior*/
}ALLOCATED;

/*
Descrição:Insere ordenadamente um nó em uma lista duplamente encadeada. O campo ID da é o argumento para a ordenação.
Argumentos:Um ponteiro para uma lista do tipo ALLOCATED e um ponteiro para um nó, tambem do tipo ALLOCATED.
retorno:void;
*/
void insertAllocatedBlock(ALLOCATED **list, ALLOCATED *newBlock);

/*
Descrição:Remove um nó de uma lista duplamente encadeada. O nó é encontrado pelo campo ID.
Argumentos:Um ponteiro para uma lista do tipo ALLOCATED e um numero do tipo unsigned int.
retorno:Retorna um ponteiro do tipo ALLOCATED com os valores do nó removido.
*/
ALLOCATED *removeAllocatedBlock(ALLOCATED **list, unsigned int id);

/*
Descrição: Deleta uma lista duplamente encadeada.
Argumentos:Um ponteiro para uma lista do tipo ALLOCATED.
retorno:void
*/
void destroysAllocated(ALLOCATED *list);

#endif

