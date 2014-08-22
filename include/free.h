/*

Biblioteca para gerenciamento de uma lista simplismente encadeada sem nó cabeça.

Author: Alvaro L. S. Q. Mariano (fabricio.paula@gmail.com)

Year: 2014

*/
#ifndef _FREE_H_
#define _FREE_H_

#define TRUE 1
#define FALSE 0

/*Estrutura de blocos disponiveis*/
typedef struct F{
	unsigned short initial;/*Endereço inicial do bloco*/
	unsigned short size;/*Tamanho do bloco*/
	
	struct F *next;/*Proximo elemento da lista*/
}FREE;

/*
Descrição:Ordena a lista pela posição que se inicia o bloco(campo 'initial').
Argumentos:Um ponteiro para uma lista do tipo FREE.
retorno:void
*/
void sortFreeBlocksByPos(FREE **list);

/*
Descrição:Ordena a lista pelo tamanho do bloco(campo 'size').
Argumentos:Um ponteiro para uma lista do tipo FREE.
retorno:void
*/
void sortFreeBlocksBySize(FREE **list);

/*
Descrição:Procura por blocos consecultivos na lista.(Dois blocos são consecultivos quando os campos 'initial' + 'size' de um é igual ao campo 'initial' do outro).
Argumentos:Um ponteiro para uma lista do tipo FREE.
retorno:void
*/
void consecultiveFreeBlock(FREE **	list);

/*
Descrição:Insere um nó no inicio da lista.
Argumentos:Um ponteiro para uma lista do tipo FREE e dois numeros inteiros não negativos, sendo o primeiro o inicio do bloco e o segunto o seu tamanho.
retorno:void
*/
void insertFreeBlock(FREE **list, unsigned int initial, unsigned int size);

/*
Descrição:Procura na lista por um bloco com tamanho igual ou maior que o valor informado em 'size'.
Argumentos:Um ponteiro para uma lista do tipo FREE e um inteiro não negativo que representa o tamanho do bloco a ser procurado.
retorno:um ponteiro do tipo FREE com os valores do bloco encontrado.
*/
FREE *findFreeBlock(FREE **list, unsigned int size);

/*
Descrição:Deleta uma lista simplismente encadeada sem nó cabeça.
Argumentos:Um ponteiro do tipo FREE para uma lista.
retorno:void
*/
void destroysFree(FREE *list);

#endif

