/*

Biblioteca para simular o gerenciamento de uma memoria RAM.

Author: Alvaro L. S. Q. Mariano (fabricio.paula@gmail.com)

Year: 2014

*/
#ifndef _RAM_H_
#define _RAM_H_

#include "allocated.h"
#include "free.h"

/*
Descrição:Aloca um bloco de memória.
Argumentos:Um ponteiro do tipo *FREE, um ponteiro do tipo *ALLOCATED e um ponteiro para um inteiro não negativo.
retorno:void
*/
void newBlock(FREE **freeBlcoks, ALLOCATED **allocatedBlocks, unsigned int *id);

/*
Descrição:Remove um bloco alocado da memória.
Argumentos:Um ponteiro do tipo *FREE e um ponteiro do tipo *ALLOCATED.
retorno:void
*/
void removeBlock(FREE **freeBlocks, ALLOCATED **allocatedBlocks);

/*
Descrição:Imprime uma representação gráfica dos blocos da memoria.
Argumentos:Um ponteiro do tipo ALLOCATED, e um inteiro não negativo contendo o tamanho total da memória.
retorno:void
*/
void printRam(ALLOCATED *list, unsigned int memorySize);

#endif

